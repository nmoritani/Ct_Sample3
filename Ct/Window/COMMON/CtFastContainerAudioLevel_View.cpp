/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Element:          CtFastContainerAudioLevel_View
 */

#include "CtFastContainerAudioLevel_View.h"

#include "CtICManager.h"

CtFastContainerAudioLevel_View::CtFastContainerAudioLevel_View(bool isRec) :
	m_bRec(isRec),
	CtFastContainerAudioLevel()
{
}

CtLayout* CtFastContainerAudioLevel_View::createLevelMeter()
{
	CtLayout* pAll = new CtLayout();
	{
		/////////////////////////  HeadRoom  /////////////////////////
		m_pAllHeadRoom = new CtLayout();
		{
			CtHLayout* pHeadRoomLine = new CtHLayout();
			{
				pHeadRoomLine->addStretch(26); // Audio Ch1/Ch2•¶Žš•”•ª
				m_pHeadRoomBase = new CtStackLabel();
				{
					// Segment8
					CtHLayout* pSeg8Line = new CtHLayout();
					{
						pSeg8Line->addStretch(74);
						CtLabel* pHeadRoomBaseSeg8 = new CtLabel(CtRect(CtColor::white, 1, CtColor::Black));
						pSeg8Line->addWidget(pHeadRoomBaseSeg8, 15);
						pSeg8Line->addStretch(119);
					}
					m_pHeadRoomBase->addLabel(pSeg8Line, 0);

					// Segment9
					CtHLayout* pSeg9Line = new CtHLayout();
					{
						pSeg9Line->addStretch(85);
						CtLabel* pHeadRoomBaseSeg9 = new CtLabel(CtRect(CtColor::white, 1, CtColor::Black));
						pSeg9Line->addWidget(pHeadRoomBaseSeg9, 15);
						pSeg9Line->addStretch(108);
					}
					m_pHeadRoomBase->addLabel(pSeg9Line, 1);

					// Segment12
					CtHLayout* pSeg12Line = new CtHLayout();
					{
						pSeg12Line->addStretch(119);
						CtLabel* pHeadRoomBaseSeg12 = new CtLabel(CtRect(CtColor::white, 1, CtColor::Black));
						pSeg12Line->addWidget(pHeadRoomBaseSeg12, 15);
						pSeg12Line->addStretch(75);
					}
					m_pHeadRoomBase->addLabel(pSeg12Line, 2);
				}
				pHeadRoomLine->addWidget(m_pHeadRoomBase, 208);
			}
			m_pAllHeadRoom->addWidget(pHeadRoomLine);
			//pAll->addWidget(pHeadRoomLine);
		}
		pAll->addWidget(m_pAllHeadRoom);
		/////////////////////////  AudioLevel  /////////////////////////
		CtHLayout* pAudioLine = new CtHLayout();
		{
			// Ch1,Ch2
			pAudioLine->addWidget(new CtLabel(IC_OSD_CH1_CH2), 24);//26-2

			// SwitchArea (LevelMeter ©¨ Mute)
			m_pLevelSwitchArea = new CtStackLabel();
			{
				// No Audio
				CtHLayout* pMuteLine = new CtHLayout();
				pMuteLine->addStretch(11);
				pMuteLine->addWidget(new CtLabel(IC_OSD_AUDIO_REC_OFF), 90);
				pMuteLine->addStretch(133);//234
				m_pLevelSwitchArea->addLabel(pMuteLine, 0);

				// Level
				CtVLayout* pLevelMeterArea = new CtVLayout();
				{
					//pLevelMeterArea->addStretch(1);
					pLevelMeterArea->addStretch(2);
					CtHLayout* pLevelCh1 = new CtHLayout();
					{
						for (int i = 0; i < AUDIO_LEVEL_NUM_MAX; i++) {
							m_pLevelCh1 = new CtStackLabel();
							{
								if (i != AUDIO_LEVEL_NUM_MAX - 1) {
									m_pLevelCh1->addLabel(IC_OSD_LEVEL_OFF);
									m_pLevelCh1->addLabel(IC_OSD_LEVEL_ON);
								}
								else {
									m_pLevelCh1->addLabel(IC_OSD_LEVEL_OFF);
									m_pLevelCh1->addLabel(IC_OSD_LEVEL_RED);
								}
								m_pLevelCh1->setFastDraw(true);
								m_pLevelCh1->index(0);
							}
							pLevelCh1->addStretch(1);
							pLevelCh1->addWidget(m_pLevelCh1, 9);
							m_pLevelSetCh1.push_back(m_pLevelCh1);
							pLevelCh1->addStretch(1);
						}
					}
					pLevelMeterArea->addWidget(pLevelCh1, 20);
					pLevelMeterArea->addStretch(1);

					CtHLayout* pLevelCh2 = new CtHLayout();
					{
						for (int i = 0; i < AUDIO_LEVEL_NUM_MAX; i++) {
							m_pLevelCh2 = new CtStackLabel();
							{
								if (i != AUDIO_LEVEL_NUM_MAX - 1) {
									m_pLevelCh2->addLabel(IC_OSD_LEVEL_OFF);
									m_pLevelCh2->addLabel(IC_OSD_LEVEL_ON);
								}
								else {
									m_pLevelCh2->addLabel(IC_OSD_LEVEL_OFF);
									m_pLevelCh2->addLabel(IC_OSD_LEVEL_RED);
								}
								m_pLevelCh2->setFastDraw(true);
								m_pLevelCh2->index(0);
							}
							pLevelCh2->addStretch(1);
							pLevelCh2->addWidget(m_pLevelCh2, 9);
							m_pLevelSetCh2.push_back(m_pLevelCh2);
							pLevelCh2->addStretch(1);
						}
					}
					pLevelMeterArea->addWidget(pLevelCh2, 20);
					pLevelMeterArea->addStretch(2);
				}
				m_pLevelSwitchArea->addLabel(pLevelMeterArea, 1);
				pAudioLine->addWidget(m_pLevelSwitchArea, 208);
			}
		}
		pAll->addWidget(pAudioLine);
	}

	return pAll;
}

bool CtFastContainerAudioLevel_View::handleParamEvent(const CtEventParam& Param) {
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();
	switch (t_Id) {
	case AplParamHeadRoom:
		return CtFastContainerAudioLevel::handleParamEvent(Param);
		break;
	case AplParamAudioLevelMeterInvalid:
		if (m_bRec) {
			return CtFastContainerAudioLevel::handleParamEvent(Param);
		}
		break;
	default:
		break;
	}
	return false;
}

bool CtFastContainerAudioLevel_View::updateAudioLevelMeterState(int int_Data) {
	if (!m_bRec) {
		m_pLevelSwitchArea->index(1);
		m_pAllHeadRoom->setVisible(true);
		m_IsMute = false;
		return true;
	}
	else {
		return CtFastContainerAudioLevel::updateAudioLevelMeterState(int_Data);
	}
	return false;
}

void CtFastContainerAudioLevel_View::updateSegmentSub() {
	if (m_pHeadRoomBase == NULL) return;
	switch (m_Seg) {
	case 4:// APL_SYS_PARAM_HEAD_ROOM_12DB Seg12
		m_pHeadRoomBase->index(2);
		break;
	case 1:// APL_SYS_PARAM_HEAD_ROOM_18DB Seg9
		m_pHeadRoomBase->index(1);
		break;
	case 0:// APL_SYS_PARAM_HEAD_ROOM_20DB Seg8
	default:
		m_pHeadRoomBase->index(0);
		break;
	}
	return;
}
