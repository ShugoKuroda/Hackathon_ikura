//=============================================================================
//
//	�v���C���[����[player.cpp]
//	Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "sound.h"
#include "renderer.h"
#include "library.h"
#include "bg.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include "score.h"
#include "rank.h"
#include "gauge.h"
//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define PLAYER_UI_SIZE		(D3DXVECTOR2(200.0f, 50.0f))
#define LIFE_UI_SIZE		(D3DXVECTOR2(120.0f, 30.0f))
#define LEVEL_UI_SIZE		(D3DXVECTOR2(50.0f, 50.0f))
#define ATTACK_INTERVAL		(7)
#define MAX_SWING_ROT		(D3DX_PI/2)
#define MAX_CHARGE_ROT		(-D3DX_PI/2)
//-----------------------------------------------------------------------------
// using�錾
//-----------------------------------------------------------------------------
using namespace LibrarySpace;
//*****************************************************************************
// �萔�錾
//*****************************************************************************
const float CPlayer::SIZE_X = 200.0f;
const float CPlayer::SIZE_Y = 600.0f;
const float CPlayer::MOVE_DEFAULT = 10.0f;
const D3DXVECTOR3 GaugePos = { 300.0f,500.0f,0.0f };
//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture = { nullptr };

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CPlayer::CPlayer() :
	m_move(0.0f, 0.0f, 0.0f), m_state(STATE_NORMAL), m_nCntState(0), m_nCntAttack(0), m_bControl(false), m_pScore(nullptr), m_bSwing(false)
{
	//�I�u�W�F�N�g�̎�ސݒ�
	SetObjType(EObject::OBJ_PLAYER);
	m_pGauge = nullptr;
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//-----------------------------------------------------------------------------
// �C���X�^���X��������
//-----------------------------------------------------------------------------
CPlayer *CPlayer::Create(const D3DXVECTOR3& pos, const int& nNum)
{
	//�C���X�^���X����
	CPlayer *pPlayer = new CPlayer;

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
HRESULT CPlayer::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PutterClub000.png",
		&m_apTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	�e�N�X�`���̍폜
//-----------------------------------------------------------------------------
void CPlayer::Unload()
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
HRESULT CPlayer::Init()
{
	// �o���Ԃɂ���
	m_state = STATE_ENTRY;

	// �T�C�Y�̐ݒ�
	CObject2D::SetSize(D3DXVECTOR2(SIZE_X, SIZE_Y));
	// ������
	CObject2D::Init();

	// ����\��Ԃɂ���
	m_bControl = true;

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CPlayer::Update()
{
	// �ʒu�����擾
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// �ʒu�����擾
	float fRot = CObject2D::GetRot();

	// 
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_ATTACK) == true && m_bControl == true)
	{//�U���L�[���� && ����\��ԂȂ�

		// �U�肩�Ԃ��Ă����Ԃɂ���
		m_bSwing = true;

	 	// ��]���̑���
		fRot -= 0.01f;



		////�U���J�E���^�[�̉��Z
		//m_nCntAttack++;

		//if (m_nCntAttack > ATTACK_INTERVAL)
		//{
		//	//�U���J�E���^�[�����Z�b�g
		//	m_nCntAttack = 0;

		//	//�T�E���h�Đ�
		//	CSound::Play(CSound::SOUND_LABEL_SE_SHOT);
		//}
		//�Q�[�W��\��������
		//�k���`�F�b�N
		if (!m_pGauge)
		{
			m_pGauge = CGauge::Create(GaugePos, { 500.0f,50.0f,0.0f }, MAX_SWING_ROT);
		}
		if (m_pGauge)
		{
			//�Q�[�W�𑝂₷
			m_pGauge->SetAddGauge(0.01f);
		}

		if (fRot < MAX_CHARGE_ROT)
		{
			m_bControl = false;
		}
	}
	else if (m_bSwing == true)
	{
		m_bControl = false;

		if (fRot <= MAX_SWING_ROT)
		{
			// ��]���̑���
			fRot += 0.15f;
		}
	}

	// ��]���̍X�V
	SetRot(fRot);

	//�ʒu���X�V
	CObject2D::SetPosition(pos);

	//��ԊǗ�
	State();

	//���_���W�̐ݒ�
	CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void CPlayer::Draw()
{
	//�`��
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------
// ��ԊǗ�
//-----------------------------------------------------------------------------
void CPlayer::State()
{
	switch (m_state)
	{
	case CPlayer::STATE_NORMAL:
		break;
	case CPlayer::STATE_ENTRY:
		break;
	case CPlayer::STATE_RESPAWN:
		break;
	case CPlayer::STATE_DIE:
		break;
	default:
		break;
	}
}
