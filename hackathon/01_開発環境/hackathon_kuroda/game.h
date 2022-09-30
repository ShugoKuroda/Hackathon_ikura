//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : SHUGO KURODA
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "base.h"
#include "enemy_data.h"
#include "cloud_data.h"

#include "player.h"
#include "bg.h"

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CScore;
class CMeshField;

//-----------------------------------------------------------------------------
// ベースクラス(派生クラス)
//-----------------------------------------------------------------------------
class CGame : public CBase
{
private:	//定数
	static const int MAX_POS_CLOUD = 250;
	static const int MIN_POS_CLOUD = 180;

public:		//メンバ関数
	CGame();
	~CGame() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;

	// プレイヤー情報の取得
	static CPlayer *GetPlayer(int nNum) { return m_pPlayer; }

	// プレイヤー情報の取得
	static CBg *GetBg() { return m_pBg; }

	// プレイヤーのスコアをランキングに設定
	static void SetPlayerScore();

private:
	// テクスチャ読み込み
	static void LoadAll();
	// テクスチャ破棄
	static void UnloadAll();

private:	//メンバ変数
	// プレイヤー情報
	static CPlayer *m_pPlayer;
	// 背景
	static CBg *m_pBg;

	// ラウンド数
	static int m_nRoundNum;
};

#endif	//_GAME_H_
