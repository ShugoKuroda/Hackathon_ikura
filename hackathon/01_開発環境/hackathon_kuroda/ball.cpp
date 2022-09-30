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
#include "fade.h"

#include "goal_flag.h"
#include "game.h"
#include "player.h"
#include "ball.h"
#include "gauge.h"
#include "score.h"
#include "logo.h"
#include "rank.h"
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
CBall::CBall() : m_move(0.0f, 0.0f, 0.0f), m_bFall(false), m_nCntRestart(0), m_bPlayShop(false), m_bPlayCupIn(false)
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
		if (!m_bPlayShop)
		{
			CSound::Play(CSound::SOUND_LABEL_SE_SHOT);

			m_bPlayShop = true;
		}

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

		// ゴールポールの位置取得
		D3DXVECTOR3 goalPos = CGame::GetGoal()->GetObject(2)->GetPosition();

		// 落下中ではない場合
		if (m_bFall == false)
		{
			// ボールの速度が一定以下
			if (m_fBallSpeed <= 15.0f)
			{
				// ゴールポール穴の範囲内なら
				if (pos.x <= goalPos.x + 35.0f && pos.x >= goalPos.x - 35.0f)
				{
					// 落下フラグを立てる
					m_bFall = true;
				}
			}
		}
		else if (m_bFall == true)
		{
			// 重力を掛ける
			m_move.y += 1.5f;
			pos += m_move;

			// 色の取得
			D3DXCOLOR col = GetColor();
			col.a -= 0.1f;
			SetColor(col);
		}

		if (m_bFall == true)
		{
			if (m_nCntRestart == 0)
			{
				// 今の記録ロゴ
				CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 180.0f, 0.0f), D3DXVECTOR2(300.0f, 90.0f),
					CLogo::TYPE_SCOREUI, CLogo::ANIM_NONE, 180);

				// ｍロゴ
				CLogo::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 2) + 200.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 90.0f),
					CLogo::TYPE_M, CLogo::ANIM_NONE, 180);

				// 残りロゴ
				CLogo::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 2) - 200.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 90.0f),
					CLogo::TYPE_NOKORI, CLogo::ANIM_NONE, 180);

				// スコアの生成
				CScore::Create(D3DXVECTOR3(530.0f, 360.0f, 0.0f),
					D3DXVECTOR2(70.0f, 90.0f), 50)->Add(0);

				if (!m_bPlayCupIn)
				{
					CSound::Play(CSound::SOUND_LABEL_SE_CUPIN);

					m_bPlayCupIn = true;
				}
			}

			m_nCntRestart++;
		}
		else if (m_fBallSpeed <= 0.0f)
		{
			if (m_nCntRestart == 0)
			{
				// ボス接近中のロゴ
				CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 180.0f, 0.0f), D3DXVECTOR2(300.0f, 90.0f),
					CLogo::TYPE_SCOREUI, CLogo::ANIM_NONE, 180);

				// ｍロゴ
				CLogo::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 2) + 200.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 90.0f),
					CLogo::TYPE_M, CLogo::ANIM_NONE, 180);

				// 残りロゴ
				CLogo::Create(D3DXVECTOR3((CRenderer::SCREEN_WIDTH / 2) - 200.0f, 360.0f, 0.0f), D3DXVECTOR2(100.0f, 90.0f),
					CLogo::TYPE_NOKORI, CLogo::ANIM_NONE, 180);

				int nScore = (int)(goalPos.x - pos.x);
				if (nScore < 0)
				{
					nScore *= -1;
				}

				// スコアの生成
				CScore::Create(D3DXVECTOR3(530.0f, 360.0f, 0.0f),
					D3DXVECTOR2(70.0f, 90.0f), 50)->Add(nScore);

				// スコアの加算
				CRank::AddScore(nScore);
			}

			m_nCntRestart++;
		}

		if (m_nCntRestart == 180)
		{
			if (CGame::GetRoundNum() == 3)
			{
				// ボス接近中のロゴ
				CLogo::Create(D3DXVECTOR3(CRenderer::SCREEN_WIDTH / 2, 300.0f, 0.0f), D3DXVECTOR2(300.0f, 90.0f),
					CLogo::TYPE_FINISH, CLogo::ANIM_HORIZONTALLY, 180);

				if (m_nCntRestart == 360)
				{
					// モードの設定
					CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_RESULT);
				}
			}
			else
			{
				// モードの設定
				CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);
			}
		}
	}

	if (!(ifScroll()))
	{
		SetPosition(D3DXVECTOR3(GetPosition().x + m_fBallSpeed, pos.y, 0.0f));
	}

	else
	{
		SetPosition(D3DXVECTOR3(GetPosition().x, pos.y, 0.0f));
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

bool CBall::ifScroll()
{
	if (CGame::GetBall()->GetPosition().x >= SCROLLBALLPOS &&
		CGame::GetGoal()->GetObject(CGoal::FLAG_POLE)->GetPosition().x >= SCROLLFLAGPOS)
	{
		return true;
	}

	return false;
}