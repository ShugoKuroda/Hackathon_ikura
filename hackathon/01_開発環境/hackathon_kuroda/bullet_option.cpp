//-----------------------------------------------------------------------------------------------
//
// 弾の処理[bullet.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "bullet_option.h"
#include "bullet.h"
#include "manager.h"
#include "renderer.h"

#include "library.h"
#include "game.h"

#include "enemy.h"
#include "explosion.h"

//-----------------------------------------------------------------------------------------------
// 静的メンバ変数
//-----------------------------------------------------------------------------------------------
// テクスチャのポインタ
LPDIRECT3DTEXTURE9 CBulletOption::m_apTexture = { nullptr };

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CBulletOption::CBulletOption() :m_fRad(0.0f), m_col(FADE_NONE), m_nCounterAttack(0)
{
	SetObjType(EObject::OBJ_BULLET);
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CBulletOption::~CBulletOption()
{

}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CBulletOption* CBulletOption::Create(const float& fRot, const PARENT& parent)
{
	// ポインタクラスを宣言
	CBulletOption* pOption = new CBulletOption;

	if (pOption != nullptr)
	{// もしnullptrではなかったら

		// 角度の設定
		pOption->m_fRad = fRot;

		//親の設定(所有するプレイヤー)
		pOption->m_parent = parent;

		// 初期化
		pOption->Init();

		// テクスチャの設定
		pOption->BindTexture(m_apTexture);
	}

	return pOption;
}

//-----------------------------------------------------------------------------------------------
// テクスチャの読み込み
//-----------------------------------------------------------------------------------------------
HRESULT CBulletOption::Load()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/option000.png",
		&m_apTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// テクスチャの削除
//-----------------------------------------------------------------------------------------------
void CBulletOption::Unload()
{
	// テクスチャの破棄
	if (m_apTexture != nullptr)
	{
		m_apTexture->Release();
		m_apTexture = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// 初期化
//-----------------------------------------------------------------------------------------------
HRESULT CBulletOption::Init()
{
	// プレイヤー位置の取得
	D3DXVECTOR3 posPlayer = CGame::GetPlayer(m_parent)->GetPosition();

	// 位置設定
	CObject2D::SetPosition(D3DXVECTOR3(posPlayer.x - sinf(m_fRad) * 100,
		posPlayer.y - cosf(m_fRad) * 100,
		0.0f));

	// 色状態の初期化
	m_col = FADE_GREEN;

	//サイズの設定
	CObject2D::SetSize(D3DXVECTOR2((float)SIZE, (float)SIZE));

	// 初期化
	CObject2D::Init();

	// 色設定
	CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// 終了
//-----------------------------------------------------------------------------------------------
void CBulletOption::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CBulletOption::Update()
{
	// 色の取得
	D3DXCOLOR col = GetColor();

	//色を常に変化させる
	if (m_col == FADE_RED)
	{
		col.r += 0.01f;
		col.b -= 0.01f;
		if (col.r >= 1.0f)
		{
			m_col = FADE_GREEN;
		}
	}
	else if (m_col == FADE_GREEN)
	{
		col.g += 0.01f;
		col.r -= 0.01f;
		if (col.g >= 1.0f)
		{
			m_col = FADE_BLUE;
		}
	}
	else if (m_col == FADE_BLUE)
	{
		col.b += 0.01f;
		col.g -= 0.01f;
		if (col.b >= 1.0f)
		{
			m_col = FADE_RED;
		}
	}

	// 位置の取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();

	// プレイヤー位置の取得
	D3DXVECTOR3 posPlayer;

	CPlayer* pPlayer = CGame::GetPlayer(m_parent);
	if (pPlayer != nullptr)
	{
		posPlayer = CGame::GetPlayer(m_parent)->GetPosition();

		// 位置の更新(プレイヤーを中心に回転させる)
		pos = D3DXVECTOR3(posPlayer.x - sinf(m_fRad) * 100,
			posPlayer.y - cosf(m_fRad) * 100,
			0.0f);
	}
	else
	{
		Uninit();
		return;
	}

	// 回転量の加算
	m_fRad += 0.1f;
	if (m_fRad >= D3DX_PI * 2)
	{
		m_fRad = 0.0f;
	}

	// 位置の更新
	CObject2D::SetPosition(pos);

	// 色の設定
	SetColor(col);

	//頂点座標の設定
	CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------------------------
void CBulletOption::Draw()
{
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------------------------
// 攻撃処理
//-----------------------------------------------------------------------------------------------
void CBulletOption::Attack()
{
	// カウンター加算
	m_nCounterAttack++;

	// カウンターが一定数以上
	if (m_nCounterAttack >= 5)
	{
		//カウンター初期化
		m_nCounterAttack = 0;

		// 位置の取得
		D3DXVECTOR3 pos = GetPosition();

		//弾の設定
		CBullet::Create(pos, D3DXVECTOR3(15.0f, 0.0f, 0.0f),
			DAMAGE, CBullet::TYPE_PLAYER_GREEN)->SetParent((CBullet::EParent)m_parent);
	}
}
