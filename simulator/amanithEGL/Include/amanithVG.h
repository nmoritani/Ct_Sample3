#include <string>

#include "amanithvg/openvg.h"

#ifndef __AMANITH_VG_H
#define __AMANITH_VG_H


typedef VGErrorCode VG_API_ENTRY (*VGGETERROR)(void) ;

typedef void VG_API_ENTRY (*VGFLUSH)(void) ;

typedef void VG_API_ENTRY (*VGFINISH)(void) ;

/* Getters and Setters */
typedef void VG_API_ENTRY (*VGSETF)(VGParamType type,
                                     VGfloat value) ;

typedef void VG_API_ENTRY (*VGSETI)(VGParamType type,
                                     VGint value) ;

typedef void VG_API_ENTRY (*VGSETFV)(VGParamType type,
                                      VGint count,
                                      const VGfloat *values) ;

typedef void VG_API_ENTRY (*VGSETIV)(VGParamType type,
                                      VGint count,
                                      const VGint *values) ;

typedef VGfloat VG_API_ENTRY (*VGGETF)(VGParamType type) ;

typedef VGint VG_API_ENTRY (*VGGETI)(VGParamType type) ;

typedef VGint VG_API_ENTRY (*VGGETVECTORSIZE)(VGParamType type) ;

typedef void VG_API_ENTRY (*VGGETFV)(VGParamType type,
                                      VGint count,
                                      VGfloat *values) ;

typedef void VG_API_ENTRY (*VGGETIV)(VGParamType type,
                                      VGint count,
                                      VGint *values) ;

typedef void VG_API_ENTRY (*VGSETPARAMETERF)(VGHandle object,
                                              VGint paramType,
                                              VGfloat value) ;

typedef void VG_API_ENTRY (*VGSETPARAMETERI)(VGHandle object,
                                              VGint paramType,
                                              VGint value) ;

typedef void VG_API_ENTRY (*VGSETPARAMETERFV)(VGHandle object,
                                               VGint paramType,
                                               VGint count,
                                               const VGfloat *values) ;

typedef void VG_API_ENTRY (*VGSETPARAMETERIV)(VGHandle object,
                                               VGint paramType,
                                               VGint count,
                                               const VGint *values) ;

typedef VGfloat VG_API_ENTRY (*VGGETPARAMETERF)(VGHandle object,
                                                 VGint paramType) ;

typedef VGint VG_API_ENTRY (*VGGETPARAMETERI)(VGHandle object,
                                               VGint paramType) ;

typedef VGint VG_API_ENTRY (*VGGETPARAMETERVECTORSIZE)(VGHandle object,
                                                        VGint paramType) ;

typedef void VG_API_ENTRY (*VGGETPARAMETERFV)(VGHandle object,
                                               VGint paramType,
                                               VGint count,
                                               VGfloat *values) ;

typedef void VG_API_ENTRY (*VGGETPARAMETERIV)(VGHandle object,
                                               VGint paramType,
                                               VGint count,
                                               VGint *values) ;

/* Matrix Manipulation */
typedef void VG_API_ENTRY (*VGLOADIDENTITY)(void) ;

typedef void VG_API_ENTRY (*VGLOADMATRIX)(const VGfloat *m) ;

typedef void VG_API_ENTRY (*VGGETMATRIX)(VGfloat *m) ;

typedef void VG_API_ENTRY (*VGMULTMATRIX)(const VGfloat *m) ;

typedef void VG_API_ENTRY (*VGTRANSLATE)(VGfloat tx,
                                          VGfloat ty) ;

typedef void VG_API_ENTRY (*VGSCALE)(VGfloat sx,
                                      VGfloat sy) ;

typedef void VG_API_ENTRY (*VGSHEAR)(VGfloat shx,
                                      VGfloat shy) ;

typedef void VG_API_ENTRY (*VGROTATE)(VGfloat angle) ;

/* Masking and Clearing */
#if defined(OPENVG_VERSION_1_1)
typedef void VG_API_ENTRY (*VGMASK)(VGHandle mask,
#else
typedef void VG_API_ENTRY (*VGMASK)(VGImage mask,
#endif
                                     VGMaskOperation operation,
                                     VGint x,
                                     VGint y,
                                     VGint width,
                                     VGint height) ;

#if defined(OPENVG_VERSION_1_1)
typedef void VG_API_ENTRY (*VGRENDERTOMASK)(VGPath path,
                                             VGbitfield paintModes,
                                             VGMaskOperation operation) ;

typedef VGMaskLayer VG_API_ENTRY (*VGCREATEMASKLAYER)(VGint width,
                                                       VGint height) ;

typedef void VG_API_ENTRY (*VGDESTROYMASKLAYER)(VGMaskLayer maskLayer) ;

typedef void VG_API_ENTRY (*VGFILLMASKLAYER)(VGMaskLayer maskLayer,
                                              VGint x,
                                              VGint y,
                                              VGint width,
                                              VGint height,
                                              VGfloat value) ;

typedef void VG_API_ENTRY (*VGCOPYMASK)(VGMaskLayer maskLayer,
                                         VGint dx,
                                         VGint dy,
                                         VGint sx,
                                         VGint sy,
                                         VGint width,
                                         VGint height) ;
#endif

typedef void VG_API_ENTRY (*VGCLEAR)(VGint x,
                                      VGint y,
                                      VGint width,
                                      VGint height) ;

/* Paths */
typedef VGPath VG_API_ENTRY (*VGCREATEPATH)(VGint pathFormat,
                                             VGPathDatatype datatype,
                                             VGfloat scale,
                                             VGfloat bias,
                                             VGint segmentCapacityHint,
                                             VGint coordCapacityHint,
                                             VGbitfield capabilities) ;

typedef void VG_API_ENTRY (*VGCLEARPATH)(VGPath path,
                                          VGbitfield capabilities) ;

typedef void VG_API_ENTRY (*VGDESTROYPATH)(VGPath path) ;

typedef void VG_API_ENTRY (*VGREMOVEPATHCAPABILITIES)(VGPath path,
                                                       VGbitfield capabilities) ;

typedef VGbitfield VG_API_ENTRY (*VGGETPATHCAPABILITIES)(VGPath path) ;

typedef void VG_API_ENTRY (*VGAPPENDPATH)(VGPath dstPath,
                                           VGPath srcPath) ;

typedef void VG_API_ENTRY (*VGAPPENDPATHDATA)(VGPath dstPath,
                                               VGint numSegments,
                                               const VGubyte *pathSegments,
                                               const void *pathData) ;

typedef void VG_API_ENTRY (*VGMODIFYPATHCOORDS)(VGPath dstPath,
                                                 VGint startIndex,
                                                 VGint numSegments,
                                                 const void *pathData) ;

typedef void VG_API_ENTRY (*VGTRANSFORMPATH)(VGPath dstPath,
                                              VGPath srcPath) ;

typedef VGboolean VG_API_ENTRY (*VGINTERPOLATEPATH)(VGPath dstPath,
                                                     VGPath startPath,
                                                     VGPath endPath,
                                                     VGfloat amount) ;

typedef VGfloat VG_API_ENTRY (*VGPATHLENGTH)(VGPath path,
                                              VGint startSegment,
                                              VGint numSegments) ;

typedef void VG_API_ENTRY (*VGPOINTALONGPATH)(VGPath path,
                                               VGint startSegment,
                                               VGint numSegments,
                                               VGfloat distance,
                                               VGfloat *x,
                                               VGfloat *y,
                                               VGfloat *tangentX,
                                               VGfloat *tangentY) ;

typedef void VG_API_ENTRY (*VGPATHBOUNDS)(VGPath path,
                                           VGfloat *minX,
                                           VGfloat *minY,
                                           VGfloat *width,
                                           VGfloat *height) ;

typedef void VG_API_ENTRY (*VGPATHTRANSFORMEDBOUNDS)(VGPath path,
                                                      VGfloat *minX,
                                                      VGfloat *minY,
                                                      VGfloat *width,
                                                      VGfloat *height) ;

typedef void VG_API_ENTRY (*VGDRAWPATH)(VGPath path,
                                         VGbitfield paintModes) ;

/* Paint */
typedef VGPaint VG_API_ENTRY (*VGCREATEPAINT)(void) ;

typedef void VG_API_ENTRY (*VGDESTROYPAINT)(VGPaint paint) ;

typedef void VG_API_ENTRY (*VGSETPAINT)(VGPaint paint,
                                         VGbitfield paintModes) ;

typedef VGPaint VG_API_ENTRY (*VGGETPAINT)(VGPaintMode paintMode);

typedef void VG_API_ENTRY (*VGSETCOLOR)(VGPaint paint,
                                         VGuint rgba) ;

typedef VGuint VG_API_ENTRY (*VGGETCOLOR)(VGPaint paint) ;

typedef void VG_API_ENTRY (*VGPAINTPATTERN)(VGPaint paint,
                                             VGImage pattern) ;

/* Images */
typedef VGImage VG_API_ENTRY (*VGCREATEIMAGE)(VGImageFormat format,
                                               VGint width,
                                               VGint height,
                                               VGbitfield allowedQuality) ;

typedef void VG_API_ENTRY (*VGDESTROYIMAGE)(VGImage image) ;

typedef void VG_API_ENTRY (*VGCLEARIMAGE)(VGImage image,
                                           VGint x,
                                           VGint y,
                                           VGint width,
                                           VGint height) ;

typedef void VG_API_ENTRY (*VGIMAGESUBDATA)(VGImage image,
                                             const void *data,
                                             VGint dataStride,
                                             VGImageFormat dataFormat,
                                             VGint x,
                                             VGint y,
                                             VGint width,
                                             VGint height) ;

typedef void VG_API_ENTRY (*VGGETIMAGESUBDATA)(VGImage image,
                                                void *data,
                                                VGint dataStride,
                                                VGImageFormat dataFormat,
                                                VGint x,
                                                VGint y,
                                                VGint width,
                                                VGint height) ;

typedef VGImage VG_API_ENTRY (*VGCHILDIMAGE)(VGImage parent,
                                              VGint x,
                                              VGint y,
                                              VGint width,
                                              VGint height) ;

typedef VGImage VG_API_ENTRY (*VGGETPARENT)(VGImage image) ;

typedef void VG_API_ENTRY (*VGCOPYIMAGE)(VGImage dst,
                                          VGint dx,
                                          VGint dy,
                                          VGImage src,
                                          VGint sx,
                                          VGint sy,
                                          VGint width,
                                          VGint height,
                                          VGboolean dither) ;

typedef void VG_API_ENTRY (*VGDRAWIMAGE)(VGImage image) ;

typedef void VG_API_ENTRY (*VGSETPIXELS)(VGint dx,
                                          VGint dy,
                                          VGImage src,
                                          VGint sx,
                                          VGint sy,
                                          VGint width,
                                          VGint height) ;

typedef void VG_API_ENTRY (*VGWRITEPIXELS)(const void *data,
                                            VGint dataStride,
                                            VGImageFormat dataFormat,
                                            VGint dx,
                                            VGint dy,
                                            VGint width,
                                            VGint height) ;

typedef void VG_API_ENTRY (*VGGETPIXELS)(VGImage dst,
                                          VGint dx,
                                          VGint dy,
                                          VGint sx,
                                          VGint sy,
                                          VGint width,
                                          VGint height) ;

typedef void VG_API_ENTRY (*VGREADPIXELS)(void *data,
                                           VGint dataStride,
                                           VGImageFormat dataFormat,
                                           VGint sx,
                                           VGint sy,
                                           VGint width,
                                           VGint height) ;

typedef void VG_API_ENTRY (*VGCOPYPIXELS)(VGint dx,
                                           VGint dy,
                                           VGint sx,
                                           VGint sy,
                                           VGint width,
                                           VGint height) ;

#if defined(OPENVG_VERSION_1_1)
/* Text */
typedef VGFont VG_API_ENTRY (*VGCREATEFONT)(VGint glyphCapacityHint) ;

typedef void VG_API_ENTRY (*VGDESTROYFONT)(VGFont font) ;

typedef void VG_API_ENTRY (*VGSETGLYPHTOPATH)(VGFont font,
                                               VGuint glyphIndex,
                                               VGPath path,
                                               VGboolean isHinted,
                                               const VGfloat glyphOrigin[2],
                                               const VGfloat escapement[2]) ;

typedef void VG_API_ENTRY (*VGSETGLYPHTOIMAGE)(VGFont font,
                                                VGuint glyphIndex,
                                                VGImage image,
                                                const VGfloat glyphOrigin[2],
                                                const VGfloat escapement[2]) ;

typedef void VG_API_ENTRY (*VGCLEARGLYPH)(VGFont font,
                                           VGuint glyphIndex) ;

typedef void VG_API_ENTRY (*VGDRAWGLYPH)(VGFont font,
                                          VGuint glyphIndex,
                                          VGbitfield paintModes,
                                          VGboolean allowAutoHinting) ;

typedef void VG_API_ENTRY (*VGDRAWGLYPHs)(VGFont font,
                                           VGint glyphCount,
                                           const VGuint *glyphIndices,
                                           const VGfloat *adjustments_x,
                                           const VGfloat *adjustments_y,
                                           VGbitfield paintModes,
                                           VGboolean allowAutoHinting) ;
#endif

/* Image Filters */
typedef void VG_API_ENTRY (*VGCOLORMATRIX)(VGImage dst,
                                            VGImage src,
                                            const VGfloat *matrix) ;

typedef void VG_API_ENTRY (*VGCONVOLVE)(VGImage dst,
                                         VGImage src,
                                         VGint kernelWidth,
                                         VGint kernelHeight,
                                         VGint shiftX,
                                         VGint shiftY,
                                         const VGshort *kernel,
                                         VGfloat scale,
                                         VGfloat bias,
                                         VGTilingMode tilingMode) ;

typedef void VG_API_ENTRY (*VGSEPARABLECONVOLVE)(VGImage dst,
                                                  VGImage src,
                                                  VGint kernelWidth,
                                                  VGint kernelHeight,
                                                  VGint shiftX,
                                                  VGint shiftY,
                                                  const VGshort *kernelX,
                                                  const VGshort *kernelY,
                                                  VGfloat scale,
                                                  VGfloat bias,
                                                  VGTilingMode tilingMode) ;

typedef void VG_API_ENTRY (*VGGAUSSIANBLUR)(VGImage dst,
                                             VGImage src,
                                             VGfloat stdDeviationX,
                                             VGfloat stdDeviationY,
                                             VGTilingMode tilingMode) ;

typedef void VG_API_ENTRY (*VGLOOKUP)(VGImage dst,
                                       VGImage src,
                                       const VGubyte *redLUT,
                                       const VGubyte *greenLUT,
                                       const VGubyte *blueLUT,
                                       const VGubyte *alphaLUT,
                                       VGboolean outputLinear,
                                       VGboolean outputPremultiplied) ;

typedef void VG_API_ENTRY (*VGLOOKUPSINGLE)(VGImage dst,
                                             VGImage src,
                                             const VGuint *lookupTable,
                                             VGImageChannel sourceChannel,
                                             VGboolean outputLinear,
                                             VGboolean outputPremultiplied) ;

/* Hardware Queries */
typedef VGHardwareQueryResult VG_API_ENTRY (*VGHARDWAREQUERY)(VGHardwareQueryType key,
                                                               VGint setting) ;

/* Renderer and Extension Information */
typedef const VGubyte * VG_API_ENTRY (*VGGETSTRING)(VGStringID name);

typedef void VG_API_ENTRY (*VGPOSTSWAPBUFFERSAM)(void);

typedef void* VG_API_ENTRY (*VGPRIVSURFACECREATEAM)(VGint width,
													VGint height,
													VGboolean linearColorSpace,
													VGboolean alphaPremultiplied,
													VGboolean alphaMask);
typedef VGint VG_API_ENTRY (*VGPRIVGETSURFACEWIDTHAM)(const void *_surface);
typedef VGint VG_API_ENTRY (*VGPRIVGETSURFACEHEIGHTAM)(const void *_surface);
typedef VGImageFormat VG_API_ENTRY (*VGPRIVGETSURFACEFORMATAM)(const void *_surface);
typedef const VGubyte* VG_API_ENTRY (*VGPRIVGETSURFACEPIXELSAM)(const void *_surface);
typedef void* VG_API_ENTRY (*VGPRIVCONTEXTCREATEAM)(void *_sharedContext);

typedef void VG_API_ENTRY (*VGPRIVSURFACEDESTROYAM)(void *_surface);
typedef VGboolean VG_API_ENTRY(*VGPRIVMAKECURRENTAM)(void *_context, void *_surface);
typedef void VG_API_ENTRY (*VGPRIVCONTEXTDESTROYAM)(void *_context);
typedef VGboolean VG_API_ENTRY (*VGRESIZESURFACEAM)(VGint surfaceWidth, VGint surfaceHeight);

typedef void* VG_API_ENTRY (*VGPRIVSURFACECREATEFROMIMAGEAM)(VGImage image, VGboolean alphaMask);


//関数ポインタ呼び出し用定義
extern VGGETERROR	amanith_vg_geterror;
extern VGFLUSH	amanith_vg_flush;
extern VGFINISH	amanith_vg_finish;
extern VGSETF	amanith_vg_setf;
extern VGSETI	amanith_vg_seti;
extern VGSETFV	amanith_vg_setfv;
extern VGSETIV	amanith_vg_setiv;
extern VGGETF	amanith_vg_getf;
extern VGGETI	amanith_vg_geti;
extern VGGETVECTORSIZE	amanith_vg_getvectorsize;
extern VGGETFV	amanith_vg_getfv;
extern VGGETIV	amanith_vg_getiv;
extern VGSETPARAMETERF	amanith_vg_setparameterf;
extern VGSETPARAMETERI	amanith_vg_setparameteri;
extern VGSETPARAMETERFV	amanith_vg_setparameterfv;
extern VGSETPARAMETERIV	amanith_vg_setparameteriv;
extern VGGETPARAMETERF	amanith_vg_getparameterf;
extern VGGETPARAMETERI	amanith_vg_getparameteri;
extern VGGETPARAMETERVECTORSIZE	amanith_vg_getparametervectorsize;
extern VGGETPARAMETERFV	amanith_vg_getparameterfv;
extern VGGETPARAMETERIV	amanith_vg_getparameteriv;
extern VGLOADIDENTITY	amanith_vg_loadidentity;
extern VGLOADMATRIX	amanith_vg_loadmatrix;
extern VGGETMATRIX	amanith_vg_getmatrix;
extern VGMULTMATRIX	amanith_vg_multmatrix;
extern VGTRANSLATE	amanith_vg_translate;
extern VGSCALE	amanith_vg_scale;
extern VGSHEAR	amanith_vg_shear;
extern VGROTATE	amanith_vg_rotate;
#if defined(OPENVG_VERSION_1_1)	
extern VGMASK	amanith_vg_mask;
#else	
extern VGMASK	amanith_vg_mask;
#endif	
#if defined(OPENVG_VERSION_1_1)
extern VGRENDERTOMASK	amanith_vg_rendertomask;
extern VGCREATEMASKLAYER	amanith_vg_createmasklayer;
extern VGDESTROYMASKLAYER	amanith_vg_destroymasklayer;
extern VGFILLMASKLAYER	amanith_vg_fillmasklayer;
extern VGCOPYMASK	amanith_vg_copymask;
#endif	
extern VGCLEAR	amanith_vg_clear;
extern VGCREATEPATH	amanith_vg_createpath;
extern VGCLEARPATH	amanith_vg_clearpath;
extern VGDESTROYPATH	amanith_vg_destroypath;
extern VGREMOVEPATHCAPABILITIES	amanith_vg_removepathcapabilities;
extern VGGETPATHCAPABILITIES	amanith_vg_getpathcapabilities;
extern VGAPPENDPATH	amanith_vg_appendpath;
extern VGAPPENDPATHDATA	amanith_vg_appendpathdata;
extern VGMODIFYPATHCOORDS	amanith_vg_modifypathcoords;
extern VGTRANSFORMPATH	amanith_vg_transformpath;
extern VGINTERPOLATEPATH	amanith_vg_interpolatepath;
extern VGPATHLENGTH	amanith_vg_pathlength;
extern VGPOINTALONGPATH	amanith_vg_pointalongpath;
extern VGPATHBOUNDS	amanith_vg_pathbounds;
extern VGPATHTRANSFORMEDBOUNDS	amanith_vg_pathtransformedbounds;
extern VGDRAWPATH	amanith_vg_drawpath;
extern VGCREATEPAINT	amanith_vg_createpaint;
extern VGDESTROYPAINT	amanith_vg_destroypaint;
extern VGSETPAINT	amanith_vg_setpaint;
extern VGGETPAINT	amanith_vg_getpaint;
extern VGSETCOLOR	amanith_vg_setcolor;
extern VGGETCOLOR	amanith_vg_getcolor;
extern VGPAINTPATTERN	amanith_vg_paintpattern;
extern VGCREATEIMAGE	amanith_vg_createimage;
extern VGDESTROYIMAGE	amanith_vg_destroyimage;
extern VGCLEARIMAGE	amanith_vg_clearimage;
extern VGIMAGESUBDATA	amanith_vg_imagesubdata;
extern VGGETIMAGESUBDATA	amanith_vg_getimagesubdata;
extern VGCHILDIMAGE	amanith_vg_childimage;
extern VGGETPARENT	amanith_vg_getparent;
extern VGCOPYIMAGE	amanith_vg_copyimage;
extern VGDRAWIMAGE	amanith_vg_drawimage;
extern VGSETPIXELS	amanith_vg_setpixels;
extern VGWRITEPIXELS	amanith_vg_writepixels;
extern VGGETPIXELS	amanith_vg_getpixels;
extern VGREADPIXELS	amanith_vg_readpixels;
extern VGCOPYPIXELS	amanith_vg_copypixels;
#if defined(OPENVG_VERSION_1_1)	
extern VGCREATEFONT	amanith_vg_createfont;
extern VGDESTROYFONT	amanith_vg_destroyfont;
extern VGSETGLYPHTOPATH	amanith_vg_setglyphtopath;
extern VGSETGLYPHTOIMAGE	amanith_vg_setglyphtoimage;
extern VGCLEARGLYPH	amanith_vg_clearglyph;
extern VGDRAWGLYPH	amanith_vg_drawglyph;
extern VGDRAWGLYPHs	amanith_vg_drawglyphs;
#endif	
extern VGCOLORMATRIX	amanith_vg_colormatrix;
extern VGCONVOLVE	amanith_vg_convolve;
extern VGSEPARABLECONVOLVE	amanith_vg_separableconvolve;
extern VGGAUSSIANBLUR	amanith_vg_gaussianblur;
extern VGLOOKUP	amanith_vg_lookup;
extern VGLOOKUPSINGLE	amanith_vg_lookupsingle;
extern VGHARDWAREQUERY	amanith_vg_hardwarequery;
extern VGGETSTRING	amanith_vg_getstring;
extern VGPOSTSWAPBUFFERSAM		amanith_vg_postswapbuffersAM;
extern VGPRIVSURFACECREATEAM	amanith_vg_privsurfacecreateAM;
extern VGPRIVGETSURFACEWIDTHAM	amanith_vg_privgetsurfacewidthAM;
extern VGPRIVGETSURFACEHEIGHTAM	amanith_vg_privgetsurfaceheightAM;
extern VGPRIVGETSURFACEFORMATAM	amanith_vg_privgetsurfaceformatAM;
extern VGPRIVGETSURFACEPIXELSAM	amanith_vg_privgetsurfacepixelsAM;
extern VGPRIVCONTEXTCREATEAM	amanith_vg_privcontextcreateAM;
extern VGPRIVSURFACEDESTROYAM	amanith_vg_privsurfacedestroyAM;
extern VGPRIVMAKECURRENTAM		amanith_vg_privmakecurrentAM;
extern VGPRIVCONTEXTDESTROYAM	amanith_vg_privcontextdestroyAM;
extern VGRESIZESURFACEAM		amanith_vg_resizesurfaceAM;
extern VGPRIVSURFACECREATEFROMIMAGEAM	amanith_vg_privsurfacecreatefromimageAM;



#endif
