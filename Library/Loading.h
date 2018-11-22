//=============================================================================
//
// ローディング画面処理 <Loading.h>
//
//=============================================================================
#ifndef __LOADING_INCLUDE_H__
#define __LOADING_INCLUDE_H__


#include "ObjectBase2D.h"


class CNowLoading
{
public:
	UIBackGround     Back;
	C2DObject        Text;

	void Init();
	void Uninit(void);
	void Progress(int per);
};



#endif
