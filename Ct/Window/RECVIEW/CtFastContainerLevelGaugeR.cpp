/**
*  Copyright (c) 2018 Persol AVC Technology
*  Element:          CtFastContainerLevelGaugeR
*/

#include "CtFastContainerLevelGaugeR.h"


CtFastContainerLevelGaugeR::CtFastContainerLevelGaugeR()
{
}

CtFastContainerLevelGaugeR::~CtFastContainerLevelGaugeR()
{
}

void CtFastContainerLevelGaugeR::updatePos()
{
	// �e���x����Region��` (-1 �� updatePosCommon���œ��I�ύX����ӏ� )
	CtRegion rAori = CtRegion(
		(VIEW_WINDOW_SIZE_W - (VIEW_LEVELGAUGE_WIDE_W * 2)), -1,
		VIEW_LEVELGAUGE_WIDE_W, 5
	);
	CtRegion rCenter = CtRegion(
		(VIEW_WINDOW_SIZE_W - (VIEW_LEVELGAUGE_WIDE_W)), -1,
		VIEW_LEVELGAUGE_WIDE_W, 5
	);
	CtRegion rBar = CtRegion(
		(VIEW_WINDOW_SIZE_W - (VIEW_LEVELGAUGE_WIDE_W)) + VIEW_LEVELGAUGE_MARGIN_W, -1,
		VIEW_LEVELGAUGE_SHORT_W, -1
	);

	int aori = getAngleValue();
	int balance = getBalanceValue();

	updatePosCommon(aori, balance, rAori, rCenter, rBar);
}
