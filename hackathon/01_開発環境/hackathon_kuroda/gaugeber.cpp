//-----------------------------------------------------------------------------------------------
//
// �w�i�̏���[bg.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "gaugeber.h"

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
LPDIRECT3DTEXTURE9 CGaugeber::m_apTexture = {};

//-----------------------------------------------------------------------------------------------
//	�R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CGaugeber::CGaugeber()
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(EObject::OBJ_EFFECT);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CGaugeber::~CGaugeber()
{

}

//-----------------------------------------------------------------------------------------------
//	�e�N�X�`���ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CGaugeber::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Sky.png", &m_apTexture);		// ��

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	�e�N�X�`���j��
//-----------------------------------------------------------------------------------------------
void CGaugeber::Unload()
{
	// �e�N�X�`���̔j��
	if (m_apTexture != nullptr)
	{
		m_apTexture->Release();
		m_apTexture = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
//	��������
//-----------------------------------------------------------------------------------------------
CGaugeber *CGaugeber::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale, const int& nMaxValue)
{
	// �|�C���^�N���X��錾
	CGaugeber* pGaugeber = new CGaugeber;

	if (pGaugeber != nullptr)
	{
		// ������
		pGaugeber->m_pos = pos;
		pGaugeber->m_scale = scale;
		pGaugeber->m_fMaxGauge = scale.x;

		pGaugeber->m_fValue = nMaxValue;

		pGaugeber->Init();

	}

	return pGaugeber;
}

//-----------------------------------------------------------------------------------------------
//	������
//-----------------------------------------------------------------------------------------------
HRESULT CGaugeber::Init()
{
	m_apGaugeBer = new CObject2D;
	//�I�u�W�F�N�g�̎�ސݒ�
	m_apGaugeBer->SetObjType(EObject::OBJ_EFFECT);
	m_apGaugeBer->SetPosition(m_pos);
	m_apGaugeBer->SetSize({ m_scale .x,m_scale .y});

	//m_apGaugeBer->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	//m_apGaugeBer->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	m_apGaugeBer->Init();
	m_apGaugeBer->BindTexture(m_apTexture);




	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	�I��
//-----------------------------------------------------------------------------------------------
void CGaugeber::Uninit()
{
	if (m_apGaugeBer != nullptr)
	{
		m_apGaugeBer->Uninit();
		m_apGaugeBer = nullptr;
	}

	Release();
}

//-----------------------------------------------------------------------------------------------
//	�X�V
//-----------------------------------------------------------------------------------------------
void CGaugeber::Update()
{
	//�ʒu�Ƒ傫�������A���^�C���ōX�V
	SetScalePos(m_pos, m_scale);
}

//-----------------------------------------------------------------------------------------------
//	�`��
//-----------------------------------------------------------------------------------------------
void CGaugeber::Draw()
{

}
//--------------------------------------------------------------------
//�X�P�[����pos�{���������₷����
//--------------------------------------------------------------------
void CGaugeber::SetScalePos(D3DXVECTOR3 pos, D3DXVECTOR3 scale)
{

	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�o�b�t�@�̐���
	pVtx[0].pos = D3DXVECTOR3(pos.x, pos.y - scale.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + scale.x, pos.y - scale.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x, pos.y + scale.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + scale.x, pos.y + scale.y, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0, 0.0);
	pVtx[1].tex = D3DXVECTOR2((1.0f / m_fMaxGauge)*scale.x, 0.0);
	pVtx[2].tex = D3DXVECTOR2(0.0, 1.0);
	pVtx[3].tex = D3DXVECTOR2((1.0f / m_fMaxGauge)*scale.x, 1.0);

	m_pVtxBuff->Unlock();

}
//--------------------------------------------------------------------
//�Q�[�W�̑�������
//--------------------------------------------------------------------
void CGaugeber::SetGauge(float AddValue)
{
	m_fValue -= AddValue;
	float fAdd = (m_fMaxGauge * AddValue) / m_fValueMax;
	m_scale.x -= fAdd;

	if (m_fValue >= m_fValueMax)
	{
		m_fValue = m_fValueMax;
		m_scale.x = m_fMaxGauge;
	}
}