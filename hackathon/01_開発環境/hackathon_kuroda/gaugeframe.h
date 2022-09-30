//===================================================================
//
//	�w�i����[gaugeframe.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _GAUGEFRAME_H_
#define _GAUGEFRAME_H_

#include "object2D.h"

//*******************************************************************
// �O���錾
//*******************************************************************
class CObject2D;

//*******************************************************************
//	�w�i�N���X�̒�`
//*******************************************************************
class CGaugeFrame : public CObject2D
{
public:
	CGaugeFrame();
	~CGaugeFrame() override;

	//�����o�֐�
	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̍폜
	static CGaugeFrame *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale);			//�C���X�^���X��������
	//static CObject2D *GetSkyObjectBg(SkyType index) { return m_apSkyObject2D[index]; }
	//static CObject2D *GetGroundObjectBg(int index) { return m_apGroundObject2D[index]; }

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetCol(D3DXCOLOR col);
	// �ړ���
private:
	//�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_apTexture;	//�e�N�X�`���̃|�C���^

	CObject2D *m_apGaugeFrame;	//2D�|���S���ւ̃|�C���^

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;
	D3DXCOLOR m_col;
};

#endif		// _GAUGEFRAME_H_
