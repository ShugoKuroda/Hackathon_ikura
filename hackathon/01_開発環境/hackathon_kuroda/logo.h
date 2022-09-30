//-------------------------------------------
//
// ���S�̏��[logo.h]
// Author : SHUGO KURODA
//
//-------------------------------------------
#ifndef _LOGO_H_
#define _LOGO_H_

//-------------------------------------------
// �C���N���[�h
//-------------------------------------------
#include "object2D.h"

//-------------------------------------------
// ���S�N���X
//-------------------------------------------
class CLogo : public CObject2D
{
public:
	enum LOGOTYPE
	{//���S�̎��
		TYPE_NONE = 0,		// �����Ȃ�
		TYPE_ROUND1,		// ���E���h1
		TYPE_ROUND2,		// ���E���h2
		TYPE_FINALROUND,	// �ŏI���E���h
		TYPE_START,			// �Q�[���J�n
		TYPE_SCOREUI,		// ���݂̃X�R�A���S
		TYPE_M,				// ��(���[�g��)�̃��S
		TYPE_FINISH,		// �I�����S
		TYPE_NOKORI,		// �c�胍�S
		TYPE_MAX
	};

	enum ANIMTYPE
	{//�A�j���[�V�����̎��
		ANIM_NONE = 0,		// �������Ȃ�
		ANIM_LENGTHWISE,	// �c�ɍL����
		ANIM_HORIZONTALLY,	// ���ɍL����
		ANIM_ZOOM_IN,		// ���񂾂�傫���Ȃ�
		ANIM_FLASHING,		// �_��
		ANIM_MAX
	};

	// �R���X�g���N�^
	CLogo();
	// �f�X�g���N�^
	~CLogo() override;

	// ����
	static CLogo* Create(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const LOGOTYPE& type, const ANIMTYPE& AnimType, const int& nCount);
	// �e�N�X�`���̓ǂݍ���
	static HRESULT Load();
	// �e�N�X�`���̍폜
	static void Unload();

	// ������
	HRESULT Init() override;
	// �I��
	void Uninit() override;
	// �X�V
	void Update() override;
	// �`��
	void Draw() override;

private:
	// �e�N�X�`���̃|�C���^
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];
	// �A�j���[�V�����̎��
	ANIMTYPE m_AnimType;
	// �j������܂ł̃J�E���^�[
	int m_nCountUninit;
	// ���̃T�C�Y�L���p
	D3DXVECTOR2 m_DefaultSize;

	LOGOTYPE m_type;
};

#endif		// _LOGO_H_
