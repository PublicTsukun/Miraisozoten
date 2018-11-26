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
	Vector3 gyro = GetGyro();

	PrintDebugProcess("X = %f, Y = %f, Z = %f\n", gyro.x, gyro.y, gyro.z);

	// ä¥ìx
	static float vX = 5.0f;
	static float vY = 5.0f;
	if (GetKeyboardTrigger(DIK_4))	vX -= 1.0f;
	if (GetKeyboardTrigger(DIK_6))	vX += 1.0f;
	if (GetKeyboardTrigger(DIK_8))	vY -= 1.0f;
	if (GetKeyboardTrigger(DIK_2))	vY += 1.0f;
	PrintDebugProcess("ä¥ìx : %d, %d\n", (int)vX, (int)vY);

	// àÍíËílà»â∫Çñ≥å¯
	static float c = 1.0f;
	if (GetKeyboardTrigger(DIK_MINUS))	c -= 0.5f;
	if (GetKeyboardTrigger(DIK_ADD))	c += 0.5f;
	PrintDebugProcess("ï‚ê≥ : %f\n", c);


	Vector2 value;
	value.x = gyro.z / vX;
	value.y = gyro.x / vY;
	if (value.x <= c && value.x >= -c)	value.x = 0.0f;
	if (value.y <= c && value.y >= -c)	value.y = 0.0f;

	PrintDebugProcess("X = %f, Y = %f\n", value.x, value.y);

	Move(value);
	if (IsMouseLeftPressed())
		Move(Vector2((float)GetMouseX(), (float)GetMouseY()));
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

