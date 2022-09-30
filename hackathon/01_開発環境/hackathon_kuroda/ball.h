//===================================================================
//
//	tamaの処理[ball.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _BALL_H_
#define _BALL_H_

#include "object2D.h"

//*******************************************************************
//	前方宣言
//*******************************************************************
class CGauge;
//*******************************************************************
//	ぼーるクラスの定義
//*******************************************************************
class CBall : public CObject2D
{
private:
	//サイズ(X)
	static const float SIZE_X;
	// サイズ(Y)
	static const float SIZE_Y;

public:
	CBall();
	~CBall() override;

	//メンバ関数
	static CBall *Create(const D3DXVECTOR3& pos, const int& nNum);	//インスタンス生成処理
	static HRESULT Load();		// テクスチャの読み込み
	static void Unload();		// テクスチャの削除

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	float GetSpeed() { return m_fBallSpeed; }

private:	//メンバ変数
			// テクスチャのポインタ
	static LPDIRECT3DTEXTURE9 m_apTexture;
	CGauge *m_pGauge;

	//移動量
	D3DXVECTOR3 m_move;

	bool m_bEnterPower;		// スイングパワーを決定させたフレームだけ動かす
	bool m_bSwing;			// ふったか
	float m_fGaugePower;	// ゲージのどこらへんで止めたか
	float m_fBallSpeed;		// ゲージから持ってきたやつ
};

#endif //_BALL_H_