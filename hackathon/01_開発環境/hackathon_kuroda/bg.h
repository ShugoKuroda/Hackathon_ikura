//===================================================================
//
//	背景処理[bg.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _BG_H_
#define _BG_H_

#include "object2D.h"

//*******************************************************************
// 前方宣言
//*******************************************************************
class CObject2D;

//*******************************************************************
//	背景クラスの定義
//*******************************************************************
class CBg : public CObject2D
{
public:
	enum SkyType
	{//背景の種類
		SKYBG_SKY = 0,		// 空
		SKYBG_CLOUD,		// 地面
		SKYBG_MAX			// 背景の最大数
	};

	CBg();
	~CBg() override;

	//メンバ関数
	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの削除
	static CBg *Create();			//インスタンス生成処理
	static CObject2D *GetSkyObjectBg(SkyType index) { return m_apSkyObject2D[index]; }
	static CObject2D *GetGroundObjectBg(int index) { return m_apGroundObject2D[index]; }

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	// 移動量
	static void ZeroMoveQuantity() { m_fMoveQuantity = 0.0f; }
	static void MoveQuantity(float move) { m_fMoveQuantity += move; }
	static float GetMoveQuantity() { return m_fMoveQuantity; }

private:
	//メンバ変数
	static const int m_nGround = 3;

	static LPDIRECT3DTEXTURE9 m_apSkyTexture[SKYBG_MAX];	//テクスチャのポインタ
	static LPDIRECT3DTEXTURE9 m_apGroundTexture[m_nGround];	//テクスチャのポインタ

	static CObject2D *m_apSkyObject2D[SKYBG_MAX];	//2Dポリゴンへのポインタ
	static CObject2D *m_apGroundObject2D[m_nGround];	//2Dポリゴンへのポインタ

	static float m_fMoveQuantity;	// 画面の総移動量
};

#endif		// _BG_H_
