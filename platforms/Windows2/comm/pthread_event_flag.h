#pragma once
#include "pthread.h"

typedef struct eventflag {
	int             use;
	int             id;
	pthread_mutex_t signal_mutex;
	pthread_cond_t  signal_cond;
	pthread_mutex_t wait_mutex;
	pthread_cond_t  wait_cond;
	unsigned int	pattern;
	unsigned int	Attribute;
	unsigned int	init_val;
} eventflag;

#define	NUM_OF_EVENTFLAG	(5)

/*
* @brief �C�x���g�t���O�̑҂�����(wfmode).
*/
#define	TWF_ANDW	0x0000			//!< AND�҂�.
#define	TWF_ORW 	0x0002			//!< OR�҂�.
#define	TWF_CLR 	0x0001			//!< �N���A�w��.

/*
* @brief �C�x���g�t���O����(flgatr).
*/
#define TA_WSGL 	0x0000			//!< �����^�X�N�̑҂��������Ȃ�.
#define TA_WMUL 	0x0002			//!< �����^�X�N�̑҂�������.
#define	TA_CLR		0x0004			//!< �t���O�p�^�[���̃N���A.

//! �^�C���A�E�g�ݒ�.
#define TMO_POL 	0					//!< �|�[�����O.
#define TMO_FEVR	(-1)				//!< �i�v�҂�.

extern int init_eventflag_table();
extern int pthread_create_eventflag(int id, unsigned int attr, unsigned int init_val);
extern int pthread_delete_eventflag(int id);
extern int pthread_event_set_flag(int id, unsigned int pattern);
extern int pthread_event_t_wait_flag(int flgid, unsigned int waiptn, unsigned int wfmode, unsigned int *p_flgptn, long tmout);
extern int pthread_event_wait_flag(int flgid, unsigned int waiptn, unsigned int wfmode, unsigned int *p_flgptn);
extern int pthread_event_clear_flag(int flgid, unsigned int clrptn);
