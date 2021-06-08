/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtVLayout
 */


#ifndef __CtVLayout_H__
#define __CtVLayout_H__

#include "Ct.h"
#include "CtLayout.h"

class CtVLayout : public CtLayout {
public :
    CtVLayout();
    CtVLayout(const CtColor& Color);
    CtVLayout(const CtSize& Size, const CtColor& Color = CtColor::NoColor);
    CtVLayout(const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
    virtual ~CtVLayout();

	virtual bool setLayout(int Screen = 0);
};

#endif
