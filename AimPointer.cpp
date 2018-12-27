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
	static bool joyconORmouse = true;
	if (GetKeyboardTrigger(DIK_M))
	{
		joyconORmouse = joyconORmouse ? false : true;
	}

	if (joyconORmouse)
	{
		PrintDebugProcess("ポインター操作方法(M) : ジャイロ\n");

		//SetCursorPos(100, 100);

		Vector3 gyro = GetGyro();

		PrintDebugProcess("ジョイコン : (%f, %f, %f)\n", gyro.x, gyro.y, gyro.z);

		// 感度
		if (GetKeyboardTrigger(DIK_4))	GlobalSensitivity.x -= 0.5f;
		if (GetKeyboardTrigger(DIK_6))	GlobalSensitivity.x += 0.5f;
		if (GetKeyboardTrigger(DIK_8))	GlobalSensitivity.y -= 0.5f;
		if (GetKeyboardTrigger(DIK_2))	GlobalSensitivity.y += 0.5f;
		PrintDebugProcess("感度 : %f, %f\n", GlobalSensitivity.x, GlobalSensitivity.y);

		// 一定値以下を無効
		if (GetKeyboardTrigger(DIK_MINUS))	GlobalCorrection -= 0.5f;
		if (GetKeyboardTrigger(DIK_ADD))	GlobalCorrection += 0.5f;
		PrintDebugProcess("補正 : %f\n", GlobalCorrection);

		Vector2 value;
		value.x = gyro.z / GlobalSensitivity.x;
		value.y = gyro.x / GlobalSensitivity.y;
		if (value.x <= GlobalCorrection && value.x >= -GlobalCorrection)	value.x = 0.0f;
		if (value.y <= GlobalCorrection && value.y >= -GlobalCorrection)	value.y = 0.0f;

		PrintDebugProcess("ポインター移動量 : (%f, %f)\n", value.x, value.y);

		/* 移動 */
		Move(value);
	}
	else if (IsMouseLeftPressed())
	{
		PrintDebugProcess("ポインター操作方法(M) : マウス\n");
		Move(Vector2((float)GetMouseX(), (float)GetMouseY()));
	}
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

