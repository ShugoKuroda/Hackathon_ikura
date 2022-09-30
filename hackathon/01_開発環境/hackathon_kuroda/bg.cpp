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

CObject2D *CBg::m_apSkyObject2D[SKYBG_MAX] = {};
CObject2D *CBg::m_apGroundObject2D[m_nGround] = {};

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
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/cloud001.png", &m_apSkyTexture[SKYBG_CLOUD]);		// 雲

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

	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{// 生成
		m_apSkyObject2D[nCnt] = new CObject2D;
		//オブジェクトの種類設定
		m_apSkyObject2D[nCnt]->SetObjType(EObject::OBJ_BG);

		m_apSkyObject2D[nCnt]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
		m_apSkyObject2D[nCnt]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	}

	for (int nCnt = 0; nCnt < SKYBG_MAX; nCnt++)
	{// 初期化とテクスチャの設定
		m_apSkyObject2D[nCnt]->Init();
		m_apSkyObject2D[nCnt]->BindTexture(m_apSkyTexture[nCnt]);
	}

	//=============================================================================
	// じめん
	//=============================================================================
	for (int nCnt = 0; nCnt < m_nGround; nCnt++)
	{// 生成
		m_apGroundObject2D[nCnt] = new CObject2D;
		//オブジェクトの種類設定
		m_apGroundObject2D[nCnt]->SetObjType(EObject::OBJ_BG);

		m_apGroundObject2D[nCnt]->SetPosition(D3DXVECTOR3(ScreenSize.x * nCnt + (ScreenSize.x / 2), ScreenSize.y / 2, 0.0f));
		m_apGroundObject2D[nCnt]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	}

	for (int nCnt = 0; nCnt < m_nGround; nCnt++)
	{// 初期化とテクスチャの設定
		m_apGroundObject2D[nCnt]->Init();
		m_apGroundObject2D[nCnt]->BindTexture(m_apGroundTexture[nCnt]);
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
		if (m_apSkyObject2D[nCnt] != nullptr)
		{
			m_apSkyObject2D[nCnt]->Uninit();
			m_apSkyObject2D[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < m_nGround; nCnt++)
	{
		if (m_apGroundObject2D[nCnt] != nullptr)
		{
			m_apGroundObject2D[nCnt]->Uninit();
			m_apGroundObject2D[nCnt] = nullptr;
		}
	}

	Release();
}

//-----------------------------------------------------------------------------------------------
//	更新
//-----------------------------------------------------------------------------------------------
void CBg::Update()
{
	float m_fMoveQuantity = 0;

	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	if (CGame::GetBall()->ifScroll())
	{
		m_fMoveQuantity = CGame::GetBall()->GetSpeed();	// 玉の移動速度
	}

	// 位置情報を取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// キーボード情報の取得
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//=============================================================================
	// 移動
	//=============================================================================
	for (int nCnt = 0; nCnt < m_nGround; nCnt++)
	{
		// 地面の位置情報更新
		m_apGroundObject2D[nCnt]->SetPosition(D3DXVECTOR3(m_apGroundObject2D[nCnt]->GetPosition().x - m_fMoveQuantity, ScreenSize.y / 2, 0.0f));

		if (m_apGroundObject2D[nCnt]->GetPosition().x <= -(ScreenSize.x / 2))
		{
			int cnt = nCnt;

			for (int nCnt2 = 0; nCnt2 < 2; nCnt2++)
			{
				cnt++;

				if (cnt = m_nGround)
				{
					cnt = 0;
				}
			}

			m_apGroundObject2D[nCnt]->SetPosition(D3DXVECTOR3(m_apGroundObject2D[cnt]->GetPosition().x + ScreenSize.x, ScreenSize.y / 2, 0.0f));
		}

		// 地面の頂点座標の設定
		m_apGroundObject2D[nCnt]->SetVertex();
	}
}

//-----------------------------------------------------------------------------------------------
//	描画
//-----------------------------------------------------------------------------------------------
void CBg::Draw()
{

}