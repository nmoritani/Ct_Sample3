/*!
 * \file        geman.c�̃_�~�[
 * \brief       Graphic Engine �Ǘ�
 * \date        2011/10/12 �V�K�쐬
 * \copyright   Panasonic
 * \author      Natsuko Masuda
 */
//#include "asic_reg.h"

#define PANA_ORG_FUNC
#define _DMPNATIVE_

#include "geman.h"

/***************************************************************
				�}�N����`
***************************************************************/

/***************************************************************
				��������
***************************************************************/

/***************************************************************
				�\����
***************************************************************/

/***************************************************************
				�v���g�^�C�v
***************************************************************/
	
/***************************************************************
				�ϐ��錾
***************************************************************/

//------------------------------------------------------------
//! Graphic Manager Task
/*!
 * \param[] 
 * \param[] 
 * \return  
 * \note    
 * @date       12.02.09 API�w�̏������^�X�N�ɈڐA
 */
void initGEman(void)
{
	/* Dummy */
}


// �Z�~�z�X�e�B���O�Ή�
int $Sub$$_sys_open(const char *name, int openmode)
{
	/* Dummy */
	return (0);
}

void $Sub$$_sys_exit(int retcode)
{
	/* Dummy */
}

void $Sub$$_ttywrch(int ch)
{
	/* Dummy */
}

void __assert_fail(void)
{
	/* Dummy */
}


// �����A�h���X��_���A�h���X�ɕϊ�
void *GE_CnvLogicAddr(unsigned int addr)
{
	return (void *)addr;
}

// �_���A�h���X�𕨗��A�h���X�ɕϊ�
void *GE_CnvPhysicalAddr(unsigned int addr)
{
	return (void *)addr;
}

void GE_suspend(void)
{
	/* Dummy */
}

void GE_resume(void)
{
	/* Dummy */
}

void GE_Irq_gp_signal()
{
	/* Dummy */
}

void GE_Irq_psc_signal()
{
	/* Dummy */
}

void GE_Irq_ppf_signal()
{
	/* Dummy */
}



// DMP��������Q�Ƃ���Ă邽�ߏ����ƃR���p�C���G���[�ɂȂ�
////////////////////////////
void utl_armcom_cachePurgeALL(void){}
void snprintf(){}
////////////////////////////
