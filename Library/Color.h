#ifndef __TSULIB_COLOR_H_INCLUDE__
#define __TSULIB_COLOR_H_INCLUDE__


#include "Math.h"
#include <d3dx9math.h>

typedef D3DCOLOR COLOR, DxColor;


#define RANDOMCOLOR (0x000000FF | Random(0, 255) << 24 | Random(0, 255) << 16 | Random(0, 255) << 8)


#define DX9COLOR_BLACK       (0x000000FF)
#define DX9COLOR_RED         (0xFF0000FF)
#define DX9COLOR_GREEN       (0x00FF00FF)
#define DX9COLOR_BLUE        (0x0000FFFF)
#define DX9COLOR_YELLOW      (0xFFFF00FF)
#define DX9COLOR_MAGENTA     (0xFF00FFFF)
#define DX9COLOR_CYAN        (0x00FFFFFF)
#define DX9COLOR_WHITE       (0xFFFFFFFF)


#endif // !__TSULIB_COLOR_INCLUDE__
