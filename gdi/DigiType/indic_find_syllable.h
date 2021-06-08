#ifndef INDIC_FIND_SYLLABLE_H
#define INDIC_FIND_SYLLABLE_H

#include "indic_common.h"

typedef DT16_short SYLLABLE_STATE;

#define MASK_CLASS        0x00ffU
#define MASK_LOCATION     0x3f00U
#define MASK_PREVIOUS	  0xC000U	
	
/**/
#define C_RESERVED                0x0000U
#define C_SIGN_NESAL              0x0001U
#define C_INDEPENDENT_VOWEL       0x0002U
#define C_CONSONANT_NUKTA         0x0003U
#define C_CONSONANT               0x0004U
#define C_SIGN_NUKTA              0x0005U
#define C_SOLE_SYLLABLE           0x0006U
#define C_SIGN_VIRAMA             0x0007U
#define C_DEPENDENT_VOWEL         0x0008U
#define C_SIGN_STRESS             0x0009U
#define C_SIGN_ACCENT             0x000aU

/*TAMIL*/
#define C_LENGTH_MARK             0x000bU 
#define C_BOTH_VOWEL_LEFT         0x000cU
#define C_BOTH_VOWEL_RIGHT        0x000dU

/*LANG_LOCATION*/
#define L_DEVENAGARI              0x0100U
#define L_BENGALI                 0x0200U
#define L_GURMUKHI                0x0300U
#define L_GUJARATI                0x0400U
#define L_ORIYA                   0x0500U
#define L_TAMIL                   0x0600U
#define L_TELUGU                  0x0700U
#define L_KANNADA                 0x0800U
#define L_MALAYALAM               0x0900U

/*Position*/
#define P_PREVIOUS                0x8000U
#define P_BOTH                    0x4000U   

/*
*/
#define STA_N 0
#define STA_VI 2
#define STA_CO 10

typedef DT16_ushort CHAR_PROPERTY;
typedef DT16_ushort CHAR_CLASS;
typedef DT16_ushort CHAR_LOCATION;
typedef DT16_ushort CHAR_PERVIOUS;


CHAR_CLASS get_class(UNI_CHAR uni_char);
CHAR_LOCATION get_location(UNI_CHAR uni_char);
DT_BOOL indic_get_syllable(UNI_CHAR* p_unitxt, DT32_int len, DT32_int * p_end);
DT_BOOL indic_get_syllable_ex(UNI_CHAR* p_unitxt, DT32_int len, DT32_int * p_end, SYLLABLE_STATE init_state);

CHAR_PROPERTY get_property(UNI_CHAR uni_char);
/*
*/
#define SYL_IS_AT_PREVIOUS(uni_char) (P_PREVIOUS == (MASK_PREVIOUS & get_property(uni_char)))
#define SYL_IS_AT_BOTH(uni_char) (P_BOTH == (MASK_PREVIOUS & get_property(uni_char)))
/*
*/
#define SYL_IS_NUKTA(uni_char) (C_SIGN_NUKTA == (MASK_CLASS & get_property(uni_char)))
#define SYL_IS_INDEPENDENT(uni_char) (C_INDEPENDENT_VOWEL == (MASK_CLASS & get_property(uni_char)))
#define SYL_IS_VIRAMA(uni_char) (C_SIGN_VIRAMA == (MASK_CLASS & get_property(uni_char)))

#endif /*INDIC_FIND_SYLLABLE_H*/


