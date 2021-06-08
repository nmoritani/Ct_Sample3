/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtVLayout
 */


#include "CtVLayout.h"

CtVLayout::CtVLayout()
{
	setLayoutType(LayoutVertical);
}

CtVLayout::CtVLayout(const CtColor& Color) :
	CtLayout(Color)
{
	setLayoutType(LayoutVertical);
}

CtVLayout::CtVLayout(const CtSize& Size, const CtColor& Color) :
	CtLayout(Size, Color)
{
	setLayoutType(LayoutVertical);
}

CtVLayout::CtVLayout(const CtRegion& Region, const CtColor& Color) :
	CtLayout(Region, Color)
{
	setLayoutType(LayoutVertical);
}

CtVLayout::~CtVLayout()
{
}

bool CtVLayout::setLayout(int Screen)
{
	return CtLayout::setVLayout(Screen);
}

