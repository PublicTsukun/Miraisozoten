//=============================================================================
//
//木村担当分　workENEMY.h
//きむら
// 
// ・編集 : [2018/11/11 - 初]
//   >> 本番用に書き換えました
//=============================================================================
#ifndef _WORKENEMY_H_
#define _WORKENEMY_H_


#include "Library\ObjectBase3D.h"
#include "Library\Common.h"

// エネミー種類列挙
enum ENEMYTYPE
{
	MAID = 0,
	OTAKU,
	CHILD,
	ENEMYTYPE_MAX
};
constexpr const char *EnemyTextureName[ENEMYTYPE_MAX] = {
	"data/TEXTURE/ENEMY/Maid.png",
	"data/TEXTURE/ENEMY/Otaku.png",
	"data/TEXTURE/ENEMY/Child.png"
};

// クラス設計
class CEnemy : public C3DPolygonObject
{
public:
	static Dx9Texture EnemyTexture[ENEMYTYPE_MAX];

private:
	int HP;

public:
	void ChangeTexture(float side);
	void Move(Vector3 v);
	void CheckHit(Vector3 pos, Vector3 box, int atk);
};


//=============================================================================
//プロトタイプ宣言
//=============================================================================
HRESULT InitENEMY(void);
void UninitENEMY(void);
void UpdateENEMY(void);
void DrawENEMY(void);

int SetEnemy(ENEMYTYPE type, int hp, Vector3 pos);
void CheckHit(Vector3 pos, Vector2 box, int atk);
CEnemy *GetEnemy(int handle);

#endif