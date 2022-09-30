//=============================================================================
//
// �S�[�������� [goal_flag.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _GOLD_FLAG_H_
#define _GOLD_FLAG_H_

#include "object.h"

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CObject2D;

//-----------------------------------------------------------------------------
// �x�[�X�N���X(�h���N���X)
//-----------------------------------------------------------------------------
class CGoal : public CObject
{
private:		// �萔
	//// �T�C�Y(X)
	//static const float SIZE_X;
	//// �T�C�Y(Y)
	//static const float SIZE_Y;
	// ���̃����_�������ʒu(X��)�̍ŏ��l
	static const int RAND_POS_X_MIN;
	// ���̃����_�������ʒu(X��)�̍ő�l
	static const int RAND_POS_X_MAX;

public:
	enum FLAG_OBJ
	{//�w�i�̎��
		FLAG_POLE = 0,	// ���̃|�[��
		FLAG_HOLE_UP,	// �S�[�����㕔
		FLAG_HOLE_DOWN,	// �S�[��������
		OBJ_MAX			// �ő吔
	};

public:
	CGoal();
	~CGoal() override;

	// ����
	static CGoal* Create();

	//�����o�֐�
	static HRESULT Load();		//�e�N�X�`���̓ǂݍ���
	static void Unload();		//�e�N�X�`���̍폜

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[OBJ_MAX];	//�e�N�X�`���̃|�C���^
	CObject2D *m_apObject2D[OBJ_MAX];
	D3DXVECTOR3 m_move;		// �ړ���
};

#endif		// _TITLE_H_
