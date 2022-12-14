//=============================================================================
//
//	プレイヤー処理[player.cpp]
//	Author : SHUGO KURODA
//
//=============================================================================
#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "sound.h"
#include "renderer.h"
#include "library.h"
#include "bg.h"
#include "bullet.h"
#include "player.h"
#include "explosion.h"
#include "score.h"
#include "rank.h"
#include "gauge.h"
#include "game.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define PLAYER_UI_SIZE		(D3DXVECTOR2(200.0f, 50.0f))
#define LIFE_UI_SIZE		(D3DXVECTOR2(120.0f, 30.0f))
#define LEVEL_UI_SIZE		(D3DXVECTOR2(50.0f, 50.0f))
#define ATTACK_INTERVAL		(7)
#define MAX_SWING_ROT		(D3DX_PI/2)
#define MAX_CHARGE_ROT		(-D3DX_PI/2)
//-----------------------------------------------------------------------------
// using宣言
//-----------------------------------------------------------------------------
using namespace LibrarySpace;
//*****************************************************************************
// 定数宣言
//*****************************************************************************
const float CPlayer::SIZE_X = 200.0f;
const float CPlayer::SIZE_Y = 600.0f;
const float CPlayer::MOVE_DEFAULT = 10.0f;
const D3DXVECTOR3 GaugePos = { 300.0f,500.0f,0.0f };
//*****************************************************************************
// 静的メンバ変数宣言
//*****************************************************************************
// テクスチャのポインタ
LPDIRECT3DTEXTURE9 CPlayer::m_apTexture = { nullptr };

//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------
CPlayer::CPlayer() :
	m_move(0.0f, 0.0f, 0.0f), m_state(STATE_NORMAL), m_nCntState(0), m_nCntAttack(0), m_bControl(false), m_pScore(nullptr),
	m_bSwing(false), m_bPlayCharge(false), m_pLogo(nullptr)
{
	//オブジェクトの種類設定
	SetObjType(EObject::OBJ_PLAYER);
	m_pGauge = nullptr;
}

//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}

//-----------------------------------------------------------------------------
// インスタンス生成処理
//-----------------------------------------------------------------------------
CPlayer *CPlayer::Create(const D3DXVECTOR3& pos, const int& nNum)
{
	//インスタンス生成
	CPlayer *pPlayer = new CPlayer;

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
HRESULT CPlayer::Load()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/PutterClub000.png",
		&m_apTexture);

	return S_OK;
}

//-----------------------------------------------------------------------------
//	テクスチャの削除
//-----------------------------------------------------------------------------
void CPlayer::Unload()
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
HRESULT CPlayer::Init()
{
	// 登場状態にする
	m_state = STATE_ENTRY;

	// サイズの設定
	CObject2D::SetSize(D3DXVECTOR2(SIZE_X, SIZE_Y));
	// 初期化
	CObject2D::Init();

	m_pLogo = CLogo::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 2) - 150.0f, 370.0f, 0.0f), D3DXVECTOR2(200.0f, 200.0f),
		CLogo::TYPE_TUTORIAL, CLogo::ANIM_NONE, 5000);

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CPlayer::Update()
{
	// 位置情報を取得
	D3DXVECTOR3 pos = CObject2D::GetPosition();
	CSound *pSound = CManager::GetSound();

	// キーボード情報の取得
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// 位置情報を取得
	float fRot = CObject2D::GetRot();

	// 
	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_ATTACK) == true && m_bControl == true)
	{//攻撃キー押下 && 操作可能状態なら

		if (!m_bPlayCharge)
		{
			pSound->Play(CSound::SOUND_LABEL_SE_CHARGE);
			m_bPlayCharge = true;
		}

		// 振りかぶっている状態にする
		m_bSwing = true;

	 	// 回転率の増加
		fRot -= 0.01f;

		////攻撃カウンターの加算
		//m_nCntAttack++;

		//if (m_nCntAttack > ATTACK_INTERVAL)
		//{
		//	//攻撃カウンターをリセット
		//	m_nCntAttack = 0;

		//	//サウンド再生
		//	CSound::Play(CSound::SOUND_LABEL_SE_SHOT);
		//}
		//ゲージを表示させる
		//ヌルチェック
		if (!m_pGauge)
		{
			m_pGauge = CGauge::Create(GaugePos, { 500.0f,25.0f,0.0f }, MAX_SWING_ROT);
		}
		if (m_pGauge)
		{
			//ゲージを増やす
			m_pGauge->SetAddGauge(0.01f);
		}

		if (fRot < MAX_CHARGE_ROT)
		{
			m_bControl = false;
		}
	}
	else if (m_bSwing == true)
	{
		pSound->Stop(CSound::SOUND_LABEL_SE_CHARGE);

		m_bControl = false;
		if (!m_bPlayLetSe)
		{
			pSound->Play(CSound::SOUND_LABEL_SE_LETGO);
			m_bPlayLetSe = true;
		}
		if (m_pGauge)
		{
			if (m_pGauge->SetEndGauge())
			{
				if (fRot <= MAX_SWING_ROT)
				{
					// 回転率の増加
					fRot += 0.15f;
				}

			}
			
		}
	}

	// 回転率の更新
	SetRot(fRot);

	float m_fMoveQuantity = 0;

	if (CGame::GetBall()->ifScroll())
	{
		m_fMoveQuantity = CGame::GetBall()->GetSpeed();	// 玉の移動速度
	}

	// ロゴの位置
	D3DXVECTOR3 LogoPos = m_pLogo->GetPosition();

	m_pLogo->SetPosition(D3DXVECTOR3(LogoPos.x - m_fMoveQuantity, LogoPos.y, LogoPos.z));

	//位置情報更新1
	CObject2D::SetPosition(D3DXVECTOR3(GetPosition().x - m_fMoveQuantity, GetPosition().y, 0.0f));

	//状態管理
	State();

	//頂点座標の設定
	CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CPlayer::Draw()
{
	//描画
	CObject2D::Draw();
}

//-----------------------------------------------------------------------------
// 状態管理
//-----------------------------------------------------------------------------
void CPlayer::State()
{
	switch (m_state)
	{
	case CPlayer::STATE_NORMAL:
		break;
	case CPlayer::STATE_ENTRY:
		break;
	case CPlayer::STATE_RESPAWN:
		break;
	case CPlayer::STATE_DIE:
		break;
	default:
		break;
	}
}
