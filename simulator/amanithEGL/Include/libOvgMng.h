#include <string>
#include "openvg.h"

#ifndef __LIB_OVG_MNG_H
#define __LIB_OVG_MNG_H


VG_API_CALL std::string foo(std::string bar);
extern "C" void InitLibOvgMng();

extern bool lib_AmanithVG_Load();
extern void lib_AmanithVG_Free();
extern void lib_vgFlush();
extern VGImage eglCreateImageForPbuffer(VGImageFormat format, VGint width, VGint height, VGint size, const void* data, VGbitfield allowedQuality);

extern void wai_sem_amanith();
extern void sig_sem_amanith();

#endif
