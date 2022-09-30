//===============================================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : SHUGO KURODA
//
//===============================================================================================
#include "manager.h"
#include "game.h"
#include "object.h"
#include "sound.h"

#include "library.h"
#include "load.h"
#include "fade_scene.h"
#include "input_keyboard.h"
#include "input_joypad.h"

#include "score.h"
#include "number.h"
#include "logo.h"
#include "pause.h"
#include "rank.h"
#include "score.h"

#include "cloud.h"
#include "enemy.h"
#include "enemy_boss.h"
#include "bullet.h"
#include "bullet_option.h"
#include "barrier.h"
#include "explosion.h"
#include "bubble.h"
#include "effect.h"
#include "bg_move.h"

//-----------------------------------------------------------------------------------------------
// using�錾
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
CPlayer *CGame::m_pPlayer = {};

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CGame::CGame()
{
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CGame::~CGame()
{
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CGame::Init()
{
	// �{�X�ڋߒ��̃��S
	CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2(CRenderer::SCREEN_WIDTH - 400.0f, 90.0f),
		CLogo::TYPE_WARNING, CLogo::ANIM_LENGTHWISE, 420);

	// �e�N�X�`���ǂݍ���
	LoadAll();

	// �v���C���[����
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300.0f, CRenderer::SCREEN_HEIGHT / 2, 0.0f), 0);

	// �Q�[��BGM
	CSound::Play(CSound::SOUND_LABEL_GAME);

	// Round���̉��Z
	m_nRoundNum++;

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CGame::Uninit()
{
	//�e�N�X�`���̔j��
	UnloadAll();

	// �|�[�Y��Ԃ�����
	CManager::SetPause(false);

	// ���艹
	CSound::Stop();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CGame::Update()
{
	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();
	// �Q�[���p�b�h���̎擾
	CInputJoypad *pJoypad = CManager::GetInputJoypad();

	if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_PAUSE) == true || pJoypad->GetTrigger(CInputJoypad::JOYKEY_START, 0) == true)
	{
		// �|�[�Y��Ԃ̎擾
		bool bPause = CManager::GetPause();
		// �|�[�Y���łȂ����
		if (bPause == false)
		{//�|�[�Y��ʂ𐶐�
			CPause::Create(0);
		}
	}

	////�_�𐶐����邩�ǂ���
	//if (m_bCreateCloud == true)
	//{
	//	//�_�̐�������
	//	CreateCloud();
	//}
}

//-----------------------------------------------------------------------------------------------
// �����L���O�X�R�A�̐ݒ�
//-----------------------------------------------------------------------------------------------
void CGame::SetPlayerScore()
{
	// �v���C���[�̃X�R�A��ۑ�
	if (m_pPlayer != nullptr)
	{
		// �v���C���[�X�R�A�̏�����
		CRank::SetScore(0);

		CScore* pScore = m_pPlayer->GetScore();

		if (pScore != nullptr)
		{
			int nSocre = pScore->GetScore();
			CRank::SetScore(nSocre);
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���ǂݍ���
//-----------------------------------------------------------------------------------------------
void CGame::LoadAll()
{
	// �v���C���[
	CPlayer::Load();
	// ����
	CExplosion::Load();
	// �X�R�A
	CNumber::Load();
	// ���S
	CLogo::Load();
	// �|�[�Y���
	CPause::Load();
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���j���@
//-----------------------------------------------------------------------------------------------
void CGame::UnloadAll()
{
	// �v���C���[
	CPlayer::Unload();
	// ����
	CExplosion::Unload();
	// �X�R�A
	CNumber::Unload();
	// ���S
	CLogo::Unload();
	// �|�[�Y���
	CPause::Unload();
}
