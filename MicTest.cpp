#define _CRT_SECURE_NO_WARNINGS

#include "Library/DebugProcess.h"
#include "MicTest.h"
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <math.h>
#include <dsound.h>
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "DSound.lib")


LPDIRECTSOUNDCAPTURE g_pDSCapture = NULL;// DirectSoundCaptureDeviceオブジェクト
LPDIRECTSOUNDCAPTUREBUFFER g_pDSBCapture = NULL;// DirectSoundCaptureBufferオブジェクト
DSCBUFFERDESC dscbd;// DirectSound Capture Buffer DESC キャプチャ バッファを記述する構造体。 


DWORD dwNextCaptureOffset = 0;	// 次の読み込み開始位置を格納する変数。
DWORD dwReadPos;				// 読み込み可能カーソルのカレントポジ
DWORD dwCapturePos;				// キャプチャカーソルのカレントポジ
void* pbCaptureData = NULL;	// 読み込む一つ目のブロックのポインタ 
DWORD dwCaptureLength;		// 読み込む一つ目のブロックの長さ
void* pbCaptureData2 = NULL;// 読み込む２つ目のブロックのポインタ 
DWORD dwCaptureLength2;		// 読み込む２つ目のブロックの長さ
UINT  dwDataWorte;
LONG  lLockSize;	// バッファから読み込むサイズ

short data1, data2;

WAVEFORMATEX wfx = { 
	WAVE_FORMAT_PCM,// wFormatTag、Waveのフォーマット
	1,				// nChannels　モノラル１　ステレオ２（データセットの種類）
	48000,			// nSamplesPerSec　1秒あたりのサンプル数
	48000 * 1,		// mAvgBytesPerSec、1秒あたりのバイト数。nSamplesPerSec＊nBlockAlign。
	1,				// nBlockAlign １サンプルのバイト数。nChannels×wBitsPerSample÷８
	8,				// wBitsPerSample　1サンプルあたりのビット数。８か１６
	0 };			// cbSize　常に０
// 単純なPCMのWAVEデータを定義。
// wFormatTag、Waveのフォーマット
// nChannels　モノラル１　ステレオ２（データセットの種類）
// nSamplesPerSec　1秒あたりのサンプル数
// mAvgBytesPerSec、1秒あたりのバイト数。nSamplesPerSec＊nBlockAlign。
// nBlockAlign １サンプルのバイト数。nChannels×wBitsPerSample÷８　８・・・８ビット=１バイト
// wBitsPerSample　1サンプルあたりのビット数。８か１６
// cbSize　常に０

int MicTestInit()
{
	// Initialize COM 
	CoInitialize(NULL);

	// Create IDirectSoundCapture8 using the default capture device
	DirectSoundCaptureCreate8(NULL, &g_pDSCapture, NULL);

	dscbd.dwSize = sizeof(DSCBUFFERDESC);
	dscbd.dwFlags = 0;
	dscbd.dwBufferBytes = wfx.nAvgBytesPerSec * 1;	// ここでキャプチャバッファのサイズを設定している。
													// 今回の例では、1秒間分の容量バッファ。
	dscbd.dwReserved = 0;
	dscbd.lpwfxFormat = &wfx;
	dscbd.dwFXCount = 0;
	dscbd.lpDSCFXDesc = NULL;


	g_pDSCapture->CreateCaptureBuffer(&dscbd, &g_pDSBCapture, NULL);
	// バッファの作成終了

	// キャプチャバッファスタート。
	g_pDSBCapture->Start(DSCBSTART_LOOPING);
	// この命令でオーディオデバイス自体は音声入力を
	// 開始し、メモリに書き込み出す。ただし、現段階では、まだそのメモリにアクセス
	// することはできない。

	return 0;
}

void MicTestUninit()
{
	// キャプチャバッファストップ
	g_pDSBCapture->Stop();

	// オブジェクトのリリース。まあ、DirectSoundオブジェクトの後始末。
	g_pDSBCapture->Release();
	g_pDSBCapture = NULL;
	g_pDSCapture->Release();
	g_pDSCapture = NULL;

	CoUninitialize();
}

short MicTest()
{
	// キャプチャカーソルと読み込み可能カーソルのカレントポジションを取る。
	g_pDSBCapture->GetCurrentPosition(&dwCapturePos, &dwReadPos);

	/*  */

	// 読み込みカーソルの直下のデータのみを読み込もう。
	g_pDSBCapture->Lock(dwReadPos, 1,
		&pbCaptureData, &dwCaptureLength,
		&pbCaptureData2, &dwCaptureLength2,
		NULL);

	data1 = *((short*)pbCaptureData);

	// 32639 : 7f7f : 0111 1111 0111 1111
	// 32640 : 7f80 : 0111 1111 1000 0000
	//-32640 : 8080 : 1000 0000 1000 0000
	//-32384 : 8180 : 1000 0001 1000 0000
	//const short L1 = 0x7FFF; //  127
	//const short L2 = 0x8000; //  128
	//const short L3 = 0x0180; // -32768

	short val = (data1 < 0) ? (-data1 - 32768) : (32767 - data1);

	// ロックの解除
	g_pDSBCapture->Unlock(pbCaptureData, dwCaptureLength,
		pbCaptureData2, dwCaptureLength2);

	return val;
}

void MicReStart()
{
	g_pDSBCapture->Stop();

	if (g_pDSBCapture != NULL)
	{
		g_pDSBCapture->Release();
		g_pDSBCapture = NULL;
	}
	if (g_pDSCapture != NULL)
	{
		g_pDSCapture->Release();
		g_pDSCapture = NULL;
	}

	DirectSoundCaptureCreate8(NULL, &g_pDSCapture, NULL);
	g_pDSCapture->CreateCaptureBuffer(&dscbd, &g_pDSBCapture, NULL);
	g_pDSBCapture->Start(DSCBSTART_LOOPING);
}


