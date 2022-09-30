//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "base.h"
#include "enemy_data.h"
#include "cloud_data.h"

#include "player.h"
#include "bg.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CScore;
class CMeshField;

//-----------------------------------------------------------------------------
// �x�[�X�N���X(�h���N���X)
//-----------------------------------------------------------------------------
class CGame : public CBase
{
private:	//�萔
	static const int MAX_POS_CLOUD = 250;
	static const int MIN_POS_CLOUD = 180;

public:		//�����o�֐�
	CGame();
	~CGame() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	// �v���C���[���̎擾
	static CPlayer *GetPlayer() { return m_pPlayer; }

	// �v���C���[���̎擾
	static CBg *GetBg() { return m_pBg; }

	// �v���C���[�̃X�R�A�������L���O�ɐݒ�
	static void SetPlayerScore();

private:
	// �e�N�X�`���ǂݍ���
	static void LoadAll();
	// �e�N�X�`���j��
	static void UnloadAll();

private:	//�����o�ϐ�
	// �v���C���[���
	static CPlayer *m_pPlayer;
	// �w�i
	static CBg *m_pBg;

	// ���E���h��
	static int m_nRoundNum;
};

#endif	//_GAME_H_
