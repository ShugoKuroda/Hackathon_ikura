//===================================================================
//
//	tama�̏���[ball.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _BALL_H_
#define _BALL_H_

#include "object2D.h"

//*******************************************************************
//	�O���錾
//*******************************************************************
class CGauge;
//*******************************************************************
//	�ځ[��N���X�̒�`
//*******************************************************************
class CBall : public CObject2D
{
private:
	//�T�C�Y(X)
	static const float SIZE_X;
	// �T�C�Y(Y)
	static const float SIZE_Y;

public:
	CBall();
	~CBall() override;

	//�����o�֐�
	static CBall *Create(const D3DXVECTOR3& pos, const int& nNum);	//�C���X�^���X��������
	static HRESULT Load();		// �e�N�X�`���̓ǂݍ���
	static void Unload();		// �e�N�X�`���̍폜

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	float GetSpeed() { return m_fBallSpeed; }

private:	//�����o�ϐ�
			// �e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apTexture;
	CGauge *m_pGauge;

	//�ړ���
	D3DXVECTOR3 m_move;

	bool m_bEnterPower;		// �X�C���O�p���[�����肳�����t���[������������
	bool m_bSwing;			// �ӂ�����
	float m_fGaugePower;	// �Q�[�W�̂ǂ���ւ�Ŏ~�߂���
	float m_fBallSpeed;		// �Q�[�W���玝���Ă������
};

#endif //_BALL_H_