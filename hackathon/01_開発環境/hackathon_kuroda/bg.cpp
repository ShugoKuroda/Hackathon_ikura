//-----------------------------------------------------------------------------------------------
//
// �w�i�̏���[bg.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "bg.h"

#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "input_keyboard.h"

#include "game.h"
#include "cloud.h"

//-----------------------------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CBg::m_apSkyTexture[SKYBG_MAX] = {};
LPDIRECT3DTEXTURE9 CBg::m_apGroundTexture[m_nGround] = {};

CObject2D *CBg::m_apObject2D[SKYBG_MAX + m_nGround] = {};

float CBg::m_fMoveQuantity = 0;

//-----------------------------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CBg::CBg()
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(EObject::OBJ_BG_MOVE);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CBg::~CBg()
{

}

//-----------------------------------------------------------------------------------------------
//	�e�N�X�`���ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CBg::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Sky.png", &m_apSkyTexture[SKYBG_SKY]);			// ��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Cloud.png", &m_apSkyTexture[SKYBG_CLOUD]);		// �_

	for (int nCnt = 0; nCnt < m_nGround; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Ground.png", &m_apGroundTexture[nCnt]);	// �n��
	}

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	�e�N�X�`���j��
//-----------------------------------------------------------------------------------------------
void CBg::Unload()
{
	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apSkyTexture[nCnt] != nullptr)
		{
			m_apSkyTexture[nCnt]->Release();
			m_apSkyTexture[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nGround; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apGroundTexture[nCnt] != nullptr)
		{
			m_apGroundTexture[nCnt]->Release();
			m_apGroundTexture[nCnt] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
//	��������
//-----------------------------------------------------------------------------------------------
CBg *CBg::Create()
{
	// �|�C���^�N���X��錾
	CBg* pBg = new CBg;

	if (pBg != nullptr)
	{
		// ������
		pBg->Init();
	}

	return pBg;
}

//-----------------------------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------------------------
HRESULT CBg::Init()
{
	//=============================================================================
	// ����
	//=============================================================================
	//�X�N���[���T�C�Y�̕ۑ�
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);
	// �ړ��ʃ��Z�b�g
	m_fMoveQuantity = 0;

	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{// ����
		m_apObject2D[nCnt] = new CObject2D;
		//�I�u�W�F�N�g�̎�ސݒ�
		m_apObject2D[nCnt]->SetObjType(EObject::OBJ_BG);

		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
		m_apObject2D[nCnt]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	}

	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{// �������ƃe�N�X�`���̐ݒ�
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apSkyTexture[nCnt]);
	}

	//=============================================================================
	// ���߂�
	//=============================================================================
	for (int nCnt = SKYBG_MAX; nCnt < SKYBG_MAX + m_nGround; nCnt++)
	{// ����
		m_apObject2D[nCnt] = new CObject2D;
		//�I�u�W�F�N�g�̎�ސݒ�
		m_apObject2D[nCnt]->SetObjType(EObject::OBJ_BG);

		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(ScreenSize.x * nCnt + (ScreenSize.x / 2), ScreenSize.y / 2, 0.0f));
		m_apObject2D[nCnt]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	}

	for (int nCnt = SKYBG_MAX; nCnt < SKYBG_MAX + m_nGround; nCnt++)
	{// �������ƃe�N�X�`���̐ݒ�
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apGroundTexture[nCnt]);
	}

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------------------------
void CBg::Uninit()
{
	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}

	Release();
}

//-----------------------------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------------------------
void CBg::Update()
{
	// �ʒu�����擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//=============================================================================
	// ���������ꂽ
	//=============================================================================
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_RIGHT) &&
		!pKeyboard->GetPress(CInputKeyboard::KEYINFO_LEFT))
	{
		m_fMoveQuantity += 16;	// �ʂ̈ړ����x
	}

	for (int nCnt = SKYBG_MAX; nCnt < SKYBG_MAX + m_nGround; nCnt++)
	{
		// �n�ʂ̈ʒu���X�V
		m_apObject2D[nCnt]->SetMove(D3DXVECTOR3(-m_fMoveQuantity, 0.0f, 0.0f));

		// �n�ʂ̒��_���W�̐ݒ�
		m_apObject2D[nCnt]->SetVertex();
	}
}

//-----------------------------------------------------------------------------------------------
//	�`��
//-----------------------------------------------------------------------------------------------
void CBg::Draw()
{

}