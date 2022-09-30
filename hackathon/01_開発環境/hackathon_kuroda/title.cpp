//===============================================================================================
//
// ゲーム画面処理 [title.cpp]
// Author : SHUGO KURODA
//
//===============================================================================================
#include "title.h"
#include "sound.h"

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "object.h"
#include "object2D.h"
#include "library.h"
#include "fade.h"

#include "cloud.h"
#include "fade_scene.h"
#include "library.h"

//-----------------------------------------------------------------------------------------------
// using宣言
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------
// テクスチャのポインタ
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[OBJ_MAX] = { nullptr };

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CTitle::CTitle() :m_nCntLoop(0), m_bPush(false), m_move(0.0f, 0.0f, 0.0f), m_bDrawPress(false)
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CTitle::~CTitle()
{
}

//-----------------------------------------------------------------------------------------------
// テクスチャの読み込み処理
//-----------------------------------------------------------------------------------------------
HRESULT CTitle::Load()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title000.png", &m_apTexture[BG_TITLE]);		// 背景の空
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title001.png", &m_apTexture[LOGO_TITLE]);		// タイトルロゴ
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title002.png", &m_apTexture[LOGO_PUSH]);		// プレイヤーロゴ

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// テクスチャの破棄
//-----------------------------------------------------------------------------------------------
void CTitle::Unload()
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CTitle::Init()
{
	// テクスチャのロード
	CTitle::Load();

	// スクリーンサイズの保存
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// 生成
		m_apObject2D[nCnt] = new CObject2D;
	}

	// 背景
	m_apObject2D[BG_TITLE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[BG_TITLE]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	// タイトルロゴ
	m_apObject2D[LOGO_TITLE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, -ScreenSize.y / 2, 0.0f));
	m_apObject2D[LOGO_TITLE]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	// PRESS_SPACEロゴ
	m_apObject2D[LOGO_PUSH]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[LOGO_PUSH]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// 初期化とテクスチャの設定
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	//背景とプレイヤーロゴ以外を前に描画する(タイプを設定する)
	m_apObject2D[BG_TITLE]->SetObjType(CObject::OBJ_TITLE);
	//プレイヤーロゴを背景の次に描画する
	m_apObject2D[LOGO_TITLE]->SetObjType(CObject::OBJ_TITLE_LOGO);
	m_apObject2D[LOGO_PUSH]->SetObjType(CObject::OBJ_TITLE_LOGO);

	//タイトルとPressロゴを透明にする
	m_apObject2D[LOGO_PUSH]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// タイトルBGM
	CSound::Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CTitle::Uninit()
{
	// ポインタの破棄
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt] = nullptr;
		}
	}

	//タイトルテクスチャの破棄
	CTitle::Unload();

	// タイトルBGM
	CSound::Stop();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CTitle::Update()
{
	// キーボード情報の取得
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// 位置の取得
	D3DXVECTOR3 pos = m_apObject2D[LOGO_TITLE]->GetPosition();

	// タイトルロゴが移動しきるまで移動
	if (pos.y <= CRenderer::SCREEN_HEIGHT / 2)
	{
		pos.y += 5.0f;
		m_bDrawPress = true;
	}

	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_ATTACK) == true)
	{//攻撃キー押下
		if (m_bDrawPress == false)
		{
			pos.y = CRenderer::SCREEN_HEIGHT / 2;
			m_bDrawPress == true;
		}
		else if (m_bPush == false && m_bDrawPress == true)
		{
			m_bPush = true;

			// モードの設定
			CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);
		}
	}

	// 画面遷移中はリセットしない
	if (m_bPush == false)
	{
		// タイトル画面をループさせるまでの時間
		m_nCntLoop++;

		// 50秒経過でタイトル画面リセット
		if (m_nCntLoop >= 5000)
		{
			//カウンターリセット
			m_nCntLoop = 0;

			// モードの設定
			CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_TITLE);
		}
	}

	m_apObject2D[LOGO_TITLE]->SetPosition(pos);
	m_apObject2D[LOGO_TITLE]->SetVertex();
}
