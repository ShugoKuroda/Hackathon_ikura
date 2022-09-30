//-----------------------------------------------------------------------------------------------
//
// ���S����[logo.cpp]
// Author : SHUGO KURODA
//
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------------------------
#include "logo.h"
#include "manager.h"	// �A�v���P�[�V����
#include "renderer.h"	// �����_�����O
#include "fade.h"
#include "game.h"

//-----------------------------------------------------------------------------------------------
// �萔�錾
//-----------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ�
//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 CLogo::m_pTexture[TYPE_MAX] = {};

//-----------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------------------------
CLogo::CLogo()
	:m_nCountUninit(0), m_AnimType(ANIM_NONE), m_type(TYPE_NONE)
{
	SetObjType(EObject::OBJ_LOGO);
}

//-----------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------------------------
CLogo::~CLogo()
{

}

//-----------------------------------------------------------------------------------------------
// ����
// const D3DXVECTOR3& pos �� ��������ʒu
// const D3DXVECTOR2& size �� ��������T�C�Y
// const LOGOTYPE& type �� ����������
// const ANIMTYPE& AnimType �� �A�j���[�V�����̎��
// const int& nCount �� �j������܂ł̎���
//-----------------------------------------------------------------------------------------------
CLogo* CLogo::Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const LOGOTYPE& type, const ANIMTYPE& AnimType, const int& nCount)
{
	// �|�C���^�N���X��錾
	CLogo* pLogo = new CLogo;

	if (pLogo != nullptr)
	{// ����nullptr�ł͂Ȃ�������

		// �ʒu�ݒ�
		pLogo->SetPosition(pos);

		// �T�C�Y�̕ۑ�
		pLogo->m_DefaultSize = size;

		// �A�j���[�V�����̎�ނ�ݒ�
		pLogo->m_AnimType = AnimType;

		// �j���J�E���^�[��ݒ�
		pLogo->m_nCountUninit = nCount;

		// ������
		pLogo->Init();

		// ��ނ̐ݒ�
		pLogo->m_type = type;

		// �e�N�X�`���̐ݒ�
		pLogo->BindTexture(m_pTexture[type]);
	}

	return pLogo;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̓ǂݍ���
//-----------------------------------------------------------------------------------------------
HRESULT CLogo::Load()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/round1_000.png",
		&m_pTexture[TYPE_ROUND1]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/round2_000.png",
		&m_pTexture[TYPE_ROUND2]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/finalRound000.png",
		&m_pTexture[TYPE_FINALROUND]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/letshot000.png",
		&m_pTexture[TYPE_START]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/kiroku000.png",
		&m_pTexture[TYPE_SCOREUI]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/m.png",
		&m_pTexture[TYPE_M]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/end000.png",
		&m_pTexture[TYPE_FINISH]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/nokori000.png",
		&m_pTexture[TYPE_NOKORI]);
	D3DXCreateTextureFromFile(pDevice,
		"data/TEXTURE/tatehuda000.png",
		&m_pTexture[TYPE_TUTORIAL]);

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �e�N�X�`���̍폜
//-----------------------------------------------------------------------------------------------
void CLogo::Unload()
{
	for (int nCnt = 0; nCnt >= ANIM_MAX; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != nullptr)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = nullptr;
		}
	}
}

//-----------------------------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------------------------
HRESULT CLogo::Init()
{
	switch (m_AnimType)
	{
	case CLogo::ANIM_LENGTHWISE:
		SetSize(D3DXVECTOR2(m_DefaultSize.x, 0.0f));
		break;
	case CLogo::ANIM_HORIZONTALLY:
		SetSize(D3DXVECTOR2(0.0f, m_DefaultSize.y));
		break;
	default:
		SetSize(D3DXVECTOR2(m_DefaultSize));
		break;
	}

	//������
	CObject2D::Init();

	return S_OK;
}

//-----------------------------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------------------------
void CLogo::Uninit()
{
	CObject2D::Uninit();
}

//-----------------------------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------------------------
void CLogo::Update()
{
	// �J�E���g�����炷
	m_nCountUninit--;

	// �\���J�E���^�[��0�ȉ�
	if (m_nCountUninit <= 0)
	{// �j��
		// �j��
		Uninit();
		return;
	}

	// �T�C�Y�̎擾
	D3DXVECTOR2 size = GetSize();

	switch (m_AnimType)
	{
	case CLogo::ANIM_LENGTHWISE:

		size.y += 1.0f;

		if (m_DefaultSize.y <= size.y)
		{
			size.y = m_DefaultSize.y;
		}

		break;

	case CLogo::ANIM_HORIZONTALLY:
		size.x += 10.0f;
		if (m_DefaultSize.x <= size.x)
		{
			size.x = m_DefaultSize.x;
		}
		break;
	case CLogo::ANIM_FLASHING:
		if (m_nCountUninit % 3 == 0)
		{
			CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
		break;
	default:
		break;
	}

	//�T�C�Y�̐ݒ�
	CObject2D::SetSize(size);

	//���_���W�̐ݒ�
	CObject2D::SetVertex();
}

//-----------------------------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------------------------
void CLogo::Draw()
{
	CObject2D::Draw();
}