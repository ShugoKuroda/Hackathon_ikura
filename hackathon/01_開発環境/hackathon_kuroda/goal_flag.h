//=============================================================================
//
// ゴール旗処理 [goal_flag.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _GOLD_FLAG_H_
#define _GOLD_FLAG_H_

#include "object.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObject2D;

//-----------------------------------------------------------------------------
// ベースクラス(派生クラス)
//-----------------------------------------------------------------------------
class CGoal : public CObject
{
private:		// 定数
	//// サイズ(X)
	//static const float SIZE_X;
	//// サイズ(Y)
	//static const float SIZE_Y;
	// 旗のランダム生成位置(X軸)の最小値
	static const int RAND_POS_X_MIN;
	// 旗のランダム生成位置(X軸)の最大値
	static const int RAND_POS_X_MAX;

public:
	enum FLAG_OBJ
	{//背景の種類
		FLAG_POLE = 0,	// 旗のポール
		FLAG_HOLE_UP,	// ゴール穴上部
		FLAG_HOLE_DOWN,	// ゴール穴下部
		OBJ_MAX			// 最大数
	};

public:
	CGoal();
	~CGoal() override;

	// 生成
	static CGoal* Create();

	//メンバ関数
	static HRESULT Load();		//テクスチャの読み込み
	static void Unload();		//テクスチャの削除

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture[OBJ_MAX];	//テクスチャのポインタ
	CObject2D *m_apObject2D[OBJ_MAX];
	D3DXVECTOR3 m_move;		// 移動量
};

#endif		// _TITLE_H_
