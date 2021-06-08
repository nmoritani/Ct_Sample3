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
	// 各ラベルのRegion定義 (-1 は updatePosCommon内で動的変更する箇所 )
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

	/* LRでDataを逆転させる */
	balance = balance * -1;

	updatePosCommon(aori, balance, rAori, rCenter, rBar);
}
