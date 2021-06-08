/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowCommon
 */


#ifndef __CtWindowCommon_H__
#define __CtWindowCommon_H__

#include "Ct.h"
#include "CtObject.h"
#include "CtWidget.h"
#include "CtWindowMain.h"

#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtGridLayout.h"

#include "CtButton.h"
#include "CtLinkButton.h"
#include "CtLabel.h"
#include "CtSlideLabel.h"
#include "CtStackLabel.h"
#include "CtListView.h"
#include "CtScrollBar.h"
#include "CtTextField.h"
#include "CtToggleButton.h"
#include "CtInterface.h"

#include "CtWindowID.h"

#include "AplParamService.h"

// 共通部品として、画面タイプを区別する
enum CtWindowCommonType{
    CT_COMMON_TYPE_REC,
	CT_COMMON_TYPE_PLAY,
    CT_COMMON_TYPE_HOME
};

#endif
