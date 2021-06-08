/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtStyle
 */


#include "CtStyle.h"
#include "CtStyleDefault.h"
#include "CtStyleWhite.h"

CtStyle::Style CtStyle::m_Style = Default;
const CtRegion CtStyle::DefaultRegion = CtRegion(0,0,960,540);

const CtStyle::CtProperty CtStyle::m_Properties[] =
{
	CtStyleDefault,
	CtStyleWhite,
};

void CtStyle::setStyle(Style style)
{
	m_Style = style;
}

CtStyle::Style CtStyle::getStyle()
{
	return m_Style;
}

const CtStyle::CtProperty& CtStyle::getProperty()
{
	return m_Properties[m_Style];
}
