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
#include "fade.h"

#include "goal_flag.h"
#include "game.h"
#include "player.h"
#include "ball.h"
#include "gauge.h"
#include "score.h"
#include "logo.h"
#include "rank.h"
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
CBall::CBall() : m_move(0.0f, 0.0f, 0.0f), m_bFall(false), m_nCntRestart(0), m_bPlayShop(false), m_bPlayCupIn(false)
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
		if (!m_bPlayShop)
		{
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT);

			m_bPlayShop = true;
		}

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

		// �S�[���|�[���̈ʒu�擾
		D3DXVECTOR3 goalPos = CGame::GetGoal()->GetObject(2)->GetPosition();

		// �������ł͂Ȃ��ꍇ
		if (m_bFall == false)
		{
			// �{�[���̑��x�����ȉ�
			if (m_fBallSpeed <= 15.0f)
			{
				// �S�[���|�[�����͈͓̔��Ȃ�
				if (pos.x <= goalPos.x + 35.0f && pos.x >= goalPos.x - 35.0f)
				{
					// �����t���O�𗧂Ă�
					m_bFall = true;
				}
			}
		}
		else if (m_bFall == true)
		{
			// �d�͂��|����
			m_move.y += 1.5f;
			pos += m_move;

			// �F�̎擾
			D3DXCOLOR col = GetColor();
			col.a -= 0.1f;
			SetColor(col);
		}

		if (m_bFall == true)
		{
			if (m_nCntRestart == 0)
			{
				// ���̋L�^���S
				CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 180.0f, 0.0f), D3DXVECTOR2(300.0f, 90.0f),
					CLogo::TYPE_SCOREUI, CLogo::ANIM_NONE, 180);

				// �����S
				CLogo::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 2) + 200.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 90.0f),
					CLogo::TYPE_M, CLogo::ANIM_NONE, 180);

				// �c�胍�S
				CLogo::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 2) - 200.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 90.0f),
					CLogo::TYPE_NOKORI, CLogo::ANIM_NONE, 180);

				// �X�R�A�̐���
				CScore::Create(D3DXVECTOR3(530.0f, 360.0f, 0.0f),
					D3DXVECTOR2(70.0f, 90.0f), 50)->Add(0);

				if (!m_bPlayCupIn)
				{
					CSound::Play(CSound::SOUND_LABEL_SE_CUPIN);

					m_bPlayCupIn = true;
				}
			}

			m_nCntRestart++;
		}
		else if (m_fBallSpeed <= 0.0f)
		{
			if (m_nCntRestart == 0)
			{
				// �{�X�ڋߒ��̃��S
				CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 180.0f, 0.0f), D3DXVECTOR2(300.0f, 90.0f),
					CLogo::TYPE_SCOREUI, CLogo::ANIM_NONE, 180);

				// �����S
				CLogo::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 2) + 200.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 90.0f),
					CLogo::TYPE_M, CLogo::ANIM_NONE, 180);

				// �c�胍�S
				CLogo::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 2) - 200.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 90.0f),
					CLogo::TYPE_NOKORI, CLogo::ANIM_NONE, 180);

				int nScore = (int)(goalPos.x - pos.x);
				if (nScore < 0)
				{
					nScore *= -1;
				}

				// �X�R�A�̐���
				CScore::Create(D3DXVECTOR3(530.0f, 360.0f, 0.0f),
					D3DXVECTOR2(70.0f, 90.0f), 50)->Add(nScore);

				// �X�R�A�̉��Z
				CRank::AddScore(nScore);
			}

			m_nCntRestart++;
		}

		if (m_nCntRestart == 180)
		{
			if (CGame::GetRoundNum() == 3)
			{
				// �{�X�ڋߒ��̃��S
				CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2(300.0f, 90.0f),
					CLogo::TYPE_FINISH, CLogo::ANIM_HORIZONTALLY, 180);

				if (m_nCntRestart == 360)
				{
					// ���[�h�̐ݒ�
					CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_RESULT);
				}
			}
			else
			{
				// ���[�h�̐ݒ�
				CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);
			}
		}
	}

	if (!(ifScroll()))
	{
		SetPosition(D3DXVECTOR3(GetPosition().x + m_fBallSpeed, pos.y, 0.0f));
	}

	else
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, pos.y, 0.0f));
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

bool CBall::ifScroll()
{
	if (CGame::GetBall()->GetPosition().x >= SCROLLBALLPOS &&
		CGame::GetGoal()->GetObject(CGoal::FLAG_POLE)->GetPosition().x >= SCROLLFLAGPOS)
	{
		return true;
	}

	return false;
}