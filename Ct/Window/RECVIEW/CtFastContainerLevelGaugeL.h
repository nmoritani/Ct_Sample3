/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Element:			CtFastContainerLevelGaugeL
 */


#ifndef __CtFastContainerLevelGaugeL_H__
#define __CtFastContainerLevelGaugeL_H__

#include "CtFastContainerLevelGauge.h"

class CtFastContainerLevelGaugeL : public CtFastContainerLevelGauge {

public :
	CtFastContainerLevelGaugeL();
	virtual ~CtFastContainerLevelGaugeL();
	
private :
	void updatePos();
};

#endif
