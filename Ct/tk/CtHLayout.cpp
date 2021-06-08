/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtHLayout
 */


#include "CtHLayout.h"

CtHLayout::CtHLayout()
{
	setLayoutType(LayoutHolizontal);
}

CtHLayout::CtHLayout(const CtColor& Color) : 
	CtLayout(Color)
{
	setLayoutType(LayoutHolizontal);
}

CtHLayout::CtHLayout(const CtSize& Size, const CtColor& Color) :
	CtLayout(Size, Color)
{
	setLayoutType(LayoutHolizontal);
}

CtHLayout::CtHLayout(const CtRegion& Region, const CtColor& Color) :
	CtLayout(Region, Color)
{
	setLayoutType(LayoutHolizontal);
}

CtHLayout::~CtHLayout()
{
}

bool CtHLayout::setLayout(int Screen)
{
	return CtLayout::setHLayout(Screen);
}

