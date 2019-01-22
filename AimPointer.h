#ifndef _AIM_POINTER_H_INCLUDE_
#define _AIM_POINTER_H_INCLUDE_


#include "Library\ObjectBase2D.h"


class AimPointer : public C2DObject
{
	static Vector2 GlobalPosition;
	static Vector2 GlobalSensitivity;
	static float   GlobalCorrection;

public:
	static Vector2 GetPosition(Vector2 set = Vector2(-1, -1));
	static Vector2 *GetSensitivity();
	static float   *GetCorrection();

public:
	void Update();
	void Move(Vector2 v);

};


#endif // !_AIM_POINTER_H_INCLUDE_
