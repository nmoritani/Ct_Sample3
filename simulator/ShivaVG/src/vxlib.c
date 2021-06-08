/*************************************************************************/
/**
 * @file      vxlib.c
 * @brief     VXLIB�X�^�u
 * @date      
 * @copyright Panasonic Co.,Ltd.
 * @author    
 *************************************************************************/
/***************************************************************
				�C���N���[�h�t�@�C��
***************************************************************/
#include <windows.h>
#include <tchar.h>
#include "vxlib.h"

/***************************************************************
				�^��`�A�}�N����`
***************************************************************/

#define	VX_WINDOW_CLASS		_T("VxWindow")

typedef struct	VXwindow {
	HWND			hWnd;
	VXuint			*addr;
	VXint			x;
	VXint			y;
	VXint			width;
	VXint			height;
	VXint			depth;
} VXwindow;

/***************************************************************
				�ϐ��錾
***************************************************************/

static int s_WindowClassRegisterd = 0;

/***************************************************************
				�֐��錾
***************************************************************/

static int vxRegisterWindowClass(void);
static HWND vxCreateWindow(int nWidth, int nHeight);
static LRESULT CALLBACK	vxWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/***************************************************************
				�֐�
***************************************************************/

VXDisplay* VXOpenDisplay(char *id)
{
    return (VXDisplay *)1;
}

VXAPI VXWindow   VXCreateWindow(VXDisplay *dpy, VXint x, VXint y, VXint width, VXint height, VXint depth)
{
	VXwindow	*window;
	
	/* �E�C���h�E�N���X�o�^ */
	if (s_WindowClassRegisterd == 0) {
		vxRegisterWindowClass();
		s_WindowClassRegisterd = 1;
	}
	
	/* �������m�� */
	window = malloc(sizeof(VXwindow));
	/* �l�ݒ� */
	window->x = x;
	window->y = y;
	window->width = width;
	window->height = height;
	window->depth = depth;
	window->hWnd = vxCreateWindow(width, height);
	
	return (VXWindow)window;
}

VXAPI void       VXDestroyWindow(VXDisplay *dpy, VXWindow win)
{
	VXwindow	*window = (VXwindow*)win;
	
	DestroyWindow(window->hWnd);
	free(window);
}

VXPixmap VXCreatePixmap(VXDisplay *dpy, VXWindow win, VXint width, VXint height, VXint depth)
{
	VXwindow	*window;
	int			bufsize;
	
	/* �������m�� */
	window = malloc(sizeof(VXwindow));
	/* �l�ݒ� */
	bufsize = width * height * (depth >> 3);
	window->x = 0;
	window->y = 0;
	window->width = width;
	window->height = height;
	window->depth = depth;
	window->hWnd = NULL;
	window->addr = malloc(bufsize);
	
	return (VXPixmap)window;
}

void VXFreePixmap(VXDisplay *dpy, VXPixmap pixmap)
{
	VXwindow	*window = (VXwindow*)pixmap;
	
	if (window->addr != NULL) {
		free(window->addr);
	}
	free(window);
}

VXAPI void       VXQueryWindow(VXDisplay *dpy, void *target, VXuint attribute, VXuint *value)
{
	VXwindow *window;

	window = (VXwindow *)target;
	switch (attribute) {
		case VX_HWND:
			*value = (VXuint)(window->hWnd);
			return;
		case VX_ADDR:
			*value = (VXuint)(window->addr);
			return;
		case VX_WIDTH:
			*value = (VXuint)(window->width);
			return;
		case VX_HEIGHT:
			*value = (VXuint)(window->height);
			return;
		case VX_DEPTH:
			*value = (VXuint)(window->depth);
			return;
		case VX_VALID:
			*value = 1;
			return;
		default:
			*value = 0;
			break;
	}
	return;
}

static int vxRegisterWindowClass(void)
{
	WNDCLASSEX	wc;

	wc.cbSize		 = sizeof(WNDCLASSEX);				// �\���̃T�C�Y
	wc.style		 = CS_HREDRAW | CS_VREDRAW;			// �N���X�X�^�C��
	wc.lpfnWndProc	 = vxWindowProc;					// �v���V�[�W��
	wc.cbClsExtra	 = 0;								// �⑫�������u���b�N�̃T�C�Y
	wc.cbWndExtra	 = 0;								// �V
	wc.hInstance	 = GetModuleHandle(NULL);			// �C���X�^���X
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);	// �A�C�R��
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		// �J�[�\��
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);// �w�i�F
	wc.lpszMenuName	 = NULL;							// ���j���[
	wc.lpszClassName = VX_WINDOW_CLASS;					// �N���X��
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);	// �������A�C�R��

	return(RegisterClassEx(&wc));
}

/* GL�̕`��ɕK�v�ȃE�C���h�E���쐬���� */
static HWND vxCreateWindow(int nWidth, int nHeight)
{
	HWND		hWnd;
	DWORD		dwStyle;
	DWORD		dwExStyle;
	
	dwExStyle = 0;
	dwStyle = (WS_POPUP | WS_CLIPCHILDREN);
	//dwStyle |= WS_VISIBLE;		//for Debug
	hWnd = CreateWindowEx(
						dwExStyle,				// �g���E�B���h�E�X�^�C��
						VX_WINDOW_CLASS,		// �o�^����Ă���N���X��
						_T(""),					// �E�B���h�E��
						dwStyle,				// �E�B���h�E�X�^�C��
						CW_USEDEFAULT,			// �E�B���h�E�̉������̈ʒu
						CW_USEDEFAULT,			// �E�B���h�E�̏c�����̈ʒu
						nWidth,					// �E�B���h�E�̕�
						nHeight,				// �E�B���h�E�̍���
						NULL,					// �e�E�B���h�E�܂��̓I�[�i�E�B���h�E�̃n���h��
						NULL,					// ���j���[�n���h���܂��͎q���ʎq
						GetModuleHandle(NULL),	// �A�v���P�[�V�����C���X�^���X�̃n���h��
						NULL);					// �E�B���h�E�쐬�f�[�^
	return hWnd;
}

static LRESULT CALLBACK	vxWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

