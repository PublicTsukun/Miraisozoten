#ifndef _HIT_CHECK_H_INCLUDE_
#define _HIT_CHECK_H_INCLUDE_


#include "Library/Vector.h"
#include "Library/Math.h"

namespace Collision
{
	/* 2D */
	bool RxC(Vector2 lu, Vector2 rb, Vector2 co);
	bool RxC2(Vector2 pos, Vector2 siz, Vector2 cod);
	bool Rectangle(Vector2 p1, Vector2 s1, Vector2 p2, Vector2 s2);

	/* 3D */
	bool AABBxC(Vector3 v1, Vector3 v2, Vector3 co);
	bool AABB(Vector3 vA1, Vector3 vA2, Vector3 vB1, Vector3 vB2);
}



#endif // !_HIT_CHECK_H_INCLUDE_
