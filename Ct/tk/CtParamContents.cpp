#include "CtParamContents.h"
#include <string.h>

CtParamContents::CtParamContents():
	CtWindowContents(WindowID_MAX),
    m_ParamId(AplParamIdMax),
    m_Data(0),
    m_Size(sizeof(int))
{
	memset(m_Buff, 0, sizeof(m_Buff));
}
CtParamContents::CtParamContents(const CtWindowID WindowID, const AplParamEepromId paramId, const int data) : 
	CtWindowContents(WindowID),
    m_ParamId(paramId),
    m_Data(data),
    m_Size(sizeof(int))
{
	    memset(m_Buff, 0, sizeof(m_Buff));
}

CtParamContents::CtParamContents(CtParamContents& Contents) : CtWindowContents(Contents.getType()){
    m_ParamId = Contents.getContentsParamId();
	m_Data = Contents.getContentsParamData();
	m_Size = Contents.getContentsParamDataSize();
	memcpy( m_Buff, Contents.getContentsParamDataBuff(), sizeof(m_Buff));
}

CtParamContents::CtParamContents(const CtWindowID WindowID, const AplParamEepromId paramId, const char buff[32], const int size) : 
	CtWindowContents(WindowID),
    m_ParamId(paramId),
    m_Size(size)
{
    if( sizeof( m_Buff) > sizeof(buff)){
        memcpy( m_Buff, buff, sizeof(buff));
    }
}
CtParamContents::~CtParamContents(){
}

void CtParamContents::setContentsParamData(const AplParamEepromId paramId, const int data)
{
	m_ParamId = paramId;
	m_Data = data;
}

void CtParamContents::setContentsParamData(const AplParamEepromId paramId, const char buff[32], const int size)
{
	m_ParamId = paramId;
	if( sizeof( m_Buff) > sizeof(buff)){
        memcpy( m_Buff, buff, sizeof(buff));
    }
	m_Size = size;
}

AplParamEepromId CtParamContents::getContentsParamId(){
    return m_ParamId;
}

int CtParamContents::getContentsParamDataSize(){
    return m_Size;
}

char* CtParamContents::getContentsParamDataBuff(){
    return m_Buff;
}

int CtParamContents::getContentsParamData(){
    return m_Data;
}
