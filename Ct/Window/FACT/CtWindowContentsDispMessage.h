#ifndef __CtWindowContentsDispMessage_H__
#define __CtWindowContentsDispMessage_H__

#include "CtWindowContents.h"

class CtWindowContentsDispMessage : public CtWindowContents {
public :
	
	CtWindowContentsDispMessage(const CtWindowID WindowID);
	CtWindowContentsDispMessage(CtWindowContentsDispMessage& message);
	virtual ~CtWindowContentsDispMessage();

	//���ʒʒm���b�Z�[�W�p(APL��GUI�ւ̒ʒm)
	void setMessage(const char* message);								//APL���F�o���������b�Z�[�W���Z�b�g����(���b�Z�[�W���o���Ȃ��ꍇ��NULL)
																		//�p�����̂ݎg�p�\�B���s�R�[�h(\n)�͎g�p�\(�������A10�s�܂�)
	const char* getMessage();											//GUI���F���b�Z�[�W��NULL�ȊO�Ȃ甼�������w�i�ɂ��ĕ�������ʒ����ɕ\������

private:
	char m_message[50];
};

#endif
