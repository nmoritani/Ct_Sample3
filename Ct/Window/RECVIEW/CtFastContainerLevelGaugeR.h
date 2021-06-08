/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Element:			CtFastContainerLevelGaugeR
 */


#ifndef __CtFastContainerLevelGaugeR_H__
#define __CtFastContainerLevelGaugeR_H__

#include "CtFastContainerLevelGauge.h"

class CtFastContainerLevelGaugeR : public CtFastContainerLevelGauge {

public :
	CtFastContainerLevelGaugeR();
	virtual ~CtFastContainerLevelGaugeR();
	
private :
	void updatePos();
};

#endif
