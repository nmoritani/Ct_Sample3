#include <string>

#include "amanithvg/openvg.h"
#include "amanithvg/vgplatform.h"

#include "amanithVG.h"
#include "libOvgMng.h"



////////////////////
//以下、OpenVG用のラッパ関数

VGErrorCode vgGetError(void)
{
	wai_sem_amanith();

	VGErrorCode ret = amanith_vg_geterror();
	sig_sem_amanith();
	return ret;
}

void vgFlush(void)
{
	wai_sem_amanith();

	amanith_vg_flush();
	sig_sem_amanith();
}

void vgFinish(void)
{
	wai_sem_amanith();

	amanith_vg_finish();
	sig_sem_amanith();
}

/* Getters and Setters */
void vgSetf(VGParamType type, VGfloat value)
{
	wai_sem_amanith();

	amanith_vg_setf(type, value);
	sig_sem_amanith();
}

void vgSeti(VGParamType type, VGint value)
{
	wai_sem_amanith();

	amanith_vg_seti(type, value);
	sig_sem_amanith();
}

void vgSetfv(VGParamType type, VGint count, const VGfloat *values)
{
	wai_sem_amanith();

	amanith_vg_setfv(type, count, values);
	sig_sem_amanith();
}

void vgSetiv(VGParamType type, VGint count, const VGint *values)
{
	wai_sem_amanith();

	amanith_vg_setiv(type, count, values);
	sig_sem_amanith();
}

VGfloat vgGetf(VGParamType type)
{
	wai_sem_amanith();

	VGfloat ret = amanith_vg_getf(type);
	sig_sem_amanith();
	return ret;
}

VGint vgGeti(VGParamType type)
{
	wai_sem_amanith();

	VGint ret = amanith_vg_geti(type);
	sig_sem_amanith();
	return ret;
}

VGint vgGetVectorSize(VGParamType type)
{
	wai_sem_amanith();

	VGint ret = amanith_vg_getvectorsize(type);
	sig_sem_amanith();
	return ret;
}

void vgGetfv(VGParamType type, VGint count, VGfloat *values)
{
	wai_sem_amanith();

	amanith_vg_getfv(type, count, values);
	sig_sem_amanith();
}

void vgGetiv(VGParamType type, VGint count, VGint *values)
{
	wai_sem_amanith();

	amanith_vg_getiv(type, count, values);
	sig_sem_amanith();
}

void vgSetParameterf(VGHandle object, VGint paramType, VGfloat value)
{
	wai_sem_amanith();

	amanith_vg_setparameterf(object, paramType, value);
	sig_sem_amanith();
}

void vgSetParameteri(VGHandle object, VGint paramType, VGint value)
{
	wai_sem_amanith();

	amanith_vg_setparameteri(object, paramType, value);
	sig_sem_amanith();
}

void vgSetParameterfv(VGHandle object, VGint paramType, VGint count, const VGfloat *values)
{
	wai_sem_amanith();

	amanith_vg_setparameterfv(object, paramType, count, values);
	sig_sem_amanith();
}

void vgSetParameteriv(VGHandle object, VGint paramType, VGint count, const VGint *values)
{
	wai_sem_amanith();

	amanith_vg_setparameteriv(object, paramType, count, values);
	sig_sem_amanith();
}

VGfloat vgGetParameterf(VGHandle object, VGint paramType)
{
	wai_sem_amanith();

	VGfloat ret = amanith_vg_getparameterf(object, paramType);
	sig_sem_amanith();
	return ret;
}

VGint vgGetParameteri(VGHandle object, VGint paramType)
{
	wai_sem_amanith();
	VGint ret = amanith_vg_getparameteri(object, paramType);
	sig_sem_amanith();
	return ret;
}

VGint vgGetParameterVectorSize(VGHandle object, VGint paramType)
{
	wai_sem_amanith();
	VGint ret = amanith_vg_getparametervectorsize(object, paramType);
	sig_sem_amanith();
	return ret;
}

void vgGetParameterfv(VGHandle object, VGint paramType, VGint count, VGfloat *values)
{
	wai_sem_amanith();
	amanith_vg_getparameterfv(object, paramType, count, values);
	sig_sem_amanith();
}

void vgGetParameteriv(VGHandle object, VGint paramType, VGint count, VGint *values)
{
	wai_sem_amanith();
	amanith_vg_getparameteriv(object, paramType, count, values);
	sig_sem_amanith();
}

/* Matrix Manipulation */
void vgLoadIdentity(void)
{
	wai_sem_amanith();
	amanith_vg_loadidentity();
	sig_sem_amanith();
}

void vgLoadMatrix(const VGfloat *m)
{
	wai_sem_amanith();
	amanith_vg_loadmatrix(m);
	sig_sem_amanith();
}

void vgGetMatrix(VGfloat *m)
{
	wai_sem_amanith();
	amanith_vg_getmatrix(m);
	sig_sem_amanith();
}

void vgMultMatrix(const VGfloat *m)
{
	wai_sem_amanith();
	amanith_vg_multmatrix(m);
	sig_sem_amanith();
}

void vgTranslate(VGfloat tx, VGfloat ty)
{
	wai_sem_amanith();
	amanith_vg_translate(tx, ty);
	sig_sem_amanith();
}

void vgScale(VGfloat sx, VGfloat sy)
{
	wai_sem_amanith();
	amanith_vg_scale(sx, sy);
	sig_sem_amanith();
}

void vgShear(VGfloat shx, VGfloat shy)
{
	wai_sem_amanith();
	amanith_vg_shear(shx, shy);
	sig_sem_amanith();
}

void vgRotate(VGfloat angle)
{
	wai_sem_amanith();
	amanith_vg_rotate(angle);
	sig_sem_amanith();
}

/* Masking and Clearing */
#if defined(OPENVG_VERSION_1_1)
void vgMask(VGHandle mask, VGMaskOperation operation, VGint x, VGint y, VGint width, VGint height)
#else
void vgMask(VGImage mask, VGMaskOperation operation, VGint x, VGint y, VGint width, VGint height)
#endif
{
	wai_sem_amanith();
	amanith_vg_mask(mask, operation, x, y, width, height);
	sig_sem_amanith();
}

#if defined(OPENVG_VERSION_1_1)
void vgRenderToMask(VGPath path, VGbitfield paintModes, VGMaskOperation operation)
{
	wai_sem_amanith();
	amanith_vg_rendertomask(path, paintModes, operation);
	sig_sem_amanith();
}

VGMaskLayer vgCreateMaskLayer(VGint width, VGint height)
{
	wai_sem_amanith();
	VGMaskLayer ret = amanith_vg_createmasklayer(width, height);
	sig_sem_amanith();
	return ret;
}

void vgDestroyMaskLayer(VGMaskLayer maskLayer)
{
	wai_sem_amanith();
	amanith_vg_destroymasklayer(maskLayer);
	sig_sem_amanith();
}

void vgFillMaskLayer(VGMaskLayer maskLayer, VGint x, VGint y, VGint width, VGint height, VGfloat value)
{
	wai_sem_amanith();
	amanith_vg_fillmasklayer(maskLayer, x, y, width, height, value);
	sig_sem_amanith();
}

void vgCopyMask(VGMaskLayer maskLayer, VGint dx, VGint dy, VGint sx, VGint sy, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_copymask(maskLayer, dx, dy, sx, sy, width, height);
	sig_sem_amanith();
}
#endif

void vgClear(VGint x, VGint y, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_clear(x, y, width, height);
	sig_sem_amanith();
}

/* Paths */
VGPath vgCreatePath(VGint pathFormat, VGPathDatatype datatype, VGfloat scale, VGfloat bias, VGint segmentCapacityHint, VGint coordCapacityHint, VGbitfield capabilities)
{
	wai_sem_amanith();
	VGPath ret = amanith_vg_createpath(pathFormat, datatype, scale, bias, segmentCapacityHint, coordCapacityHint, capabilities);
	sig_sem_amanith();
	return ret;
}

void vgClearPath(VGPath path, VGbitfield capabilities)
{
	wai_sem_amanith();
	amanith_vg_clearpath(path, capabilities);
	sig_sem_amanith();
}

void vgDestroyPath(VGPath path)
{
	wai_sem_amanith();
	amanith_vg_destroypath(path);
	sig_sem_amanith();
}

void vgRemovePathCapabilities(VGPath path, VGbitfield capabilities)
{
	wai_sem_amanith();
	amanith_vg_removepathcapabilities(path, capabilities);
	sig_sem_amanith();
}

VGbitfield vgGetPathCapabilities(VGPath path)
{
	wai_sem_amanith();
	VGbitfield ret = amanith_vg_getpathcapabilities(path);
	sig_sem_amanith();
	return ret;
}

void vgAppendPath(VGPath dstPath, VGPath srcPath)
{
	wai_sem_amanith();
	amanith_vg_appendpath(dstPath, srcPath);
	sig_sem_amanith();
}

void vgAppendPathData(VGPath dstPath, VGint numSegments, const VGubyte *pathSegments, const void *pathData)
{
	wai_sem_amanith();
	amanith_vg_appendpathdata(dstPath, numSegments, pathSegments, pathData);
	sig_sem_amanith();
}

void vgModifyPathCoords(VGPath dstPath, VGint startIndex, VGint numSegments, const void *pathData)
{
	wai_sem_amanith();
	amanith_vg_modifypathcoords(dstPath, startIndex, numSegments, pathData);
	sig_sem_amanith();
}

void vgTransformPath(VGPath dstPath, VGPath srcPath)
{
	wai_sem_amanith();
	amanith_vg_transformpath(dstPath, srcPath);
	sig_sem_amanith();
}

VGboolean vgInterpolatePath(VGPath dstPath, VGPath startPath, VGPath endPath, VGfloat amount)
{
	wai_sem_amanith();
	VGboolean ret = amanith_vg_interpolatepath(dstPath, startPath, endPath, amount);
	sig_sem_amanith();
	return ret;
}

VGfloat vgPathLength(VGPath path, VGint startSegment, VGint numSegments)
{
	wai_sem_amanith();
	VGfloat ret = amanith_vg_pathlength(path, startSegment, numSegments);
	sig_sem_amanith();
	return ret;
}

void vgPointAlongPath(VGPath path, VGint startSegment, VGint numSegments, VGfloat distance, VGfloat *x, VGfloat *y, VGfloat *tangentX, VGfloat *tangentY)
{
	wai_sem_amanith();
	amanith_vg_pointalongpath(path, startSegment, numSegments, distance, x, y, tangentX, tangentY);
	sig_sem_amanith();
}

void vgPathBounds(VGPath path, VGfloat *minX, VGfloat *minY, VGfloat *width, VGfloat *height)
{
	wai_sem_amanith();
	amanith_vg_pathbounds(path, minX, minY, width, height);
	sig_sem_amanith();
}

void vgPathTransformedBounds(VGPath path, VGfloat *minX, VGfloat *minY, VGfloat *width, VGfloat *height)
{
	wai_sem_amanith();
	amanith_vg_pathtransformedbounds(path, minX, minY, width, height);
	sig_sem_amanith();
}

void vgDrawPath(VGPath path, VGbitfield paintModes)
{
	wai_sem_amanith();
	amanith_vg_drawpath(path, paintModes);
	sig_sem_amanith();
}

/* Paint */
VGPaint vgCreatePaint(void)
{
	wai_sem_amanith();
	VGPaint ret = amanith_vg_createpaint();
	sig_sem_amanith();
	return ret;
}

void vgDestroyPaint(VGPaint paint)
{
	wai_sem_amanith();
	amanith_vg_destroypaint(paint);
	sig_sem_amanith();
}

void vgSetPaint(VGPaint paint, VGbitfield paintModes)
{
	wai_sem_amanith();
	amanith_vg_setpaint(paint, paintModes);
	sig_sem_amanith();
}

VGPaint vgGetPaint(VGPaintMode paintMode)
{
	wai_sem_amanith();
	VGPaint ret = amanith_vg_getpaint(paintMode);
	sig_sem_amanith();
	return ret;
}

void vgSetColor(VGPaint paint, VGuint rgba)
{
	wai_sem_amanith();
	amanith_vg_setcolor(paint, rgba);
	sig_sem_amanith();
}

VGuint vgGetColor(VGPaint paint)
{
	wai_sem_amanith();
	VGuint ret = amanith_vg_getcolor(paint);
	sig_sem_amanith();
	return ret;
}

void vgPaintPattern(VGPaint paint, VGImage pattern)
{
	wai_sem_amanith();
	amanith_vg_paintpattern(paint, pattern);
	sig_sem_amanith();
}

/* Images */
VGImage vgCreateImage(VGImageFormat format, VGint width, VGint height, VGbitfield allowedQuality)
{
	wai_sem_amanith();
	VGImage ret = amanith_vg_createimage(format, width, height, allowedQuality);
	sig_sem_amanith();
	return ret;
}

void vgDestroyImage(VGImage image)
{
	wai_sem_amanith();
	amanith_vg_destroyimage(image);
	sig_sem_amanith();
}

void vgClearImage(VGImage image, VGint x, VGint y, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_clearimage(image, x, y, width, height);
	sig_sem_amanith();
}

void vgImageSubData(VGImage image, const void *data, VGint dataStride, VGImageFormat dataFormat, VGint x, VGint y, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_imagesubdata(image, data, dataStride, dataFormat, x, y, width, height);
	sig_sem_amanith();
}

void vgGetImageSubData(VGImage image, void *data, VGint dataStride, VGImageFormat dataFormat, VGint x, VGint y, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_getimagesubdata(image, data, dataStride, dataFormat, x, y, width, height);
	sig_sem_amanith();
}

VGImage vgChildImage(VGImage parent, VGint x, VGint y, VGint width, VGint height)
{
	wai_sem_amanith();
	VGImage ret = amanith_vg_childimage(parent, x, y, width, height);
	sig_sem_amanith();
	return ret;
}

VGImage vgGetParent(VGImage image)
{
	wai_sem_amanith();
	VGImage ret = amanith_vg_getparent(image);
	sig_sem_amanith();
	return ret;
}

void vgCopyImage(VGImage dst, VGint dx, VGint dy, VGImage src, VGint sx, VGint sy, VGint width, VGint height, VGboolean dither)
{
	wai_sem_amanith();
	amanith_vg_copyimage(dst, dx, dy, src, sx, sy, width, height, dither);
	sig_sem_amanith();
}

void vgDrawImage(VGImage image)
{
	wai_sem_amanith();
	amanith_vg_drawimage(image);
	sig_sem_amanith();
}

void vgSetPixels(VGint dx, VGint dy, VGImage src, VGint sx, VGint sy, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_setpixels(dx, dy, src, sx, sy, width, height);
	sig_sem_amanith();
}

void vgWritePixels(const void *data, VGint dataStride, VGImageFormat dataFormat, VGint dx, VGint dy, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_writepixels(data, dataStride, dataFormat, dx, dy, width, height);
	sig_sem_amanith();
}

void vgGetPixels(VGImage dst, VGint dx, VGint dy, VGint sx, VGint sy, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_getpixels(dst, dx, dy, sx, sy, width, height);
	sig_sem_amanith();
}

void vgReadPixels(void *data, VGint dataStride, VGImageFormat dataFormat, VGint sx, VGint sy, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_readpixels(data, dataStride, dataFormat, sx, sy, width, height);
	sig_sem_amanith();
}

void vgCopyPixels(VGint dx, VGint dy, VGint sx, VGint sy, VGint width, VGint height)
{
	wai_sem_amanith();
	amanith_vg_copypixels(dx, dy, sx, sy, width, height);
	sig_sem_amanith();
}

#if defined(OPENVG_VERSION_1_1)
/* Text */
VGFont vgCreateFont(VGint glyphCapacityHint)
{
	wai_sem_amanith();
	VGFont ret = amanith_vg_createfont(glyphCapacityHint);
	sig_sem_amanith();
	return ret;
}

void vgDestroyFont(VGFont font)
{
	wai_sem_amanith();
	amanith_vg_destroyfont(font);
	sig_sem_amanith();
}

void vgSetGlyphToPath(VGFont font, VGuint glyphIndex, VGPath path, VGboolean isHinted, const VGfloat glyphOrigin[2], const VGfloat escapement[2])
{
	wai_sem_amanith();
	amanith_vg_setglyphtopath(font, glyphIndex, path, isHinted, glyphOrigin, escapement);
	sig_sem_amanith();
}

void vgSetGlyphToImage(VGFont font, VGuint glyphIndex, VGImage image, const VGfloat glyphOrigin[2], const VGfloat escapement[2])
{
	wai_sem_amanith();
	amanith_vg_setglyphtoimage(font, glyphIndex, image, glyphOrigin, escapement);
	sig_sem_amanith();
}

void vgClearGlyph(VGFont font, VGuint glyphIndex)
{
	wai_sem_amanith();
	amanith_vg_clearglyph(font, glyphIndex);
	sig_sem_amanith();
}

void vgDrawGlyph(VGFont font, VGuint glyphIndex, VGbitfield paintModes, VGboolean allowAutoHinting)
{
	wai_sem_amanith();
	amanith_vg_drawglyph(font, glyphIndex, paintModes, allowAutoHinting);
	sig_sem_amanith();
}

void vgDrawGlyphs(VGFont font, VGint glyphCount, const VGuint *glyphIndices, const VGfloat *adjustments_x, const VGfloat *adjustments_y, VGbitfield paintModes, VGboolean allowAutoHinting)
{
	wai_sem_amanith();
	amanith_vg_drawglyphs(font, glyphCount, glyphIndices, adjustments_x, adjustments_y, paintModes, allowAutoHinting);
	sig_sem_amanith();
}
#endif

/* Image Filters */
void vgColorMatrix(VGImage dst, VGImage src, const VGfloat *matrix)
{
	wai_sem_amanith();
	amanith_vg_colormatrix(dst, src, matrix);
	sig_sem_amanith();
}

void vgConvolve(VGImage dst, VGImage src, VGint kernelWidth, VGint kernelHeight, VGint shiftX, VGint shiftY, const VGshort *kernel, VGfloat scale, VGfloat bias, VGTilingMode tilingMode)
{
	wai_sem_amanith();
	amanith_vg_convolve(dst, src, kernelWidth, kernelHeight, shiftX, shiftY, kernel, scale, bias, tilingMode);
	sig_sem_amanith();
}

void vgSeparableConvolve(VGImage dst, VGImage src, VGint kernelWidth, VGint kernelHeight, VGint shiftX, VGint shiftY, const VGshort *kernelX, const VGshort *kernelY, VGfloat scale, VGfloat bias, VGTilingMode tilingMode)
{
	wai_sem_amanith();
	amanith_vg_separableconvolve(dst, src, kernelWidth, kernelHeight, shiftX, shiftY, kernelX, kernelY, scale, bias, tilingMode);
	sig_sem_amanith();
}

void vgGaussianBlur(VGImage dst, VGImage src, VGfloat stdDeviationX, VGfloat stdDeviationY, VGTilingMode tilingMode)
{
	wai_sem_amanith();
	amanith_vg_gaussianblur(dst, src, stdDeviationX, stdDeviationY, tilingMode);
	sig_sem_amanith();
}

void vgLookup(VGImage dst, VGImage src, const VGubyte *redLUT, const VGubyte *greenLUT, const VGubyte *blueLUT, const VGubyte *alphaLUT, VGboolean outputLinear, VGboolean outputPremultiplied)
{
	wai_sem_amanith();
	amanith_vg_lookup(dst, src, redLUT, greenLUT, blueLUT, alphaLUT, outputLinear, outputPremultiplied);
	sig_sem_amanith();
}

void vgLookupSingle(VGImage dst, VGImage src, const VGuint *lookupTable, VGImageChannel sourceChannel, VGboolean outputLinear, VGboolean outputPremultiplied)
{
	wai_sem_amanith();
	amanith_vg_lookupsingle(dst, src, lookupTable, sourceChannel, outputLinear, outputPremultiplied);
	sig_sem_amanith();
}

/* Hardware Queries */
VGHardwareQueryResult vgHardwareQuery(VGHardwareQueryType key, VGint setting)
{
	wai_sem_amanith();
	VGHardwareQueryResult ret = amanith_vg_hardwarequery(key, setting);
	sig_sem_amanith();
	return ret;
}

/* Renderer and Extension Information */
const VGubyte * vgGetString(VGStringID name)
{
	wai_sem_amanith();
	const VGubyte * ret = amanith_vg_getstring(name);
	sig_sem_amanith();
	return ret;
}

VGImage vgCreateImageStandardDataDMP(VGImageFormat format, VGint width, VGint height, VGint size, const void* data, VGbitfield allowedQuality)
{
	wai_sem_amanith();
	//※ 注意：シミュレータのvgCreateImageStandardDataDMP()はDrawableの描画専用なので、他では使用しないこと！
	VGImage ret = eglCreateImageForPbuffer(format, width, height, size, data, allowedQuality);
	sig_sem_amanith();
	return ret;
}
