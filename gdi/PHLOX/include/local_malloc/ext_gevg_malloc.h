/******************************************************************************
 Copyright (C) 2011 Panasonic Corporation.

 Filename:
     ext_gevg_malloc.h

 Description:
     Declaration of memory pool

 Authors:
     YO - Yoshinori OKAZAKI@AVC

 File History:
 Date        Sign    Description
 ----------  ----    -------------------------------------------------------
 2011/10/04   YO     �V�K�쐬
 ******************************************************************************/

#ifndef _EXT_GEVG_MALLOC_H_
#define _EXT_GEVG_MALLOC_H_

/* ----------------------------------------------------------------------*/
/* �C���N���[�h�t�@�C��                                                  */
/* ----------------------------------------------------------------------*/
#include "string.h"

// ----------------------------------------------------------------------
// �ݒ�l(�K�v�ɉ����ĕύX���Ă�������)
// ----------------------------------------------------------------------
// �������u���b�N�Ǘ���
#define	GEVG_MEM_CONF_MAX_ID		(15)		// 15��ފǗ�

// �f�o�b�O�@�\�L��(1:�L��, 0:����)
#define	GEVG_MEM_CONF_DEBUG			(1)


// ----------------------------------------------------------------------
// �}�N����`
// ----------------------------------------------------------------------
#define MEM_TSZ_MPF_INFO(num) ( ((sizeof(SMemMngMpfInfo) + num) + (32-1)) / 32 * 32 )
#define MEM_TSZ_MPF(size, num) ( ((num) * ((size + (32-1)) / 32 * 32)) + MEM_TSZ_MPF_INFO(num) )


/* ----------------------------------------------------------------------*/
/* �^��`                                                                */
/* ----------------------------------------------------------------------*/
// �������v�[���Ǘ����
typedef struct _SMemMngMpfInfo {
    unsigned long	size;       // �������u���b�N�̃T�C�Y
    unsigned long	num;        // �������u���b�N�̐�
    char*			addr;       // �������u���b�N�擪�A�h���X
    unsigned long	use_num;    // �������u���b�N�̎g�p��
    unsigned long	next;       // ���󂫃u���b�Nindex
    char*			flag;       // �u���b�N�g�p�t���O�擪�A�h���X
} SMemMngMpfInfo;

// ���������������
typedef struct _SMemMngInit {
	char*			mem_adr;	// �擪�A�h���X
	unsigned long	mem_size;	// �������T�C�Y
	struct {
		unsigned long	size;	// �������u���b�N�T�C�Y
		unsigned long	num;	// �������u���b�N��
	} mem_pool_info[GEVG_MEM_CONF_MAX_ID];
} SMemMngInit;


/* ----------------------------------------------------------------------*/
/* �֐��v���g�^�C�v�錾                                                  */
/* ----------------------------------------------------------------------*/
void *tkmalloc(size_t size);
void tkfree(void *ptr);
void *tkrealloc(void *ptr, size_t size);

int tkMemMngInitialize(SMemMngInit *ptInit);
int tkMemMngTerminate(void);


#endif /* _EXT_GEVG_MALLOC_H_ */

/*****************************************************************************/
/* Copyright (C) 2011 Panasonic Corporation.                                 */
/*****************************************************************************/
