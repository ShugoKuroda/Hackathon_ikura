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
const float CGoal::SIZE_X = 100.0f;
const float CGoal::SIZE_Y = 500.0f;

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CGoal::CGoal() :m_move(0.0f, 0.0f, 0.0f)
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CGoal::~CGoal()
{
}

//-----------------------------------------------------------------------------------------------
// ����
// const int & nRandPosX �� ��������X���̈ʒu(�����_��)
//-----------------------------------------------------------------------------------------------
CGoal* CGoal::Create(const int& nRandPosX)
{
	// �|�C���^�N���X��錾
	CGoal* pGoal = new CGoal;

	if (pGoal != nullptr)
	{// ����nullptr�ł͂Ȃ�������

		// �ʒu�ݒ�
		pGoal->SetPosition(pos);

		// �T�C�Y�̕ۑ�
		pGoal->m_DefaultSize = size;

		// �A�j���[�V�����̎�ނ�ݒ�
		pGoal->m_AnimType = AnimType;

		// �j���J�E���^�[��ݒ�
		pGoal->m_nCountUninit = nCount;

		// ������
		pGoal->Init();

		// ��ނ̐ݒ�
		pGoal->m_type = type;

		// �e�N�X�`���̐ݒ�
		pGoal->BindTexture(m_pTexture[type]);
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

	// �w�i
	m_apObject2D[FLAG_POLE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[FLAG_POLE]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	// �^�C�g�����S
	m_apObject2D[FLAG_HOLE_DOWN]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, -ScreenSize.y / 2, 0.0f));
	m_apObject2D[FLAG_HOLE_DOWN]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	// PRESS_SPACE���S
	m_apObject2D[FLAG_HOLE_UP]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[FLAG_HOLE_UP]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// �������ƃe�N�X�`���̐ݒ�
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	//�w�i�ƃv���C���[���S�ȊO��O�ɕ`�悷��(�^�C�v��ݒ肷��)
	m_apObject2D[FLAG_POLE]->SetObjType(CObject::OBJ_TITLE);
	//�v���C���[���S��w�i�̎��ɕ`�悷��
	m_apObject2D[FLAG_HOLE_DOWN]->SetObjType(CObject::OBJ_TITLE_LOGO);
	m_apObject2D[FLAG_HOLE_UP]->SetObjType(CObject::OBJ_TITLE_LOGO);

	//�^�C�g����Press���S�𓧖��ɂ���
	m_apObject2D[FLAG_HOLE_UP]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// �^�C�g��BGM
	CSound::Play(CSound::SOUND_LABEL_TITLE);

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

	//�^�C�g���e�N�X�`���̔j��
	CGoal::Unload();

	// �^�C�g��BGM
	CSound::Stop();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CGoal::Update()
{
	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// �ʒu�̎擾
	D3DXVECTOR3 pos = m_apObject2D[FLAG_HOLE_DOWN]->GetPosition();

	// �^�C�g�����S���ړ�������܂ňړ�
	if (pos.y <= CRenderer::SCREEN_HEIGHT / 2)
	{
		pos.y += 5.0f;
	}
	else
	{
		m_bDrawPress = true;
	}

	if (pKeyboard->GetTrigger(CInputKeyboard::KEYINFO_ATTACK) == true)
	{//�U���L�[����
		if (m_bDrawPress == false)
		{
			pos.y = CRenderer::SCREEN_HEIGHT / 2;
			m_bDrawPress = true;
		}
		else if (m_bPush == false && m_bDrawPress == true)
		{
			m_bPush = true;

			// ���[�h�̐ݒ�
			CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);


		}
	}

	if (m_bDrawPress == true)
	{
		// �F�̎擾
		D3DXCOLOR col = m_apObject2D[FLAG_HOLE_UP]->GetColor();

		// PRESS���S��_�ł�����
		if (m_bPressFade == false)
		{
			// a�l�����Z
			col.a += 0.02f;
			// a�l�̉��Z���I�������
			if (col.a >= 1.0f)
			{// a�l�̌��Z���n�߂�
				m_bPressFade = true;
			}
		}
		else if (m_bPressFade == true)
		{
			// a�l�����Z
			col.a -= 0.02f;
			// a�l�̌��Z���I�������
			if (col.a <= 0.0f)
			{// a�l�̉��Z���n�߂�
				m_bPressFade = false;
			}
		}

		// PRESS���S�̐F��ݒ�
		m_apObject2D[FLAG_HOLE_UP]->SetColor(col);
	}

	// ��ʑJ�ڒ��̓��Z�b�g���Ȃ�
	if (m_bPush == false)
	{
		// �^�C�g����ʂ����[�v������܂ł̎���
		m_nCntLoop++;

		// 50�b�o�߂Ń^�C�g����ʃ��Z�b�g
		if (m_nCntLoop >= 5000)
		{
			//�J�E���^�[���Z�b�g
			m_nCntLoop = 0;

			// ���[�h�̐ݒ�
			CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_TITLE);
		}
	}

	m_apObject2D[FLAG_HOLE_DOWN]->SetPosition(pos);
	m_apObject2D[FLAG_HOLE_DOWN]->SetVertex();
}

void CGoal::Draw()
{
}
