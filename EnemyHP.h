//=============================================================================
//
// EnemyHP���� [EnemyHP.h]
// Author : �v�F��
//
//=============================================================================
#ifndef _ENEMYHP_INCLUDE_H_
#define _ENEMYHP_INCLUDE_H_

#include "Library/Vector.h"
#include "Library/ObjectBase3D.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class EnemyHP : public C3DPolygonObject
{
private:
	bool use;
	void SetUse(bool use);

public:
	void Enable(void);
	void Disable(void);
	bool GetUse(void);
	float GetSizeX(void);

	void InitVertexEnemyHP(void);
	void SetVertexEnemyHP(float coord, float uv);

};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
EnemyHP *GetEnemyHP(int no);
void InitEnemyHP(void);
void UninitEnemyHP(void);
void DrawEnemyHP(void);
void UpdateEnemyHP(void);

void SetEnemyHP(int no);

#endif