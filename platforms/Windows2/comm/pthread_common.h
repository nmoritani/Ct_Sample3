#pragma once
#include "pthread.h"
#include "winlib/system_time_spec.h"


#define ERR_OK			0					//!< ����I��.
#define ERR_SYS			(-5)				//!< �V�X�e���G���[.
#define ERR_NOSPT 		(-9)				//!< ���T�|�[�g�@�\.
#define ERR_RSFN		(-10)				//!< �\��@�\�R�[�h�ԍ�.
#define ERR_RSATR 		(-11)				//!< �\�񑮐�.
#define ERR_PAR			(-17)				//!< �p�����[�^�G���[.
#define ERR_ID			(-18)				//!< �s��ID�ԍ�.
#define ERR_CTX			(-25)				//!< �R���e�L�X�g�G���[.
#define ERR_MACV		(-26)				//!< �������A�N�Z�X�s�\�A�������A�N�Z�X���ᔽ.
#define ERR_OACV		(-27)				//!< �I�u�W�F�N�g�A�N�Z�X���ᔽ.
#define ERR_ILUSE		(-28)				//!< �T�[�r�X�R�[���s���g�p.
#define ERR_NOMEM 		(-33)				//!< �������s��.
#define ERR_NOID	 	(-34)				//!< ID�ԍ��s��.
#define ERR_OBJ			(-41)				//!< �I�u�W�F�N�g�̏�Ԃ��s��.
#define ERR_NOEXS 		(-42)				//!< �I�u�W�F�N�g�����݂��Ȃ�.
#define ERR_QOVR		(-43)				//!< �L���[�C���O�܂��̓l�X�g�̃I�[�o�[�t���[.
#define ERR_RLWAI 		(-49)				//!< �҂���ԋ�������.
#define ERR_TMOUT 		(-50)				//!< �|�[�����O���s�܂��̓^�C���A�E�g.
#define ERR_DLT			(-51)				//!< �҂��I�u�W�F�N�g���폜���ꂽ.
#define ERR_CLS			(-52)				//!< �҂��I�u�W�F�N�g�̏�Ԃ��ω�����.
#define ERR_WBLK		(-57)				//!< �m���u���b�L���O��t��.
#define ERR_BOVR		(-58)				//!< �o�b�t�@�I�[�o�[�t���[.


/* macro */
#define ARRAY_NUM(array) (sizeof(array) / sizeof(array[0]))
#define	ZERO_CLEAR(var)	 (memset(&(var), 0, sizeof(var)))

///////////////////////////////////////////////////////////////////////
//�X���b�h�N���p������`
typedef void *(PTHREAD_START_FUNC)(void *);
#define PTHREAD_START_FUNC_CAST(f)	(void*(*)(void*))((f))
typedef struct _thread_arg {
	unsigned int		tskatr;				//!< �^�X�N�̑���.
	void				*exinf;				//!< �g�����.
	PTHREAD_START_FUNC	*task;				//!< �X�^�[�g�E�A�h���X.
	int					itskpri;			//!< �����̃^�X�N�D��x.
	int					stksz;				//!< �X�^�b�N�E�T�C�Y.
	void				*stk;				//!< �X�^�b�N�̈�̐擪�A�h���X.
} thread_arg;


///////////////////////////////////////////////////////////////////////
//�T�C�N���b�N�n���h���p������`
typedef void (CYCLETIMER__FUNC)();
#define CYCLETIMER_FUNC_CAST(f)		(void (*)())((f))
typedef struct _cycle_time_arg {
	unsigned int		attr; 				//!< �����n���h������.
	CYCLETIMER__FUNC	*func;				//!< �����n���h���̃A�h���X.
	long				cycle_time;			//!< �����N�����ԊԊu(ms�P��)
} cycle_time_arg;

typedef struct _cycle_handler_state {
	bool	active;					// �����n���h��������
	long	remain_time; 			// ���N�������܂ł̎���
} cycle_handler_state;


///////////////////////////////////////////////////////////////////////
extern int create_cycle_timer_thread(unsigned int id, thread_arg *parg);
