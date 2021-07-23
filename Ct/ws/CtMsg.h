/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtMsg
 */


#ifndef __CtMsg_H__
#define __CtMsg_H__

#include "CtObject.h"

/// �^�X�N�ԒʐM�Ɏg�p���郁�b�Z�[�W�̒��ۃN���X
/// �^�X�N�ԒʐM�����郁�b�Z�[�W�͂́A���̃N���X����h���N���X���쐬����
class CtMsg : public CtObject {
public :

	CtMsg();
	CtMsg(int Priority);
	
	int getPriority();
	void setPriority(int Priority);
	
public :
    virtual ~CtMsg();
	
private :
	int		m_Priority;
};

#endif
