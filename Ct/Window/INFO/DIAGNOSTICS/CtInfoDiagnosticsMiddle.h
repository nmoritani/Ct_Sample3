/**
 *  Copyright (c) 2009-2010 Panasonic Corporation
 *  Element:			CtWidgetControl
 */


#ifndef __CtInfoDiagnosticsMiddle_H__
#define __CtInfoDiagnosticsMiddle_H__

#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtButton.h"
#include "CtStackLabel.h"
#include "CtInterface.h"

class CtInfoDiagnosticsMiddle : public CtContainer {
public :
	
	enum Warning2nd {
		Warning2nd_None,
		Warning2nd_OverMaxNum,
		Warning2nd_Slot1,
		Warning2nd_Slot2,
		Warning2nd_Slot1_Slot2,
		Warning2nd_Slot1_OverMaxNum,
		Warning2nd_Slot2_OverMaxNum,
		Warning2nd_Slot1_Slot2_OverMaxNum,
		Warning2nd_ClockReset,
	};
	
	enum InfoErr {
		InfoErr_NODISP,
		InfoErr_NONE,
		InfoErr_ABB_NG,
		InfoErr_ABB_NG_TIME_OVER,
		InfoErr_ABB_NG_SELECT_TEST_SIG,
		InfoErr_ABB_NG_LENS_NOT_CLOSE,
		InfoErr_AWB_NG_TIME_OVER,
		InfoErr_AWB_NG_SELECT_TEST_SIG,
		InfoErr_AWB_NG_COL_TEMP_LOW,
		InfoErr_AWB_NG_COL_TEMP_HIGH,
		InfoErr_AWB_NG_GMG_OVER,
		InfoErr_AWB_NG_LEVEL_OVER,
		InfoErr_AWB_NG_LOW_LIGHT,
	};

    CtInfoDiagnosticsMiddle();

    virtual ~CtInfoDiagnosticsMiddle();

    CtLayout* createContainer();
	bool destroyContainer();

    virtual bool handleParamEvent(const CtEventParam& Param);
	
protected:

private :

    void setWarningLabel(CtStackLabel *pWarningValue);
    void setWarning2ndLabel(CtStackLabel *pWarningValue);
    void setAlertLabel(CtStackLabel *pAlertValue);
    void setInfoErrorLabel(CtStackLabel *pInfoError);

    void updateWarning_Alert();
    void updateInfo_Error();
    void updateTotalOperation();
    void updateIrisDial();

	bool isDispAlert();
	bool isDispWarning();
	CtInfoDiagnosticsMiddle::Warning2nd get2ndWarningAlert();
	CtInfoDiagnosticsMiddle::InfoErr getAbbErr();
	CtInfoDiagnosticsMiddle::InfoErr getAwbErr();
	CtInfoDiagnosticsMiddle::InfoErr get1stInfoErr();
	CtInfoDiagnosticsMiddle::InfoErr get2ndInfoErr();

    CtVLayout *m_pBox;
	CtHLayout *m_pWarning_Alert2nd;
    CtStackLabel *m_pInfoError;
    CtStackLabel *m_pInfoError2nd;
    CtStackLabel *m_pWarningValue;
    CtStackLabel *m_pWarning2ndValue;
    CtStackLabel *m_pAlertValue;
    CtLabel *m_pWarning_AlertValue_Non;
    CtLabel *m_pTotalOperationValue;
    CtLabel *m_pIrisDialValue;

};

#endif
