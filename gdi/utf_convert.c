/**
 * Copyright(c) 2018 Persol AVC Technology.
 *
 * @file   utf_convert.c
 * @brief  ������̕����R�[�h�ϊ�
 * 
 * UTF-16 <=> UTF-8�̕ϊ��������s���B
 *
 */
#include <stdio.h>
#include "utf_convert.h"
#include "utf16_char.h"

#define CURRENTCHAR(p)  ((p)[0])
#define NEXTCHAR(p)     ((p)[1])
#define NEXTNEXTCHAR(p)     ((p)[2])

/* UTF-8(1byte)�̃r�b�g�p�^�[�����𔻕� */
#define UTF8_1BYTE_BITPATTERN(p) ( ((p)[0]&0x80)==0x00 )
/* UTF-8(2byte)�̃r�b�g�p�^�[�����𔻕� */
#define UTF8_2BYTE_BITPATTERN(p) ( ( ((p)[0]&0xe0)==0xc0 ) && ( ((p)[1]&0xc0)==0x80 ) )
/* UTF-8(3byte)�̃r�b�g�p�^�[�����𔻕� */
#define UTF8_3BYTE_BITPATTERN(p) ( ( ((p)[0]&0xf0)==0xe0 ) && ( ((p)[1]&0xc0)==0x80 ) && ( ((p)[2]&0xc0)==0x80 ) )


/* UTF-8����UNCODE�����o�� */
#define GET_1BYTE_UTF8_BITS(p)           ( (p)[0]&0x007f )
#define GET_2BYTE_UTF8_HIGH_BITS(p)      ( ((p)[0]&0x001f)<<6 )
#define GET_2BYTE_UTF8_LOW_BITS(p)       ( (p)[1]&0x003f )
#define GET_3BYTE_UTF8_HIGH_BITS(p)      ( ((p)[0]&0x000f)<<12 )
#define GET_3BYTE_UTF8_MID_BITS(p)       ( ((p)[1]&0x003f)<<6 )
#define GET_3BYTE_UTF8_LOW_BITS(p)       ( (p)[2]&0x003f )


/* UNCODE��UTF-8�`���ɃZ�b�g */
#define SET_1BYTE_UTF8(code)             ((unsigned char)( code&0x007f ))
#define SET_2BYTE_UTF8_HIGH(code)        ((unsigned char)(0xc0|((code&0x07c0)>>6)))
#define SET_2BYTE_UTF8_LOW(code)         ((unsigned char)(0x80|(code&0x003f)))
#define SET_3BYTE_UTF8_HIGH(code)        ((unsigned char)(0xe0|((code&0xf000)>>12)))
#define SET_3BYTE_UTF8_MID(code)         ((unsigned char)(0x80|((code&0x0fc0)>>6)))
#define SET_3BYTE_UTF8_LOW(code)         ((unsigned char)(0x80|(code&0x003f)))


/* UTF-8��1byte�p�b�P�[�W�Ɏ��܂邩���� */
#define CHECK_UTF8_1BYTE_PACKAGE(code)   ((code&0xff80)==0)
/* UTF-8��2byte�p�b�P�[�W�Ɏ��܂邩���� */
#define CHECK_UTF8_2BYTE_PACKAGE(code)   ((code&0xf800)==0)


/* UTF-8(3byte)��BOM�R�[�h���𔻕� */
#define UTF8_BOM_BITPATTERN(p) ( ((p)[0]==0xef ) && ( (p)[1]==0xbb ) && ( (p)[2]==0xbf ) )

/* UNICODE��NULL���� */
#define UNICODE_NULL_CHAR 0x0000


static int utf8_to_utf16(unsigned char *utf8_chr, unsigned short *utf16_chr, int *nbyte)
{
	if ((NULL == utf8_chr) || (NULL == utf16_chr) || (NULL == nbyte)) {
		return UTF_ERR_BAD_ARG;
	}

	if (UTF8_1BYTE_BITPATTERN(utf8_chr)) {
		// 1byte����
		*utf16_chr = (unsigned short)GET_1BYTE_UTF8_BITS(utf8_chr);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		*nbyte = 1;
		return UTF_OK;
	}
	if (UTF8_2BYTE_BITPATTERN(utf8_chr)) {
		// 2byte����
		*utf16_chr = (unsigned short)( GET_2BYTE_UTF8_HIGH_BITS(utf8_chr) 	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
															| GET_2BYTE_UTF8_LOW_BITS(utf8_chr) );
		*nbyte = 2;
		return UTF_OK;
	}
	if (NEXTCHAR(utf8_chr) != '\0') {
		if (UTF8_3BYTE_BITPATTERN(utf8_chr)) {
			// 3byte����
			*utf16_chr = (unsigned short)(GET_3BYTE_UTF8_HIGH_BITS(utf8_chr)	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
										| GET_3BYTE_UTF8_MID_BITS(utf8_chr)
										| GET_3BYTE_UTF8_LOW_BITS(utf8_chr));
			*nbyte = 3;
			return UTF_OK;
		}
	}

	/* UTF8�̃t�H�[�}�b�g�ᔽ��������4byte�ȏ�̕����Ŕ�Ή� */
	{
		*utf16_chr = UNICODE_NULL_CHAR; /* NULL������Ԃ� */
		*nbyte=1;
	}
	return UTF_ERR_DECODE;
}


static int utf16_to_utf8(unsigned short code, unsigned char *str, int *num)
{
	if ((NULL == str) || (NULL == num)) {
		return UTF_ERR_BAD_ARG;
	}

	if (CHECK_UTF8_1BYTE_PACKAGE(code)) {
		// 1byte
		str[0] = (unsigned char)SET_1BYTE_UTF8(code);		/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		*num = 1;
	} else if (CHECK_UTF8_2BYTE_PACKAGE(code)) {
		// 2byte
		str[0] = (unsigned char)SET_2BYTE_UTF8_HIGH(code);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		str[1] = (unsigned char)SET_2BYTE_UTF8_LOW(code);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		*num = 2;
	} else {
		// 3byte
		str[0] = (unsigned char)SET_3BYTE_UTF8_HIGH(code);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		str[1] = (unsigned char)SET_3BYTE_UTF8_MID(code);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		str[2] = (unsigned char)SET_3BYTE_UTF8_LOW(code);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		*num = 3;
	}
	return UTF_OK;
}

/** @addtogroup utf_convert
 *  @{
 */

/** 
 * utf8������UTF16�����ɕϊ�
 *
 * @param utf8 [IN] ����UTF8�����̐擪�A�h���X
 * @param utf16 [OUT] �o��UTF16����������߂邽�߂̃A�h���X
 * @param nbyte [OUT] UTF8�̃o�C�g�������߂邽�߂̃A�h���X
 *
 * @return  @ref utf_err_id "�G���[�R�[�h"
 *
 * @attention nbyte�͏I�[����(NULL����)���܂�
 *
 */
int UTF_ConvertChar8to16(char *utf8, unsigned short *utf16, int *nbyte)
{
	if (utf8 == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (utf16 == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (nbyte == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	return utf8_to_utf16(utf8, utf16, nbyte);
}

/** 
 * utf16������UTF8�����ɕϊ�
 *
 * @param utf16 [IN] ����UTF16����
 * @param utf8 [OUT] �o��UTF8���������߂邽�߂̃A�h���X
 * @param nbyte [OUT] UTF8�̃o�C�g�������߂邽�߂̃A�h���X
 *
 * @return  @ref utf_err_id "�G���[�R�[�h"
 *
 * @attention nbyte�͏I�[����(NULL����)���܂�
 *
 */
int UTF_ConvertChar16to8(unsigned short utf16, char *utf8, int *nbyte)
{
	if (utf8 == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	if (nbyte == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	return utf16_to_utf8(utf16, utf8, nbyte);
}

/** 
 * utf8�������UTF16������ɕϊ�
 *
 * @param utf8 [IN] ����UTF8������̐擪�A�h���X
 * @param utf16 [OUT] �o��UTF16������̐擪�A�h���X
 * @param nbyte [OUT] UTF8�̃o�C�g�������߂邽�߂̃A�h���X
 * @param nchar [OUT] �ϊ������������߂邽�߂̃A�h���X
 *
 * @return  @ref utf_err_id "�G���[�R�[�h"
 *
 * @attention NULL���������o���邩�A100�����ɒB����܂ŏ����𑱂���
 * @attention nbyte�Anchar�͏I�[����(NULL����)���܂�
 *
 */
int UTF_ConvertString8to16(char *utf8, unsigned short *utf16, int *nbyte, int *nchar)
{
	int sum_byte, byte;
	int cnt;
	int ret = UTF_OK;

	if (utf8 == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (utf16 == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (nbyte == NULL) {
		return UTF_ERR_BAD_ARG;
	}
	if (nchar == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	for (cnt = 0, sum_byte = 0; cnt < UTF_NUM_MAX_CHAR; cnt++, sum_byte += byte) {
		ret = utf8_to_utf16(&utf8[sum_byte], &utf16[cnt], &byte);
		if(utf16[cnt] == UNICODE_NULL_CHAR) {
			cnt++;
			sum_byte+=byte;
			break;
		}
	}

	*nbyte = sum_byte;
	*nchar = cnt;

	return ret;
}

/** 
 * utf16�������UTF8������ɕϊ�
 *
 * @param utf16 [IN] ����UTF16������̐擪�A�h���X
 * @param utf8 [OUT] �o��UTF8������̐擪�A�h���X
 * @param nbyte [OUT] UTF8�̃o�C�g�������߂邽�߂̃A�h���X
 * @param nchar [OUT] �ϊ������������߂邽�߂̃A�h���X
 *
 * @return  @ref utf_err_id "�G���[�R�[�h"
 *
 * @attention NULL���������o���邩�A100�����ɒB����܂ŏ����𑱂���
 * @attention nbyte�Anchar�͏I�[����(NULL����)���܂�
 *
 */
int UTF_ConvertString16to8(unsigned short *utf16, char *utf8, int *nbyte, int *nchar)
{
	int sum_byte, byte;
	int cnt;
	int ret = UTF_OK;

	if (utf16 == NULL) {
	  return UTF_ERR_BAD_ARG;
	}

	if (utf8 == NULL) {
	  return UTF_ERR_BAD_ARG;
	}

	if (nbyte == NULL) {
	  return UTF_ERR_BAD_ARG;
	}

	if (nchar == NULL) {
	  return UTF_ERR_BAD_ARG;
	}


	for (cnt = 0, sum_byte = 0; cnt < UTF_NUM_MAX_CHAR; cnt++, sum_byte += byte) {
		ret = utf16_to_utf8(utf16[cnt], &utf8[sum_byte], &byte);
		if(utf8[sum_byte] == '\0') {
			cnt++;
			sum_byte+=byte;
			break;
		}
	}

	*nbyte = sum_byte;
	*nchar = cnt;

	return ret;
}


/** 
 * utf16�������UTF8�ɕύX�����ۂ�UTF8�o�C�g���擾
 *
 * @param utf16 [IN] UTF16������̐擪�A�h���X
 *
 * @return  UTF8������̃o�C�g��
 *
 * @attention �I�[����(NULL����)���܂�
 *
 */
int UTF_NumBytes16to8(unsigned short *utf16)
{
	int sum_byte, byte;
	int cnt;
	unsigned char utf8[3];

	if (utf16 == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	for (cnt = 0, sum_byte = 0; cnt < UTF_NUM_MAX_CHAR; cnt++, sum_byte += byte) {
		utf16_to_utf8(utf16[cnt], utf8, &byte);
		if (utf16[cnt] == UNICODE_NULL_CHAR) {
			sum_byte+=byte;
			break;
		}
	}

	return sum_byte;
}

/** 
 * utf8�������擾
 *
 * @param utf8 [IN] UTF8������̐擪�A�h���X
 *
 * @return  ������
 *
 * @attention �I�[����(NULL����)���܂�
 *
 */
int UTF_StrLen(char *utf8)
{
	int sum_byte, byte;
	int cnt;
	unsigned short utf16;

	if(utf8 == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	for (cnt = 0, sum_byte = 0; cnt < UTF_NUM_MAX_CHAR; cnt++, sum_byte += byte) {
		utf8_to_utf16(&utf8[sum_byte], &utf16, &byte);
		if (utf8[sum_byte] == '\0') {
			cnt++;
			sum_byte += byte;
			break;
		}
	}
	return cnt;
}

/** 
 * 8bit������̕������擾�֐�
 *
 * @param in  [IN]  char�^�̕�����̐擪�A�h���X
 *
 * @return  @ref ������(NULL�܂�)
 *
 * @note IN��������͕K��NULL�I�[���邱��
 */
int get_char_string_length(const char *str)
{
	int len = 0;
	if (str == NULL)
		return 0;
		
	for (len = 0; str[len]; len++) {	/* parasoft-suppress BD-PB-NOTINIT */
		if (str[len] == 0) break;
	}
	return len;
}


/** 
 * 16bit������̕������擾�֐�
 *
 * @param in  [IN]  unsigned short�^�̕�����̐擪�A�h���X
 *
 * @return  @ref ������(NULL�܂�)
 *
 * @note IN��������͕K��NULL�I�[���邱��
 */
int get_ushort_string_length(const unsigned short *str)
{
	int len = 0;
	
	if (str == NULL)
		return 0;
		
	for (len = 0; str[len]; len++) {
		if (str[len] == 0) break;
	}
	return len;
}

/** 
 * 8bit������16bit������ϊ��֐�
 *
 * @param in  [IN]  char�^�̕�����̐擪�A�h���X
 * @param out [OUT] unsigned short�^�̕�����̐擪�A�h���X
 *
 * @return  @ref �i�[����������(NULL�܂�)
 *
 * @note IN��������͕K��NULL�I�[���邱��
 */
int convert_char_str_to_ushort_str(unsigned short *dst, const char *src)
{
	int len = 0;

	if (dst == NULL || src == NULL)
		return 0;
	
	for (len = 0; src[len]; len++) {
		if (src[len] == 0) break;
		dst[len] = (unsigned short)src[len];
	}
	dst[len] = 0x0000;
	
	return len;
}

/** 
 * 16bit������8bit������ϊ��֐�
 *
 * @param in  [IN]  unsigned short�^�̕�����̐擪�A�h���X
 * @param out [OUT] char�^�̕�����̐擪�A�h���X
 *
 * @return  @ref �i�[����������(NULL�܂�)
 *
 * @note IN��������͕K��NULL�I�[���邱��
 */
int convert_ushort_str_to_char_str(char *dst, const unsigned short *src)
{
	int len = 0;

	if (dst == NULL || src == NULL)
		return 0;
	
	for (len = 0; src[len]; len++) {
		if (src[len] == 0) break;
		dst[len] = (unsigned char)(src[len] & 0x00FF);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	}
	dst[len] = 0x00;
	return len;
}


/** @addtogroup utf_string
 *  @{
 */
/** 
 * UTF16������̑}��
 *
 * @param in [IN] �}���O�̓��͕�����̐擪�A�h���X
 * @param out [OUT] �}����̏o�͕�����̐擪�A�h���X
 * @param chr [IN] �}������(UTF16�`��)
 * @param pos [IN] �}���ʒu
 *
 * @return  @ref utf_err_id "�G���[�R�[�h"
 *
 * @note �}���ʒu�ɂ��āA�擪�ɑ}������ꍇ��0���w�肷��B
 * @note �}���ʒu���O��NULL���������o���ꂽ�ꍇ�́A������̍Ō�ɒǉ�����B
 *
 */
int UTF_InsertString(unsigned short *in, unsigned short *out, unsigned short chr, int pos)
{
	int idx;

	if(in == NULL)
	{
		return UTF_ERR_BAD_ARG;
	}
	if(out == NULL)
	{
		return UTF_ERR_BAD_ARG;
	}
	if( (pos<0)||(pos>=(UTF_NUM_MAX_CHAR-1)) )
	{
		return UTF_ERR_BAD_ARG;
	}

	for(idx=0;idx<pos;idx++)
	{
		out[idx] = in[idx];
		if(out[idx] == UNICODE_NULL_CHAR)
		{
			/* pos�ɂ��ǂ蒅���r����NULL�����������ꍇ�ANULL�����̏ꏊ�ɕ�����ǉ� */
			out[idx++] = chr;
			out[idx] = UNICODE_NULL_CHAR;
			return UTF_OK;
		}
	}

	out[idx] = chr;

	for(;idx<(UTF_NUM_MAX_CHAR-1);idx++)
	{
		out[idx+1] = in[idx];

		if(in[idx] == UNICODE_NULL_CHAR)
		{
			/* NULL�����ɂ��ǂ蒅�����ꍇ�A�폜���� */
			return UTF_OK;
		}
	}
	out[idx] = UNICODE_NULL_CHAR;
	return UTF_OK;
}



/** 
 * UTF16������̍폜
 *
 * @param in [IN] �폜�O�̓��͕�����̐擪�A�h���X
 * @param out [OUT] �폜��̏o�͕�����̐擪�A�h���X
 * @param pos [IN] �폜�ʒu
 *
 * @return  @ref utf_err_id "�G���[�R�[�h"
 *
 * @note �폜�ʒu�ɂ��āA�擪�������폜����ꍇ��0���w�肷��B
 * @note �폜�ʒu���O��NULL���������o���ꂽ�ꍇ�́A�폜�͍s���Ȃ��B
 *
 */
int UTF_DeleteString(unsigned short *in, unsigned short *out, int pos)
{
	int idx;

	if (in == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	if (out == NULL) {
		return UTF_ERR_BAD_ARG;
	}

	if ((pos < 0) || (pos >= UTF_NUM_MAX_CHAR)) {
		return UTF_ERR_BAD_ARG;
	}

	for (idx = 0; idx < pos; idx++) {
		out[idx] = in[idx];
		if (in[idx] == UNICODE_NULL_CHAR) {
			/* pos�ɂ��ǂ蒅���r����NULL�����������ꍇ�A�폜�o���Ȃ����ߏI������ */
			return UTF_OK;
		}
	}

	if (in[idx] == UNICODE_NULL_CHAR) {
		/* pos��NULL�����̏ꍇ�A�폜���Ă��Ӗ������̂�NULL�������ďI�� */
		out[idx] = UNICODE_NULL_CHAR;
		return UTF_OK;
	}

	for (; idx < (UTF_NUM_MAX_CHAR - 1); idx++) {
		out[idx] = in[idx + 1];

		if (out[idx] == UNICODE_NULL_CHAR) {
			/* NULL�����ɂ��ǂ蒅�����ꍇ�A�P�����폜���� */
			return UTF_OK;
		}
	}
	out[idx] = UNICODE_NULL_CHAR;
	return UTF_OK;
}




static unsigned short add_mark_a_to_o(unsigned short in, UTF_MARK_TYPE type)
{
	/*
	��������"����
	*/
	unsigned short output = in;

	//���̂�"�̂ݕϊ�
	/* �W������������������ɕϊ� */
	if (in == UTF_H_LETTER_U) {
		if (type == UTF_VOICED) {
			return UTF_H_LETTER_VU;
		}
	}

	/* ������������W�������ɕϊ� */
	if (in == UTF_H_LETTER_VU) {
		if (type == UTF_DEFAULT) {
			return UTF_H_LETTER_U;
		}
	}
	return output;
}

static unsigned short add_mark_ka_to_ti(unsigned short in, UTF_MARK_TYPE type)
{
	/*
		�������������������� 
		�������������������� 
		��������
		��F�W������
		�����F��������
	*/
	unsigned short output = in;

	if (in & 0x0001) {
		/* ��͕W������ */
		if (type == UTF_VOICED) {
			/* �W������������������ɕϊ� */
			output = (unsigned short)(in + 1);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		}
	} else {
		/* �����͑������� */
		if (type == UTF_DEFAULT) {
			/* ������������W�������ɕϊ� */
			output = (unsigned short)(in - 1);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		}
	}
	return output;
}

static unsigned short add_mark_tu_to_to(unsigned short in, UTF_MARK_TYPE type)
{
	/*
		���ÂĂłƂ�
	*/
	unsigned short output = in;
	unsigned short offset;

	//�u���v�����͂��̂܂ܕԂ�
	if (in == UTF_H_LETTER_SMALL_TU) {
		return output;
	}

	if (type == UTF_DEFAULT) {
		offset = 0;
	} else if (type == UTF_VOICED) {
		offset = 1;
	} else {
		return output;
	}

	if (in <= UTF_H_LETTER_DU) {
		output = (unsigned short)(UTF_H_LETTER_TU + offset);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	} else if(in <= UTF_H_LETTER_DE) {
		output = (unsigned short)(UTF_H_LETTER_TE + offset);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	} else if(in <= UTF_H_LETTER_DO) {
		output = (unsigned short)(UTF_H_LETTER_TO + offset);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	}

	return output;
}

static unsigned short add_mark_ha_to_ho(unsigned short in, UTF_MARK_TYPE type)
{
	/*
		�͂΂ςЂт҂ӂԂՂւׂ؂قڂ�
	*/
	unsigned short output = in;
	unsigned short offset;

	if (type == UTF_DEFAULT) {
		offset = 0;
	} else if (type == UTF_VOICED) {
		offset = 1;
	} else if (type == UTF_SEMIVOICED) {
		offset = 2;
	} else {
		return in;
	}

	if (in <= UTF_H_LETTER_PA) {
		output = (unsigned short)(UTF_H_LETTER_HA + offset);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	} else if (in <= UTF_H_LETTER_PI) {
		output = (unsigned short)(UTF_H_LETTER_HI + offset);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	} else if (in <= UTF_H_LETTER_PU) {
		output = (unsigned short)(UTF_H_LETTER_HU + offset);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	} else if (in <= UTF_H_LETTER_PE) {
		output = (unsigned short)(UTF_H_LETTER_HE + offset);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	} else if (in <= UTF_H_LETTER_PO) {
		output = (unsigned short)(UTF_H_LETTER_HO + offset);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	}

	return output;
}

static unsigned short add_mark(unsigned short in, UTF_MARK_TYPE type)
{
	if(in <= UTF_H_LETTER_O) {
		/* ���s */
		return add_mark_a_to_o(in, type);
	}

	if(in <= UTF_H_LETTER_DI) {
		/* ���`�� */
		return add_mark_ka_to_ti(in, type);
	}

	if(in <= UTF_H_LETTER_DO) {
		/* �Ă� */
		return add_mark_tu_to_to(in, type);
	}

	if(in <= UTF_H_LETTER_NO) {
		/* �ȍs�͂Ȃɂ����Ȃ� */
		return in;
	}

	if(in <= UTF_H_LETTER_PO) {
		/* �́`�� */
		return add_mark_ha_to_ho(in, type);
	}

	if(in == UTF_H_LETTER_VU) {
		/* ��" */
		return add_mark_a_to_o(in, type);
	}

	/* �u�܁`��v�͉������Ȃ� */
	return in;
}



static unsigned short add_mark_hiragana(unsigned short in, unsigned short *out, UTF_MARK_TYPE type)
{
	unsigned short chr;

	chr = add_mark(in, type);

	return chr;
}

static unsigned short add_mark_katakana(unsigned short in, unsigned short *out, UTF_MARK_TYPE type)
{
	unsigned short chr;

	/* �Ђ炪�ȂƏ��������ʂɂ��邽�߁A��U�Ђ炪�Ȃɕϊ� */
	chr = (unsigned short)(in - UTF_K_LETTER_SMALL_A + UTF_H_LETTER_SMALL_A);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */

	chr = add_mark(chr, type);

	/* �J�^�J�i�ɖ߂� */
	chr = (unsigned short)(chr - UTF_H_LETTER_SMALL_A + UTF_K_LETTER_SMALL_A);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */

	return chr;
}



/** @addtogroup utf_add_mark
 *  @{
 */
/** 
 * ���ȁE�J�i�̑����E�������ϊ�
 *
 * @param in [IN] �ϊ��O�̕���
 * @param out [OUT] �ϊ���̕������i�[����A�h���X
 * @param type [IN] �ϊ��^�C�v
 *
 * @return  �Ȃ�
 *
 * @attention �����ȕύX���w�肵���ꍇ�A���͕�����Ԃ��B\n
 *            (���Ƃ��΁u�ȁv�ɑ������w�肵���ꍇ�u�ȁv���A�u���v�ɔ��������w�肵���ꍇ�́u���v��Ԃ�)
 *
 */
void UTF_AddMark(unsigned short in, unsigned short *out, UTF_MARK_TYPE type)
{
	if (NULL == out) {
		return;
	}

	if ((UTF_H_LETTER_SMALL_A <= in) && (in <= UTF_H_LETTER_VU)) {
		//�Ђ炪�ȃR�[�h�͈̔�
		*out = add_mark_hiragana(in, out, type);
	} else if ((UTF_K_LETTER_SMALL_A <= in) && (in <= UTF_K_LETTER_VU)) {
		//�J�^�J�i�R�[�h�͈̔�
		*out = add_mark_katakana(in, out, type);
	} else {
		/* �Ђ炪�ȁE�J�^�J�i�ȊO�̏ꍇ�͕ϊ������ɏI������ */
		*out = in;
	}

	return;
}



static unsigned short add_nextmark_a_to_o(unsigned short in)
{
	/*
	��������"����
	*/
	unsigned short output = in;

	//�E�̃��̂ݕϊ�
	// �W������������������ɕϊ�
	if (in == UTF_K_LETTER_U) {
		return UTF_K_LETTER_VU;
	}

	// ������������W�������ɕϊ�
	if(in == UTF_K_LETTER_VU) {
		return UTF_K_LETTER_U;
	}

	return output;
}

static unsigned short add_nextmark_ka_to_ti(unsigned short in)
{
	/*
		�������������������� 
		�������������������� 
		��������
		��F�W������
		�����F��������
	*/
	unsigned short output = in;

	if (in & 0x0001) {
		/* ��͕W������ */
		/* �W������������������ɕϊ� */
		output = (unsigned short)(in + 1);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	} else {
		/* �����͑������� */
		/* ������������W�������ɕϊ� */
		output = (unsigned short)(in - 1);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	}
	return output;
}

static unsigned short add_nextmark_tu_to_to(unsigned short in)
{
	/*
		���ÂĂłƂ�
	*/
	unsigned short output = in;

	//�u���v�����͂��̂܂ܕԂ�
	if (in == UTF_H_LETTER_SMALL_TU) {
		return output;
	}

	/* �擪����Q�Ŋ����ė]��Ō��݂�type�����߂�
		�]��	0:���_�C�����_�Ȃ�,1�F���_
	*/
	switch ((in - UTF_H_LETTER_TU) % 2) {
	case 0:	//���_�C�����_�Ȃ�
		//NEXT
		output = (unsigned short)(in + 1);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		break;
	case 1:	//���_
	default:
		//���_�C�����_�Ȃ��ɖ߂�
		output = (unsigned short)(in - 1);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		break;
	}
	return output;
}

static unsigned short add_nextmark_ha_to_ho(unsigned short in)
{
	/*
		�͂΂ςЂт҂ӂԂՂւׂ؂قڂ�
	*/
	unsigned short output = in;

	/* �擪����R�Ŋ����ė]��Ō��݂�type�����߂�
		�]��	0:���_�C�����_�Ȃ�,1�F���_�C2�F�����_
	*/
	switch ((in - UTF_H_LETTER_HA) % 3) {
	case 0:	//���_�C�����_�Ȃ�
	case 1:	//���_
		//NEXT
		output = (unsigned short)(in + 1);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		break;
	case 2:	//�����_
	default:
		//���_�C�����_�Ȃ��ɖ߂�
		output = (unsigned short)(in - 2);	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		break;
	}
	return output;
}


static unsigned short add_nextmark(unsigned short in)
{

	if(in <= UTF_H_LETTER_O) {
		/* ���s*/
		return add_nextmark_a_to_o(in);
	}

	if (in <= UTF_H_LETTER_DI) {
		/* ���`�� */
		return add_nextmark_ka_to_ti(in);
	}

	if (in <= UTF_H_LETTER_DO) {
		/* �`�� */
		return add_nextmark_tu_to_to(in);
	}

	if (in <= UTF_H_LETTER_NO) {
		/* �ȍs�͂Ȃɂ����Ȃ� */
		return in;
	}

	if (in <= UTF_H_LETTER_PO) {
		/* �́`�� */
		return add_nextmark_ha_to_ho(in);
	}

	if (in == UTF_K_LETTER_VU) {
		/* �� */
		return add_nextmark_a_to_o(in);
	}

	if (in == UTF_K_LETTER_U) {
		/* �E */
		return add_nextmark_a_to_o(in);
	}

	/* �u�܁`��v�͉������Ȃ� */
	return in;
}


static unsigned short add_nextmark_hiragana(unsigned short in, unsigned short *out)
{
	unsigned short chr;

	chr = add_nextmark(in);

	return chr;
}

static unsigned short add_nextmark_katakana(unsigned short in, unsigned short *out)
{
	unsigned short chr;

	if ((in == UTF_K_LETTER_U) || (in == UTF_K_LETTER_VU)) {
		/* �u�E�v�͂Ђ炪�Ȃɕϊ������ɏ������s�� (�u���v�̈����̓J�^�J�i�A�Ђ炪�Ȃŏ������قȂ邽��)*/
		chr = add_nextmark(in);
	} else {
		/* �Ђ炪�ȂƏ��������ʂɂ��邽�߁A��U�Ђ炪�Ȃɕϊ� */
		chr = (unsigned short)(in - UTF_K_LETTER_SMALL_A + UTF_H_LETTER_SMALL_A );	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
		chr = add_nextmark(chr);

		/* �J�^�J�i�ɖ߂� */
		chr = (unsigned short)(chr - UTF_H_LETTER_SMALL_A + UTF_K_LETTER_SMALL_A );	/* pgr0247 �Ӑ}�ʂ�̃L���X�g */
	}
	return chr;
}

/*
in : ���ݓ��͂���Ă���l
out�F�ϊ���̒l�i�W�������������������W���̏��ɐ؂�ւ���j
*/
void UTF_AddNextMark(unsigned short in, unsigned short *out)
{
	if (NULL == out) {
		return;
	}

	//�]���̕ϊ��Ɠ�������
	if ((in >= UTF_H_LETTER_SMALL_A) && (in <= UTF_H_LETTER_VU)) {
		//�Ђ炪�ȃR�[�h�͈̔�
		*out = add_nextmark_hiragana(in, out);
	} else if ((in >= UTF_K_LETTER_SMALL_A) && (in <= UTF_K_LETTER_VU)) {
		//�J�^�J�i�R�[�h�͈̔�
		*out = add_nextmark_katakana(in, out);
	} else {
		/* �Ђ炪�ȁE�J�^�J�i�ȊO�̏ꍇ�͕ϊ������ɏI������ */
		*out = in;
	}

	return;
}





/** @} */ //end of utf_convert
