/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Element:          CtFastContainerAudioLevel
 */
#ifdef WIN32_GUI_SIM
#include <stdlib.h>
#endif

#include "CtFastContainerAudioLevel.h"

CtFastContainerAudioLevel::CtFastContainerAudioLevel() :
	m_Seg(-1),
	m_peakCh1(0),
	m_peakCh2(0),
	m_pLevelCh1(NULL),
	m_pLevelCh2(NULL),
	m_pLevelSwitchArea(NULL),
	m_pAllHeadRoom(NULL)
{
	m_PreSeg = 7 + getStandardSegment();
	m_Ch1FrameCount = 0;
	m_Ch2FrameCount = 0;
}

CtLayout* CtFastContainerAudioLevel::createContainer()
{
	CtLayout* pAll = createLevelMeter();
	// セグメント更新
	updateSegment();
	updateAudioLevelMeterState(APL_PARAM_GET_DATA(AplParamAudioLevelMeterInvalid));
	
	return pAll;
}

bool CtFastContainerAudioLevel::destroyContainer()
{
	m_pLevelSetCh1.clear();
	m_pLevelSetCh2.clear();
	return true;
}

CtFastContainerAudioLevel::~CtFastContainerAudioLevel()
{
	
}

bool CtFastContainerAudioLevel::updateFastDraw()
{
	if (m_IsMute == false) {
		updateFastDrawAudioLevel();
	}
	return true;
}

int CtFastContainerAudioLevel::getStandardSegment()
{
	if (APL_PARAM_GET_DATA(AplParamHeadRoom) == APL_SYS_PARAM_HEAD_ROOM_12DB) {
		return 4;
	}
	else if (APL_PARAM_GET_DATA(AplParamHeadRoom) == APL_SYS_PARAM_HEAD_ROOM_18DB) {
		return 1;
	}
	else if (APL_PARAM_GET_DATA(AplParamHeadRoom) == APL_SYS_PARAM_HEAD_ROOM_20DB) {
		return 0;
	}
	return 1;
}

void CtFastContainerAudioLevel::updateSegment()
{
	int seg;

	/* 基準セグメント設定 */
	if ((seg = getStandardSegment()) < 0) {
		return;
	}

	if (seg == m_Seg)
		return;

	m_Seg = seg;

	updateSegmentSub();
}

bool CtFastContainerAudioLevel::updateFastDrawAudioLevel()
{
#ifdef WIN32_GUI_SIM
	short Ch1 = rand() % AUDIO_LEVEL_NUM_MAX + 1;// 0 ~ 19
	short Ch2 = rand() % AUDIO_LEVEL_NUM_MAX + 1;// 0 ~ 19

#else
	short Ch1 = getCh1Level();
	short Ch2 = getCh2Level();
#endif
	// LevelMeterIndexに直す
	if (Ch1 != 0) Ch1 -= 1;
	if (Ch2 != 0) Ch2 -= 1;

	m_Ch1FrameCount++;
	
	if (m_Ch1FrameCount > 60) {// 1V周期でのCallなので1秒カウント
		m_peakCh1 = -1;
		m_Ch1FrameCount = 0;
	}

	m_Ch2FrameCount++;
	
	if (m_Ch2FrameCount > 60) {// 1V周期でのCallなので1秒カウント
		m_peakCh2 = -1;
		m_Ch2FrameCount = 0;
	}

	if (m_peakCh1 <= Ch1) {
		m_peakCh1 = Ch1;// 更新し1秒以内に更新されない場合は最少にPeak
		m_Ch1FrameCount = 0;
	}
	
	if (m_peakCh2 <= Ch2) {
		m_peakCh2 = Ch2;
		m_Ch2FrameCount = 0;
	}

	/* レベルメータ描画 */
	for (int i = 0; i < AUDIO_LEVEL_NUM_MAX; i++) {
		if (Ch1 >= i) {
			if (Ch1 == 0) {
				m_pLevelSetCh1[i]->index(0);
			}
			else {
				m_pLevelSetCh1[i]->index(1);
			}
		} else {
			// Peak値はindex 1
			if(m_peakCh1 == i) m_pLevelSetCh1[i]->index(1);
			else m_pLevelSetCh1[i]->index(0);
		}

		if (Ch2 >= i) {
			if (Ch2 == 0) {
				m_pLevelSetCh2[i]->index(0);
			}
			else {
				m_pLevelSetCh2[i]->index(1);
			}
		} else {
			// Peak値はindex 1
			if (m_peakCh2 == i) m_pLevelSetCh2[i]->index(1);
			else m_pLevelSetCh2[i]->index(0);
		}
	}

	return true;
}

bool CtFastContainerAudioLevel::handleParamEvent(const CtEventParam& Param) {
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();

	switch (t_Id) {
	case AplParamHeadRoom:
		updateSegment();
		return true;
		break;
	case AplParamAudioLevelMeterInvalid:
		updateAudioLevelMeterState(int_Data);
		return true;
	default:
		break;
	}
	return false;
}

bool CtFastContainerAudioLevel::updateAudioLevelMeterState(int int_Data) {
	if (int_Data == APL_SYS_PARAM_SWITCH_ON) {
		m_pLevelSwitchArea->index(0);
		m_pAllHeadRoom->setVisible(false);
		m_IsMute = true;
		return true;
	}else if (int_Data == APL_SYS_PARAM_SWITCH_OFF) {
		m_pLevelSwitchArea->index(1);
		m_pAllHeadRoom->setVisible(true);
		m_IsMute = false;
		return true;
	}
	return false;
}

bool CtFastContainerAudioLevel::isMute()
{
	return m_IsMute;
}

short CtFastContainerAudioLevel::getCh1Level()
{
	short lv = APL_PARAM_GET_DATA(AplParamAudioLevelMeterCH1);
	return (lv >= AUDIO_LEVEL_NUM_MAX) ? AUDIO_LEVEL_NUM_MAX : lv;
}

short CtFastContainerAudioLevel::getCh2Level()
{
	short lv = APL_PARAM_GET_DATA(AplParamAudioLevelMeterCH2);
	return (lv >= AUDIO_LEVEL_NUM_MAX) ? AUDIO_LEVEL_NUM_MAX : lv;
}
