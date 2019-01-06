//=============================================================================
//
// EnemyHP処理 [EnemyHP.h]
// Author : 宋彦霖
//
//=============================================================================
#ifndef _ENEMYHP_INCLUDE_H_
#define _ENEMYHP_INCLUDE_H_

#include "Library/Vector.h"
#include "Library/ObjectBase3D.h"
#include <Windows.h>
#include <d3dx9.h>

//*****************************************************************************
// クラス定義
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
// プロトタイプ宣言
//*****************************************************************************
EnemyHP *GetEnemyHP(int no);
void InitEnemyHP(void);
void UninitEnemyHP(void);
void DrawEnemyHP(void);
void UpdateEnemyHP(void);

void SetEnemyHP(int no);

#endif