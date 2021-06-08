

#ifdef WIN32_GUI_SIM
#else
# include "SysIf.h"
#endif

#include "language_id.h"	/*������ID�i���ʁj*/
//#include "str_id.h"	/*����ID�i���ʁj*/
#include "gdi_string.h"	/*����ID�i���ʁj*/
#include "string_sub.h"	/*����ID�i���ʁj*/
#include "string_api.h"	/*����ID�i���ʁj*/
#include "fontapi.h"

static LANG_INFO lang_info_list [] =
  {
	{ false, ".ja_string", str_table_ja },  /* [0]	���{��					*/
	{ false, ".en_string", str_table_en }, 	/* [1]	�p��			PAL		*/
	{ false, ".ue_string", str_table_ue }, 	/* [2]	�p��			NTSC	*/
	{ false, ".ge_string", str_table_ge }, 	/* [3]	�ƌ�					*/
	{ false, ".fr_string", str_table_fr }, 	/* [4]	����			PAL		*/
//	{ false, ".ca_string", str_table_ca }, 	/* [5]	����			NTSC	*/
	{ false, ".it_string", str_table_it }, 	/* [6]	�Ɍ�					*/
	{ false, ".sp_string", str_table_sp }, 	/* [7]	����			PAL		*/
//	{ false, ".us_string", str_table_us }, 	/* [8]	����			NTSC	*/
	{ false, ".du_string", str_table_du }, 	/* [9]	����					*/
	{ false, ".sw_string", str_table_sw }, 	/* [10]	�X�E�F�[�f����			*/
	{ false, ".po_string", str_table_po }, 	/* [11]	�|�[�����h��			*/
	{ false, ".ru_string", str_table_ru }, 	/* [12]	�I��					*/
//	{ false, ".ar_string", str_table_ar }, 	/* [13]	�A���r�A��				*/
//	{ false, ".pe_string", str_table_pe }, 	/* [14]	�y���V����				*/
//	{ false, ".ko_string", str_table_ko }, 	/* [15]	�؍���					*/
	{ false, ".sc_string", str_table_sc }, 	/* [16]	�ȑ̌�					*/
	{ false, ".tc_string", str_table_tc }, 	/* [17]	�ɑ̌�			PAL		*/
	{ false, ".tw_string", str_table_tw }, 	/* [18]	�ɑ̌�			NTSC	*/
	{ false, ".cz_string", str_table_cz }, 	/* [19]	�`�F�R��				*/
//	{ false, ".th_string", str_table_th }, 	/* [20]	�^�C��					*/
//	{ false, ".hi_string", str_table_hi }, 	/* [21]	�q���f�B�� 				*/
	{ false, ".je_string", str_table_je }, 	/* [22]	�p��(���{����)	NTSC	*/
	{ false, ".tu_string", str_table_tu }, 	/* [23]	�g���R��                */
	{ false, ".hu_string", str_table_hu },	/* [24]	�n���K���[��            */
//	{ false, ".pt_string", str_table_pt }	/* [25]	�|���g�K����            */
  };

// ������擾�}�N��
#define GET_LANG_INFO(lang_id) (&(lang_info_list[(lang_id)]))

#ifdef WIN32_GUI_SIM
#else
/**
 * @brief  ������f�[�^�̃��[�h
 * @param  language_id   ����h�c
 * @return �Ȃ�
 */
static void SLIB_load_string (LANGUAGE_ID language_id)
{
  LANG_INFO *langInfo;

  // �����`�F�b�N
  if(language_id >= LANGUAGE_ID_MAX)
	{
	  return;
	}

  langInfo = GET_LANG_INFO(language_id);
  if(langInfo->is_load == TRUE)
	{
	  return;   // ���Ƀ��[�h�ς�
	}

  // �S���[�h�t���O��FALSE�ɂ���
  {
	INT i;

	for(i = 0; i < LANGUAGE_ID_MAX; i++)
	  {
		GET_LANG_INFO(i)->is_load = false;
	  }
  }
  
  if(SYS_Section_Load(langInfo->section_name) == SYS_OK)
	{
	  // ���[�h�ɐ���������t���O�𗧂Ă�
	  langInfo->is_load = true;
	}
}
#endif

unsigned short* GDI_GetString ( LANGUAGE_ID language_id, unsigned short string_id )
{
  unsigned short* str;
  LANG_INFO *langInfo;

  // �����`�F�b�N
  if( (language_id >= LANGUAGE_ID_MAX) || (string_id >= (GDI_STRING_ID)STR_ID_MAX_SIZE) )
	{
	  return 0;
	}

#ifdef WIN32_GUI_SIM
#else
	// ������̃��[�h�`�F�b�N�����[�h
	SLIB_load_string(language_id);
#endif

  langInfo = &lang_info_list[language_id];
//  if(langInfo->is_load == false){
//	  return null;  // �����[�h�f�[�^
//  }

  str = (unsigned short*)(langInfo->string_table[string_id]);

  return str;
}

