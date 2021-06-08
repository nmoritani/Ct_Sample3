#ifndef DEVANAGARI_RENDER_H
#define DEVANAGARI_RENDER_H

#include "indic_common.h"
#include "DcwLayout.h"

DT32_int deva_render(pLayWrk pwrk, UNI_CHAR* p_unitxt, DT32_int len, UNI_CHAR* p_heap_memory ,
				UNI_CHAR* p_out , DT16_ushort * out_len , GlyphSeq * p_trace , DT16_ushort * count_syllable, ALL_TBL * p_all_table);

#endif /*DEVANAGARI_RENDER_H*/
