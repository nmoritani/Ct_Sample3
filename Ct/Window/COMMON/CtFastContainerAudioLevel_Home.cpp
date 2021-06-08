/**
 *  Copyright (c) 2018 Persol AVC Technology
 *  Element:          CtFastContainerAudioLevel_Home
 */


#include "CtFastContainerAudioLevel_Home.h"

CtFastContainerAudioLevel_Home::CtFastContainerAudioLevel_Home() : CtFastContainerAudioLevel()
{
}

CtLayout* CtFastContainerAudioLevel_Home::createLevelMeter()
{
	// W:27 H:4
	CtLayout* pAll = new CtLayout();
	{
		/////////////////////////  HeadRoom  /////////////////////////
		// W:27 H:4
		m_pAllHeadRoom = new CtVLayout();
		{
			m_pAllHeadRoom->addStretch(32);

			CtHLayout* pHeadRoomLine = new CtHLayout();
			{
				pHeadRoomLine->addStretch(68);
				for (int i = 0; i < 19; i++) {
					CtHLayout* pHeadRoomBase = new CtHLayout(CtColor(0xd4d4d4ff));
					{
						pHeadRoomBase->addStretch(9);

						CtVLayout* pHeadRoomLine = new CtVLayout();
						{
							pHeadRoomLine->addStretch(3);
							pHeadRoomLine->addWidget(new CtLabel(CtColor::Black), 8);
							pHeadRoomLine->addStretch(43);
							pHeadRoomLine->addWidget(new CtLabel(CtColor::Black), 8);
							pHeadRoomLine->addStretch(43);
							pHeadRoomLine->addWidget(new CtLabel(CtColor::Black), 8);
							pHeadRoomLine->addStretch(3);
						}
						pHeadRoomBase->addWidget(pHeadRoomLine, 4);
						pHeadRoomBase->addStretch(9);
					}
					pHeadRoomBase->setVisible(false);
					m_pHeadRooms.push_back(pHeadRoomBase);
					
					pHeadRoomLine->addWidget(pHeadRoomBase, 22);
					//pHeadRoomLine->addStretch(5);
				}
			}
			m_pAllHeadRoom->addWidget(pHeadRoomLine, 116);
			m_pAllHeadRoom->addStretch(32);
		}
		pAll->addWidget(m_pAllHeadRoom);

		/////////////////////////  AudioLevel  /////////////////////////
		// W:27 H:2
		CtVLayout* pAllAudioLevel = new CtVLayout();
		{
			pAllAudioLevel->addStretch(1);

			CtHLayout* pAudioLine = new CtHLayout();
			{
				// W:27 H:2
				// Ch1,Ch2
				pAudioLine->addWidget(new CtLabel(IC_AUDIO_CH1_CH2), 4);
				// SwitchArea (LevelMeter ©¨ Mute)
				m_pLevelSwitchArea = new CtStackLabel();
				{
					// No Audio
					CtHLayout* pMuteLine = new CtHLayout();
					pMuteLine->addStretch(4);
					pMuteLine->addWidget(new CtLabel(IC_AUDIO_REC_OFF), 11);
					pMuteLine->addStretch(8);
					m_pLevelSwitchArea->addLabel(pMuteLine, 0);

					// Level
					CtVLayout* pLevelMeterArea = new CtVLayout();
					{
						CtHLayout* pLevelCh1 = new CtHLayout();
						{
							for (int i = 0; i < 19; i++) {
								m_pLevelCh1 = new CtStackLabel();
								{
									if (i != 18) {
										m_pLevelCh1->addLabel(IC_AUDIO_LEVEL_OFF);
										m_pLevelCh1->addLabel(IC_AUDIO_LEVEL_ON);
									}
									else {
										m_pLevelCh1->addLabel(IC_AUDIO_LEVEL_OFF);
										m_pLevelCh1->addLabel(IC_AUDIO_LEVEL_RED);
									}
									m_pLevelCh1->setFastDraw(true);
								}
								pLevelCh1->addWidget(m_pLevelCh1, 18);
								m_pLevelSetCh1.push_back(m_pLevelCh1);
								pLevelCh1->addStretch(4);
							}
						}
						pLevelMeterArea->addWidget(pLevelCh1, 38);
						pLevelMeterArea->addStretch(14);

						CtHLayout* pLevelCh2 = new CtHLayout();
						{
							for (int i = 0; i < 19; i++) {
								m_pLevelCh2 = new CtStackLabel();
								{
									if (i != 18) {
										m_pLevelCh2->addLabel(IC_AUDIO_LEVEL_OFF);
										m_pLevelCh2->addLabel(IC_AUDIO_LEVEL_ON);
									}
									else {
										m_pLevelCh2->addLabel(IC_AUDIO_LEVEL_OFF);
										m_pLevelCh2->addLabel(IC_AUDIO_LEVEL_RED);
									}
									m_pLevelCh2->setFastDraw(true);
								}
								pLevelCh2->addWidget(m_pLevelCh2, 18);
								m_pLevelSetCh2.push_back(m_pLevelCh2);
								pLevelCh2->addStretch(4);
							}
						}
						pLevelMeterArea->addWidget(pLevelCh2, 38);
					}
					m_pLevelSwitchArea->addLabel(pLevelMeterArea, 1);
					pAudioLine->addWidget(m_pLevelSwitchArea, 23);
				}
			}
			pAllAudioLevel->addWidget(pAudioLine, 2);
			pAllAudioLevel->addStretch(1);
		}
		pAll->addWidget(pAllAudioLevel);
	}
	return pAll;
}

CtFastContainerAudioLevel_Home::~CtFastContainerAudioLevel_Home() {
	m_pHeadRooms.clear();
};

void CtFastContainerAudioLevel_Home::updateSegmentSub()
{
	m_pHeadRooms[m_PreSeg]->setVisible(false);
	m_pHeadRooms[7 + m_Seg]->setVisible(true);
	m_PreSeg = 7 + m_Seg;
}
