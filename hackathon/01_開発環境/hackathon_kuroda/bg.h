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
	enum SkyType
	{//�w�i�̎��
		SKYBG_SKY = 0,		// ��
		SKYBG_CLOUD,		// kumo
		SKYBG_MAX			// �w�i�̍ő吔
	};

	CBg();
	~CBg() override;

	//�����o�֐�
	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̍폜
	static CBg *Create();			//�C���X�^���X��������
	static CObject2D *GetSkyObjectBg(SkyType index) { return m_apSkyObject2D[index]; }
	static CObject2D *GetGroundObjectBg(int index) { return m_apGroundObject2D[index]; }

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	//�����o�ϐ�
	static const int m_nGround = 3;

	static LPDIRECT3DTEXTURE9 m_apSkyTexture[SKYBG_MAX];	//�e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_apGroundTexture[m_nGround];	//�e�N�X�`���̃|�C���^

	static CObject2D *m_apSkyObject2D[SKYBG_MAX];	//2D�|���S���ւ̃|�C���^
	static CObject2D *m_apGroundObject2D[m_nGround];	//2D�|���S���ւ̃|�C���^
};

#endif		// _BG_H_
