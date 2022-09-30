//===============================================================================================
//
// �Q�[����ʏ��� [title.cpp]
// Author : SHUGO KURODA
//
//===============================================================================================
#include "title.h"
#include "sound.h"

#include "manager.h"
#include "input_keyboard.h"
#include "input_joypad.h"
#include "object.h"
#include "object2D.h"
#include "library.h"
#include "fade.h"

#include "cloud.h"
#include "fade_scene.h"
#include "library.h"

//-----------------------------------------------------------------------------------------------
// using�錾
//-----------------------------------------------------------------------------------------------
using namespace LibrarySpace;

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CTitle::m_apTexture[OBJ_MAX] = { nullptr };

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CTitle::CTitle() :m_nCntLoop(0), m_bPush(false), m_move(0.0f, 0.0f, 0.0f), m_bDrawPress(false)
{
	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{
		m_apObject2D[nCnt] = nullptr;
	}
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CTitle::~CTitle()
{
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ��ݏ���
//-----------------------------------------------------------------------------------------------
HRESULT CTitle::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title000.png", &m_apTexture[BG_TITLE]);		// �w�i�̋�
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title001.png", &m_apTexture[LOGO_TITLE]);		// �^�C�g�����S
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title002.png", &m_apTexture[LOGO_PUSH]);		// �v���C���[���S

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̔j��
//-----------------------------------------------------------------------------------------------
void CTitle::Unload()
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
HRESULT CTitle::Init()
{
	// �e�N�X�`���̃��[�h
	CTitle::Load();

	// �X�N���[���T�C�Y�̕ۑ�
	D3DXVECTOR2 ScreenSize = D3DXVECTOR2((float)CRenderer::SCREEN_WIDTH, (float)CRenderer::SCREEN_HEIGHT);

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// ����
		m_apObject2D[nCnt] = new CObject2D;
	}

	// �w�i
	m_apObject2D[BG_TITLE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[BG_TITLE]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	// �^�C�g�����S
	m_apObject2D[LOGO_TITLE]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, -ScreenSize.y / 2, 0.0f));
	m_apObject2D[LOGO_TITLE]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));
	// PRESS_SPACE���S
	m_apObject2D[LOGO_PUSH]->SetPosition(D3DXVECTOR3(ScreenSize.x / 2, ScreenSize.y / 2, 0.0f));
	m_apObject2D[LOGO_PUSH]->SetSize(D3DXVECTOR2(ScreenSize.x, ScreenSize.y));

	for (int nCnt = 0; nCnt < OBJ_MAX; nCnt++)
	{// �������ƃe�N�X�`���̐ݒ�
		m_apObject2D[nCnt]->Init();
		m_apObject2D[nCnt]->BindTexture(m_apTexture[nCnt]);
	}

	//�w�i�ƃv���C���[���S�ȊO��O�ɕ`�悷��(�^�C�v��ݒ肷��)
	m_apObject2D[BG_TITLE]->SetObjType(CObject::OBJ_TITLE);
	//�v���C���[���S��w�i�̎��ɕ`�悷��
	m_apObject2D[LOGO_TITLE]->SetObjType(CObject::OBJ_TITLE_LOGO);
	m_apObject2D[LOGO_PUSH]->SetObjType(CObject::OBJ_TITLE_LOGO);

	//�^�C�g����Press���S�𓧖��ɂ���
	m_apObject2D[LOGO_PUSH]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	// �^�C�g��BGM
	CSound::Play(CSound::SOUND_LABEL_TITLE);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CTitle::Uninit()
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
	CTitle::Unload();

	// �^�C�g��BGM
	CSound::Stop();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CTitle::Update()
{
	// �L�[�{�[�h���̎擾
	CInputKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// �ʒu�̎擾
	D3DXVECTOR3 pos = m_apObject2D[LOGO_TITLE]->GetPosition();

	// �^�C�g�����S���ړ�������܂ňړ�
	if (pos.y <= CRenderer::SCREEN_HEIGHT / 2)
	{
		pos.y += 5.0f;
		m_bDrawPress = true;
	}

	if (pKeyboard->GetPress(CInputKeyboard::KEYINFO_ATTACK) == true)
	{//�U���L�[����
		if (m_bDrawPress == false)
		{
			pos.y = CRenderer::SCREEN_HEIGHT / 2;
			m_bDrawPress == true;
		}
		else if (m_bPush == false && m_bDrawPress == true)
		{
			m_bPush = true;

			// ���[�h�̐ݒ�
			CManager::GetFade()->SetFade(CFade::FADE_OUT, CManager::MODE::MODE_GAME);
		}
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

	m_apObject2D[LOGO_TITLE]->SetPosition(pos);
	m_apObject2D[LOGO_TITLE]->SetVertex();
}
