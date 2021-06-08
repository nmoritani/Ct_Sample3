#ifndef __STRING_SUB_H__
#define __STRING_SUB_H__

#ifdef WIN32_GUI_SIM
#else
#include "stdbool.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


typedef struct _lang_info
{
  bool is_load;
  const char *section_name;
  const unsigned char *const *string_table;
} LANG_INFO;

extern const unsigned char *const str_table_ja[];
extern const unsigned char *const str_table_en[];
extern const unsigned char *const str_table_ue[];
extern const unsigned char *const str_table_sc[];
extern const unsigned char *const str_table_tc[];
extern const unsigned char *const str_table_tw[];
extern const unsigned char *const str_table_je[];
extern const unsigned char *const str_table_ge[];
extern const unsigned char *const str_table_it[];
extern const unsigned char *const str_table_sp[];
extern const unsigned char *const str_table_du[];
extern const unsigned char *const str_table_sw[];
extern const unsigned char *const str_table_po[];
extern const unsigned char *const str_table_ru[];
//extern const unsigned char *const str_table_ar[];
//extern const unsigned char *const str_table_pe[];
//extern const unsigned char *const str_table_ko[];
//extern const unsigned char *const str_table_us[];
extern const unsigned char *const str_table_fr[];
//extern const unsigned char *const str_table_ca[];
extern const unsigned char *const str_table_tw[];
extern const unsigned char *const str_table_cz[];
//extern const unsigned char *const str_table_th[];
//extern const unsigned char *const str_table_hi[];
extern const unsigned char *const str_table_tu[];
extern const unsigned char *const str_table_hu[];
//extern const unsigned char *const str_table_pt[];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __STRING_SUB_H__ */
