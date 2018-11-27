#ifndef __COMMON_H_INCLUDE__
#define __COMMON_H_INCLUDE__


#define _CRT_SECURE_NO_WARNINGS // warning�h�~


//================================================================
// ��ʃT�C�Y�֌W
//================================================================
/* ��ʃT�C�Y */
#define SCREEN_SCALE	(1.0f)
#define SCREEN_WIDTH    (1280*SCREEN_SCALE)
#define SCREEN_HEIGHT   (720*SCREEN_SCALE)
#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)	// ��ʒ������W
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)	// ��ʒ������W

/* ��ʍ��W�v�Z */
#define RelativeSX(m)   (SCREEN_WIDTH  * m)	// �E�C���h�E�����ʒuX
#define RelativeSY(m)   (SCREEN_HEIGHT * m)	// �E�C���h�E�����ʒuY
#define RS_X(m)         RelativeSX(m)		// <���L>
#define RS_Y(m)         RelativeSY(m)		// <���L>
#define RS_IX(m)   (int)RelativeSX(m)		// <���L>int�^�o��
#define RS_IY(m)   (int)RelativeSY(m)		// <���L>int�^�o��


//================================================================
// �}�N���֐�
//================================================================



#endif // !__COMMON_H_INCLUDE__
