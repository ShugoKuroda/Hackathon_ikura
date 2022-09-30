//----------------------------------------------
//ゲージの処理
//Author::林海斗
//--------------------------------------------
#include "main.h" 
#include "manager.h"
#include "renderer.h"
#include "gauge.h"
#include "fade.h"
#include "gaugeber.h"
#include "gaugeframe.h"
//#include "Polygon.h"
//#include "gaugeber.h"
static const float MaxendDelay = 20.0f;
//-----------------------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------------------

CGauge::CGauge()
{

	m_pFrame = nullptr;
	m_bEndDelay = MaxendDelay;
}
//-----------------------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------------------

CGauge::~CGauge()
{

}
//-----------------------------------------------------------------------------
// インスタンス生成処理
//-----------------------------------------------------------------------------

CGauge *CGauge::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale,
	const float& fMaxValue)
{
	CGauge *pGauge = NULL;
	pGauge = new CGauge();
	//ゲージの枠の生成
	if (!pGauge->m_pFrame)
	{
		pGauge->m_pFrame = CGaugeFrame::Create({ pos.x + (scale.x / 2.0f),pos.y,0.0f }, scale);
	}
	pGauge->m_pGaugeBer = CGaugeber::Create(pos, scale, fMaxValue);

	pGauge->Init();

	return pGauge;
}
//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------

HRESULT CGauge::Init(void)
{

	return S_OK;
}
//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------

void CGauge::Uninit()
{
	if (m_pFrame != nullptr)
	{
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}
}
//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------

void CGauge::Update()
{
	if (m_pGaugeBer)
	{
		m_fValue = m_pGaugeBer->GetGaugeValue();
	}

}
//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------

void CGauge::Draw()
{

}


//--------------------------------------------------------------------
//ゲージの増加処理
//--------------------------------------------------------------------
void CGauge::SetAddGauge(float AddValue)
{
	if (m_pGaugeBer)
	{
		m_pGaugeBer->SetGauge(AddValue);
	}
}

bool CGauge::SetEndGauge()
{
	bool bEndGaugeBer = false;
	bool bEndGaugeFrame = false;
	m_bEndDelay--;
	if (m_bEndDelay <= 0.0f)
	{
		if (m_pGaugeBer)
		{
			float fBerCola = m_pGaugeBer->GetCol().a;
			fBerCola -= 0.03f;
			m_pGaugeBer->SetCol({ 1.0,1.0,1.0,fBerCola });
			if (fBerCola <= 0.0f)
			{
				m_pGaugeBer->Uninit();
				m_pGaugeBer = nullptr;
				m_bEndGaugeBer = true;
			}

		}
		if (m_pFrame)
		{
			float fFrameCola = m_pFrame->GetCol().a;
			fFrameCola -= 0.03f;
			m_pFrame->SetCol({ 1.0,1.0,1.0,fFrameCola });
			if (fFrameCola <= 0.0f)
			{
				m_pFrame->Uninit();
				m_pFrame = nullptr;
				m_bEndGaugeFrame = true;
			}
		}

	}
	if (m_bEndGaugeFrame&&m_bEndGaugeBer)
	{
		return true;
	}
	return false;
}

float CGauge::GetGaugeValue()
{
	return m_fValue;
}
