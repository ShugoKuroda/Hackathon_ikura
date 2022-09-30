//===============================================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : SHUGO KURODA
//
//===============================================================================================
#include "manager.h"
#include "game.h"
#include "object.h"
#include "sound.h"

#include "library.h"
#include "load.h"
#include "fade_scene.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "gaugeframe.h"
#include "score.h"
#include "number.h"
#include "logo.h"
#include "pause.h"
#include "rank.h"
#include "score.h"
#include "gaugeber.h"
#include "explosion.h"

//-----------------------------------------------------------------------------------------------
// using宣言
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------
CPlayer *CGame::m_pPlayer = {};
CBg *CGame::m_pBg = {};
CBall *CGame::m_pBall = {};
CGoal *CGame::m_pGoal = {};

int CGame::m_nRoundNum = 0;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CGame::CGame() :m_nCounterLogo(0)
{
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CGame::~CGame()
{
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CGame::Init()
{
	// テクスチャ読み込み
	LoadAll();

	// プレイヤー生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(300.0f, CRenderer::SCREEN_HEIGHT / 2, 0.0f), 0);

	// 背景生成
	m_pBall = CBall::Create(D3DXVECTOR3(300.0f, 550.0f, 0.0f), 0);

	// 背景生成
	m_pBg = CBg::Create();

	// 旗
	m_pGoal = CGoal::Create();

	// ゲームBGM
	CSound::Play(CSound::SOUND_LABEL_GAME);

	// Round数の加算
	m_nRoundNum++;

	// ボス接近中のロゴ
	CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2(300.0f, 90.0f),
		(CLogo::LOGOTYPE)m_nRoundNum, CLogo::ANIM_LENGTHWISE, 120);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CGame::Uninit()
{
	//テクスチャの破棄
	UnloadAll();

	// ポーズ状態を解除
	CManager::SetPause(false);

	// 決定音
	CSound::Stop();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CGame::Update()
{
	m_nCounterLogo++;

	if (m_nCounterLogo == 120)
	{
		// STARTロゴ
		CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2(300.0f, 90.0f),
			CLogo::TYPE_START, CLogo::ANIM_NONE, 120);

		// プレイヤーを操作可能状態にする
		if (m_pPlayer != nullptr)
		{
			m_pPlayer->SetControl(true);
		}
	}
	else if (m_nCounterLogo >= 121)
	{
		m_nCounterLogo = 121;
	}

	// キーボード情報の取得
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_PAUSE) == true)
	{
		// ポーズ状態の取得
		bool bPause = CManager::GetPause();
		// ポーズ中でなければ
		if (bPause == false)
		{//ポーズ画面を生成
			CPause::Create(0);
		}
	}
}

//-----------------------------------------------------------------------------------------------
// ランキングスコアの設定
//-----------------------------------------------------------------------------------------------
void CGame::SetPlayerScore()
{
	// プレイヤーのスコアを保存
	if (m_pPlayer != nullptr)
	{
		// プレイヤースコアの初期化
		CRank::AddScore(0);

		CScore* pScore = m_pPlayer->GetScore();

		if (pScore != nullptr)
		{
			int nSocre = pScore->GetScore();
			CRank::AddScore(nSocre);
		}
	}
}

//-----------------------------------------------------------------------------------------------
// テクスチャ読み込み
//-----------------------------------------------------------------------------------------------
void CGame::LoadAll()
{
	// プレイヤー
	CPlayer::Load();
	// 背景
	CBg::Load();
	// tama
	CBall::Load();
	// 爆発
	CExplosion::Load();
	// スコア
	CNumber::Load();
	// ロゴ
	CLogo::Load();
	// ポーズ画面
	CPause::Load();
	CGaugeber::Load();
	CGaugeFrame::Load();

}

//-----------------------------------------------------------------------------------------------
// テクスチャ破棄　
//-----------------------------------------------------------------------------------------------
void CGame::UnloadAll()
{
	// プレイヤー
	CPlayer::Unload();
	// 背景
	CBg::Unload();
	// tama
	CBall::Unload();
	// 爆発
	CExplosion::Unload();
	// スコア
	CNumber::Unload();
	// ロゴ
	CLogo::Unload();
	// ポーズ画面
	CPause::Unload();
	CGaugeber::Unload();
	CGaugeFrame::Unload();

}
