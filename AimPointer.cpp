#include "AimPointer.h"
#include "Library\Common.h"
#include "Library\Input.h"
#include "Library\DebugProcess.h"

void AimPointer::Update()
{
	Vector3 gyro = GetGyro(0);

	PrintDebugProcess("X = %f, Y = %f, Z = %f\n", gyro.x, gyro.y, gyro.z);

	static float v = 100.0f;
	if (GetKeyboardTrigger(DIK_LBRACKET))	v -= 10.0f;
	if (GetKeyboardTrigger(DIK_RBRACKET))	v += 10.0f;
	PrintDebugProcess("ä¥ìx : %d\n", (int)v);

	static float c = 1.0f;
	if (GetKeyboardTrigger(DIK_MINUS))	c -= 0.5f;
	if (GetKeyboardTrigger(DIK_ADD))	c += 0.5f;
	PrintDebugProcess("ï‚ê≥ : %f\n", c);


	Vector2 value;
	value.x = -(gyro.z - 32767.0f) / v;
	value.y =  (gyro.x - 32767.0f) / v;
	if (value.x <= c && value.x >= -c)	value.x = 0.0f;
	if (value.y <= c && value.y >= -c)	value.y = 0.0f;

	PrintDebugProcess("X = %f, Y = %f\n", value.x, value.y);

	Move(value);
}

void AimPointer::Move(Vector2 v)
{
	Position += v;
	if (Position.x > SCREEN_WIDTH)	Position.x = SCREEN_WIDTH;
	if (Position.x < 0.0f)			Position.x = 0.0f;
	if (Position.y > SCREEN_HEIGHT)	Position.y = SCREEN_HEIGHT;
	if (Position.y < 0.0f)			Position.y = 0.0f;

	SetVertex();
}
