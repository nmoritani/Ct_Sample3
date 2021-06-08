/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_resource.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (���\�[�X��`).
 *
 *	@author	���V �閾
 */
#ifndef	__WI_RESOURCE_H__
#define	__WI_RESOURCE_H__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * �V���{����`.
 *
 ****************************************************************************/
#define		IDD_WIN_ITRON		100		//!< �_�C�A���O�̃��\�[�XID.

BOOL ITRON_Init();
void ITRON_Quit();
void ITRON_START();
void ITRON_iset_flg(int flagid, UINT setptn);
BOOL ITRON_snd_msg(int mbxid, USHORT msgtype, int length, USHORT *data);

#ifdef __cplusplus
}
#endif
#endif	// __WI_RESOURCE_H__
/* End of file */
