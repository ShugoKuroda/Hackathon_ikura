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
#include "game.h"
#include "ball.h"

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
//const float CGoal::SIZE_X = 100.0f;
//const float CGoal::SIZE_Y = 500.0f;
const int CGoal::RAND_POS_X_MIN = 3000;
const int CGoal::RAND_POS_X_MAX = 5500;

//-----------------------------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------------------------
CGoal::CGoal() :m_move(0.0f, 0.0f, 0.0f)
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}

	SetObjType(CObject::OBJ_GOAL);
}

//-----------------------------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------------------------
CGoal::~CGoal()
{
}

//-----------------------------------------------------------------------------------------------
// 生成
//-----------------------------------------------------------------------------------------------
CGoal* CGoal::Create()
{
	// ポインタクラスを宣言
	CGoal* pGoal = new CGoal;

	if (pGoal != nullptr)
	{// もしnullptrではなかったら
		// 初期化
		pGoal->Init();
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

	// ランダム生成位置の取得
	int nRandPosX = LibrarySpace::GetRandNum(RAND_POS_X_MAX, RAND_POS_X_MIN);

	// 旗のポール
	m_apObject2D[FLAG_POLE]->SetPosition(D3DXVECTOR3(45.0f + nRandPosX, (ScreenSize.y / 2) - 40.0f, 0.0f));
	m_apObject2D[FLAG_POLE]->SetSize(D3DXVECTOR2(100.0f, 500.0f));
	// ゴール穴上部
	m_apObject2D[FLAG_HOLE_UP]->SetPosition(D3DXVECTOR3(nRandPosX, ScreenSize.y - 170.0f, 0.0f));
	m_apObject2D[FLAG_HOLE_UP]->SetSize(D3DXVECTOR2(70.0f, 50.0f));
	// ゴール穴下部
	m_apObject2D[FLAG_HOLE_DOWN]->SetPosition(D3DXVECTOR3(nRandPosX, ScreenSize.y - 170.0f, 0.0f));
	m_apObject2D[FLAG_HOLE_DOWN]->SetSize(D3DXVECTOR2(70.0f, 50.0f));

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// 初期化とテクスチャの設定
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	//穴の下部を次に描画する
	m_apObject2D[FLAG_POLE]->SetObjType(CObject::OBJ_GOAL_POLE);
	//穴の下部を次に描画する
	m_apObject2D[FLAG_HOLE_DOWN]->SetObjType(CObject::OBJ_GOAL_HOLE);

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
}

//-----------------------------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------------------------
void CGoal::Update()
{
	float m_fMoveQuantity = 0.0f;
	if (CGame::GetBall()->ifScroll())
	{
		m_fMoveQuantity = CGame::GetBall()->GetSpeed();	// 玉の移動速度
	}

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		// 地面の位置情報更新
 		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(m_apObject2D[nCnt]->GetPosition().x - m_fMoveQuantity, m_apObject2D[nCnt]->GetPosition().y, 0.0f));
		m_apObject2D[nCnt]->SetVertex();
	}
}

void CGoal::Draw()
{

}
