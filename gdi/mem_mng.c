/******************************************************************************
 Copyright (C) 2011 Panasonic Corporation.

 Filename:
     mem_mng.c

 Description:
     Declaration of memory pool

 Authors:
     YO - Yoshinori OKAZAKI@AVC

 File History:
 Date        Sign    Description
 ----------  ----    -------------------------------------------------------
 2011/10/04   YO     �V�K�쐬(AVFW���p)
 ******************************************************************************/

// ----------------------------------------------------------------------
// �C���N���[�h�t�@�C��
// ----------------------------------------------------------------------
#include <kernel.h>
#include "SysIf.h"

#include "mem_mng.h"

#ifdef WIN32_GUI_SIM
#include <smDebugSerial.h>
#include "kernel_id.h"
#include "win_itron.h"
#else
#include <dbgserial/smDebugSerial.h>
#endif

// ----------------------------------------------------------------------
// �萔��`
// ----------------------------------------------------------------------
#define	DBG_MEM_POOL_VARIABLE	(0)


// ----------------------------------------------------------------------
// �ϐ��錾
// ----------------------------------------------------------------------
// �������v�[���Ǘ��e�[�u��
SMemMngPoolMng g_tMemMngPoolTable[GEVG_MEM_CONF_MAX_ID + 1];

// �������ς݃t���O
static unsigned int g_uiMemMngInitFlg = 0;


// ----------------------------------------------------------------------
// �֐���`
// ----------------------------------------------------------------------
static void* MemMngAlloc(size_t uiSize);
static void MemMngFree(void *pAddr);
static size_t MemMngGetSize(void *pAddr);

static MEM_ER mem_mng_lock(void);
static MEM_ER mem_mng_unlock(void);

/***********************************************************************
   API �֐�
************************************************************************/
static int max_memory_syze = 0;

static BOOL get_memory_size(ID mplid, int *mem_size)
{
	T_RMPL rmpl;

	if (mem_size == NULL)
		return FALSE;
	
	if (ref_mpl(mplid, &rmpl) != E_OK) {
		return FALSE;
	}
	*mem_size = rmpl.fmplsz;

	return TRUE;
}

static int get_remain_mem_percent(ID mplid)
{
	int remain;

	if (0 == max_memory_syze) {
		return (get_memory_size(mplid, &max_memory_syze)) ? 100 : 0;
	}

	if (!get_memory_size(mplid, &remain)) {
		return 0;
	}

	//smDebugPrintf(1, "ID:[%d]  �������c��: %d%%(%d / %d)\n", mplid, (remain * 100 / max_memory_syze), remain, max_memory_syze);

	//�c�胁�����T�C�Y�����ŕԂ�
	return remain * 100 / max_memory_syze;
}

void *gdi_alloc(int size)
{
	void *mem;

	if (tget_mpl(GFX_RESMPL_ID, size, &mem,  500) != E_OK) {
		return NULL;
	}
	return mem;
}

void gdi_free(void *ptr)
{
	rel_mpl(GFX_RESMPL_ID, ptr);
}

int gdi_remain_mem_percent()
{
	return get_remain_mem_percent(GFX_RESMPL_ID);
}

void *gdi_bmp_alloc(int size, int align)
{
	void *p = NULL;
	unsigned long temp = 0;

	size += align+4;
	if (tget_mpl(GUI_WORKMPL_ID, size, &p,  500) != E_OK) {
		return NULL;
	}
	temp = (unsigned long)p + 4;
	if (temp & (align-1)) {
		p = (void *)((temp & (0xFFFFFFFF-(align-1))) +align);
	} else {
		p = (void *)temp;
	}
	((unsigned long *)p)[-1] = temp - 4;

	return p;
}

void gdi_bmp_free(void *ptr)
{
	unsigned long temp = 0;
	
	if (ptr != NULL) {
		temp = ((unsigned long *)ptr)[-1];
	}
	rel_mpl(GUI_WORKMPL_ID, (void *)temp);
}

int gdi_bmp_remain_mem_percent()
{
	return get_remain_mem_percent(GUI_WORKMPL_ID);
}


void *gui_alloc(int size, int align)
{
	void *p = NULL;
	unsigned long temp = 0;

	size += align+4;
	if (tget_mpl(GUI_WORKMPL_ID, size, &p,  500) != E_OK) {
		return NULL;
	}
	temp = (unsigned long)p + 4;
	if (temp & (align-1)) {
		p = (void *)((temp & (0xFFFFFFFF-(align-1))) +align);
	} else {
		p = (void *)temp;
	}
	((unsigned long *)p)[-1] = temp - 4;

	return p;
}

void gui_free(void *ptr)
{
	unsigned long temp = 0;
	
	if (ptr != NULL) {
		temp = ((unsigned long *)ptr)[-1];
	}
	rel_mpl(GUI_WORKMPL_ID, (void *)temp);
}

int gui_remain_mem_percent()
{
	return get_remain_mem_percent(GUI_WORKMPL_ID);
}

int largesize = 0;
void *tkmalloc(size_t size)
{
	void * p;

	if (size <= 32*1024) {		// 32KB���傫�����TkMalloc���g�p���Ȃ�(mem_config.h���Q��)
		p = MemMngAlloc(size);
	} else {
		p = gui_alloc(size, 0x10);
	}
	return p;
}

void tkfree(void *ptr)
{
	if ((g_tMemMngPoolTable[0].m_pStartAddr <= ptr) &&
		(ptr <= g_tMemMngPoolTable[10].m_pEndAddr)) {
		MemMngFree(ptr);
	} else {
		gui_free(ptr);
	}
}

void *tkrealloc(void *ptr, size_t size)
{
	void* p;
	size_t	blsz;

	if (ptr == NULL) {
		return (tkmalloc(size));
	}

	blsz = MemMngGetSize(ptr);
	if (blsz < size) {
		p = tkmalloc(size);
		if (p == NULL) {
			tkfree(ptr);
			return (NULL);
		}
		memcpy(p, ptr, blsz);
		tkfree(ptr);
	} else {
		p = ptr;
	}

	return p;
}

/***********************************************************************
 Function : �������u���b�N�l��
 Calling  : void* MemMngAlloc(size_t uiSize)
 Input    : size_t uiSize : �T�C�Y
 OutPut   : �Ȃ�
 Return   : �������u���b�N�̐擪�A�h���X
 Comment  : 
 Update   : 2007.11.02 : AW : �V�K�쐬
            2007.11.26 : AW : ��^�X�N�R���e�L�X�g�Ăяo���Ή�
            2008.08.20 : AW : �ĒT���J�n�v�[���̏����l��NULL����
                             �Ǘ��e�[�u���̐擪�ɕύX
************************************************************************/
static void* MemMngAlloc(size_t uiSize)
{
    MEM_ER ercd;
    MEM_VP pMemBlk = NULL;
    MEM_ER eRet;
    SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;

    // �����`�F�b�N
    if (uiSize <= 0) {
        return NULL;
    }

    eRet = mem_mng_lock();
    if (eRet != MEM_E_OK) {
        return NULL;
    }

    // �����ς݃`�F�b�N
    if (g_uiMemMngInitFlg != 1) {
        (void)mem_mng_unlock();
        return NULL;
    }

    // ����uiSize�ɑΉ�����Œ蒷�������v�[�������݂���ꍇ�́A
    // �Y������v�[���̃������u���b�N���l������

    // �Ή�����Œ蒷�������v�[������`�T������
    while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
        if ((pMemPoolMng->m_tPoolData.m_uiMinSize <= (unsigned long)uiSize) &&
            ((unsigned long)uiSize <= pMemPoolMng->m_tPoolData.m_uiMaxSize) &&
            (pMemBlk == NULL)) {
            //  �Œ蒷�������u���b�N���l������
            ercd = tkmem_mng_pget_mpf(pMemPoolMng->m_Id, &pMemBlk);
            if (ercd != MEM_E_OK) {
                // �l���G���[�̂Ƃ��͖����I��NULL�ɂ���
                 pMemBlk = NULL;

				// �擾���s
				pMemPoolMng->m_tPoolData.m_ulFail ++;
				
                // �������u���b�N�̊l���Ɏ��s�����ꍇ�́A��ʃv�[����
                // �u���b�N�ł̎擾�����݂邽�߂� 1�v�[����i�߂�
                pMemPoolMng ++;
            }
			else
			{
				// �擾����(���v���X�V)
				if (pMemPoolMng->m_tPoolData.m_ulPeakSize < (unsigned long)uiSize) {
					pMemPoolMng->m_tPoolData.m_ulPeakSize = (unsigned long)uiSize;
				}
				pMemPoolMng->m_tPoolData.m_ulUseNum ++;
				if (pMemPoolMng->m_tPoolData.m_ulPeakNum < pMemPoolMng->m_tPoolData.m_ulUseNum) {
					pMemPoolMng->m_tPoolData.m_ulPeakNum = pMemPoolMng->m_tPoolData.m_ulUseNum;
				}
			}
            break;   /* pgr0701 */
        }
        pMemPoolMng++;
    }

    // ����uiSize�ɑΉ�����Œ蒷�������v�[�������݂��Ȃ��ꍇ�́A
    // �l���\�ȃv�[���̃u���b�N���l������

    if (pMemBlk == NULL) {
        // �Ή�����Œ蒷�������v�[������`�T������
        while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
            //  �Œ蒷�������u���b�N���l������
            ercd = tkmem_mng_pget_mpf(pMemPoolMng->m_Id, &pMemBlk);
            if (ercd != MEM_E_OK) {
                // �l���G���[�̂Ƃ��͖����I��NULL�ɂ���
                pMemBlk = NULL;
				// �擾���s
				pMemPoolMng->m_tPoolData.m_ulFail ++;
            } else {
				// �擾����(���v���X�V)
				if (pMemPoolMng->m_tPoolData.m_ulPeakSize < (unsigned long)uiSize) {
					pMemPoolMng->m_tPoolData.m_ulPeakSize = (unsigned long)uiSize;
				}
				pMemPoolMng->m_tPoolData.m_ulUseNum ++;
				if (pMemPoolMng->m_tPoolData.m_ulPeakNum < pMemPoolMng->m_tPoolData.m_ulUseNum) {
					pMemPoolMng->m_tPoolData.m_ulPeakNum = pMemPoolMng->m_tPoolData.m_ulUseNum;
				}
				pMemPoolMng->m_tPoolData.m_ulOtherSize ++;
                break;  /* pgr0701 */
            }

            pMemPoolMng++;
        }
    }
	
    (void)mem_mng_unlock();
    return (void*)pMemBlk;
}

/***********************************************************************
 Function : �������u���b�N�ԋp
 Calling  : void MemMngFree(void *pAddr)
 Input    : void *pAddr : �������u���b�N�̐擪�A�h���X
 OutPut   : �Ȃ�
 Return   : �Ȃ�
 Comment  : 
 Update   : 2007.11.02 : AW : �V�K�쐬
            2007.11.26 : AW : ��^�X�N�R���e�L�X�g�Ăяo���Ή�
************************************************************************/
static void MemMngFree(void *pAddr)
{
    MEM_ER ercd;
    MEM_ER eRet;
    SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;

    // �����`�F�b�N
    if (pAddr == NULL) {
        return ;
    }

    eRet = mem_mng_lock();
    if(eRet != MEM_E_OK) {
        return ;
    }

    // �������`�F�b�N
    if (g_uiMemMngInitFlg != 1) {
        eRet = mem_mng_unlock();
        if (eRet != MEM_E_OK) {
            return ;
        }
        return ;
    }

	// ����addr���Œ蒷�������v�[���̃A�h���X�̏ꍇ�́A
    // �Œ蒷�������u���b�N��ԋp����
    while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
        if ((pMemPoolMng->m_pStartAddr <= pAddr) &&
            (pAddr <= pMemPoolMng->m_pEndAddr)) {
            // �Œ蒷�������u���b�N��ԋp����
            ercd = tkmem_mng_rel_mpf(pMemPoolMng->m_Id, pAddr);
            if (ercd == MEM_E_OK) {
            	if(pMemPoolMng->m_tPoolData.m_ulUseNum > 0){
					pMemPoolMng->m_tPoolData.m_ulUseNum --;
            	}
                break;    /*    pgr0701 */ /* �Ӑ}����break */
            } else {
                // �������Ȃ�(�v���I�ȏ��)
            }
            break;
        }

        pMemPoolMng++;
    }

    (void)mem_mng_unlock();
    return ;
}

/***********************************************************************
 Function : �������u���b�N�ԋp
 Calling  : size_t MemMngGetSize(void *pAddr)
 Input    : void *pAddr : �������u���b�N�̐擪�A�h���X
 OutPut   : size_t �������u���b�N�T�C�Y
 Return   : �Ȃ�
 Comment  : 
 Update   : 2011.10.04 : AW : �V�K�쐬
************************************************************************/
static size_t MemMngGetSize(void *pAddr)
{
    SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;
    MEM_ER eRet;

    // �����`�F�b�N
    if (pAddr == NULL) {
        return (0);
    }

    eRet = mem_mng_lock();
    if(eRet != MEM_E_OK) {
        return (0);
    }

    // �������`�F�b�N
    if (g_uiMemMngInitFlg != 1) {
        (void)mem_mng_unlock();
        return (0);
    }

    // ����addr�̌Œ蒷�u���b�N����������
    while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
        if ((pMemPoolMng->m_pStartAddr <= pAddr) &&
            (pAddr <= pMemPoolMng->m_pEndAddr)) {
            (void)mem_mng_unlock();
            return (pMemPoolMng->m_tPoolData.m_uiMaxSize);
        }
        pMemPoolMng++;
    }

    (void)mem_mng_unlock();
    return (0);
}

/***********************************************************************
 Function : �������֐�
 Calling  : int tkMemMngInitialize(SMemMngInit *ptInit)
 Input    : �Ȃ�
 OutPut   : �Ȃ�
 Return   :  0 : ����I��
            -1 : �G���[
 Comment  : 
 Update   : 2007.10.18 : AW : �V�K�쐬
            2007.11.26 : AW : ��^�X�N�R���e�L�X�g�Ăяo���Ή�
            2011.10.07 : YO : GE�p�ɍ�蒼��
            2011.10.18 : YO : CACHE-IF��PURGE�R�[�h�ǉ�
************************************************************************/
int tkMemMngInitialize(SMemMngInit *ptInit)
{
	MEM_ER ercd;
	MEM_T_CMPF pk_cmpf;
	MEM_ID mpfid;
	SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;
	char*			pStartAddr;
	unsigned long	ulMemSize;
	int	i;

	// �������`�F�b�N
	if (g_uiMemMngInitFlg == 1) {
		return -1;
	}

	// �p�����[�^�`�F�b�N
	if (ptInit == NULL) {
		return -1;
	}

	// �������A�h���X�`�F�b�N
	if (ptInit->mem_adr == NULL) {
		return -1;
	}

	// �������v�[���擪���m�F
	if (ptInit->mem_pool_info[0].size == 0) {
		// �擪�� 0 �͂�������
		return -1;
	}
	
	// �������J�n�A�h���X�A�S�̃T�C�Y�擾
	pStartAddr	= ptInit->mem_adr;
	ulMemSize	= ptInit->mem_size;

	// �������Ǘ���񏉊���
	memset(pMemPoolMng, 0, sizeof(SMemMngPoolMng)*(GEVG_MEM_CONF_MAX_ID + 1));

	// �������v�[���̐���
	for (i = 0; i < GEVG_MEM_CONF_MAX_ID; i ++) {
		// �������v�[�������I��
		if ((ptInit->mem_pool_info[i].num == 0) ||
			(ptInit->mem_pool_info[i].size == 0)) {
			break;
		}

		// ��I�[�v�[��(id < MAX_ID -1)
		if (i < (GEVG_MEM_CONF_MAX_ID - 1)) {
			// �T�C�Y�͏����Ŗ�����΂Ȃ�Ȃ�
			if (ptInit->mem_pool_info[i+1].size < ptInit->mem_pool_info[i].size) {
				return -1;
			}
		}

		// �v�[���Ǘ����̐ݒ�
		pMemPoolMng->m_tPoolData.m_uiBlkSize	= ptInit->mem_pool_info[i].size;
		pMemPoolMng->m_tPoolData.m_uiBlkNum		= ptInit->mem_pool_info[i].num;
		if (i == 0) {
			// �擪�� 1 ����
			pMemPoolMng->m_tPoolData.m_uiMinSize	= 1;
		} else {
			// 2�Ԗڈȍ~�́A1�O + 1
			pMemPoolMng->m_tPoolData.m_uiMinSize	= ptInit->mem_pool_info[i-1].size + 1;
		}
		pMemPoolMng->m_tPoolData.m_uiMaxSize	= ptInit->mem_pool_info[i].size;
		pMemPoolMng->m_tPoolData.m_ulPeakSize	= pMemPoolMng->m_tPoolData.m_uiMinSize;
		pMemPoolMng->m_tPoolData.m_ulUseNum		= 0;
		pMemPoolMng->m_tPoolData.m_ulPeakNum	= 0;
		pMemPoolMng->m_tPoolData.m_ulFail		= 0;
		pMemPoolMng->m_tPoolData.m_ulOtherSize	= 0;
		pMemPoolMng->m_pStartAddr = pStartAddr;
		pMemPoolMng->m_pEndAddr   = (char*)pMemPoolMng->m_pStartAddr
			+ MEM_TSZ_MPF(ptInit->mem_pool_info[i].size , ptInit->mem_pool_info[i].num) - 1;

		// �I�[���������T�C�Y�𒴂���
		if (((unsigned long)(ptInit->mem_adr) + ptInit->mem_size) < (unsigned long)(pMemPoolMng->m_pEndAddr)) {
			return -1;
		}
		
		// �������v�[���쐬
		pk_cmpf.mpfatr	= MEM_TA_TFIFO;
		pk_cmpf.blkcnt	= pMemPoolMng->m_tPoolData.m_uiBlkNum;
		pk_cmpf.blksz	= pMemPoolMng->m_tPoolData.m_uiBlkSize;
		pk_cmpf.mpf		= pMemPoolMng->m_pStartAddr;

		// �Œ蒷�������v�[���𐶐�����
		ercd = tkmem_mng_acre_mpf(&pk_cmpf, &mpfid);
		if (ercd != MEM_E_OK) {
			return -1;
		} else {
			pMemPoolMng->m_Id = mpfid;
		}

		pStartAddr = (char*)pMemPoolMng->m_pEndAddr + 1;
		pMemPoolMng++;
	}

	ercd = mem_mng_lock();
	if(ercd != MEM_E_OK) {
		return -1;
	}
	// �������ς݃t���O�𗧂Ă�
	g_uiMemMngInitFlg = 1;
	(void)mem_mng_unlock();

	return 0;
}

/***********************************************************************
 Function : �I���֐�
 Calling  : int tkMemMngTerminate(void)
 Input    : �Ȃ�
 OutPut   : �Ȃ�
 Return   : 0 : ����I��
            -1 : �G���[
 Comment  : 
 Update   : 2007.10.18 : AW : �V�K�쐬
            2007.11.26 : AW : ��^�X�N�R���e�L�X�g�Ăяo���Ή�
************************************************************************/
int tkMemMngTerminate(void)
{
	int iRet = 0;
	MEM_ER ercd;
	SMemMngPoolMng* pMemPoolMng = g_tMemMngPoolTable;

	ercd = mem_mng_lock();
	if(ercd != MEM_E_OK) {
		return -1;
	}

	// �������`�F�b�N�͂��Ȃ�
	// �������������̃G���[�����ɂ�菉�����������������Ȃ������ꍇ���A
	// �r���܂łɊl���������\�[�X��������邽��

	while (pMemPoolMng->m_tPoolData.m_uiBlkNum != 0) {
		// �Œ蒷�������v�[�����폜����
		ercd = tkmem_mng_del_mpf(pMemPoolMng->m_Id);
		if ((ercd != MEM_E_OK) && (ercd != MEM_E_ID)) {
			// �I���������̃G���[�����́A�\�Ȍ��菈���𑱍s����
			iRet = -1;
		} else {
			// �폜�����Œ蒷�������v�[����ID�ԍ����N���A����
			pMemPoolMng->m_Id = 0;
		}
		pMemPoolMng++;
	}

	// �������ς݃t���O��������
	g_uiMemMngInitFlg = 0;
	(void)mem_mng_unlock();

	return iRet;
}

/***********************************************************************
 Function : �A�g�~�b�N�ȃ��b�N�J�n
 Calling  : ER mem_mng_lock()
 Input    : �Ȃ�
 OutPut   : �Ȃ�
 Return   : ����I��(E_OK)�܂��̓G���[�R�[�h
 Comment  : 
 Update   : 2007.11.26 : AW : �V�K�쐬
            2008.04.14 : AW : vent_cim/ivent_cim���g�p���Ȃ��悤�ɏC��
************************************************************************/
static MEM_ER mem_mng_lock(void)
{
    ER eRet = E_OK;

    eRet = loc_cpu();
    if (eRet == E_CTX) {
        eRet = iloc_cpu();
    }
    if (eRet == E_OK)
		return (MEM_E_OK);
	
    return (MEM_E_PAR);
}

/***********************************************************************
 Function : �A�g�~�b�N�ȃ��b�N����
 Calling  : ER mem_mng_unlock(void)
 Input    : �Ȃ�
 OutPut   : �Ȃ�
 Return   : ����I��(E_OK)�܂��̓G���[�R�[�h
 Comment  : 
 Update   : 2007.11.26 : AW : �V�K�쐬
            2008.04.14 : AW : vlea_cim/ivlea_cim���g�p���Ȃ��悤�ɏC��
************************************************************************/
static MEM_ER mem_mng_unlock(void)
{
    ER eRet = E_OK;

    eRet = unl_cpu();
    if (eRet == E_CTX) {
        eRet = iunl_cpu();
    }
    if (eRet == E_OK)
		return (MEM_E_OK);
	
    return (MEM_E_PAR);
}

#if CFG_ENABLE_HJ_SHELL
void ge_mpl_info(void)
{
	int id;
	
	smDebugPrintf(1, "ID,StAdd,EndAdd,BlkSize,BlkNum,MinSize,MaxSize,PeakSize,UseNum,PeakNum,FailNum,OthSize\r\n");
	for(id=0;id<GEVG_MEM_CONF_MAX_ID;id++){
		smDebugPrintf(1, "%x,%x,%x,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n",
			g_tMemMngPoolTable[id].m_Id,
			g_tMemMngPoolTable[id].m_pStartAddr,
			g_tMemMngPoolTable[id].m_pEndAddr,
			g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkSize,
		    g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum,
			g_tMemMngPoolTable[id].m_tPoolData.m_uiMinSize,
			g_tMemMngPoolTable[id].m_tPoolData.m_uiMaxSize,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulPeakSize,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulPeakNum,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulFail,
			g_tMemMngPoolTable[id].m_tPoolData.m_ulOtherSize );
		}
	smDebugPrintf(1, "---------------------\r\n\r\n\r\n");
}
#endif /* CFG_ENABLE_HJ_SHELL */


void geman_mpl_info(void)
{
	unsigned long id, use_total = 0, total = 0;
	
	smDebugPrintf(1, "|Block Size X Block Num  |UsedSize(Peak Num)  | Percent\n");
	for (id=0;id<GEVG_MEM_CONF_MAX_ID;id++) {
		smDebugPrintf(1, " %12d X %4d , %12d(%4d), (%3d) \n",
					  g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkSize,
					  g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum,
					  g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum,
					  g_tMemMngPoolTable[id].m_tPoolData.m_ulPeakNum,
					  (g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum*100)/(g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum));
		use_total += (g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkSize)*(g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum);
		total += (g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkSize)*(g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum);
		}
	smDebugPrintf(1, "-------- %12d / %12d ---------------------\n", use_total, total);
}


BOOL GDI_checkRemainMpl(unsigned int percent)
{
#ifdef WIN32_GUI_SIM
	return FALSE;
#else
	unsigned int id, per;
	
	for (id = 0; id < GEVG_MEM_CONF_MAX_ID; id++) {
		if (g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum == 0 ||
			g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum == 0) {
			continue;
		}

		per = (g_tMemMngPoolTable[id].m_tPoolData.m_ulUseNum * 100)/g_tMemMngPoolTable[id].m_tPoolData.m_uiBlkNum;
		if (per > percent) {	// percent�ȏ�g�p���Ă���΁Atrue��Ԃ�
			return TRUE;
		}
	}
	return FALSE;
#endif
}

/***********************************************************************
 Function : �Œ蒷�������v�[���̐���
 Calling  : MEM_ER_ID tkmem_mng_acre_mpf(MEM_T_CMPF *pk_cmpf)
 Input    : MEM_T_CMPF *pk_cmpf : �Œ蒷�������v�[������������ꂽ�p�P�b�g�ւ̃|�C���^
 OutPut   : MEM_ID *id : ���������Œ蒷�������v�[����ID�ԍ�(���̒l)
 Return   : ����I��(MEM_E_OK)�܂��̓G���[�R�[�h
 Comment  : 
 Update   : 2007.11.26 : AW : �V�K�쐬
            2007.11.26 : YO : �C��
            2007.12.07 : AW : ITRON�̌^��Ǝ��̌^�ɕύX
************************************************************************/
MEM_ER tkmem_mng_acre_mpf(MEM_T_CMPF* pk_cmpf, MEM_ID* id)
{
    SMemMngMpfInfo* info = NULL;
    unsigned long i;

    // �����`�F�b�N
    if ((pk_cmpf == NULL) || (id == NULL)) {
        return MEM_E_PAR;
    }

    if ((pk_cmpf->blkcnt <= 0) || (pk_cmpf->blksz <= 0) || (pk_cmpf->mpf == NULL)) {
        return MEM_E_PAR;
    }

    // �Œ蒷�������v�[���̈�̐擪�����͊Ǘ������i�[����Ƃ��A
    // ���̏��������s��
    info            = (SMemMngMpfInfo*)(pk_cmpf->mpf);
    info->num       = pk_cmpf->blkcnt;
    info->size      = pk_cmpf->blksz;
    info->use_num   = 0;
    info->next      = 0;
    info->addr      = (char*)(pk_cmpf->mpf) + MEM_TSZ_MPF_INFO(pk_cmpf->blkcnt);
    info->flag      = (char*)(pk_cmpf->mpf) + sizeof(SMemMngMpfInfo);

    // �g�p�t���O�N���A
    for (i = 0; i < info->num; i++) {
        info->flag[i] = 0;
    }

    // ID�ɂ̓A�h���X��Ԃ�
    *id = (MEM_ID)(pk_cmpf->mpf);
    return MEM_E_OK;
}


/***********************************************************************
 Function : �Œ蒷�������v�[���̍폜
 Calling  : MEM_ER tkmem_mng_del_mpf(MEM_ID mpfid)
 Input    : MEM_ID mpfid : �폜�Ώۂ̌Œ蒷�������v�[����ID
 OutPut   : �Ȃ�
 Return   : ����I��(MEM_E_OK)�܂��̓G���[�R�[�h
 Comment  : 
 Update   : 2007.11.26 : YO : �V�K�쐬
            2007.12.07 : AW : ITRON�̌^��Ǝ��̌^�ɕύX
************************************************************************/
MEM_ER tkmem_mng_del_mpf(MEM_ID mpfid)
{
    // ID�`�F�b�N
    if ((MEM_VP)mpfid == NULL) {
        return MEM_E_ID;
    }

    // �j�������͕s�v
    return MEM_E_OK;
}


/***********************************************************************
 Function : �Œ蒷�������v�[���̊l��
 Calling  : MEM_ER tkmem_mng_pget_mpf(MEM_ID mpfid, MEM_VP *p_blk)
 Input    : MEM_ID mpfid : �������u���b�N�l���Ώۂ̌Œ蒷�������v�[����ID�ԍ�
 OutPut   : MEM_VP blk : �l�������������u���b�N�̐擪�Ԓn
 Return   : ����I��(MEM_E_OK)�܂��̓G���[�R�[�h
 Comment  : 
 Update   : 2007.11.26 : YO : �V�K�쐬
            2007.12.07 : AW : ITRON�̌^��Ǝ��̌^�ɕύX
************************************************************************/
MEM_ER tkmem_mng_pget_mpf(MEM_ID mpfid, MEM_VP *p_blk)
{
    SMemMngMpfInfo* info = NULL;
    unsigned long i;

    // ID�`�F�b�N
    if ((MEM_VP)mpfid == NULL) {
        return MEM_E_ID;
    }

    // �p�����[�^�`�F�b�N
    if (p_blk == NULL) {
        return MEM_E_PAR;
    }

    info = (SMemMngMpfInfo*)mpfid;
    for (i = info->next; i < info->num; i++) {
        if (info->flag[i] == 0) {
            *p_blk = info->addr + (info->size * i); /* pgr0244 */
            info->flag[i] = 1;
            (info->next)++;
            (info->use_num)++;
            return MEM_E_OK;
        }
    }

    // �l�����s(�󂫃u���b�N�Ȃ�)
    return MEM_E_TMOUT;
}


/***********************************************************************
 Function : �Œ蒷�������v�[���̕ԋp
 Calling  : MEM_ER tkmem_mng_rel_mpf(MEM_ID mpfid, MEM_VP blk)
 Input    : MEM_ID mpfid : �������u���b�N�ԋp�Ώۂ̌Œ蒷�������v�[����ID�ԍ�
 OutPut   : MEM_VP blk : �ԋp���郁�����u���b�N�̐擪�Ԓn
 Return   : ����I��(MEM_E_OK)�܂��̓G���[�R�[�h
 Comment  : 
 Update   : 2007.11.26 : YO : �V�K�쐬
            2007.12.07 : AW : ITRON�̌^��Ǝ��̌^�ɕύX
************************************************************************/
MEM_ER tkmem_mng_rel_mpf(MEM_ID mpfid, MEM_VP blk)
{
    SMemMngMpfInfo* info = NULL;
    long            index;

    // ID�`�F�b�N
    if (mpfid == 0) {
        return MEM_E_ID;
    }

    // �����`�F�b�N
    if (blk == NULL) {
        return MEM_E_PAR;
    }

    info = (SMemMngMpfInfo*)mpfid;

    // �ԋp�u���b�N�`�F�b�N(�A���C�����g)
    index = (long)blk - (long)(info->addr);
    if (((unsigned long)index % info->size) != 0) {
        // �A�h���X���u���b�N�擪�ł͂Ȃ�
        return MEM_E_PAR;
    }

    // �ԋp�u���b�N�`�F�b�N(�͈�)
    index /= info->size;
    if (((long)index < 0) || ((unsigned long)index >= info->num)) {
        // �A�h���X���v�[���f�[�^�͈͊O
        return MEM_E_PAR;
    }

    // �ԋp�u���b�N�`�F�b�N(�g�p���)
    if (info->flag[index] == 0) {
        // �����蓖�ău���b�N
        return MEM_E_PAR;
    }

    // �Ǘ����X�V
    (info->use_num)--;
    info->flag[index] = 0;
    if ((unsigned long)index < info->next)
    {
        // �󂫃u���b�N�ʒu�X�V
        info->next = index;
    }

    return MEM_E_OK;
}
