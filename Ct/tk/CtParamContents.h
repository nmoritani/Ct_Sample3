#ifndef __CtParamContents_H__
#define __CtParamContents_H__

#include "AplParamService.h"
#include "CtWindowContents.h"

class CtParamContents : public CtWindowContents {
public :
	CtParamContents();
	CtParamContents(const CtWindowID WindowID, const AplParamEepromId paramId, const int data);
    CtParamContents(CtParamContents& pContents);
    CtParamContents(const CtWindowID WindowID, const AplParamEepromId paramId, const char buff[32], const int size);
	virtual ~CtParamContents();

    void setContentsParamData(const AplParamEepromId paramId, const int data);
    void setContentsParamData(const AplParamEepromId paramId, const char buff[32], const int size);
	AplParamEepromId getContentsParamId();
    int getContentsParamDataSize();
    char* getContentsParamDataBuff();
    int getContentsParamData();

private :
	AplParamEepromId m_ParamId;
    int m_Data;
    char m_Buff[32];
	int m_Size;
};

#endif
