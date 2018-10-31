#include "HitCheck.h"


/****************************************************************/
/* 2D */
/****************************************************************/

/* �ʂƓ_�̏Փ� */
/* lu : �ʂ̍��� */
/* rb : �ʂ̉E�� */
/* co : �_�̍��W */
bool Collision::RxC(Vector2 lu, Vector2 rb, Vector2 co)
{
	if ((lu.x < co.x) && (co.x < rb.x) &&
		(lu.y < co.y) && (co.y < rb.y))
		return true;
	return false;
}

/* �ʂƓ_�̏Փ� */
/* pos : �ʂ̍��W */
/* siz : �ʂ̃T�C�Y */
/* cod : �_�̍��W */
bool Collision::RxC2(Vector2 pos, Vector2 siz, Vector2 cod)
{
	if ((pos.x - siz.x < cod.x) && (cod.x < pos.x + siz.x) &&
		(pos.y - siz.y < cod.y) && (cod.y < pos.y + siz.y))
		return true;
	return false;
}


/* �ʂƖʂ̏Փ� 2 */
/* p1 : ��1�̍��W   */
/* s1 : ��1�̃T�C�Y */
/* p2 : ��2�̍��W   */
/* s2 : ��2�̃T�C�Y */
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

/* AABB���̂Ɠ_�̏Փ� */
/* v1 : ���̂̍���O */
/* v2 : ���̂̉E���� */
/* co : �_�̍��W */
bool Collision::AABBxC(Vector3 v1, Vector3 v2, Vector3 co)
{
	if ((v1.x < co.x) && (co.x < v2.x) &&
		(v1.y < co.y) && (co.y < v2.y) &&
		(v1.z < co.z) && (co.z < v2.z))
		return true;
	return false;
}

/* AABB���̓��m�̏Փ� */
/* vA1 : AABB�̍���O */
/* vA2 : AABB�̉E���� */
/* vB1 : AABB�̍���O */
/* vB2 : AABB�̍���O */
bool Collision::AABB(Vector3 vA1, Vector3 vA2, Vector3 vB1, Vector3 vB2)
{
	if ((vA2.x > vB1.x) && (vB2.x > vA1.x) &&
		(vA2.y < vB1.y) && (vB2.y < vA1.y) &&
		(vA2.z > vB1.z) && (vB2.z > vA1.z))
		return true;
	return false;
}
