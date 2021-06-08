/**
*  Copyright (c) 2018 Persol AVC Technology
*  Element:          CtFastContainerLevelGaugeL
*/

#include "CtFastContainerLevelGaugeL.h"


CtFastContainerLevelGaugeL::CtFastContainerLevelGaugeL()
{
}

CtFastContainerLevelGaugeL::~CtFastContainerLevelGaugeL()
{
}

void CtFastContainerLevelGaugeL::updatePos()
{
	// �e���x����Region��` (-1 �� updatePosCommon���œ��I�ύX����ӏ� )
	CtRegion rAori = CtRegion(
		VIEW_LEVELGAUGE_WIDE_W,		-1,
		VIEW_LEVELGAUGE_WIDE_W,		5
	);
	CtRegion rCenter = CtRegion(
		0,							-1,
		VIEW_LEVELGAUGE_WIDE_W,		5
	);
	CtRegion rBar = CtRegion(
		VIEW_LEVELGAUGE_MARGIN_W,	-1,
		VIEW_LEVELGAUGE_SHORT_W,	-1
	);

	int aori = getAngleValue();
	int balance = getBalanceValue();

	/* LR��Data���t�]������ */
	balance = balance * -1;

	updatePosCommon(aori, balance, rAori, rCenter, rBar);
}
