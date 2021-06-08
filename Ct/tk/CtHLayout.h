/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Rhapsody Version:	7.5.1
 *  Element:			CtHLayout
 */


#ifndef __CtHLayout_H__
#define __CtHLayout_H__

#include "Ct.h"
#include "CtLayout.h"

class CtHLayout : public CtLayout {
public :
    CtHLayout();
    CtHLayout(const CtColor& Color);
    CtHLayout(const CtSize& Size, const CtColor& Color = CtColor::NoColor);
    CtHLayout(const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
    virtual ~CtHLayout();

	virtual bool setLayout(int Screen = 0);
};

#endif
