/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtFastCounter
 */
#include "CtFastCounter.h"
#include "CtHLayout.h"

CtFastCounter::CtFastCounter() :
	m_Counter(0),
	m_rank_1000(-1),
	m_rank_100(-1),
	m_rank_10(-1),
	m_rank_1(-1)
{
	setClassType(CtClassType_LayoutMain);
}


CtLayout* CtFastCounter::createContainer()
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	const char *pText[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	
	CtLayout* pLayout = new CtHLayout(CtSize(200, 50), CtColor::darkGreen);

	for (int i = 0; i < 4; i++) {
		m_pLabel[i] = new CtStackLabel();
		
		for (int j = 0; j < 10; j++) {
			m_pLabel[i]->addLabel(pText[j], fSet);
		}
		m_pLabel[i]->setFastDraw(true);
		pLayout->addWidget(m_pLabel[i]);
	}
	//	pLayout->setFastDraw(true);
	
	return pLayout;
}

bool CtFastCounter::destroyContainer()
{
	return true;
}

CtFastCounter::~CtFastCounter()
{
}

bool CtFastCounter::updateFastDraw()
{
	int rank_1000, rank_100, rank_10, rank_1;
	
	m_Counter++;

	rank_1000 = m_Counter / 1000;
	rank_1000 = rank_1000 % 10;

	rank_100 = m_Counter / 100;
	rank_100 = rank_100 % 10;
	
	rank_10 = m_Counter / 10;
	rank_10 = rank_10 % 10;

	rank_1 = m_Counter % 10;
	
	if (m_rank_1000 != rank_1000) {
		m_pLabel[0]->index(rank_1000);
		m_rank_1000 = rank_1000;
	}
	
	if (m_rank_100 != rank_100) {
		m_pLabel[1]->index(rank_100);
		m_rank_100 = rank_100;
	}
	
	if (m_rank_10 != rank_10) {
		m_pLabel[2]->index(rank_10);
		m_rank_10 = rank_10;
	}
	
	if (m_rank_1 != rank_1) {
		m_pLabel[3]->index(rank_1);
		m_rank_1 = rank_1;
	}

	return true;
}

