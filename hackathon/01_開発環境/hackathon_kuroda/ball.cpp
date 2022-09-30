//=============================================================================
//
//	�v���C���[����[ball.cpp]
//	Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "sound.h"
#include "renderer.h"

#include "game.h"
#include "player.h"
#include "ball.h"
#include "gauge.h"
//*****************************************************************************
// �萔�錾
//*****************************************************************************
const float CBall::SIZE_X = 60.0f;
const float CBall::SIZE_Y = 60.0f;
//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CBall::m_apTexture = { nullptr };

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CBall::CBall() : m_move(0.0f, 0.0f, 0.0f)
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(EObject::OBJ_PLAYER);
	m_pGauge = nullptr;
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CBall::~CBall()
{
}

//-----------------------------------------------------------------------------
// �C���X�^���X��������
//-----------------------------------------------------------------------------
CBall *CBall::Create(const D3DXVECTOR3& pos, const int& nNum)
{
	//�C���X�^���X����
	CBall *pPlayer = new CBall;

	if (pPlayer != nullptr)
	{
		// �ʒu�ݒ�
		pPlayer->SetPosition(D3DXVECTOR3(pos));
		// ��������
		pPlayer->Init();
		// �e�N�X�`���̐ݒ�
		pPlayer->BindTexture(m_apTexture);
	}

	return pPlayer;
}

//-----------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------
HRESULT CBall::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GolfBall.png",
		&m_apTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	�e�N�X�`���̍폜
//-----------------------------------------------------------------------------
void CBall::Unload()
{
	// �e�N�X�`���̔j��
	if (m_apTexture != nullptr)
	{
		m_apTexture->Release();
		m_apTexture = nullptr;
	}
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT CBall::Init()
{
	m_bSwing = false;
	m_fGaugePower = 0.0f;
	m_fBallSpeed = 0.0f;

	// �T�C�Y�̐ݒ�
	CObject2D::SetSize(D3DXVECTOR2(SIZE_X, SIZE_Y));
	// ������
	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CBall::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CBall::Update()
{
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	// �ʒu�����擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// �ʒu�����擾
	float fRot = CObject2D::GetRot();

	m_bSwing = CGame::GetPlayer()->GetSwing();

	if (m_bSwing && CGame::GetPlayer()->GetRot() >= 0.0f)
	{
		if (m_bEnterPower)
		{
			m_fBallSpeed -= 0.02;

			if (m_fBallSpeed <= 0.0f)
			{
				m_fBallSpeed = 0.0f;
			}
		}

		else
		{
			m_fGaugePower = CGame::GetPlayer()->GetGauge()->GetGaugeValue();
			m_fBallSpeed = m_fGaugePower * 10.0f;
		}

		m_bEnterPower = true;
	}

	if (!(ifScroll()))
	{
		SetPosition(D3DXVECTOR3(GetPosition().x + m_fBallSpeed, GetPosition().y, 0.0f));
	}

	else
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, 0.0f));
	}

	// ��]���̍X�V
	SetRot(fRot);

	//���_���W�̐ݒ�
	CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void CBall::Draw()
{
	//�`��
	CObject2D::Draw();
}