//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#include "timer.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UI2DNumber number[MAX_DIGIT];	//�^�C�}�[����
C2DObject frame;	//�^�C�}�[�t���[��



//3���o�[�W����
//const float NumberInter = NUMBER_SIZE_X * 2; //�^�C�}�[�����̊Ԋu
//const float Digit1_posX = SCREEN_CENTER_X + NumberInter;
//const float Digit2_posX = SCREEN_CENTER_X;
//const float Digit3_posX = SCREEN_CENTER_X - NumberInter;

//2���o�[�W����
const float NumberInter = NUMBER_SIZE_X ; //�^�C�}�[�����̊Ԋu
const float Digit1_posX = SCREEN_CENTER_X + NumberInter;
const float Digit2_posX = SCREEN_CENTER_X - NumberInter;

const float FrameSizeX = MAX_DIGIT * NUMBER_SIZE_X+25;
const float FrameSizeY = NUMBER_SIZE_Y+20;

int Time;

int fcount;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitTimer(void)
{
	number[0].Init(Digit1_posX, NUMBER_POS_Y, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);
	number[1].Init(Digit2_posX, NUMBER_POS_Y, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);
	//number[2].Init(Digit3_posX, NUMBER_POS_Y, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);

	frame.Init(SCREEN_CENTER_X, 50, FrameSizeX, FrameSizeY, FRAME_TEX);


	Time = 99;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimer(void)
{

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		number[i].Release();
	}

	frame.Release();

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{
	frame.Draw();

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		number[i].Draw();
	}

}


//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimer(void)
{

	fcount++;
	if (fcount > 62)
	{
		fcount = 0;
		Time--;
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		int num;

		num = (Time / (int)(pow(10, i)));
		num %= 10;


		number[i].SetNumber(num);


	}


}