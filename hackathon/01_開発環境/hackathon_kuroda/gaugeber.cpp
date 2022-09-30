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
	m_fValue = 0.0f;
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
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gaugeColor000.png", &m_apTexture);		// ��

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
CGaugeber *CGaugeber::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale, const float& fMaxValue)
{
	// �|�C���^�N���X��錾
	CGaugeber* pGaugeber = new CGaugeber;

	if (pGaugeber != nullptr)
	{
		// ������
		pGaugeber->m_pos = pos;
		pGaugeber->m_scale = { 0.0f,scale .y,0.0f};
		pGaugeber->m_fMaxGauge = scale.x;

		//pGaugeber->m_fValue = nMaxValue;
		pGaugeber->m_fValueMax = fMaxValue;

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
	//m_apGaugeBer->SetPosition(m_pos);
	//m_apGaugeBer->SetSize({ m_scale .x,m_scale .y});

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
	if (m_apGaugeBer)
	{
		m_apGaugeBer->SetGaugePos(m_pos, m_scale, m_fMaxGauge);
	}
}

//-----------------------------------------------------------------------------------------------
//	�`��
//-----------------------------------------------------------------------------------------------
void CGaugeber::Draw()
{

}

//--------------------------------------------------------------------
//�Q�[�W�̑�������
//--------------------------------------------------------------------
void CGaugeber::SetGauge(const float& AddValue)
{
	m_fValue += AddValue;
	float fAdd =  (m_fMaxGauge * AddValue)/ m_fValueMax;
	m_scale.x += fAdd;

	if (m_fValue >= m_fValueMax)
	{
		m_fValue = m_fValueMax;
		m_scale.x = m_fMaxGauge;
	}
}

void CGaugeber::SetCol(D3DXCOLOR col)
{
	if (m_apGaugeBer)
	{
		m_apGaugeBer->SetColor(col);
	}
}
