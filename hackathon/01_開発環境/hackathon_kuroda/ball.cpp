//=============================================================================
//
//	プレイヤー処理[ball.cpp]
//	Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "sound.h"
#include "renderer.h"

#include "game.h"
#include "player.h"
#include "ball.h"
#include "gauge.h"
//*****************************************************************************
// 定数宣言
//*****************************************************************************
const float CBall::SIZE_X = 60.0f;
const float CBall::SIZE_Y = 60.0f;
//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
// テクスチャのポインタ
LPDIRECT3DTEXTURE9 CBall::m_apTexture = { nullptr };

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CBall::CBall() : m_move(0.0f, 0.0f, 0.0f)
{
	//オブジェクトの種類設定
	SetObjType(EObject::OBJ_PLAYER);
	m_pGauge = nullptr;
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CBall::~CBall()
{
}

//-----------------------------------------------------------------------------
// インスタンス生成処理
//-----------------------------------------------------------------------------
CBall *CBall::Create(const D3DXVECTOR3& pos, const int& nNum)
{
	//インスタンス生成
	CBall *pPlayer = new CBall;

	if (pPlayer != nullptr)
	{
		// 位置設定
		pPlayer->SetPosition(D3DXVECTOR3(pos));
		// 生成処理
		pPlayer->Init();
		// テクスチャの設定
		pPlayer->BindTexture(m_apTexture);
	}

	return pPlayer;
}

//-----------------------------------------------------------------------------
// テクスチャの読み込み
//-----------------------------------------------------------------------------
HRESULT CBall::Load()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/GolfBall.png",
		&m_apTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	テクスチャの削除
//-----------------------------------------------------------------------------
void CBall::Unload()
{
	// テクスチャの破棄
	if (m_apTexture != nullptr)
	{
		m_apTexture->Release();
		m_apTexture = nullptr;
	}
}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CBall::Init()
{
	m_bSwing = false;
	m_fGaugePower = 0.0f;
	m_fBallSpeed = 0.0f;

	// サイズの設定
	CObject2D::SetSize(D3DXVECTOR2(SIZE_X, SIZE_Y));
	// 初期化
	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CBall::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CBall::Update()
{
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	// 位置情報を取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// 位置情報を取得
	float fRot = CObject2D::GetRot();

	m_bSwing = CGame::GetPlayer()->GetSwing();

	if (m_bSwing && CGame::GetPlayer()->GetRot() >= 0.0f)
	{
		if (m_bEnterPower)
		{
			m_fBallSpeed -= 0.02;

			if (m_fBallSpeed <= 0.0f)
			{
				m_fBallSpeed = 0.0f;
			}
		}

		else
		{
			m_fGaugePower = CGame::GetPlayer()->GetGauge()->GetGaugeValue();
			m_fBallSpeed = m_fGaugePower * 10.0f;
		}

		m_bEnterPower = true;
	}

	if (!(ifScroll()))
	{
		SetPosition(D3DXVECTOR3(GetPosition().x + m_fBallSpeed, GetPosition().y, 0.0f));
	}

	else
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, GetPosition().y, 0.0f));
	}

	// 回転率の更新
	SetRot(fRot);

	//頂点座標の設定
	CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CBall::Draw()
{
	//描画
	CObject2D::Draw();
}