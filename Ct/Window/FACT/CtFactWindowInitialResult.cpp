/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowInitialResult
*/


#include "CtFactWindowInitialResult.h"

CtFactWindowInitialResult::CtFactWindowInitialResult(CtWindowContents *pContents) :
	m_pContent(NULL)
{
	if( pContents != NULL ){
		m_pContent = new CtWindowContentsInitialResult((CtWindowContentsInitialResult&)*pContents);
	}
	setClassType(CtClassType_WindowFACT);
}


CtWindow* CtFactWindowInitialResult::createWindow()
{
	m_pWin = new CtWindow();

	CtVLayout* pAll = new CtVLayout(CtColor::Gray);
	if( m_pContent != NULL ){
		CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

		CtHLayout* pLayou1 = new CtHLayout();
		CtHLayout* pLayou2 = new CtHLayout();
		CtHLayout* pLayou3 = new CtHLayout();
		CtHLayout* pLayou4 = new CtHLayout();
		CtHLayout* pLayou5 = new CtHLayout();
		CtHLayout* pLayou6 = new CtHLayout();
		CtHLayout* pLayou7 = new CtHLayout();
		
		pAll->addWidget(pLayou1);
		pAll->addWidget(pLayou2);
		pAll->addWidget(pLayou3);
		pAll->addWidget(pLayou4);
		pAll->addWidget(pLayou5);
		pAll->addWidget(pLayou6);
		pAll->addWidget(pLayou7);

		/* 1段目 */
		if ( m_pContent->getResult()->RESULT ){
			pLayou1->addWidget(new CtLabel("*** END ***"));
		} else {
			pLayou1->addWidget(new CtLabel("*** NG ***"));
		}
		/* 2段目 */
		if( (false == m_pContent->getResult()->SUM_CAM) && (false == m_pContent->getResult()->SUM_BE) ){
			pLayou2->addWidget(new CtLabel("SUM  CAM/BE", fSet), AlignRight,2);
			pLayou2->addWidget(new CtLabel(":"),1);
			pLayou2->addWidget(new CtLabel("NG", fSet), AlignHCenter,1);
			pLayou2->addStretch(1);
		}else if( false == m_pContent->getResult()->SUM_CAM ){
			pLayou2->addWidget(new CtLabel("SUM  CAM", fSet), AlignRight,2);
			pLayou2->addWidget(new CtLabel(":"),1);
			pLayou2->addWidget(new CtLabel("NG", fSet), AlignHCenter,1);
			pLayou2->addStretch(1);
		}else if( false == m_pContent->getResult()->SUM_BE ){
			pLayou2->addWidget(new CtLabel("SUM  BE", fSet), AlignRight,2);
			pLayou2->addWidget(new CtLabel(":"),1);
			pLayou2->addWidget(new CtLabel("NG", fSet), AlignHCenter,1);
			pLayou2->addStretch(1);
		}else{
			pLayou2->addWidget(new CtLabel("SUM CHECK", fSet), AlignRight,2);
			pLayou2->addWidget(new CtLabel(":"),1);
			pLayou2->addWidget(new CtLabel("OK", fSet), AlignHCenter, 1);
			pLayou2->addStretch(1);
		}
		/* 3段目 */
		pLayou3->addWidget(new CtLabel("CAM RESET", fSet), AlignRight, 2);
		pLayou3->addWidget(new CtLabel(":"), 1);
		if ( m_pContent->getResult()->CAM_RESET ){
			pLayou3->addWidget(new CtLabel("OK", fSet), AlignHCenter, 1);
		} else {
			pLayou3->addWidget(new CtLabel("NG", fSet), AlignHCenter, 1);
		}
		pLayou3->addStretch(1);
		/* 4段目 */
		pLayou4->addWidget(new CtLabel(""));
		/* 5段目 */
		pLayou5->addWidget(new CtLabel(""));
		/* 6段目 */
		pLayou6->addWidget(new CtLabel(""));
		/* 7段目 */
		pLayou7->addWidget(new CtLabel(""));
		
	}

	m_pWin->addWidget(pAll, CtMargin(20,20));
	m_pWin->setTrans(false);
	m_pWin->setColor(CtColor::Trans);

	return m_pWin;
}

CtFactWindowInitialResult::~CtFactWindowInitialResult()
{
	if(m_pContent != NULL){
		delete m_pContent;
		m_pContent = NULL;	
	}
}

bool CtFactWindowInitialResult::destroyWindow()
{
	return true;
}



bool CtFactWindowInitialResult::setContents(const CtWindowContents* pContents)
{
	return false;
}

