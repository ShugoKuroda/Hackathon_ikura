//===============================================================================================
//
// �S�[�������� [goal_flag.cpp]
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
// using�錾
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CGoal::m_apTexture[OBJ_MAX] = { nullptr };
//const float CGoal::SIZE_X = 100.0f;
//const float CGoal::SIZE_Y = 500.0f;
const int CGoal::RAND_POS_X_MIN = 3000;
const int CGoal::RAND_POS_X_MAX = 5500;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
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
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CGoal::~CGoal()
{
}

//-----------------------------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------------------------
CGoal* CGoal::Create()
{
	// �|�C���^�N���X��錾
	CGoal* pGoal = new CGoal;

	if (pGoal != nullptr)
	{// ����nullptr�ł͂Ȃ�������
		// ������
		pGoal->Init();
	}

	return pGoal;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ��ݏ���
//-----------------------------------------------------------------------------------------------
HRESULT CGoal::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/GoalFlag000.png", &m_apTexture[FLAG_POLE]);		// ���̃|�[��
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/holeUp000.png", &m_apTexture[FLAG_HOLE_UP]);		// �S�[�����㕔
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/holeDown000.png", &m_apTexture[FLAG_HOLE_DOWN]);	// �S�[��������

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̔j��
//-----------------------------------------------------------------------------------------------
void CGoal::Unload()
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CGoal::Init()
{
	// �e�N�X�`���̃��[�h
	CGoal::Load();

	// �X�N���[���T�C�Y�̕ۑ�
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// ����
		m_apObject2D[nCnt] = new CObject2D;
	}

	// �����_�������ʒu�̎擾
	int nRandPosX = LibrarySpace::GetRandNum(RAND_POS_X_MAX, RAND_POS_X_MIN);

	// ���̃|�[��
	m_apObject2D[FLAG_POLE]->SetPosition(D3DXVECTOR3(45.0f + nRandPosX, (ScreenSize.y / 2) - 40.0f, 0.0f));
	m_apObject2D[FLAG_POLE]->SetSize(D3DXVECTOR2(100.0f, 500.0f));
	// �S�[�����㕔
	m_apObject2D[FLAG_HOLE_UP]->SetPosition(D3DXVECTOR3(nRandPosX, ScreenSize.y - 170.0f, 0.0f));
	m_apObject2D[FLAG_HOLE_UP]->SetSize(D3DXVECTOR2(70.0f, 50.0f));
	// �S�[��������
	m_apObject2D[FLAG_HOLE_DOWN]->SetPosition(D3DXVECTOR3(nRandPosX, ScreenSize.y - 170.0f, 0.0f));
	m_apObject2D[FLAG_HOLE_DOWN]->SetSize(D3DXVECTOR2(70.0f, 50.0f));

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// �������ƃe�N�X�`���̐ݒ�
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	//���̉��������ɕ`�悷��
	m_apObject2D[FLAG_POLE]->SetObjType(CObject::OBJ_GOAL_POLE);
	//���̉��������ɕ`�悷��
	m_apObject2D[FLAG_HOLE_DOWN]->SetObjType(CObject::OBJ_GOAL_HOLE);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CGoal::Uninit()
{
	// �|�C���^�̔j��
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		if (m_apObject2D[nCnt] != nullptr)
		{
			m_apObject2D[nCnt] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CGoal::Update()
{
	float m_fMoveQuantity = 0.0f;
	if (CGame::GetBall()->ifScroll())
	{
		m_fMoveQuantity = CGame::GetBall()->GetSpeed();	// �ʂ̈ړ����x
	}

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		// �n�ʂ̈ʒu���X�V
 		m_apObject2D[nCnt]->SetPosition(D3DXVECTOR3(m_apObject2D[nCnt]->GetPosition().x - m_fMoveQuantity, m_apObject2D[nCnt]->GetPosition().y, 0.0f));
		m_apObject2D[nCnt]->SetVertex();
	}
}

void CGoal::Draw()
{

}
