/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_config.h
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[���̊���`.
 *
 *	@author	���V �閾
 */
#ifndef	__WI_CONFIG_H__
#define	__WI_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 *
 * �V���{����`.
 *
 ****************************************************************************/
#define		TMAX_MAXTSK		256			//!< �^�X�NID�̍ő�ԍ�.
#define		TMAX_MAXSEM		256			//!< �Z�}�t�HID�̍ő�ԍ�.
#define		TMAX_MAXFLG		256			//!< �C�x���g�t���OID�̍ő�ԍ�.
#define		TMAX_MAXDTQ		256			//!< �f�[�^�L���[ID�̍ő�ԍ�.
#define		TMAX_MAXMBX		256			//!< ���[���{�b�N�XID�̍ő�ԍ�.
#define		TMAX_MAXMBF		256			//!< ���b�Z�[�W�o�b�t�@ID�̍ő�ԍ�.
#define		TMAX_MAXMTX		256			//!< �~���[�e�b�N�XID�̍ő�ԍ�.
#define		TMAX_MAXPOR		256			//!< �����f�u�|�[�gID�̍ő�ԍ�.
#define		TMAX_MAXMPF		256			//!< �Œ蒷�������v�[��ID�̍ő�ԍ�.
#define		TMAX_MAXMPL		256			//!< �ϒ��������v�[��ID�̍ő�ԍ�.
#define		TMAX_MAXCYC		256			//!< �����n���h���ԍ��̍ő�ԍ�.
#define		TMAX_MAXALM		256			//!< �A���[���n���h���ԍ��̍ő�ԍ�.
#define		TMAX_MAXINT		256			//!< ���荞�݃n���h���ԍ��̍ő�ԍ�.
#define		TMAX_MAXRDV		0x7FFFFFFF	//!< �����f�u�ԍ��̍ő�ԍ�.

#define		TMAX_ACTCNT		1			//!< �^�X�N�N���v���L���[�C���O���̍ő吔.
#define		TBIT_FLGPTN		32			//!< �C�x���g�t���O�̃r�b�g��.
#define		TMAX_MPRI		256			//!< ���b�Z�[�W�D��x�̍ő�l.

#define		CYCLETIME		10			//!< �����^�C�}�Ԋu.

//#define	__ITRON3__					//!< Ver3.0
#ifndef		__ITRON3__
#ifndef		__ITRON4__
#define		__ITRON4__					//!< Ver4.0
#endif	//	__ITRON4__
#endif	//	__ITRON3__

#ifdef __cplusplus
}
#endif
#endif	// __WI_CONFIG_H__
/* End of file */
