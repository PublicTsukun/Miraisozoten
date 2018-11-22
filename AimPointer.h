#ifndef _AIM_POINTER_H_INCLUDE_
#define _AIM_POINTER_H_INCLUDE_


#include "Library\ObjectBase2D.h"


static class AimPointer : public C2DObject
{
	static Vector2 GlobalPosition;

public:
	static Vector2 GetPosition(Vector2 set = Vector2(-1, -1));

public:
	void Update();
	void Move(Vector2 v);

};


#endif // !_AIM_POINTER_H_INCLUDE_
