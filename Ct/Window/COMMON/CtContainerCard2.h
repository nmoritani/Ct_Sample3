/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtButton
 */
 
#ifndef __CtContainerCard2_H_
#define __CtContainerCard2_H_

#include "CtContainerCard.h"

class CtContainerCard2 : public CtContainerCard {
public :
	CtContainerCard2(CtWindowCommonType Type);
	~CtContainerCard2();

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
