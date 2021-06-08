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
	// Slotの記録状態
	void updateRecState(int int_Data);
	// Slotのカード状態
	void updateCardState(int int_Data);
	// Slotの残量状態
	void updateSlotRemain(int int_Data);
};

#endif
