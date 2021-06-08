/* ShivaVGに無い関数のスタブ */
#define VG_API_EXPORT
#include <openvg.h>

VG_API_CALL void vgSetColor(VGPaint paint, VGuint rgba)
{
	VGfloat	color[4];
	
	color[0] = (float)((float)(( rgba & 0xFF000000 ) >> 24 ) / 255.0F );
	color[1] = (float)((float)(( rgba & 0x00FF0000 ) >> 16 ) / 255.0F );
	color[2] = (float)((float)(( rgba & 0x0000FF00 ) >>  8 ) / 255.0F );
	color[3] = (float)((float)(( rgba & 0x000000FF )       ) / 255.0F );
	
	vgSetParameterfv( paint, VG_PAINT_COLOR, 4, color );
}

VG_API_CALL void vgDestroyFont (void *font)
{
	//GPIではなくても大丈夫
	return;
}

