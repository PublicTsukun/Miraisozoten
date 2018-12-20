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
	Vector3 Position;	// �G�t�F�N�g�����ʒu
	float   Range;		// �G�t�F�N�g�����͈�
	int     Counter;	// �G�t�F�N�g��������

public:
	int Init();
	int Update();
	void Draw(bool mode = true);
	void Uninit();

	void Call(Vector3 pos, float rng);
	int  CheckState();

};

/* �e�X�g�p */
int *GetEffectFBTime();
//bool ChangeFBBlendMode(bool mode);


#endif // !_EFFECT_FEELBETTER_H_INCLUDE_
