//-----------------------------------------------------------------------------------------------
//
// 背景の処理[bg.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "bg.h"

#include "manager.h"
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "input_keyboard.h"

#include "game.h"
#include "cloud.h"

//-----------------------------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------
// テクスチャのポインタ
LPDIRECT3DTEXTURE9 CBg::m_apSkyTexture[SKYBG_MAX] = {};
LPDIRECT3DTEXTURE9 CBg::m_apGroundTexture[m_nGround] = {};

CObject2D *CBg::m_apObject2D[SKYBG_MAX + m_nGround] = {};

float CBg::m_fMoveQuantity = 0;

//-----------------------------------------------------------------------------------------------
//	コンストラクタ
//-----------------------------------------------------------------------------------------------
CBg::CBg()
{
	//オブジェクトの種類設定
	SetObjType(EObject::OBJ_BG_MOVE);
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CBg::~CBg()
{

}

//-----------------------------------------------------------------------------------------------
//	テクスチャ読み込み
//-----------------------------------------------------------------------------------------------
HRESULT CBg::Load()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Sky.png", &m_apSkyTexture[SKYBG_SKY]);			// 空
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Cloud.png", &m_apSkyTexture[SKYBG_CLOUD]);		// 雲

	for (int nCnt = 0; nCnt < m_nGround; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Ground.png", &m_apGroundTexture[nCnt]);	// 地面
	}

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	テクスチャ破棄
//-----------------------------------------------------------------------------------------------
void CBg::Unload()
{
	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{
		// テクスチャの破棄
		if (m_apSkyTexture[nCnt] != nullptr)
		{
			m_apSkyTexture[nCnt]->Release();
			m_apSkyTexture[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nGround; nCnt++)
	{
		// テクスチャの破棄
		if (m_apGroundTexture[nCnt] != nullptr)
		{
			m_apGroundTexture[nCnt]->Release();
			m_apGroundTexture[nCnt] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
//	生成処理
//-----------------------------------------------------------------------------------------------
CBg *CBg::Create()
{
	// ポインタクラスを宣言
	CBg* pBg = new CBg;

	if (pBg != nullptr)
	{
		// 初期化
		pBg->Init();
	}

	return pBg;
}

//-----------------------------------------------------------------------------------------------
//	初期化
//-----------------------------------------------------------------------------------------------
HRESULT CBg::Init()
{
	//=============================================================================
	// そら
	//=============================================================================
	//スクリーンサイズの保存
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);
	// 移動量リセット
	m_fMoveQuantity = 0;

	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{// 生成
		m_apObject2D[nCnt] = new CObject2D;
		//オブジェクトの種類設定
		m_apObject2D[nCnt]->SetObjType(EObject::OBJ_BG);

		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
		m_apObject2D[nCnt]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	}

	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{// 初期化とテクスチャの設定
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apSkyTexture[nCnt]);
	}

	//=============================================================================
	// じめん
	//=============================================================================
	for (int nCnt = SKYBG_MAX; nCnt < SKYBG_MAX + m_nGround; nCnt++)
	{// 生成
		m_apObject2D[nCnt] = new CObject2D;
		//オブジェクトの種類設定
		m_apObject2D[nCnt]->SetObjType(EObject::OBJ_BG);

		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(ScreenSize.x * nCnt + (ScreenSize.x / 2), ScreenSize.y / 2, 0.0f));
		m_apObject2D[nCnt]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	}

	for (int nCnt = SKYBG_MAX; nCnt < SKYBG_MAX + m_nGround; nCnt++)
	{// 初期化とテクスチャの設定
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apGroundTexture[nCnt]);
	}

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	終了
//-----------------------------------------------------------------------------------------------
void CBg::Uninit()
{
	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt]->Uninit();
			m_apObject2D[nCnt] = nullptr;
		}
	}

	Release();
}

//-----------------------------------------------------------------------------------------------
//	更新
//-----------------------------------------------------------------------------------------------
void CBg::Update()
{
	// 位置情報を取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// キーボード情報の取得
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//=============================================================================
	// →が押された
	//=============================================================================
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_RIGHT) &&
		!pKeyboard->GetPress(CInputKeyboard::KEYINFO_LEFT))
	{
		m_fMoveQuantity += 16;	// 玉の移動速度
	}

	for (int nCnt = SKYBG_MAX; nCnt < SKYBG_MAX + m_nGround; nCnt++)
	{
		// 地面の位置情報更新
		m_apObject2D[nCnt]->SetMove(D3DXVECTOR3(-m_fMoveQuantity, 0.0f, 0.0f));

		// 地面の頂点座標の設定
		m_apObject2D[nCnt]->SetVertex();
	}
}

//-----------------------------------------------------------------------------------------------
//	描画
//-----------------------------------------------------------------------------------------------
void CBg::Draw()
{

}