/* "$Id: vxlib.h,v 1.2 2010/10/18 06:28:08 fujimori Exp $";
 *
 *         Original Window System Library for GSHARK series.
 *
 *   Copyright (C) 2010 TAKUMI Corporation. All Rights Reserved.
 *
 * This program is a trade secret of TAKUMI Corporation and it is not to be
 * reproduced, published, disclosed to others, copied, adapted, distributed,
 * or displayed without the prior authorization of TAKUMI Corporation. Licensee 
 * agrees to attach or embed this Notice on all copies of the program,
 * including partial copies or modified versions thereof.
 */

#ifndef VXVLIB_H
#define VXVLIB_H

typedef void                    VXDisplay;
typedef void*                   VXWindow;
typedef void*                   VXPixmap;
typedef int                     VXint;
typedef unsigned int            VXuint;

#define VXAPI                   extern

/* Query Attribute */
#define VX_WIDTH    0x00000001
#define VX_HEIGHT   0x00000002
#define VX_ADDR     0x00000004
#define VX_SWIDTH   0x00000008
#define VX_SHEIGHT  0x00000010
#define VX_DEPTH    0x00000020
#define VX_HWND     0x00000040	//add
#define VX_VALID    0x10000000

/* Error Code */
#define VX_NO_ERROR         0x00000000
#define VX_BAD_ALLOC        0x00000001
#define VX_BAD_DISPLAY      0x00000002
#define VX_BAD_WINDOW       0x00000003
#define VX_BAD_PIXMAP       0x00000004
#define VX_BAD_ATTRIBUTE    0x00000005
#define VX_INVALID_VALUE    0x00000006

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

VXAPI VXDisplay* VXOpenDisplay(char   *id);
VXAPI void       VXCloseDisplay(VXDisplay *dpy);
VXAPI VXWindow   VXCreateWindow(VXDisplay *dpy, VXint x, VXint y, VXint width, VXint height, VXint depth);
VXAPI void       VXDestroyWindow(VXDisplay *dpy, VXWindow win);
VXAPI VXPixmap   VXCreatePixmap(VXDisplay *dpy, VXWindow win, VXint width, VXint height, VXint depth);
VXAPI void       VXFreePixmap(VXDisplay *dpy, VXPixmap pixmap);
VXAPI void       VXQueryDisplay(VXDisplay *dpy, VXuint attribute, VXuint *value);
VXAPI void       VXQueryWindow(VXDisplay *dpy, void *target, VXuint attribute, VXuint *value);
VXAPI VXuint     VXGetError(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* VXLIB_H */

