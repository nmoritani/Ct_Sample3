/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerToggleDialog_TimeZonesetting.h"


CtContainerToggleDialog_TimeZonesetting::TimeZoneTable CtContainerToggleDialog_TimeZonesetting::TimeZone[] = {
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_12	,	"-12:00"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_11_30	,	"-11:30"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_11	,	"-11:00"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_10_30	,	"-10:30"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_10	,	"-10:00"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_9_30	,	"-9:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_9 	,	"-9:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_8_30	,	"-8:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_8 	,	"-8:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_7_30	,	"-7:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_7 	,	"-7:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_6_30	,	"-6:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_6 	,	"-6:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_5_30	,	"-5:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_5 	,	"-5:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_4_30	,	"-4:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_4 	,	"-4:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_3_30	,	"-3:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_3 	,	"-3:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_2_30	,	"-2:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_2 	,	"-2:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_1_30	,	"-1:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_1 	,	"-1:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_MINUS_0_30	,	"-0:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT         	,	"+0:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_0_30	,	"+0:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_1  	,	"+1:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_1_30	,	"+1:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_2  	,	"+2:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_2_30	,	"+2:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_3  	,	"+3:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_3_30	,	"+3:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_4  	,	"+4:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_4_30	,	"+4:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_5  	,	"+5:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_5_30	,	"+5:30"		},
//	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_5_45	,	"+5:45"		},	//K519‚Å‚ÍŽg—p‚µ‚È‚¢
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_6  	,	"+6:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_6_30	,	"+6:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_7  	,	"+7:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_7_30	,	"+7:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_8  	,	"+8:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_8_30	,	"+8:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_9  	,	"+9:00"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_9_30	,	"+9:30"		},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_10 	,	"+10:00"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_PLUS_10_30  	,	"+10:30"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_11 	,	"+11:00"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_PLUS_11_30  	,	"+11:30"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_12 	,	"+12:00"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_12_45	,	"+12:45"	},
	{ APL_SYS_PARAM_WORLD_TIME_AREA_GMT_PLUS_13 	,	"+13:00"	},
};


CtContainerToggleDialog_TimeZonesetting::CtContainerToggleDialog_TimeZonesetting(CtWindowID id) :CtContainerToggleDialog(id)
{
	setClassType(CtClassType_LayoutMain);
}
CtContainerToggleDialog_TimeZonesetting::~CtContainerToggleDialog_TimeZonesetting()
{
	destroyContainer();
}


//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------
CtLayout* CtContainerToggleDialog_TimeZonesetting::createToggle()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

	CtStackLabel* pStackLabel = new CtStackLabel();
	int index = -1;
	int value = APL_PARAM_GET_DATA(AplParamWTTravelArea);

	for (unsigned int i = 0; i < sizeof(TimeZone) / sizeof(TimeZoneTable); i++) {
		pStackLabel->addLabel(new CtLabel( TimeZone[i].str, fSet), CtMargin(0,10), AlignCenter, i);
		if (value == TimeZone[i].id) {
			index = i;
		}
	}
	if (index == -1) {
		for (unsigned int i = 0; i < sizeof(TimeZone) / sizeof(TimeZoneTable); i++) {
			if (APL_SYS_PARAM_WORLD_TIME_AREA_GMT == TimeZone[i].id) {
				index = i;
				break;
			}
		}
	}
	pStackLabel->index(index);

	CtButton* pButton = new CtButton(AutoSize, pStackLabel);

	ToggleButton Toggle;
	memset(&Toggle, 0, sizeof(Toggle));
	Toggle.Button = pButton;
	Toggle.Stack  = pStackLabel;
	Toggle.Data = index;
	Toggle.Max    = sizeof(TimeZone) / sizeof(TimeZoneTable) -1;
	m_Toggle.push_back(Toggle);

	m_Toggle[0].Button->setPressed();
	m_Toggle[0].Button->cancelPressed();

	CtHLayout* pLayout = new CtHLayout();
	pLayout->addStretch(405);
	pLayout->addWidget(m_Toggle[0].Button, 150);
	pLayout->addStretch(405);

	return pLayout;
}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
bool CtContainerToggleDialog_TimeZonesetting::executionSet()
{

	APL_PARAM_SET_DATA(AplParamWTTravelArea, TimeZone[m_Toggle[m_CurSelect].Data].id);
	CtEventInterface::requestWindowCmd((CtEventWindow::WinCmd)Close, WindowNone);

	return true;
}
