#ifndef _AIM_POINTER_H_INCLUDE_
#define _AIM_POINTER_H_INCLUDE_


#include "Library\ObjectBase2D.h"


class AimPointer : public C2DObject
{
public:
	void Update();
	void Move(Vector2 v);

};

#endif // !_AIM_POINTER_H_INCLUDE_
