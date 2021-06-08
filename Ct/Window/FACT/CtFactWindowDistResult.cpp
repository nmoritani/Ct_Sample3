/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactWindowDistResult
*/


#include "CtFactWindowDistResult.h"

CtFactWindowDistResult::CtFactWindowDistResult(CtWindowContents *pContents) :
	m_pContent(NULL)
{
	if( pContents != NULL ){
		m_pContent = new CtWindowContentsDistResultInfo((CtWindowContentsDistResultInfo&)*pContents);
	}
	setClassType(CtClassType_WindowFACT);
}


CtWindow* CtFactWindowDistResult::createWindow()
{
	
    char Data[32] = {};

    CtFontSet fSet_Center = CtFontSet(FontTypeNormal_alignCenter,CtColor::orange);
    CtFontSet fSet_Left = CtFontSet(FontTypeNormal,CtColor::White);
    CtFontSet fSet_Right = CtFontSet(FontTypeNormal_alignRight,CtColor::White);

	m_pWin = new CtWindow();
	CtVLayout* pAll = new CtVLayout(CtColor::Gray);

	if( m_pContent != NULL ){
		CtHLayout* pLayout1 = new CtHLayout();
		CtHLayout* pLayout2 = new CtHLayout();
//		CtHLayout* pLayout3 = new CtHLayout();
		CtHLayout* pLayout4 = new CtHLayout();
		CtHLayout* pLayout5 = new CtHLayout();
		CtHLayout* pLayout6 = new CtHLayout();
		CtHLayout* pLayout7 = new CtHLayout();
		CtHLayout* pLayout8 = new CtHLayout();


		pAll->addWidget(pLayout1,AlignCenter,1);
		pAll->addWidget(pLayout2,AlignCenter,2);
//		pAll->addWidget(pLayout3,1);
		pAll->addWidget(pLayout4,1);
		pAll->addWidget(pLayout5,1);
		pAll->addWidget(pLayout6,1);
		pAll->addWidget(pLayout7,1);
		pAll->addWidget(pLayout8,1);

		/* 1’i–Ú */

		pLayout1->addWidget(new CtLabel("[EEP UPDATE]"));

		pLayout2->addWidget(new CtLabel(m_pContent->getDistResult()->dist_name,fSet_Center),AlignCenter,100);

//		pLayout3->addWidget(new CtLabel(""));

		if(m_pContent->getDistResult()->RESULT){

			pLayout4->addWidget(new CtLabel());
			pLayout4->addWidget(new CtLabel("SUM"));
			pLayout4->addWidget(new CtLabel("CRC"));
			pLayout4->addWidget(new CtLabel());

			pLayout5->addWidget(new CtLabel("CAM",fSet_Right));
			{
				int Value = APL_PARAM_GET_DATA( AplParamCamSum );
				sprintf( Data, "%04X", Value );
			}
			pLayout5->addWidget(new CtLabel(Data));
			{
				int Value = APL_PARAM_GET_DATA( AplParamCamCrc );
				sprintf( Data, "%04X", Value );
			}
			pLayout5->addWidget(new CtLabel(Data));
			pLayout5->addWidget(new CtLabel());

			pLayout6->addWidget(new CtLabel("AM",fSet_Right));
			{
				int Value = APL_PARAM_GET_DATA( AplParamBeSum );
				sprintf( Data, "%04X", Value );
			}
			pLayout6->addWidget(new CtLabel(Data));
			{
				int Value = APL_PARAM_GET_DATA( AplParamBeCrc );
				sprintf( Data, "%04X", Value );
			}
			pLayout6->addWidget(new CtLabel(Data));
			pLayout6->addWidget(new CtLabel());

		}else{
			pLayout4->addWidget(new CtLabel("ERROR"));
			pLayout5->addWidget(new CtLabel("Check Debug Log"));
			pLayout6->addWidget(new CtLabel("-> Fact EepModel"));
		}


		pLayout7->addWidget(new CtLabel());

		pLayout8->addWidget(new CtLabel("PLEASE TURN POWER OFF"));
		
	
	}
	m_pWin->addWidget(pAll, CtMargin(20, 20));
	m_pWin->setTrans(false);
	m_pWin->setColor(CtColor::Trans);

	return m_pWin;
}



CtFactWindowDistResult::~CtFactWindowDistResult()
{
	if(m_pContent != NULL){
		delete m_pContent;
		m_pContent = NULL;	
	}
}

bool CtFactWindowDistResult::destroyWindow()
{
	return true;
}



bool CtFactWindowDistResult::setContents(const CtWindowContents* pContents)
{
	return false;
}

