#include "AimPointer.h"
#include "Library\Common.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"


Vector2 AimPointer::GlobalPosition = Vector2();

Vector2 AimPointer::GetPosition(Vector2 set)
{
	if (set.x > 0 && set.y > 0)
		GlobalPosition = set;
	return GlobalPosition;
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

		SetCursorPos(100, 100);

		Vector3 gyro = GetGyro();

		PrintDebugProcess("ジョイコン : (%f, %f, %f)\n", gyro.x, gyro.y, gyro.z);

		// 感度
		static float vX = 4.0f;
		static float vY = 6.0f;
		if (GetKeyboardTrigger(DIK_4))	vX -= 0.5f;
		if (GetKeyboardTrigger(DIK_6))	vX += 0.5f;
		if (GetKeyboardTrigger(DIK_8))	vY -= 0.5f;
		if (GetKeyboardTrigger(DIK_2))	vY += 0.5f;
		PrintDebugProcess("感度 : %d, %d\n", (int)vX, (int)vY);

		// 一定値以下を無効
		static float c = 0.0f;
		if (GetKeyboardTrigger(DIK_MINUS))	c -= 0.5f;
		if (GetKeyboardTrigger(DIK_ADD))	c += 0.5f;
		PrintDebugProcess("補正 : %f\n", c);

		Vector2 value;
		value.x = gyro.z / vX;
		value.y = gyro.x / vY;
		if (value.x <= c && value.x >= -c)	value.x = 0.0f;
		if (value.y <= c && value.y >= -c)	value.y = 0.0f;

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

