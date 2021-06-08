/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtParamConvIf_H__
#define __CtParamConvIf_H__

#include "AplParamService.h"
#include "Ct.h"

class CtParamConvIf{
public:
	CtParamConvIf();
    
    char* convFromUserParamToCharStr(AplParamEepromId userSwNoParamNo);
	GDI_STRING_ID convFromUserParamToStringId(int userSwNoParamData) ;
    ~CtParamConvIf();
protected :
	
private :
};

#endif /* __CtParameterConvIf_H__ */

