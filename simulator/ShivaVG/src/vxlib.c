/*************************************************************************/
/**
 * @file      vxlib.c
 * @brief     VXLIBスタブ
 * @date      
 * @copyright Panasonic Co.,Ltd.
 * @author    
 *************************************************************************/
/***************************************************************
				インクルードファイル
***************************************************************/
#include <windows.h>
#include <tchar.h>
#include "vxlib.h"

/***************************************************************
				型定義、マクロ定義
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
				変数宣言
***************************************************************/

static int s_WindowClassRegisterd = 0;

/***************************************************************
				関数宣言
***************************************************************/

static int vxRegisterWindowClass(void);
static HWND vxCreateWindow(int nWidth, int nHeight);
static LRESULT CALLBACK	vxWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/***************************************************************
				関数
***************************************************************/

VXDisplay* VXOpenDisplay(char *id)
{
    return (VXDisplay *)1;
}

VXAPI VXWindow   VXCreateWindow(VXDisplay *dpy, VXint x, VXint y, VXint width, VXint height, VXint depth)
{
	VXwindow	*window;
	
	/* ウインドウクラス登録 */
	if (s_WindowClassRegisterd == 0) {
		vxRegisterWindowClass();
		s_WindowClassRegisterd = 1;
	}
	
	/* メモリ確保 */
	window = malloc(sizeof(VXwindow));
	/* 値設定 */
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
	
	/* メモリ確保 */
	window = malloc(sizeof(VXwindow));
	/* 値設定 */
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

	wc.cbSize		 = sizeof(WNDCLASSEX);				// 構造体サイズ
	wc.style		 = CS_HREDRAW | CS_VREDRAW;			// クラススタイル
	wc.lpfnWndProc	 = vxWindowProc;					// プロシージャ
	wc.cbClsExtra	 = 0;								// 補足メモリブロックのサイズ
	wc.cbWndExtra	 = 0;								// 〃
	wc.hInstance	 = GetModuleHandle(NULL);			// インスタンス
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION);	// アイコン
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);		// カーソル
	wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);// 背景色
	wc.lpszMenuName	 = NULL;							// メニュー
	wc.lpszClassName = VX_WINDOW_CLASS;					// クラス名
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION);	// 小さいアイコン

	return(RegisterClassEx(&wc));
}

/* GLの描画に必要なウインドウを作成する */
static HWND vxCreateWindow(int nWidth, int nHeight)
{
	HWND		hWnd;
	DWORD		dwStyle;
	DWORD		dwExStyle;
	
	dwExStyle = 0;
	dwStyle = (WS_POPUP | WS_CLIPCHILDREN);
	//dwStyle |= WS_VISIBLE;		//for Debug
	hWnd = CreateWindowEx(
						dwExStyle,				// 拡張ウィンドウスタイル
						VX_WINDOW_CLASS,		// 登録されているクラス名
						_T(""),					// ウィンドウ名
						dwStyle,				// ウィンドウスタイル
						CW_USEDEFAULT,			// ウィンドウの横方向の位置
						CW_USEDEFAULT,			// ウィンドウの縦方向の位置
						nWidth,					// ウィンドウの幅
						nHeight,				// ウィンドウの高さ
						NULL,					// 親ウィンドウまたはオーナウィンドウのハンドル
						NULL,					// メニューハンドルまたは子識別子
						GetModuleHandle(NULL),	// アプリケーションインスタンスのハンドル
						NULL);					// ウィンドウ作成データ
	return hWnd;
}

static LRESULT CALLBACK	vxWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

