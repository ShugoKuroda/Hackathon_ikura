//----------------------------------------------
//�Q�[�W�̏���
//Author::�ъC�l
//--------------------------------------------

#ifndef _GAUGE_H_
#define _GAUGE_H_
#include "object.h"

class CPolygon;
class CGaugeber;
class CGaugeFrame;

class CGauge : public CObject
{
public:

	CGauge();
	~CGauge();
	static CGauge*Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale,const float& fMaxValue);
	static HRESULT Load();		// �e�N�X�`���̓ǂݍ���
	static void Unload();		// �e�N�X�`���̍폜

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetAddGauge(float AddValue);//�Q�[�W�̑���
	bool SetEndGauge();
	float GetGaugeValue();
private:
	CGaugeFrame *m_pFrame;//�Q�[�W�̘g
	CGaugeber *m_pGaugeBer;
	float m_fValue;//�Q�[�W�̒l
	float m_bEndDelay;
	bool m_bEndGaugeBer;
	bool m_bEndGaugeFrame;

};

#endif // !_TIME_H_*/#pragma once
