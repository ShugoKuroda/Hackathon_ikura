//===============================================================================================
//
// ゴール旗処理 [goal_flag.cpp]
// Author : SHUGO KURODA
//
//===============================================================================================
#include "sound.h"

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "object.h"
#include "object2D.h"
#include "library.h"
#include "fade.h"

#include "fade_scene.h"
#include "library.h"
#include "goal_flag.h"

//-----------------------------------------------------------------------------------------------
// using宣言
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------
// テクスチャのポインタ
LPDIRECT3DTEXTURE9 CGoal::m_apTexture[OBJ_MAX] = { nullptr };
const float CGoal::SIZE_X = 100.0f;
const float CGoal::SIZE_Y = 500.0f;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CGoal::CGoal() :m_move(0.0f, 0.0f, 0.0f)
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CGoal::~CGoal()
{
}

//-----------------------------------------------------------------------------------------------
// 生成
// const int & nRandPosX → 生成するX軸の位置(ランダム)
//-----------------------------------------------------------------------------------------------
CGoal* CGoal::Create(const int& nRandPosX)
{
	// ポインタクラスを宣言
	CGoal* pGoal = new CGoal;

	if (pGoal != nullptr)
	{// もしnullptrではなかったら

		// 位置設定
		pGoal->SetPosition(pos);

		// サイズの保存
		pGoal->m_DefaultSize = size;

		// アニメーションの種類を設定
		pGoal->m_AnimType = AnimType;

		// 破棄カウンターを設定
		pGoal->m_nCountUninit = nCount;

		// 初期化
		pGoal->Init();

		// 種類の設定
		pGoal->m_type = type;

		// テクスチャの設定
		pGoal->BindTexture(m_pTexture[type]);
	}

	return pGoal;
}

//-----------------------------------------------------------------------------------------------
// テクスチャの読み込み処理
//-----------------------------------------------------------------------------------------------
HRESULT CGoal::Load()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/GoalFlag000.png", &m_apTexture[FLAG_POLE]);		// 旗のポール
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/holeUp000.png", &m_apTexture[FLAG_HOLE_UP]);		// ゴール穴上部
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/holeDown000.png", &m_apTexture[FLAG_HOLE_DOWN]);	// ゴール穴下部

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// テクスチャの破棄
//-----------------------------------------------------------------------------------------------
void CGoal::Unload()
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
HRESULT CGoal::Init()
{
	// テクスチャのロード
	CGoal::Load();

	// スクリーンサイズの保存
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// 生成
		m_apObject2D[nCnt] = new CObject2D;
	}

	// 背景
	m_apObject2D[FLAG_POLE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[FLAG_POLE]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	// タイトルロゴ
	m_apObject2D[FLAG_HOLE_DOWN]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, -ScreenSize.y / 2, 0.0f));
	m_apObject2D[FLAG_HOLE_DOWN]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	// PRESS_SPACEロゴ
	m_apObject2D[FLAG_HOLE_UP]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[FLAG_HOLE_UP]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// 初期化とテクスチャの設定
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	//背景とプレイヤーロゴ以外を前に描画する(タイプを設定する)
	m_apObject2D[FLAG_POLE]->SetObjType(CObject::OBJ_TITLE);
	//プレイヤーロゴを背景の次に描画する
	m_apObject2D[FLAG_HOLE_DOWN]->SetObjType(CObject::OBJ_TITLE_LOGO);
	m_apObject2D[FLAG_HOLE_UP]->SetObjType(CObject::OBJ_TITLE_LOGO);

	//タイトルとPressロゴを透明にする
	m_apObject2D[FLAG_HOLE_UP]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// タイトルBGM
	CSound::Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CGoal::Uninit()
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
	CGoal::Unload();

	// タイトルBGM
	CSound::Stop();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CGoal::Update()
{
	// キーボード情報の取得
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// 位置の取得
	D3DXVECTOR3 pos = m_apObject2D[FLAG_HOLE_DOWN]->GetPosition();

	// タイトルロゴが移動しきるまで移動
	if (pos.y <= CRenderer::SCREEN_HEIGHT / 2)
	{
		pos.y += 5.0f;
	}
	else
	{
		m_bDrawPress = true;
	}

	if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_ATTACK) == true)
	{//攻撃キー押下
		if (m_bDrawPress == false)
		{
			pos.y = CRenderer::SCREEN_HEIGHT / 2;
			m_bDrawPress = true;
		}
		else if (m_bPush == false && m_bDrawPress == true)
		{
			m_bPush = true;

			// モードの設定
			CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);


		}
	}

	if (m_bDrawPress == true)
	{
		// 色の取得
		D3DXCOLOR col = m_apObject2D[FLAG_HOLE_UP]->GetColor();

		// PRESSロゴを点滅させる
		if (m_bPressFade == false)
		{
			// a値を加算
			col.a += 0.02f;
			// a値の加算が終わったら
			if (col.a >= 1.0f)
			{// a値の減算を始める
				m_bPressFade = true;
			}
		}
		else if (m_bPressFade == true)
		{
			// a値を減算
			col.a -= 0.02f;
			// a値の減算が終わったら
			if (col.a <= 0.0f)
			{// a値の加算を始める
				m_bPressFade = false;
			}
		}

		// PRESSロゴの色を設定
		m_apObject2D[FLAG_HOLE_UP]->SetColor(col);
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

	m_apObject2D[FLAG_HOLE_DOWN]->SetPosition(pos);
	m_apObject2D[FLAG_HOLE_DOWN]->SetVertex();
}

void CGoal::Draw()
{
}
