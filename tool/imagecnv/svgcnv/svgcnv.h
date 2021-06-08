#ifndef __SVGCNV_H__
#define __SVGCNV_H__

#include "output_type.h"

#if 0	//ãåÉpÅ[ÉT
int output_svgdata(Engine::UI::SVG::SvgBuildVisitor *builder, const char *id, OUTPUT_SVG_TYPE type, bool abscoord, FILE *fp);
#endif

int output_svgdata(SvgParser *parser, const char *id, OUTPUT_TYPE type, int flag, FILE *output);


#endif
