#ifndef __TSULIB_STSTEM_H_INCLUDE__
#define __TSULIB_STSTEM_H_INCLUDE__

#include <windows.h>

typedef class TSULibrarySystem
{
public:
	static HRESULT Initialize(HINSTANCE hInstance);
	static void    Uninitialize();

private:
	TSULibrarySystem() {};

}TsuSystem;



#endif // !__TSULIB_STSTEM_H_INCLUDE__
