//----------------------------------------------
//ƒQ[ƒW‚Ìˆ—
//Author::—ÑŠC“l
//--------------------------------------------
#include "main.h" 
#include "manager.h"
#include "renderer.h"
#include "gauge.h"
#include "fade.h"
#include "gaugeber.h"
//#include "Polygon.h"
//#include "gaugeber.h"

CGauge::CGauge()
{

	m_pFrame = nullptr;
}

CGauge::~CGauge()
{

}

CGauge *CGauge::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& scale,
	const int& nMaxValue)
{
	CGauge *pGauge = NULL;
	pGauge = new CGauge();
	pGauge->m_pGaugeBer = CGaugeber::Create(pos, scale, nMaxValue);
	//ƒQ[ƒW‚Ì˜g‚Ì¶¬
	//if (!pGauge->m_pFrame)
	//{
	//	pGauge->m_pFrame = CPolygon::Create({ pos.x + (MaxGauge / 2.0f),pos.y,0.0f }, { scale.x / 1.97f ,scale.y*1.1f,0.0f }, CTexture::GAUGEFRAME, { 1.0,1.0,1.0,1.0 }, OBJTYPE_GAUGEFRAME);
	//}
	pGauge->Init();

	return pGauge;
}

HRESULT CGauge::Init(void)
{

	return S_OK;
}

void CGauge::Uninit()
{
	//if (m_pFrame != nullptr)
	//{
	//	m_pFrame->Uninit();
	//	m_pFrame = nullptr;
	//}
}

void CGauge::Update()
{


}

void CGauge::Draw()
{

}


//--------------------------------------------------------------------
//ƒQ[ƒW‚Ì‘‰Áˆ—
//--------------------------------------------------------------------
void CGauge::SetAddGauge(float Set, int nGaugeType)
{
	
}
