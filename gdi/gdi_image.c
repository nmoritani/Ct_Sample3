/*
 * Copyright(c) 2018 Persol AVC Technology.
 */

#include <stdio.h>
#include "gdi.h"
#include "gdi_local.h"
#include "gdi_image.h"


/////// K460?p

#ifdef WIN32_GUI_SIM
#include "../../../../../image/image_resource.c"
#else
#include "../image/image_resource.c"
#endif

GDI_IMAGE_BASE *GdiImageTable[] = {
#ifdef WIN32_GUI_SIM
#include "../../../../../image/initial.def"
#else
#include "../image/initial.def"
#endif
};
	
GDI_IMAGE_BASE* GDI_GetImage(GDI_IMAGE_ID id)
{
	if (id > IMAGE_ID_MAX)
		return NULL;
		
	return GdiImageTable[id];
}

GDI_IMAGE_SVG* GDI_GetImageSVG(GDI_IMAGE_ID id)
{
	if (id > IMAGE_ID_MAX)
		return NULL;
		
	return (GDI_IMAGE_SVG*)GdiImageTable[id];
}

GDI_IMAGE_BITMAP* GDI_GetImageBitmap(GDI_IMAGE_ID id)
{
	if (id > IMAGE_ID_MAX)
		return NULL;
		
	return (GDI_IMAGE_BITMAP*)GdiImageTable[id];
}
