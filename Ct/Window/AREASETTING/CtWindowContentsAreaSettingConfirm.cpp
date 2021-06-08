#include "CtWindowContentsAreaSettingConfirm.h"

CtWindowContentsAreaSettingConfirm::CtWindowContentsAreaSettingConfirm(const CtWindowID WindowID) : 
    CtWindowContents(WindowID),
    m_AreaSetting(ContentsAreaSetting_AREA2)
{
}

CtWindowContentsAreaSettingConfirm::~CtWindowContentsAreaSettingConfirm() 
{
}

ContentsAreaSetting CtWindowContentsAreaSettingConfirm::getContentsAreaSetting() 
{
	return m_AreaSetting;
}

void CtWindowContentsAreaSettingConfirm::setContentsAreaSetting(ContentsAreaSetting eAreaSetting) 
{
	m_AreaSetting = eAreaSetting;
}

void CtWindowContentsAreaSettingConfirm::setAreaSetingType(AreaSettingType eAreaSettingType)
{
    m_AreaSettingType = eAreaSettingType;
}

AreaSettingType CtWindowContentsAreaSettingConfirm::getAreaSettingType()
{
    return m_AreaSettingType;
}


