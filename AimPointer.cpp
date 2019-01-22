#include "AimPointer.h"
#include "Library\Common.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"


Vector2 AimPointer::GlobalPosition = Vector2();
Vector2 AimPointer::GlobalSensitivity = Vector2(4, 6);
float   AimPointer::GlobalCorrection = 0.0f;

Vector2 AimPointer::GetPosition(Vector2 set)
{
	if (set.x > 0 && set.y > 0)
		GlobalPosition = set;
	return GlobalPosition;
}

Vector2 *AimPointer::GetSensitivity()
{
	return &GlobalSensitivity;
}

float *AimPointer::GetCorrection()
{
	return &GlobalCorrection;
}

void AimPointer::Update()
{
#ifdef _DEBUG
	static bool joyconORmouse = true;
	if (GetKeyboardTrigger(DIK_M))
	{
		joyconORmouse = joyconORmouse ? false : true;
	}

	if (joyconORmouse)
	{
		PrintDebugProcess("�|�C���^�[������@(M) : �W���C��\n");
#endif // _DEBUG

		Vector3 gyro = GetGyro();

#ifdef _DEBUG
		PrintDebugProcess("�W���C�R�� : (%f, %f, %f)\n", gyro.x, gyro.y, gyro.z);

		// ���x
		if (GetKeyboardTrigger(DIK_4))	GlobalSensitivity.x -= 0.5f;
		if (GetKeyboardTrigger(DIK_6))	GlobalSensitivity.x += 0.5f;
		if (GetKeyboardTrigger(DIK_8))	GlobalSensitivity.y -= 0.5f;
		if (GetKeyboardTrigger(DIK_2))	GlobalSensitivity.y += 0.5f;
		PrintDebugProcess("���x : %f, %f\n", GlobalSensitivity.x, GlobalSensitivity.y);

		// ���l�ȉ��𖳌�
		if (GetKeyboardTrigger(DIK_MINUS))	GlobalCorrection -= 0.5f;
		if (GetKeyboardTrigger(DIK_ADD))	GlobalCorrection += 0.5f;
		PrintDebugProcess("�␳ : %f\n", GlobalCorrection);
#endif // _DEBUG

		Vector2 value;
		value.x = gyro.z / GlobalSensitivity.x;
		value.y = gyro.x / GlobalSensitivity.y;
		if (value.x <= GlobalCorrection && value.x >= -GlobalCorrection)	value.x = 0.0f;
		if (value.y <= GlobalCorrection && value.y >= -GlobalCorrection)	value.y = 0.0f;

#ifdef _DEBUG
		PrintDebugProcess("�|�C���^�[�ړ��� : (%f, %f)\n", value.x, value.y);
#endif // _DEBUG

		/* �ړ� */
		Move(value);
#ifdef _DEBUG
	}
	else if (IsMouseLeftPressed())
	{
		PrintDebugProcess("�|�C���^�[������@(M) : �}�E�X\n");
		Move(Vector2((float)GetMouseX(), (float)GetMouseY()));
	}
#endif // _DEBUG
}

void AimPointer::Move(Vector2 v)
{
	Position += v;
	if (Position.x > SCREEN_WIDTH)	Position.x = SCREEN_WIDTH;
	if (Position.x < 0.0f)			Position.x = 0.0f;
	if (Position.y > SCREEN_HEIGHT)	Position.y = SCREEN_HEIGHT;
	if (Position.y < 0.0f)			Position.y = 0.0f;
	GetPosition(Position);
	SetVertex();
}

