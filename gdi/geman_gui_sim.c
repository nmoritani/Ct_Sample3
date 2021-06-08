/*!
 * \file        geman.cのダミー
 * \brief       Graphic Engine 管理
 * \date        2011/10/12 新規作成
 * \copyright   Panasonic
 * \author      Natsuko Masuda
 */
//#include "asic_reg.h"

#define PANA_ORG_FUNC
#define _DMPNATIVE_

#include "geman.h"

/***************************************************************
				マクロ定義
***************************************************************/

/***************************************************************
				ｅｎｕｍ
***************************************************************/

/***************************************************************
				構造体
***************************************************************/

/***************************************************************
				プロトタイプ
***************************************************************/
	
/***************************************************************
				変数宣言
***************************************************************/

//------------------------------------------------------------
//! Graphic Manager Task
/*!
 * \param[] 
 * \param[] 
 * \return  
 * \note    
 * @date       12.02.09 API層の処理をタスクに移植
 */
void initGEman(void)
{
	/* Dummy */
}


// セミホスティング対応
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


// 物理アドレスを論理アドレスに変換
void *GE_CnvLogicAddr(unsigned int addr)
{
	return (void *)addr;
}

// 論理アドレスを物理アドレスに変換
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



// DMP内部から参照されてるため消すとコンパイルエラーになる
////////////////////////////
void utl_armcom_cachePurgeALL(void){}
void snprintf(){}
////////////////////////////
