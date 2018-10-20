//=============================================================================
//
// �t�B�[���h���� [field.cpp]
//
//=============================================================================
#include "timer.h"
#include "Library/ObjectBase2D.h"
#include "Library/Common.h"



//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
UI2DNumber number[MAX_DIGIT];	//�^�C�}�[����
C2DObject frame;	//�^�C�}�[�t���[��

const float NumberInter = NUMBER_SIZE_X * 2; //�^�C�}�[�����̊Ԋu

const float Digit1_posX = SCREEN_CENTER_X - NumberInter;
const float Digit2_posX = SCREEN_CENTER_X;
const float Digit3_posX = SCREEN_CENTER_X + NumberInter;


int Time;
//=============================================================================
// ����������
//=============================================================================
HRESULT InitTimer(void)
{
	number[0].Init(Digit1_posX, 10, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);
	number[1].Init(Digit2_posX, 10, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);
	number[2].Init(Digit3_posX, 10, NUMBER_SIZE_X, NUMBER_SIZE_Y, NUMBER_TEX);


	Time = 123;
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

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimer(void)
{

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

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		int num;

		num = (Time / (pow(10, i)));
		num %= 10;


		number[i].SetNumber(num);
	}


}