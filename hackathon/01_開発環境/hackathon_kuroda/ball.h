//===================================================================
//
//	tamaの処理[ball.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _BALL_H_
#define _BALL_H_

#define SCROLLBALLPOS (CRenderer::SCREEN_WIDTH / 3.0f)
#define SCROLLFLAGPOS (CRenderer::SCREEN_WIDTH - (CRenderer::SCREEN_WIDTH / 4.0f))

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

	bool ifScroll();

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
	bool m_bFall;
	bool m_bPlayShop;
	bool m_bPlayCupIn;

	int m_nCntRestart;
};

#endif //_BALL_H_