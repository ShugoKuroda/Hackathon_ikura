//===================================================================
//
//	�w�i����[gaugeber.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _GAUGEBER_H_
#define _GAUGEBER_H_

#include "object2D.h"

//*******************************************************************
// �O���錾
//*******************************************************************
class CObject2D;

//*******************************************************************
//	�w�i�N���X�̒�`
//*******************************************************************
class CGaugeber : public CObject2D
{
public:
	CGaugeber();
	~CGaugeber() override;

	//�����o�֐�
	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̍폜
	static CGaugeber *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale,
			const float& fMaxValue);			//�C���X�^���X��������
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetGauge(const float& AddValue);//�Q�[�W�̑���
	float GetGaugeValue() { return m_fValue; }
	void SetCol(D3DXCOLOR col);
	// �ړ���

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture;	//�e�N�X�`���̃|�C���^
	CObject2D *m_apGaugeBer;			//2D�|���S���ւ̃|�C���^
											//���_�o�b�t�@�ւ̃|�C���^�[

	static float m_fMoveQuantity;	// ��ʂ̑��ړ���
	D3DXVECTOR3 m_pos;//�ʒu
	D3DXVECTOR3 m_scale;//�ʒu
	D3DXCOLOR m_col;
	float				m_fMaxGauge;	//gauge�̍ő吔
	float				m_fValueMax;	//�Q�[�W�̒l�̍ő吔
	float				m_fValue;		//�Q�[�W�̐��l


};

#endif		// _GAUGEBER_H_
