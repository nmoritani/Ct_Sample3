/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerCard1_H_
#define __CtContainerCard1_H_

#include "CtContainerCard.h"

class CtContainerCard1 : public CtContainerCard {
public :

	CtContainerCard1(CtWindowCommonType Type);
	~CtContainerCard1();
	virtual bool startupContainer();

	virtual bool handleParamEvent(const CtEventParam& Param);
	
protected:
	GDI_IMAGE_ID getIcon(IconType type);
	
private :

	// Slot�̋L�^���
	void updateRecState(int int_Data);
	// Slot�̃J�[�h���
	void updateCardState(int int_Data);
	// Slot�̎c�ʏ��
	void updateSlotRemain(int int_Data);
};

#endif

