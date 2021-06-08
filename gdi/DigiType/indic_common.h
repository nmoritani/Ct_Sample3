#ifndef INDIC_COMMON_H
#define INDIC_COMMON_H

#include "DcwLangModule.h" 
//#include "DcwLayout.h"
#include "DTplatform.h"

/*-------------------------------------------------------------------*/
//#define TABLE_FROM_USERDATA
/*-------------------------------------------------------------------*/
#ifndef FALSE
	#define	FALSE	(0)
	#define	TRUE	(!FALSE)
#endif

#ifndef NULL
	#define NULL   (0) 
#endif

#ifndef __UNI_CHAR
#define __UNI_CHAR
typedef DT16_ushort UNI_CHAR;
#endif

typedef DT32_int TP_INDEX;
/*-------------------------------------------------------------------*/
#define ERROR_FAIL_INDEX (-1)
#define N_E(AR) (sizeof( AR )/sizeof( AR [0]))
#define TABLE_SIZE(AR) (sizeof( AR )/sizeof( AR [0]))
/*-------------------------------------------------------------------*/
//#define N			// Marked_Jacky_20110627: comflict with DcwBiDi.h
#define ZWNJ           0x200c
#define ZWJ            0x200d
/*-------------------------------------------------------------------*/
#define DEVA_EMPTY     0x0000
#define TAMIL_EMPTY    DEVA_EMPTY
#define BEN_EMPTY    DEVA_EMPTY
#define IDX_NONE       (-1)
#define OFFSET_NONE    (-1)

/*----------------------------------------------------------------------*/


#define ID_DEVA DCW_LANGTAB_HINDI
/*-------common_struct---------------------------------------------------*/
/*
	@Structure:HALF_ROW
	it implies A=B, as 0x0915+0x0940+0x200d
	==>>halfform of 0x0915.
*/
typedef struct{
	UNI_CHAR A;
	UNI_CHAR B;
}HALF_ROW, DVOWEL_ROW;

/*
	@Structure:LIGA_ROW
	It implies A+B=C, the replacment of 
	sign and ligature tables.
*/
typedef struct{
	UNI_CHAR A;
	UNI_CHAR B;
	UNI_CHAR C;
}LIGA_ROW, LIGA_LIGA_ROW, SIGN_ROW, * P_LIGA_ROW;

/*
	A+B+C=D
*/
typedef struct{
	UNI_CHAR A;
	UNI_CHAR B;
	UNI_CHAR C;
	UNI_CHAR D;
}LIGA_TRI_ROW, * P_LIGA_TRI_ROW;

/*
	@Structure:COMPLEX_LIGA
	0x0 is ending of the table. 
*/
typedef UNI_CHAR COMPLEX_LIGA;

/*
	@Structure:PAIR
	It implies part of two part vowel,
	as 0x0bc6,0x0bbe (0x0BCA)
*/
typedef struct{
	UNI_CHAR FIRST;
	UNI_CHAR SECOND;
}PAIR;
/*
	@Structure:SPLIT_TWO_PART
	ORG split to first and second.
*/
typedef struct{
	UNI_CHAR ORG;
	PAIR TWO_PART;
}SPLIT_TWO_PART, * P_SPLIT_TWO_PART_ROW;

/*
*/
typedef struct{
	UNI_CHAR ORG;
	HALF_ROW * P_SECOND_ROW;
	DT32_int TABLESIZE;
}LIGA_ROW_2, * P_LIGA_2_ROW;


/*-------some of looking up table function.------------------------------*/

UNI_CHAR lookup_consonants_table(UNI_CHAR A,  HALF_ROW * p_half_table, DT32_int length);
UNI_CHAR lookup_liga_table(UNI_CHAR A, UNI_CHAR B, P_LIGA_ROW p_liga_row, DT32_int length);
UNI_CHAR lookup_tri_liga_table(UNI_CHAR A, UNI_CHAR B, UNI_CHAR C, P_LIGA_TRI_ROW p_tri_liga_row, DT32_int length);
UNI_CHAR lookup_complex_table_ex(UNI_CHAR * p_uorg, DT32_int org_length, 
					 COMPLEX_LIGA * p_complex_table, DT32_int length, DT32_int *pstr_end_idx);
PAIR * lookup_spliter_table(UNI_CHAR u_org, SPLIT_TWO_PART * p_split_tow_part_table,
							DT32_int length);

UNI_CHAR * lookup_complex_table(UNI_CHAR * p_uorg, DT32_int org_length, 
					 COMPLEX_LIGA * p_complex_table, DT32_int length);
DT_BOOL lookup_check_table(UNI_CHAR A,  UNI_CHAR * p_check_table, DT32_int length);

UNI_CHAR lookup_liga_2_table(UNI_CHAR A, UNI_CHAR B, P_LIGA_2_ROW p_liga_2_row_table, DT32_int length);

/*-------Contruct a struct to record syllable's feature.---------------------------------------------------*/
#define OUT_REPH_SUP        0x00000001U
#define OUT_REPH_SUB        0x00000002U 
#define OUT_PREVOWEL        0x00000004U
#define OUT_NUKTA		    0x00000008U
#define OUT_DEPENDENT_NUKTA 0x00000010U
#define OUT_TWOP_DEPENDENT  0x00000020U
#define OUT_ZWNJ_DEPENDENT  0x00000040U
#define OUT_ZWNJ			0x00000080U
#define OUT_ZWJ				0x00000100U

typedef struct _out_syllable
{
	UNI_CHAR * p_unitxt;
	DT32_uint  f_special_part; 
	DT32_int idx_last_consonant;
	DT32_int idx_begin;
	DT32_int idx_end;
	DT32_int idx_half_reph_sub;
	DT32_int idx_signs;
	DT32_int idx_candra_signs;
	DT32_int idx_dependent_vowel;
	DT32_int length;
	DT32_int pre_special_part;
}s_out_syllable;


/*TO DO: Define some micro to set s_out_syslabe structure.*/
#define SET_SECIAL_PART_FALSE(x) ( (x).f_special_part = 0 ) 
#define SET_REPH_SUP_TRUE(x) ( (x).f_special_part |= OUT_REPH_SUP)   
#define SET_REPH_SUP_FALSE(x) ( (x).f_special_part &= ~OUT_REPH_SUP) 
#define SET_REPH_SUB_TRUE(x) ( (x).f_special_part |= OUT_REPH_SUB)   
#define SET_REPH_SUB_FALSE(x) ( (x).f_special_part &= ~OUT_REPH_SUB)  
#define SET_PREVOWEL_TRUE(x) ( (x).f_special_part |= OUT_PREVOWEL)   
#define SET_PREVOWEL_FALSE(x) ( (x).f_special_part &= ~OUT_PREVOWEL)
#define SET_NUKTA_TRUE(x) ( (x).f_special_part |= OUT_NUKTA)
#define SET_NUKTA_FALSE(x) ( (x).f_special_part &= ~OUT_NUKTA) 
#define SET_PREDEPENDENT_NUKTA_TRUE(x) ( (x).f_special_part |= OUT_DEPENDENT_NUKTA)
#define SET_PREDEPENDENT_NUKTA_FALSE(x) ( (x).f_special_part &= ~OUT_DEPENDENT_NUKTA) 
#define SET_OUT_TWOP_DEPENDENT_TRUE(x)  ( (x).f_special_part |= OUT_TWOP_DEPENDENT)
#define SET_OUT_TWOP_DEPENDENT_FALSE(x) ( (x).f_special_part &= ~OUT_TWOP_DEPENDENT)
#define SET_ZWNJ_DEPENDENT_TRUE(x)  ( (x).f_special_part |= OUT_ZWNJ_DEPENDENT)
#define SET_ZWNJ_DEPENDENT_FALSE(x)  ( (x).f_special_part &= ~OUT_ZWNJ_DEPENDENT)
#define SET_ZWNJ_TRUE(x)  ( (x).f_special_part |= OUT_ZWNJ)
#define SET_ZWNJ_FALSE(x)  ( (x).f_special_part &= ~OUT_ZWNJ)
#define SET_ZWJ_TRUE(x)  ( (x).f_special_part |= OUT_ZWJ)
#define SET_ZWJ_FALSE(x)  ( (x).f_special_part &= ~OUT_ZWJ)

/*TO DO: Define some micro to set idx value*/
#define SET_IDX_SIGNS(x,y) ( (x).idx_signs = y)
#define SET_IDX_BEGIN(x,y) ( (x).idx_begin = y)
#define SET_IDX_END(x,y) ( (x).idx_end = y)
#define SET_LENGTH(x,y) ( (x).length = y)
#define SET_IDX_LAST_CONSONANT(x,y) ( (x).idx_last_consonant = y)
#define SET_IDX_HALF_REPH_SUB(x,y) ( (x).idx_half_reph_sub = y)
#define SET_IDX_DEPENDENT_VOWEL(x,y) ( (x).idx_dependent_vowel = y)
#define SET_IDX_CANDRA_SIGNS(x,y) ( (x).idx_candra_signs = y)

/*TO DO: Define some micro to judge flag to be set ture or false.*/
#define IS_REPH_SUB(x) ( ( (x).f_special_part&OUT_REPH_SUB) == OUT_REPH_SUB) 
#define IS_REPH_SUP(x) ( ( (x).f_special_part&OUT_REPH_SUP) == OUT_REPH_SUP)
#define IS_PREVOWEL(x) ( ( (x).f_special_part&OUT_PREVOWEL) == OUT_PREVOWEL)
#define IS_NUKTA(x)    ( ( (x).f_special_part&OUT_NUKTA) == OUT_NUKTA)
#define IS_PREDEPENDENT_NUKTA(x)    ( ( (x).f_special_part&OUT_DEPENDENT_NUKTA) == OUT_DEPENDENT_NUKTA)
#define IS_TWOP_DEPENDENT(x) ( ( (x).f_special_part&OUT_TWOP_DEPENDENT) == OUT_TWOP_DEPENDENT) 
#define IS_ZWNJ_DEPENDENT(x) ( ( (x).f_special_part&OUT_ZWNJ_DEPENDENT) == OUT_ZWNJ_DEPENDENT) 
#define IS_ZWNJ(x) ( ( (x).f_special_part&OUT_ZWNJ) == OUT_ZWNJ) 
#define IS_ZWJ(x) ( ( (x).f_special_part&OUT_ZWJ) == OUT_ZWJ) 
/*pre_special_part*/
#define IS_ZWNJ_PRES(x) ( ( (x).pre_special_part&OUT_ZWNJ) == OUT_ZWNJ) 
#define IS_ZWJ_PRES(x) ( ( (x).pre_special_part&OUT_ZWJ) == OUT_ZWJ) 


/*TO DO: Define some micor to judge field whether be set or not.*/
#define HAS_LAST_CONSONANT(x) (((x).idx_last_consonant != IDX_NONE))  
#define HAS_HALF_REPH_SUB(x) (((x).idx_half_reph_sub != IDX_NONE))
#define HAS_DEPENDENT_VOWEL(x) (((x).idx_dependent_vowel != IDX_NONE))
#define HAS_VARIOUS_SIGNS(x) (((x).idx_signs != IDX_NONE))
#define HAS_CANDRA_SIGNS(x) (((x).idx_candra_signs != IDX_NONE))

/*TO DO: Define some mocor to get value.*/
#define GET_SECIAL_PART(x, y) ( y = (x).f_special_part )

#define PREVOWEL(x) (( (x) & OUT_PREVOWEL ) == OUT_PREVOWEL ) 

DT_void indic_init_out_syllable(s_out_syllable * , UNI_CHAR * );

/*-----------------------------------------------------------------------------*/
DT16_ushort getSubVowel_st(DT8_char * pdata, DT16_ushort vowel, DT16_ushort consonant);
DT32_int getPosAdjustment_st(DT8_char * pdata, DT16_ushort base, DT16_ushort sign, DT16_short *poffsetx, DT16_short *poffsety,DT32_int table_begin_index, DT32_int table_end_index );
DT_void change_subtable_format_st(DT8_char * pdata);

#define DISENABLE_NON 0x0
#define DISENABLE_SUB 0x1
#define ENABLE_COPY_SUB 0x2
#define ENABLE_COPY_SUB_FOR_POS 0x3

typedef struct
{
	DT8_char * p_gup_vowel_sub_table;
	DT8_char * p_gup_pos_table;
	DT32_uint process_switch;
	DT8_char * p_gup_pos_table2;
	DT8_char * p_gup_pos_table3;
}ALL_TBL;

/*-------------------------------------------------------------*/
DT_void assert(DT32_int);

#define HINDI_ASSERT(x) assert(x)

#endif /*INDIC_COMMON_H*/ 
