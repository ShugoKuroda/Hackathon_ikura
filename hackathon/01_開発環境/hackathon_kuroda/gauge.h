//----------------------------------------------
//ゲージの処理
//Author::林海斗
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
	static HRESULT Load();		// テクスチャの読み込み
	static void Unload();		// テクスチャの削除

	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetAddGauge(float AddValue);//ゲージの増減
	bool SetEndGauge();
	float GetGaugeValue();
private:
	CGaugeFrame *m_pFrame;//ゲージの枠
	CGaugeber *m_pGaugeBer;
	float m_fValue;//ゲージの値
	float m_bEndDelay;
	bool m_bEndGaugeBer;
	bool m_bEndGaugeFrame;

};

#endif // !_TIME_H_*/#pragma once
