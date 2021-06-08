/****************************************************************************
 *	Copylight(C) 2011-2012 Kanazawa-soft-design,LLC.All Rights Reserved.
 ****************************************************************************/
/*!
 *	@file	wi_variable_mempool.c
 *
 *	@brief	Windows�� iTRON�T�[�r�X�R�[�� (�ϒ��������v�[��).
 *
 *	@author	���V �閾
 */
#include <windows.h>
#include <windowsX.h>
#include <stdio.h>
#include "wi_variable_mempool.h"

/****************************************************************************
 *
 * �\���̒�`.
 *
 ****************************************************************************/
/*!
 *
 * @brief �ϒ��������u���b�N�̃w�b�_���\����.
 *
 */
typedef struct {
	INT		Size;		//!< �������u���b�N�̃T�C�Y (�ŏ�ʃr�b�g=1�̂Ƃ��݂��o����).
	DWORD	TaskId;		//!< �������u���b�N��݂��o�����^�X�N��ID.
} MEMHDR;

/****************************************************************************
 *
 * ���[�J���֐���`.
 *
 ****************************************************************************/
static BYTE		*AllocVerMem( INT len, BYTE* buf, INT max_size, DWORD tskid );
static BOOL		FreeVarMem( BYTE* adr, BYTE* buf, INT max_size );
static INT		GetFreeBufSize( INT *max_free, BYTE* buf, INT max_size );
static void		MemAllocWaitTask( WIMPLOBJ *mpl );

/****************************************************************************
 *
 * ���[�J���ϐ���`.
 *
 ****************************************************************************/
static WIHDR		*ObjList;		//!< �ϒ��������v�[������X�g�̃|�C���^.

/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̏�������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_InitVarMemPool( void )
{
	ObjList = NULL;
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̏I������.
 *
 *	@param	�Ȃ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_QuitVarMemPool( void )
{
	WIHDR		*next_ptr;
	WIMPLOBJ	*p = (WIMPLOBJ *)ObjList;

	while( p ){
		next_ptr = p->Hdr.Next;

		//! �������o�b�t�@���������.
		SAFE_RELEASE( p->MemBuf );

		//! �ϒ��������v�[����I�u�W�F�N�g�\���̂��������.
		SAFE_RELEASE( p );

		//! ���̃������v�[����I�u�W�F�N�g�\���̂����o��.
		p = (WIMPLOBJ *)next_ptr;
	}
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̐���.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *	@param	[in]	obj		�ϒ��������v�[���\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_CreateVarMemPool( INT id, const WIMPLOBJ *obj )
{
	ER			ercd;
	MEMHDR		*hdr;
	WIMPLOBJ	*p;

	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( obj->MemSize <= 0 ){
		return E_PAR;
	}
	//! �ϒ��������v�[����I�u�W�F�N�g���쐬����.
	p = (WIMPLOBJ *)wi_CreateObject( id, TMAX_MAXMPL, sizeof(WIMPLOBJ), obj, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������v�[���̃o�b�t�@���m�ۂ���.
	p->MemBuf = (BYTE*)malloc( obj->MemSize );
	if( !p->MemBuf ){
		SAFE_RELEASE( p );
		return E_NOMEM;
	}
	//! �m�ۂ����o�b�t�@���N���A����.
	memset( p->MemBuf, 0, obj->MemSize );

	//! �o�b�t�@�̐擪�Ƀ������u���b�N�w�b�_��t������.
	hdr         = (MEMHDR *)p->MemBuf;
	hdr->Size   = obj->MemSize;
	hdr->TaskId = 0;

	//! ���X�g�ɉϒ��������v�[����ǉ�����.
	wi_AddObject( (WIHDR *)p, &ObjList );

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̍폜.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_DeleteVarMemPool( INT id )
{
	ER			ercd;
	WIMPLOBJ	*p;

	//! �������v�[��ID�̃I�u�W�F�N�g���擾����.
	p = (WIMPLOBJ *)wi_FindObject( id, TMAX_MAXMPL, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! ���X�g����Y�����郁�����v�[������菜��.
	wi_DelObject( (WIHDR *)p, &ObjList );

	//! �҂��^�X�N�L���[���������.
	wi_WakeupDelResource( p->WaitQue );

	//! �������v�[���̃o�b�t�@���������.
	SAFE_RELEASE( p->MemBuf );

	//! �ϒ��������v�[����I�u�W�F�N�g�\���̂��������.
	SAFE_RELEASE( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�ϒ���������u���b�N�̊l��.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *	@param	[in]	adr		�������u���b�N�̃A�h���X���i�[����̈�̃|�C���^.
 *	@param	[in]	size	�������u���b�N�̃T�C�Y.
 *	@param	[in]	tmout	�^�C���A�E�g�ݒ�.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_GetVarMemPool( INT id, VP adr, INT size, TMO tmout )
{
	ER			ercd;
	WITSKOBJ	*tsk;
	WIMPLOBJ	*p;
	BYTE		*blk;

	//! �������v�[��ID�̃I�u�W�F�N�g���擾����.
	p = (WIMPLOBJ *)wi_FindObject( id, TMAX_MAXMPL, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !adr || size <= 0 || size > (INT)(p->MemSize - sizeof(MEMHDR)) ){
		return E_PAR;
	}
	*((BYTE **)adr) = NULL;

	//! �^�X�N�ȊO����̌Ăяo���̏ꍇ�̓G���[�ɂ���.
	tsk = wi_GetTaskObject( TSK_SELF );
	if( !tsk ){
		return E_CTX;
	}
	//! �w�肳�ꂽ�T�C�Y�̋󂫃��������m�ۂ���.
	blk = AllocVerMem( size, p->MemBuf, p->MemSize, tsk->Hdr.Id );

	//! ���������m�ۂł��Ȃ��ꍇ.
	if( !blk ){
		//! �K�v�ȃ������T�C�Y���^�X�N��I�u�W�F�N�g�ɃZ�b�g����.
		tsk->Param[0] = (VP)size;
		tsk->Param[1] = NULL;

		//! �������u���b�N���ԋp�����܂Ń^�X�N���X���[�v������.
		ercd = wi_TaskWait( id, TTW_MPL, tmout, p->Attribute, &(p->WaitQue) );

		//! �G���[���o�Ɠ����Ƀ������̊m�ۂ��o���Ă��܂����ꍇ�A�������͕ԋp����.
		if( ercd != E_OK ){
			if( tsk->Param[1] ){
				FreeVarMem( tsk->Param[1], p->MemBuf, p->MemSize );
			}
			return ercd;
		}
		//! �������u���b�N�̕ԋp�����Ŋm�ۂ����������u���b�N�̃A�h���X�����o��.
		blk = (BYTE *)(tsk->Param[1]);
	}
	//! �݂��o���������̃A�h���X��߂�l�Ɋi�[����.
	*((BYTE **)adr) = blk;
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�ϒ���������u���b�N�̕ԋp.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *	@param	[in]	adr		�ԋp���郁������u���b�N�̃A�h���X.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_ReleaseVarMemPool( INT id, VP adr )
{
	ER			ercd;
	WIMPLOBJ	*p;

	//! �������v�[��ID�̃I�u�W�F�N�g���擾����.
	p = (WIMPLOBJ *)wi_FindObject( id, TMAX_MAXMPL, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �������s���ȏꍇ�̓G���[�ɂ���.
	if( !adr ){
		return E_PAR;
	}
	//! �ԋp���ꂽ�������u���b�N���������.
	if( !FreeVarMem( (BYTE*)adr, p->MemBuf, p->MemSize ) ){
		return E_PAR;
	}
	//! �������u���b�N�l���҂��̃^�X�N������ꍇ�A���������m�ۂ���.
	MemAllocWaitTask( p );
	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�ϒ��������v�[���̎Q��.
 *
 *	@param	[in]	id		�������v�[��ID�ԍ�.
 *	@param	[out]	sts		�������v�[����Ԃ��i�[����\���̂̃|�C���^.
 *
 *	@retval	�G���[�R�[�h.
 */
ER		wi_RefarenceVarMemPool( INT id, WIMPLSTAT *sts )
{
	ER			ercd;
	WIMPLOBJ	*p;
	INT			total_free,max_free;

	//! �������v�[��ID�̃I�u�W�F�N�g���擾����.
	p = (WIMPLOBJ *)wi_FindObject( id, TMAX_MAXMPL, ObjList, &ercd );
	if( !p ){
		return ercd;
	}
	//! �󂫃������̃T�C�Y���擾����.
	total_free = GetFreeBufSize( &max_free, p->MemBuf, p->MemSize );

	//! �ϒ��������v�[���̏�Ԃ��\���̂ɃZ�b�g����.
	sts->WaitId        = wi_GetWaitTaskListFirstId( p->WaitQue );
	sts->TotalFreeSize = total_free;
	sts->MaxFreeSize   = max_free;
	sts->ExtInfo       = p->ExtInfo;
	sts->MemSize       = p->MemSize;
	sts->MemBuf        = p->MemBuf;

	return E_OK;
}

/****************************************************************************/
/*!
 *	@brief	�폜�����^�X�N���m�ۂ����������u���b�N���������.
 *
 *	@param	[in]	id		�폜�����^�X�NID�ԍ�.
 *
 *	@retval	�Ȃ�.
 */
void	wi_AllReleaseVarMemPool( INT id )
{
	WIMPLOBJ *p = (WIMPLOBJ *)ObjList;

	while( p ){
		INT		i,j;
		MEMHDR	*hdr1,*hdr2;

		//! �폜�����^�X�N�ɑ݂��o���Ă����������u���b�N��S�ĉ������.
		for( i = 0; i < p->MemSize; ){

			//! �o�b�t�@���烁�����u���b�N�̃w�b�_�����o��.
			hdr1 = (MEMHDR *)(&p->MemBuf[i]);

			//! �������u���b�N���󂫃u���b�N�ɂ���.
			if( hdr1->TaskId == id ){
				hdr1->TaskId = 0;
			}
			//! ���̃������u���b�N�����o��.
			i += hdr1->Size;
		}
		//! �אڂ����󂫃������u���b�N����������.
		for( i = 0; i < p->MemSize; ){

			//! �o�b�t�@���烁�����u���b�N�̃w�b�_�����o��.
			hdr1 = (MEMHDR *)(&p->MemBuf[i]);

			/*!
			 * �󂫃u���b�N�̏ꍇ�A���̃u���b�N���󂫃u���b�N�̂Ƃ���
			 * �������u���b�N����������1�ɂ���.
			 */
			if( hdr1->TaskId == 0 ){
				j = i + hdr1->Size;
				if( j < (p->MemSize - (signed)sizeof(MEMHDR)) ){
					hdr2 = (MEMHDR *)(&p->MemBuf[j]);
					if( hdr2->TaskId == 0 ){
						hdr1->Size += hdr2->Size;
						continue;
					}
				}
			}
			//! �������u���b�N���������Ȃ������Ƃ��͎��̃������u���b�N�����o��.
			i += hdr1->Size;
		}
		//! �҂��s�񂩂���ł���^�X�N���폜����.
		p->WaitQue = wi_DelWaitTaskList( id, p->WaitQue );

		//! �������u���b�N�l���҂��̃^�X�N������ꍇ�́A�󂫃������̊m�ۂɍĒ��킷��.
		MemAllocWaitTask( p );

		//! ���̃������v�[���\���̂������o��.
		p = (WIMPLOBJ *)(p->Hdr.Next);
	}
}

void	wi_RefarenceAllocatedVarMemPool(INT id)
{
	ER			ercd;
	WIMPLOBJ	*p;
	BYTE *buf;
	MEMHDR	*hdr;
	INT		i, max_size;

	//! �������v�[��ID�̃I�u�W�F�N�g���擾����.
	p = (WIMPLOBJ *)wi_FindObject(id, TMAX_MAXMPL, ObjList, &ercd);
	if (!p) {
		return;
	}

	//! �������u���b�N�̐擪���烊���N��H���āA�g�p�ς݃u���b�N��T��
	max_size = p->MemSize;
	buf      = p->MemBuf;

	// �w�b�_
	printf("       start      end     size     this     type\n");

	for (i = 0; i < max_size;  ) {

		//! �o�b�t�@���烁�����u���b�N�̃w�b�_�����o��.
		hdr = (MEMHDR *)buf;

		if (hdr->TaskId == 0) {
			// �󂫃u���b�N
		}
		else {
			// �g�p�ς݃u���b�N
			INT size    = hdr->Size - sizeof(MEMHDR);
			BYTE *start = buf + sizeof(MEMHDR);
			BYTE *end   = start + size - 1;
			UINT class_type = *(UINT*)(start+4);	// CtClassType
			UINT class_method = *(UINT*)start;		// �����o�֐��I�u�W�F�N�g�̃A�h���X(�N���X���Ɉ��)
			printf("    %08p-%08p %8d %8X %8X\n", start, end, size, class_method, class_type);
		}

		buf += hdr->Size;
		i += hdr->Size;
	}
	return;
}

/****************************************************************************/
/*!
 *	@brief	�w�肵���T�C�Y�̃������u���b�N���擾����.
 *
 *	@param	[in]	len			�擾���郁�����u���b�N�̃T�C�Y.
 *	@param	[in]	buf			�������o�b�t�@�̃|�C���^.
 *	@param	[in]	max_size	�������o�b�t�@�̃T�C�Y.
 *	@param	[in]	tskid		���������擾����^�X�N��ID.
 *
 *	@retval	�擾�����������u���b�N�̃|�C���^.
 */
static BYTE	*AllocVerMem( INT len, BYTE* buf, INT max_size, DWORD tskid )
{
	MEMHDR	*hdr;
	INT		i,req_size,remain;

	//! �擾����T�C�Y�Ƀw�b�_�T�C�Y�������ĕK�v�ȃ������T�C�Y���v�Z����.
	req_size = len + sizeof(MEMHDR);

	for( i = 0; i < max_size; ){

		//! �o�b�t�@���烁�����u���b�N�̃w�b�_�����o��.
		hdr = (MEMHDR *)(&buf[i]);

		if( hdr->TaskId == 0 ){
			if( hdr->Size >= req_size ){
				//! �󂫃u���b�N�̃T�C�Y����K�v�ȃT�C�Y���������]����v�Z���Ă���.
				remain = hdr->Size - req_size;

				//! �󂫃u���b�N���u�݂��o�����v�ɂ���.
				hdr->Size   = req_size;
				hdr->TaskId = tskid;

				if( remain > sizeof(MEMHDR) ){
					//! �󂫃u���b�N�ɗ]�肪����ꍇ�̓������u���b�N�𕪊����ė]��̋󂫃u���b�N���쐬����.
					hdr         = (MEMHDR *)(&buf[i+req_size]);
					hdr->Size   = remain;
					hdr->TaskId = 0;
				}else{
					//! �]�肪�w�b�_�T�C�Y�ȉ��̏ꍇ�A�݂��o�����������T�C�Y�ɗ]��������Ă���.
					hdr->Size += remain;
				}
				//! �߂�l�͎g�p�\�͋󂫃u���b�N�̐擪�A�h���X��Ԃ�.
				return &buf[i + sizeof(MEMHDR)];
			}
		}
		//! ���̃������u���b�N�����o��.
		i += hdr->Size;
	}
	return NULL;
}

/****************************************************************************/
/*!
 *	@brief	�������u���b�N��ԋp���ċ󂫃u���b�N�ɂ���.
 *
 *	@param	[in]	adr			�ԋp���郁�����u���b�N�̃|�C���^.
 *	@param	[in]	buf			�������o�b�t�@�̃|�C���^.
 *	@param	[in]	max_size	�������o�b�t�@�̃T�C�Y.
 *
 *	@retval	TRUE = OK. / FALSE = NG.
 */
static BOOL		FreeVarMem( BYTE* adr, BYTE* buf, INT max_size )
{
	MEMHDR	*hdr1,*hdr2,*hdr3;
	INT		i,j,pos;

	//! �ԋp���郁�����u���b�N�̃������o�b�t�@��̈ʒu���v�Z����.
	pos = ((INT)adr - (INT)buf) - (INT)sizeof(MEMHDR);

	//! �ԋp���郁�����u���b�N���������o�b�t�@�͈̔͊O�̏ꍇ�̓G���[�ɂ���.
	if( pos < 0 || pos >= (max_size - (INT)sizeof(MEMHDR)) ){
		return FALSE;
	}
	//! �������u���b�N�̐擪���烊���N��H���āA�ԋp���郁�����u���b�N��T��.
	hdr1 = NULL;
	for( i = 0; i < max_size && i <= pos; ){

		//! �o�b�t�@���烁�����u���b�N�̃w�b�_�����o��.
		hdr2 = (MEMHDR *)(&buf[i]);

		//! �������u���b�N�̃o�C�g���� 0 �̏ꍇ�A�������o�b�t�@���󂳂�Ă���̂ŏ����𒆒f����.
		if( hdr2->Size == 0 ){
			break;
		}
		if( i == pos ){
			//! �ԋp����u���b�N���󂫃u���b�N�̏ꍇ�̓G���[�ɂ���.
			if( hdr2->TaskId == 0 ){
				break;
			}
			//! �������u���b�N���󂫃u���b�N�ɂ���.
			hdr2->TaskId = 0;

			/*!
			 * ���̃u���b�N���󂫃u���b�N�̏ꍇ�A�ԋp�����u���b�N�ƌ�������
			 * ���̃u���b�N�����ł�����.
			 */
			j = i + hdr2->Size;
			if( j < (max_size - (INT)sizeof(MEMHDR)) ){
				hdr3 = (MEMHDR *)(&buf[j]);
				if( hdr3->TaskId == 0 ){
					hdr2->Size += hdr3->Size;
				}
			}
			/*!
			 * 1��O�̃u���b�N���󂫃u���b�N�̏ꍇ�A�ԋp�����u���b�N�ƌ�������
			 * �ԋp�����u���b�N�����ł�����.
			 */
			if( hdr1 && hdr1->TaskId == 0 ){
				hdr1->Size += hdr2->Size;
			}
			return TRUE;
		}
		//! ���̃������u���b�N�����o��.
		i += hdr2->Size;

		//! 1��O�̃������u���b�N�̃w�b�_�ʒu���X�V����.
		hdr1 = hdr2;
	}
	return FALSE;
}

/****************************************************************************/
/*!
 *	@brief	�󂫃o�b�t�@�̃T�C�Y���擾����.
 *
 *	@param	[out]	max_free	�ő�̘A���󂫗̈�̃T�C�Y���i�[����̈�̃|�C���^.
 *	@param	[in]	buf			�������o�b�t�@�̃|�C���^.
 *	@param	[in]	max_size	�������o�b�t�@�̃T�C�Y.
 *
 *	@retval	�󂫗̈�̍��v�T�C�Y.
 */
static INT	GetFreeBufSize( INT *max_free, BYTE* buf, INT max_size )
{
	MEMHDR	*hdr;
	INT		i,total_free;

	*max_free  = 0;
	total_free = 0;

	for( i = 0; i < max_size; ){

		//! �o�b�t�@���烁�����u���b�N�̃w�b�_�����o��.
		hdr = (MEMHDR *)(&buf[i]);

		//! �󂫃������u���b�N�̏ꍇ.
		if( hdr->TaskId == 0 ){
			//! ���傫�ȋ󂫃������u���b�N���������ꍇ�A�T�C�Y��ۑ�����.
			if( *max_free < hdr->Size ){
				*max_free = hdr->Size;
			}
			/*!
			 * �󂫃������̍��v�T�C�Y�ɋ󂫃u���b�N�̃T�C�Y�����Z����.
			 * (�������u���b�N�̃w�b�_�T�C�Y�͋󂫃T�C�Y�Ɋ܂߂Ȃ�)
			 */
			total_free += (hdr->Size - sizeof(MEMHDR));
		}
		//! ���̃������u���b�N�����o��.
		i += hdr->Size;
	}
	//! �ő�̘A�������󂫗̈�̃T�C�Y���烁�����u���b�N�̃w�b�_�T�C�Y������.
	if( *max_free != 0 ){
		*max_free -= sizeof(MEMHDR);
	}
	return total_free;
}

/****************************************************************************/
/*!
 *	@brief	�������u���b�N�l���҂������Ă���^�X�N�Ƀ�������݂��o��.
 *
 *	@param	[in]	mpl			�ϒ��������v�[����I�u�W�F�N�g�̃|�C���^.
 *
 *	@retval	�Ȃ�.
 */
static void		MemAllocWaitTask( WIMPLOBJ *mpl )
{
	WITSKOBJ *tsk;

	tsk = (WITSKOBJ *)mpl->WaitQue;
	while( tsk ){
		//! �w�肳�ꂽ�T�C�Y�̋󂫃��������m�ۂ���.
		tsk->Param[1] = AllocVerMem( (INT)(tsk->Param[0]), mpl->MemBuf, mpl->MemSize, tsk->Hdr.Id );
		if( !tsk->Param[1] ){
			break;
		}
		//! �X���[�v���Ă���^�X�N���N��������.
		wi_TaskWakeup( tsk->Hdr.Id, TTW_MPL, NULL );

		//! �҂��s�񂩂玟�̃^�X�N�����o��.
		tsk = tsk->QueLink;
	}
}

/* End of file */
