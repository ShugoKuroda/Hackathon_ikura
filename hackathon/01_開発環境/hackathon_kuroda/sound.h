//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA, SHUGO KURODA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include <xaudio2.h>					// サウンド再生に必要

//-----------------------------------------------------------------------------
// サウンドクラス(基本クラス)
//-----------------------------------------------------------------------------
class CSound
{
public:
	CSound();
	~CSound();

	// サウンドファイル
	typedef enum
	{
		// BGM音
		SOUND_LABEL_TITLE = 0,			// タイトルBGM
		SOUND_LABEL_GAME,				// ゲームBGM
		SOUND_LABEL_RESULT,				// リザルトBGM
		// ゲームSE音
		SOUND_LABEL_SE_BUTTON,			// 自機登場
		SOUND_LABEL_SE_SHOT,			// 弾発射
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void Uninit();
	static HRESULT Play(SOUND_LABEL label);
	static void Stop(SOUND_LABEL label);
	static void Stop();

private:
	// パラメータ構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	static IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// オーディオデータサイズ

	static SOUNDPARAM m_aParam[SOUND_LABEL_MAX];
};

#endif
