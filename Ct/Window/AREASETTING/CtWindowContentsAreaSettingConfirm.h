#ifndef __CtWindowContentsAreaSettingConfirm_H__
#define __CtWindowContentsAreaSettingConfirm_H__

#include "CtWindowContents.h"
typedef enum _ContentsAreaSetting {
	ContentsAreaSetting_AREA1,
	ContentsAreaSetting_AREA2,
	ContentsAreaSetting_AREA3,
	ContentsAreaSetting_AREA4,
} ContentsAreaSetting;
typedef enum _AreaSettingType {
	AreaSettingType_FactorySetting,
	AreaSettingType_MenuSetting,
} AreaSettingType;
class CtWindowContentsAreaSettingConfirm : public CtWindowContents {
public :
	CtWindowContentsAreaSettingConfirm(const CtWindowID WindowID);
	virtual ~CtWindowContentsAreaSettingConfirm();

    void setContentsAreaSetting(ContentsAreaSetting eAreaSetting);
	ContentsAreaSetting getContentsAreaSetting();

    void setAreaSetingType(AreaSettingType eAreaSettingType);
    AreaSettingType getAreaSettingType();

protected :
	ContentsAreaSetting m_AreaSetting;
    AreaSettingType m_AreaSettingType;
	
};

#endif
