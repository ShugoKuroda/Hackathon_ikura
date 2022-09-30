//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "base.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;

//-----------------------------------------------------------------------------
// ベースクラス(派生クラス)
//-----------------------------------------------------------------------------
class CTitle : public CBase
{
public:
	enum TITLE_OBJ
	{//背景の種類
		BG_TITLE = 0,	// 背景の空
		LOGO_TITLE,		// タイトルロゴ
		LOGO_PUSH,		// プッシュSPACEロゴ
		OBJ_MAX			// 背景の最大数
	};

public:
	CTitle();
	~CTitle() override;

	//メンバ関数
	static HRESULT Load();		//テクスチャの読み込み
	static void Unload();		//テクスチャの削除

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[OBJ_MAX];	//テクスチャのポインタ
	CObject2D *m_apObject2D[OBJ_MAX];
	int m_nCntLoop;		// タイトル演出をループさせるまでの時間
	bool m_bPush;
	bool m_bDrawPress;	// ボタン押下の催促ロゴを描画するかどうか
	D3DXVECTOR3 m_move;		// 移動量
};

#endif		// _TITLE_H_
