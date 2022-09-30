//===================================================================
//
//	�w�i����[bg.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _BG_H_
#define _BG_H_

#include "object2D.h"

//*******************************************************************
// �O���錾
//*******************************************************************
class CObject2D;

//*******************************************************************
//	�w�i�N���X�̒�`
//*******************************************************************
class CBg : public CObject2D
{
public:
	enum BGtype
	{//�w�i�̎��
		BG_SKY = 0,		// ��
		BG_GROUND,		// �n��
		BG_MAX			// �w�i�̍ő吔
	};

	CBg();
	~CBg() override;

	//�����o�֐�
	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̍폜
	static CBg *Create();			//�C���X�^���X��������
	static CObject2D *GetObjectBg(BGtype index) { return m_apObject2D[index]; }

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// �ړ���
	static void ZeroMoveQuantity() { m_fMoveQuantity = 0.0f; }
	static void MoveQuantity(float move) { m_fMoveQuantity += move; }
	static float GetMoveQuantity() { return m_fMoveQuantity; }

private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture[BG_MAX];	//�e�N�X�`���̃|�C���^
	static CObject2D *m_apObject2D[BG_MAX];			//2D�|���S���ւ̃|�C���^

	static float m_fMoveQuantity;	// ��ʂ̑��ړ���
};

#endif		// _BG_H_
