#include "HitCheck.h"


/****************************************************************/
/* 2D */
/****************************************************************/

/* 面と点の衝突 */
/* lu : 面の左上 */
/* rb : 面の右下 */
/* co : 点の座標 */
bool Collision::RxC(Vector2 lu, Vector2 rb, Vector2 co)
{
	if ((lu.x < co.x) && (co.x < rb.x) &&
		(lu.y < co.y) && (co.y < rb.y))
		return true;
	return false;
}

/* 面と点の衝突 */
/* pos : 面の座標 */
/* siz : 面のサイズ */
/* cod : 点の座標 */
bool Collision::RxC2(Vector2 pos, Vector2 siz, Vector2 cod)
{
	if ((pos.x - siz.x < cod.x) && (cod.x < pos.x + siz.x) &&
		(pos.y - siz.y < cod.y) && (cod.y < pos.y + siz.y))
		return true;
	return false;
}


/* 面と面の衝突 2 */
/* p1 : 面1の座標   */
/* s1 : 面1のサイズ */
/* p2 : 面2の座標   */
/* s2 : 面2のサイズ */
bool Collision::Rectangle(Vector2 p1, Vector2 s1, Vector2 p2, Vector2 s2)
{
	if ((p1.x - s1.x < p2.x - s2.x) && (p2.x + s2.x < p1.x + s1.x) &&
		(p1.y - s1.y < p2.y - s2.y) && (p2.y + s2.y < p1.y + s1.y))
		return true;
	return false;
}


/****************************************************************/
/* 3D */
/****************************************************************/

/* AABB立体と点の衝突 */
/* v1 : 立体の左上前 */
/* v2 : 立体の右下奥 */
/* co : 点の座標 */
bool Collision::AABBxC(Vector3 v1, Vector3 v2, Vector3 co)
{
	if ((v1.x < co.x) && (co.x < v2.x) &&
		(v1.y < co.y) && (co.y < v2.y) &&
		(v1.z < co.z) && (co.z < v2.z))
		return true;
	return false;
}

/* AABB立体同士の衝突 */
/* vA1 : AABBの左上前 */
/* vA2 : AABBの右下奥 */
/* vB1 : AABBの左上前 */
/* vB2 : AABBの左上前 */
bool Collision::AABB(Vector3 vA1, Vector3 vA2, Vector3 vB1, Vector3 vB2)
{
	if ((vA2.x > vB1.x) && (vB2.x > vA1.x) &&
		(vA2.y < vB1.y) && (vB2.y < vA1.y) &&
		(vA2.z > vB1.z) && (vB2.z > vA1.z))
		return true;
	return false;
}
