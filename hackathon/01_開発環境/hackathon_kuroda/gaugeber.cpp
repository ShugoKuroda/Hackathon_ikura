//-----------------------------------------------------------------------------------------------
//
// 背景の処理[bg.cpp]
// Author : SHUGO kURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// インクルードファイル
//-----------------------------------------------------------------------------------------------
#include "gaugeber.h"

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
LPDIRECT3DTEXTURE9 CGaugeber::m_apTexture = {};

//-----------------------------------------------------------------------------------------------
//	コンストラクタ
//-----------------------------------------------------------------------------------------------
CGaugeber::CGaugeber()
{
	//オブジェクトの種類設定
	SetObjType(EObject::OBJ_EFFECT);
	m_fValue = 0.0f;
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CGaugeber::~CGaugeber()
{

}

//-----------------------------------------------------------------------------------------------
//	テクスチャ読み込み
//-----------------------------------------------------------------------------------------------
HRESULT CGaugeber::Load()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gaugeColor000.png", &m_apTexture);		// 空

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	テクスチャ破棄
//-----------------------------------------------------------------------------------------------
void CGaugeber::Unload()
{
	// テクスチャの破棄
	if (m_apTexture != nullptr)
	{
		m_apTexture->Release();
		m_apTexture = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
//	生成処理
//-----------------------------------------------------------------------------------------------
CGaugeber *CGaugeber::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale, const float& fMaxValue)
{
	// ポインタクラスを宣言
	CGaugeber* pGaugeber = new CGaugeber;

	if (pGaugeber != nullptr)
	{
		// 初期化
		pGaugeber->m_pos = pos;
		pGaugeber->m_scale = { 0.0f,scale .y,0.0f};
		pGaugeber->m_fMaxGauge = scale.x;

		//pGaugeber->m_fValue = nMaxValue;
		pGaugeber->m_fValueMax = fMaxValue;

		pGaugeber->Init();

	}

	return pGaugeber;
}

//-----------------------------------------------------------------------------------------------
//	初期化
//-----------------------------------------------------------------------------------------------
HRESULT CGaugeber::Init()
{
	m_apGaugeBer = new CObject2D;
	//オブジェクトの種類設定
	m_apGaugeBer->SetObjType(EObject::OBJ_EFFECT);
	//m_apGaugeBer->SetPosition(m_pos);
	//m_apGaugeBer->SetSize({ m_scale .x,m_scale .y});

	//m_apGaugeBer->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	//m_apGaugeBer->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	m_apGaugeBer->Init();
	m_apGaugeBer->BindTexture(m_apTexture);




	return S_OK;
}

//-----------------------------------------------------------------------------------------------
//	終了
//-----------------------------------------------------------------------------------------------
void CGaugeber::Uninit()
{
	if (m_apGaugeBer != nullptr)
	{
		m_apGaugeBer->Uninit();
		m_apGaugeBer = nullptr;
	}

	Release();
}

//-----------------------------------------------------------------------------------------------
//	更新
//-----------------------------------------------------------------------------------------------
void CGaugeber::Update()
{
	if (m_apGaugeBer)
	{
		m_apGaugeBer->SetGaugePos(m_pos, m_scale, m_fMaxGauge);
	}
}

//-----------------------------------------------------------------------------------------------
//	描画
//-----------------------------------------------------------------------------------------------
void CGaugeber::Draw()
{

}

//--------------------------------------------------------------------
//ゲージの増減処理
//--------------------------------------------------------------------
void CGaugeber::SetGauge(const float& AddValue)
{
	m_fValue += AddValue;
	float fAdd =  (m_fMaxGauge * AddValue)/ m_fValueMax;
	m_scale.x += fAdd;

	if (m_fValue >= m_fValueMax)
	{
		m_fValue = m_fValueMax;
		m_scale.x = m_fMaxGauge;
	}
}

void CGaugeber::SetCol(D3DXCOLOR col)
{
	if (m_apGaugeBer)
	{
		m_apGaugeBer->SetColor(col);
	}
}
