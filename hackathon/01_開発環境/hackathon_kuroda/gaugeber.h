//===================================================================
//
//	背景処理[gaugeber.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _GAUGEBER_H_
#define _GAUGEBER_H_

#include "object2D.h"

//*******************************************************************
// 前方宣言
//*******************************************************************
class CObject2D;

//*******************************************************************
//	背景クラスの定義
//*******************************************************************
class CGaugeber : public CObject2D
{
public:
	CGaugeber();
	~CGaugeber() override;

	//メンバ関数
	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの削除
	static CGaugeber *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale,
			const float& fMaxValue);			//インスタンス生成処理
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetGauge(const float& AddValue);//ゲージの増減
	float GetGaugeValue() { return m_fValue; }
	void SetCol(D3DXCOLOR col);
	// 移動量

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture;	//テクスチャのポインタ
	CObject2D *m_apGaugeBer;			//2Dポリゴンへのポインタ
											//頂点バッファへのポインター

	static float m_fMoveQuantity;	// 画面の総移動量
	D3DXVECTOR3 m_pos;//位置
	D3DXVECTOR3 m_scale;//位置
	D3DXCOLOR m_col;
	float				m_fMaxGauge;	//gaugeの最大数
	float				m_fValueMax;	//ゲージの値の最大数
	float				m_fValue;		//ゲージの数値


};

#endif		// _GAUGEBER_H_
