/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			
 */


#ifndef __CtICManager_H__
#define __CtICManager_H__

#include "Ct.h"
#include "CtWidget.h"
#include "CtWindowCommon.h"
#include "AplParamService.h"
#include "CtRecViewContainer.h"

//#define INDICATOR_DISP_SCERRN(a,b)	CtICManager::getInstance()->getWidgetDispScreen(a,b)

typedef enum CtMenuOutputId {
	IC_SEL_TC,
	IC_SEL_FULL_AUTO,
	IC_SEL_CARD_STATUS,
	IC_SEL_CARD_STATUS2,
	IC_SEL_REMAIN1,
	IC_SEL_REMAIN2,
	IC_SEL_2SLOT_FUNC,
	IC_SEL_STREAMING,
	IC_SEL_NETWORK,
	IC_SEL_BAT_REMAIN,
	IC_SEL_REC_FORMAT_LINE_FREQ,
	IC_SEL_FRAME_RATE,
	IC_SEL_REC_FORMAT,
	IC_SEL_BONDING_DEVICE,
	IC_SEL_REC_REMOTE,
	IC_SEL_REC_MODE,
	IC_SEL_FBC,
	IC_SEL_HDR_DRS,
	IC_SEL_OIS,
	IC_SEL_SCENE_FILE,
	IC_SEL_AREA,
	IC_SEL_AUDIO_LEVEL_M,
	IC_SEL_GAIN,
	IC_SEL_ND_FILTER,
	IC_SEL_SHUTTER,
	IC_SEL_IRIS,
	IC_SEL_ZOOM,
	IC_SEL_WHITE,
	IC_SEL_SPOT_M,
	IC_SEL_DATE_TIME,
	IC_SEL_SHOOTING_MODE,
	IC_SEL_FOCUS,
	IC_SEL_MML,
	IC_SEL_D_ZOOM,
	IC_SEL_IR_REC,
	IC_SEL_COM,
	IC_SEL_AUDIO_VOL,
	IC_SEL_ND_WARN,
	IC_SEL_LEVEL_GAUGE,
	IC_SEL_FAN_STOPPED,
	IC_SEL_MAX
}CtMenuOutputId;

enum DataReact {
	React,
	NoReact,
};

struct CtIcReactDataSet {
	CtMenuOutputId		IcId;
	AplParamEepromId	IcParam;
	DataReact			DispMode;
	bool				MmlReact;
	bool				ExpandReact;
	struct Instance{
		CtRecViewContainer*		pContainer;
		CtWidget*			pWidget;
	}Instance;
	
};


class CtICManager : public CtObject {
private:
	CtICManager();

public:
	virtual ~CtICManager();
	static CtICManager* getInstance();

	// 状態更新
	bool setStatusMode(const bool bStatusMode);
	bool setMmlAct(const bool bMmlAct, CtMenuOutputId IcId = IC_SEL_MAX);
	bool setRecIcMode(const bool bMmlAct);

	// データ処理
	CtScreenSel getWidgetDispScreen(CtMenuOutputId Id, bool isRecOsd = false);
	bool updateWidgetDispScreen(CtIcReactDataSet& targetDataSet);
	// IC No毎に更新
	bool updateIC(CtMenuOutputId MmlActIcId);

	// 登録用
	bool registInstance(CtWidget* pWidget, CtMenuOutputId targetId);
	bool registInstance(CtRecViewContainer* pContainer, CtMenuOutputId targetId);
	bool registInstance(CtWidget* pWidget, CtRecViewContainer* pContainer, CtMenuOutputId targetId);
	bool releaseInstance(CtMenuOutputId targetId);
	
	// 更新用
	bool updateParam(int t_id, int int_Data);

private:

	/**********************  attributes **********************/
	static CtICManager* m_pThis;
	static AplParamEepromId m_Tabel[IC_SEL_MAX];
	bool m_bStatusMode;
	bool m_bMmlAct;
	bool m_bRecIc;
	CtMenuOutputId m_MmlActIcId;

	// ScreenSel更新用
	bool updateICs(); // 一括更新
	bool updateIC(int targetParamId); // Param毎に更新
	
	//@brief DispMode ON/Menu IC SwがOFF時に呼び出される
	CtScreenSel getDispIcMode(CtMenuOutputId Id);

	// 反応条件データ集合
	static CtIcReactDataSet m_pIcDataSet[IC_SEL_MAX];
};
#endif

