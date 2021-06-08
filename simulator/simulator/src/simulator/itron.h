/**
 * Copyright (c) 2017  Panasonic Corporation, All rights reserved
 * $Id$
 *
 * @file
 * @brief   itron.h �̃��b�p�[ (�V�~�����[�^�[�p)
 */
#ifndef __ITRON_H__
#define __ITRON_H__

#include "win_itron.h"

/**
 *  itron4 �ł͉��L�V�X�e���R�[���� msg �� mbx �Ɖ�������Ă��邪�A�V�~�����[�^�[�Ŏg���Ă��� win �p�̃��C�u�����ł�
 *  �Ǐ]�ł��Ă��Ȃ��炵���V�X�e���R�[������ msg �̂܂܂Ȃ̂ł����őΉ�����
 */
#define snd_mbx(...)	snd_msg(__VA_ARGS__)
#define rcv_mbx(...)	rcv_msg(__VA_ARGS__)

/* wi�̃w�b�_��NULL��`�����݂��Ȃ����ߒǉ� */
#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void *)0)
#endif
#endif

#endif	/* __ITRON_H__ */
