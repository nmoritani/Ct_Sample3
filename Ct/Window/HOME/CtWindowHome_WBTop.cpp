/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowFactory
 */

#include "CtWindowHome_WBTop.h"
#include "CtButton.h"
/*

	VerUpから外れたため、未対応
	今後のVerUpのため、置いておく

*/
CtWindow* CtWindowHome_WBTop::createWindow()
{
	m_pWin = new CtWindow();
	m_LabelColor = CtColor(71,72,74,0xff);// Gray
	m_ImageColor = CtColor(240,240,240,0xff);// White
	m_LineColor = CtColor(40, 41, 44, 0xff);// BoundaryColor 紺色

	///////////////////////////////////////// UPPER /////////////////////////////////////////
	/*                                                                                      */
	/*  |<---------(319)----------|6|---------(314)-------|6|-----------(319)----------->|  */
	/*  | 3 (addStretch )         | |                     | |                            |  */
	/*  |-------------------------|-|---------------------| |--------------------------- |  */
	/*  | 60                      | |                     | |                            |  BtnLayout*/
	/*  |-------------------------|-|---------------------| |----------------------------|  */
	/*  | 50                      | |                     | |                            |  BtnNameLayout*/
	/*  |_________________________|_|_____LayoutUpper_____| |____________________________|  */
	/*  |314 ( addStretch  )                                                             |  */
	/*  |_______________________________LayoutLower______________________________________|  */
	/*  |                         | |                      | |                           |  */
	/*  |50                       |6|                      |6|                           |  BtnNameLayout*/
	/*  |-------------------------| |----------------------| |---------------------------|  */
	/*  |60                       | |                      | |                           |  BtnLayout*/
	/*  |-------------------------| |----------------------| |-------------------------- |  */
	/*  |3(addStretch )           | |                      | |                           |  */
	/*  |<---------(319)----------| |----------(314)-------| |-----------(319)---------->|  */

	//////// NAME COMMON RESOURCE ////////
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	//////// VALUE COMMON RESOURCE ////////
	CtFontSet fBtnSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::Black);

	//Upper
#if 0
	//////// VALUE LEFT ////////
	CtStackLabel* pStackLabelUpperLeft = new CtStackLabel();
	pStackLabelUpperLeft->addLabel(new CtLabel( STR_ID_NO_10173, fBtnSet));
	CtLayout* pLayoutUpperLeft = new CtLayout();
	pLayoutUpperLeft->addWidget(pStackLabelUpperLeft);

	CtLinkButton* pButtonUpperLeft = new CtLinkButton( WindowID_Menu_WHITE_VALUE, OpenPopup, CtSize(312, 60), pLayoutUpperLeft, None);
	pButtonUpperLeft->setImage(IC_TOP_LEFT);
//	pButtonUpperLeft->setColorStyle(m_ImageColor);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//m	pButtonUpperLeft->setLabelColorStyle(CtColor::Black);
	//////// VALUE CENTER ////////
	CtStackLabel* pStackLabelUpperCenter = new CtStackLabel();
	pStackLabelUpperCenter->addLabel(new CtLabel( STR_ID_NO_10084, fBtnSet));
	CtLayout* pLayoutUpperCenter = new CtLayout();
	pLayoutUpperCenter->addWidget(pStackLabelUpperCenter);

	CtLinkButton* pButtonUpperCenter = new CtLinkButton( WindowID_Menu_AWB, OpenPopup, CtSize(312, 60), pLayoutUpperCenter, None);
	pButtonUpperCenter->setImage(IC_TOP_CENTER);
//	pButtonUpperCenter->setColorStyle(m_ImageColor);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//m	pButtonUpperCenter->setLabelColorStyle(CtColor::Black);

	//////// VALUE RIGHT ////////
	CtStackLabel* pStackLabelUpperRight = new CtStackLabel();
	pStackLabelUpperRight->addLabel(new CtLabel( STR_ID_NO_10174, fBtnSet));
	CtLayout* pLayoutUpperRight = new CtLayout();
	pLayoutUpperRight->addWidget(pStackLabelUpperRight);

	CtLinkButton* pButtonUpperRight = new CtLinkButton(WindowID_Menu_WHITE_ADD_K, OpenPopup, CtSize(312, 60), pLayoutUpperRight, None);
	pButtonUpperRight->setImage(IC_TOP_RIGHT);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//m	pButtonUpperRight->setLabelColorStyle(CtColor::Black);
//	pButtonUpperRight->setColorStyle(m_ImageColor);

	//////// VALUE LINE UP ////////
	CtHLayout* pLayoutUpperValue = new CtHLayout(m_LabelColor);
	pLayoutUpperValue->addStretch(6);
	pLayoutUpperValue->addWidget(pButtonUpperLeft, CtMargin(0, 0), 312);
	pLayoutUpperValue->addStretch(6);
	pLayoutUpperValue->addWidget(pButtonUpperCenter, CtMargin(0, 0), 312);
	pLayoutUpperValue->addStretch(6);
	pLayoutUpperValue->addWidget(pButtonUpperRight, CtMargin(0, 0), 312);
	pLayoutUpperValue->addStretch(6);

	//////// NAME LEFT ////////
	CtLabel* pLabelUpperBoundaryLeft = new CtLabel(CtSize(4, 18));
	CtLabel* pLabelUpperLeftName = new CtLabel(STR_ID_NO_10173, fSet);
	pLabelUpperBoundaryLeft->setColor(m_LineColor);

	//////// NAME CENTER ////////
	CtLabel* pLabelUpperBoundaryCenter = new CtLabel(CtSize(4, 18));
	pLabelUpperBoundaryCenter->setColor(m_LineColor);
	
	//////// NAME RIGHT ////////
	
	//////// NAME LINE UP ////////
	CtHLayout* pLayoutUpperName = new CtHLayout(); 
	pLayoutUpperName->addWidget( pLabelUpperLeftName, CtMargin( 0, 0), 319);
	pLayoutUpperName->addWidget( pLabelUpperBoundaryLeft, 4);
	pLayoutUpperName->addStretch(314);
	pLayoutUpperName->addWidget( pLabelUpperBoundaryCenter, 4);
	pLayoutUpperName->addStretch(319);
	
	//////// LOWER LAYOUT INTEG ////////
	// Name用レイアウトとValue用レイアウトの統合
	CtVLayout* pLayoutUpper = new CtVLayout( m_LabelColor);
	pLayoutUpper->addStretch(3);
	pLayoutUpper->addWidget(pLayoutUpperValue, AlignCenter, 60);
	pLayoutUpper->addWidget(pLayoutUpperName, AlignCenter, 50);

	// LOWER
	//////// VALUE LEFT ////////
	CtStackLabel* pStackLabelLowerLeft = new CtStackLabel();
	pStackLabelLowerLeft->addLabel(new CtLabel( STR_ID_NO_10175, fBtnSet));
	CtLayout* pLayoutLowerRight = new CtLayout();
	pLayoutLowerRight->addWidget( pStackLabelLowerLeft);

	CtLinkButton* pButtonLowerLeft = new CtLinkButton( WindowID_Menu_WHITE_EDIT_K, OpenPopup, CtSize(312, 60), pLayoutLowerRight, None);
	pButtonLowerLeft->setImage(IC_TOP_RIGHT);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//m	pButtonLowerLeft->setLabelColorStyle(CtColor::Black);
	//pButtonLowerLeft->setColorStyle(m_ImageColor);
	
	//////// VALUE CENTER ////////
	CtStackLabel* pStackLabelLowerCenter = new CtStackLabel();
	pStackLabelLowerCenter->addLabel(new CtLabel( STR_ID_NO_10014, fBtnSet));
	CtLayout* pLayoutLowerCenter = new CtLayout();
	pLayoutLowerCenter->addWidget( pStackLabelLowerCenter);

	CtLinkButton* pButtonLowerCenter = new CtLinkButton( WindowNone, Close, CtSize(312, 60), pLayoutLowerCenter, None);
	pButtonLowerCenter->setImage(IC_AUDIO_BOTTOM_CENTER);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//m	pButtonLowerCenter->setLabelColorStyle(CtColor::Black);
	//pButtonLowerCenter->setColorStyle(m_ImageColor);

	//////// VALUE RIGHT ////////
	CtLinkButton* pButtonLowerRight = new CtLinkButton( WindowNone, Close, CtSize(312, 60), STR_ID_NO_10794, fBtnSet, None);
	pButtonLowerRight->setImage(IC_TOP_LEFT);
	// CtButtonクラスコンストラクタでthis->LabelColor = FontSet.fontColorとすべき
	//m	pButtonLowerRight->setLabelColorStyle(CtColor::Black);
	//pButtonLowerRight->setColorStyle(m_ImageColor);
	
	//////// VALUE LINE UP ////////
	CtHLayout* pLayoutLowerValue = new CtHLayout(m_LabelColor );
	pLayoutLowerValue->addStretch(6);
	pLayoutLowerValue->addWidget(pButtonLowerLeft, CtMargin(0, 0), 312);
	pLayoutLowerValue->addStretch(6);
	pLayoutLowerValue->addWidget(pButtonLowerCenter, CtMargin(0, 0), 312);
	pLayoutLowerValue->addStretch(6);
	pLayoutLowerValue->addWidget(pButtonLowerRight, CtMargin(0, 0), 312);
	pLayoutLowerValue->addStretch(6);
	
	//////// NAME LEFT ////////
	CtLabel* pLabelLowerLeftBoundary = new CtLabel(CtSize(4, 18));
	pLabelLowerLeftBoundary->setColor(m_LineColor);
	
	//////// NAME RIGHT ////////
	
	//////// NAME CENTER ////////
	CtLabel* pLabelLowerCenterBoundary = new CtLabel(CtSize(4, 18));
	pLabelLowerCenterBoundary->setColor(m_LineColor);

	//////// NAME LINE UP ////////
	CtHLayout *pLayoutLowerName = new CtHLayout(m_LabelColor); 
	pLayoutLowerName->addStretch(319);
	pLayoutLowerName->addWidget(pLabelLowerLeftBoundary, 4);
	pLayoutLowerName->addStretch(314);
	pLayoutLowerName->addWidget(pLabelLowerCenterBoundary, 4);
	pLayoutLowerName->addStretch(319);
	
	//////// LOWER LAYOUT INTEG ////////
	// Name用レイアウトとValue用レイアウトの統合
	CtVLayout* pLayoutLower = new CtVLayout(m_LabelColor);
	pLayoutLower->addWidget( pLayoutLowerName, AlignCenter, 50);
	pLayoutLower->addWidget( pLayoutLowerValue, AlignCenter, 60);
	pLayoutLower->addStretch(3);
	
	CtVLayout *pLayoutAll = new CtVLayout();
	pLayoutAll->addWidget( pLayoutUpper, 113);
	pLayoutAll->addStretch( 314);
	pLayoutAll->addWidget( pLayoutLower, 113);
	
	//////// LOWER ////////
	m_pWin->addWidget(pLayoutAll);
	m_pWin->setRegion(CtRegion(0,0,960,540));
	m_pWin->setColor(CtColor::Black);
	m_pWin->setVisible(true);
	m_pWin->setLayout();
	//m_pWin->setName("CtWindowHome_WBTop");
#endif
	m_pWin->setRoundFocus(true);
	return m_pWin;
}

CtWindowHome_WBTop::CtWindowHome_WBTop()
{
	m_pWin = NULL;
	setClassType(CtClassType_LayoutMain);
}

