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

	// �_�𐶐�
	void CreateCloud();
	// ���S�𐶐�
	void CreateLogo(int nCounter);

	// �_�̐�����Ԃ�ݒ�
	static void SetCreateCloud(bool bCreate) { m_bCreateCloud = bCreate; }
	// �v���C���[���̎擾
	static CPlayer *GetPlayer(int nNum) { return m_pPlayer; }
	// �X�R�A���̎擾
	static CMeshField *GetMeshField() { return m_pMeshField; }
	// �A�̐�����Ԃ��擾
	static bool GetBubble() { return m_bCreateCloud; }
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
	static CMeshField *m_pMeshField;

	// �_�𐶐����邩�ǂ���
	static bool m_bCreateCloud;

	// �_�̐������
	CloudInfo m_CloudInfo;
	// �_�����������܂ł̎���(����)
	int m_nRandBubble;
	// �_�����������܂ł̎��ԃJ�E���^�[
	int m_nCntBubble;
};

#endif	//_GAME_H_
