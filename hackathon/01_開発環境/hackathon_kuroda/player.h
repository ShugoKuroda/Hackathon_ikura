//===================================================================
//
//	�v���C���[�̏���[player.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "object2D.h"

//*******************************************************************
//	�O���錾
//*******************************************************************
class CScore;
class CGauge;
//*******************************************************************
//	�v���C���[�N���X�̒�`
//*******************************************************************
class CPlayer : public CObject2D
{
private:
	//�v���C���[�̃T�C�Y(X)
	static const float SIZE_X;
	// �v���C���[�̃T�C�Y(Y)
	static const float SIZE_Y;
	// �v���C���[�̊�{�ړ���
	static const float MOVE_DEFAULT;

public:

	//���
	enum STATE
	{
		STATE_NORMAL = 0,	//�ʏ�
		STATE_ENTRY,		//�o��
		STATE_RESPAWN,		//���G(���X�|�[��)���
		STATE_DIE,			//���S���
		STATE_MAX
	};

	//�A�j���[�V�����ԍ�
	enum ANIMTYPE
	{
		TYPE_NEUTRAL = 0,
		TYPE_UP,
		TYPE_DOWN,
		TYPE_MAX
	};

	CPlayer();
	~CPlayer() override;

	//�����o�֐�
	static CPlayer *Create(const D3DXVECTOR3& pos,const int& nNum);	//�C���X�^���X��������
	static HRESULT Load();		// �e�N�X�`���̓ǂݍ���
	static void Unload();		// �e�N�X�`���̍폜

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	STATE GetState() { return m_state; }
	// �X�R�A���̎擾
	CScore *GetScore() { return m_pScore; }

	void State();

private:	//�����o�ϐ�
	// �e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture;
	CGauge *m_pGauge;
	// �X�R�A�̃|�C���^
	CScore *m_pScore;

	//�ړ���
	D3DXVECTOR3 m_move;
	//���
	STATE m_state;
	//��ԃJ�E���^�[
	int m_nCntState;
	//�U���J�E���^�[
	int m_nCntAttack;
	//�v���C���[������ł��邩�ǂ���
	bool m_bControl;
	//�N���u��U�肩�Ԃ��Ă��邩�ǂ���
	bool m_bSwing;
};

#endif //_PLAYER_H_