//===================================================================
//
//	背景処理[gaugeframe.h]
//	Author:SHUGO KURODA
//
//===================================================================
#ifndef _GAUGEFRAME_H_
#define _GAUGEFRAME_H_

#include "object2D.h"

//*******************************************************************
// 前方宣言
//*******************************************************************
class CObject2D;

//*******************************************************************
//	背景クラスの定義
//*******************************************************************
class CGaugeFrame : public CObject2D
{
public:
	CGaugeFrame();
	~CGaugeFrame() override;

	//メンバ関数
	static HRESULT Load(void);		//テクスチャの読み込み
	static void Unload(void);		//テクスチャの削除
	static CGaugeFrame *Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale);			//インスタンス生成処理
	//static CObject2D *GetSkyObjectBg(SkyType index) { return m_apSkyObject2D[index]; }
	//static CObject2D *GetGroundObjectBg(int index) { return m_apGroundObject2D[index]; }

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void SetCol(D3DXCOLOR col);
	// 移動量
private:
	//メンバ変数
	static LPDIRECT3DTEXTURE9 m_apTexture;	//テクスチャのポインタ

	CObject2D *m_apGaugeFrame;	//2Dポリゴンへのポインタ

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_scale;
	D3DXCOLOR m_col;
};

#endif		// _GAUGEFRAME_H_
