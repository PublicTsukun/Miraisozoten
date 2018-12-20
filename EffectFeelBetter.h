#ifndef _EFFECT_FEELBETTER_H_INCLUDE_
#define _EFFECT_FEELBETTER_H_INCLUDE_


#include "Library/ObjectBase3D.h"


constexpr int EFB_PolygonANumber = 30;

class EffectFeelBetter
{
	class PolygonA : public C3DPolygonObject
	{
		Vector3 KineticEnergy;
		DxColor Color;
		float   Speed;
	public:
		void Set(Vector3 pos, float rng);
		void Motion();
		inline int MakeVertex()
		{
			return C3DPolygonObject::MakeVertex();
		}
	};

private:
	static Dx9Texture texA;

public:
	static void Initialize();
	static void Uninitialize();

private:
	PolygonA Note[EFB_PolygonANumber];
	Vector3 Position;	// エフェクト発生位置
	float   Range;		// エフェクト発生範囲
	int     Counter;	// エフェクト持続時間

public:
	int Init();
	int Update();
	void Draw(bool mode = true);
	void Uninit();

	void Call(Vector3 pos, float rng);
	int  CheckState();

};

/* テスト用 */
int *GetEffectFBTime();
//bool ChangeFBBlendMode(bool mode);


#endif // !_EFFECT_FEELBETTER_H_INCLUDE_
