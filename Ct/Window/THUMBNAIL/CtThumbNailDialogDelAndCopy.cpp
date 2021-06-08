/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtThumbNailDialog_DelAndCopy
 */


#include "CtThumbNailDialogDelAndCopy.h"
#include "str_id.h"
#include "string_api.h"
#include "CtLanguage.h"


#define ThumbNailColorProgressstroke   CtColor(ColorRGBA, 0x868686ff, NULL)
#define ThumbNailColorProgressBase   CtColor(ColorRGBA, 0x000000ff, NULL)
#define ThumbNailColorProgressBar    CtColor(ColorRGBA, 0x66e300ff, NULL)

CtThumbNailDialog_DelAndCopy::CtThumbNailDialog_DelAndCopy(CtWindowContents* pContents ) :
    m_percent(0),
    m_totalValue(0),
    m_changeValue(0),
    m_pLabel(NULL),
    m_pUp(NULL),
    m_pDown(NULL),
    m_pCancel(NULL),
    m_pProgressBar(NULL),
    m_pBatt(NULL),
    m_pThumb(NULL),
    m_pWin(NULL)
{
}
CtWindow* CtThumbNailDialog_DelAndCopy::createWindow()
{
    CtFontSet fSet = CtFontSet(CtColor::White);

    m_pWin = new CtWindow();
	m_pWin->setColor(CtColor::Black);

    /* m_PWinç\íz                                                                         */
	/*                                                                                    */
	/*  |<----------------------------------(960)------------------------------------->|  */
	/*  | 49 (createTitle)                                                             |  */
	/*  |-------------------------------------------------- ---------------------------|  */
	/*  | 2 (årê¸)                                                                     |  */
	/*  |------------------------------------------------------------------------------|  */
	/*  | 292 (createMessage)                                                          |  */
	/*  |------------------------------------------------------------------------------|  */
	/*  | 70 (createProgressBar)                                                       |  */
	/*  |------------------------------------------------------------------------------|  */
	/*  | 127 (addStretch)                                                             |  */
	/*  |------------------------------------------------------------------------------|  */
	/*  | 77 (createControl)                                                           |  */
	/*  |------------------------------------------------------------------------------|  */
	/*  | 16 (addStretch )                                                             |  */
	/*  |------------------------------------------------------------------------------|  */


    CtVLayout *pAll = new CtVLayout();
    pAll->addWidget(createTitle(),49);
    CtLabel *pLine = new CtLabel(CtColor(134,134,134,0xff)); //årê¸
    pAll->addWidget(pLine,2);
    
    pAll->addWidget(createMessage(),292);
    
    pAll->addWidget(createProgressBar(),70);
    pAll->addStretch(127);
 
    pAll->addWidget(createControl(),77);
    pAll->addStretch(16);

    m_pWin->addWidget( pAll );
	m_pWin->setVisible(true);
    
	return m_pWin;

}
CtLayout* CtThumbNailDialog_DelAndCopy::createTitle()
{
    /* Window_Deleting :Layoutç\íz                                                          */
	/*                                                                                      */
	/*  |<--------------------------(960)---------------------------------------------->|   */
	/*  | 14 |  869 (Title)                                       | 57 (Battery)   | 20 |   */
	/*  |-------------------------------------------------------------------------------|   */

    /* Window_Copying :Layoutç\íz                                                           */
	/*                                                                                      */
	/*  |<--------------------------(960)---------------------------------------------->|   */
	/*  | 14 |  200 (Title)|    237   | 14 | 30 | 14  |    374    | 57 (Battery)   | 20 |   */
	/*  |-------------------------------------------------------------------------------|   */

     CtFontSet fSet = CtFontSet(CtColor::White);
     CtHLayout *pTitle = new CtHLayout();
     pTitle->addStretch(14);

     int value = APL_PARAM_GET_DATA(AplParamCopyDirection);
     switch(getWindowID()){
         case Window_Deleting :
             pTitle->addWidget(new CtLabel(STR_ID_NO_10014,fSet),AlignLeft,869);
             break;

         case Window_Copying :
             if ( APL_SYS_PARAM_COPY_DIRECTION_SLOT1_SLOT2 == value ){
             pTitle->addWidget(new CtLabel(STR_ID_NO_10016,fSet),AlignLeft,200);
             pTitle->addWidget(new CtLabel(STR_ID_NO_10005,CtFontSet(FontTypeNormal_alignRight,CtColor::White)),AlignRight,237);
             pTitle->addStretch(14);
             pTitle->addWidget(new CtLabel(IC_THUMBNAIL_COPY_ARROW),CtMargin(9,9,0,0),30);
             pTitle->addStretch(14);
             pTitle->addWidget(new CtLabel(STR_ID_NO_10006,fSet),AlignLeft,374);
             } else if (APL_SYS_PARAM_COPY_DIRECTION_SLOT2_SLOT1 == value) {
                 pTitle->addWidget(new CtLabel(STR_ID_NO_10016,fSet),AlignLeft,200);
                 pTitle->addWidget(new CtLabel(STR_ID_NO_10006,CtFontSet(FontTypeNormal_alignRight,CtColor::White)),AlignRight,237);
                 pTitle->addStretch(14);
                 pTitle->addWidget(new CtLabel(IC_THUMBNAIL_COPY_ARROW),CtMargin(9,9,0,0),30);
                 pTitle->addStretch(14);
                 pTitle->addWidget(new CtLabel(STR_ID_NO_10005,fSet),AlignLeft,374);
             }
             break;

         default:
             break; 
     
     }

     m_pBatt = new CtContainerBattery();
     pTitle->addContainer(m_pBatt,CtMargin(7,7,0,0),57);
     pTitle->addStretch(20);
     return pTitle;
}
CtLayout* CtThumbNailDialog_DelAndCopy::createMessage()
{
    /* Layoutècíz                                                               */
	/*                                                                          */
	/*  |<--------------------------(960)---------------------------------->|   */
	/*  |                           62 (addStretch)                         |   */
	/*  |-------------------------------------------------------------------|   */
    /*  |                           60 (m_pUp)                              |   */
    /*  |-------------------------------------------------------------------|   */
    /*  |                           2 (addStretch)                          |   */
    /*  |-------------------------------------------------------------------|   */
    /*  |                           60 (m_pDown)                            |   */
    /*  |-------------------------------------------------------------------|   */
    /*  |                           64 (addStretch)                         |   */
    /*  |-------------------------------------------------------------------|   */
    CtFontSet fSet = CtFontSet(CtColor::White);
    CtVLayout *pMessage = new CtVLayout();
    pMessage->addStretch(62);
    switch(getWindowID()){
        case Window_Deleting:
            m_pUp = new CtLabel(STR_ID_NO_10908);
            pMessage->addWidget( m_pUp,60);
            break;

        case Window_Copying:
             m_pUp = new CtLabel(STR_ID_NO_10911);
             pMessage->addWidget(m_pUp,60);
             break;

        default:
            break;
    }

    pMessage->addStretch(2);
    m_pDown = new CtLabel("");
    pMessage->addWidget( m_pDown,60);
    pMessage->addStretch(64);

    return pMessage;
}
CtLayout* CtThumbNailDialog_DelAndCopy::createProgressBar()
{
    /*  Layoutç\íz                                                                          */
	/*                                                                                      */
	/*  |<--------------------------(960)---------------------------------------------->|   */
	/*  | 196 (addStretch) |        568 (ProgressBar)              | 30 | 166(percent)  |   */
	/*  |-------------------------------------------------------------------------------|   */
    CtFontSet fSet = CtFontSet(CtColor::White);
    CtHLayout *pHLayout = new CtHLayout();
 
    // ProgressBar
    CtRect BaseRect = CtRect(ThumbNailColorProgressBase,2,ThumbNailColorProgressstroke);
    CtRect BarRect = CtRect(ThumbNailColorProgressBar,2,ThumbNailColorProgressBase);
    CtMargin PbMargin = CtMargin(2,2);

    //CtVLayout *pLayoutProgressBar = new CtVLayout();
    //pLayoutProgressBar->addWidget(new CtLabel(),AlignCenter,1);
    m_pProgressBar = new CtContainerIndicateFrame(CT_FRAME_TYPE_PROGRESS_BAR,BaseRect,BarRect,PbMargin);
    //percent
    m_pLabel = new CtLabel("",fSet);
    
    pHLayout->addStretch(196);
	pHLayout->addContainer(m_pProgressBar,CtMargin(20,16,0,0),568);
    pHLayout->addStretch(30);
    pHLayout->addWidget(m_pLabel,166);
  
    return pHLayout;

}
CtLayout* CtThumbNailDialog_DelAndCopy::createControl()
{
    /*  Layoutç\íz                                                                          */
	/*                                                                                      */
	/*  |<--------------------------(960)---------------------------------------------->|   */
	/*  | 336 (addStretch) |          288 (m_pCancel)              | 336 (addStretch)   |   */
	/*  |-------------------------------------------------------------------------------|   */
    CtHLayout *pBtn = new CtHLayout(); 
    m_pCancel = new CtButton(CtSize(288,60),STR_ID_NO_10217);
 
    pBtn->addStretch(336);
    pBtn->addWidget(m_pCancel,288);
    pBtn->addStretch(336);
    //set Focus
    m_pCancel->setFocus(false);
    return pBtn;
}
void CtThumbNailDialog_DelAndCopy::updateProgressBar()
{
    char str[64] = {0};
	int len = 0;
	unsigned short clip[100];
	unsigned short *gdistr = NULL;
	memset(clip,0,sizeof(clip));
	gdistr = GDI_GetString( CtLanguage::getLanguageID(), STR_ID_NO_10011 );	// "CLIP" [S:10011]CLIP 
	for (int i = 0; gdistr[i]; i++){
		clip[len++] = gdistr[i];
    }
	
	/* ÉRÉsÅ[êiíªÉoÅ[ÇÃÉpÅ[ÉZÉìÉgÇÕAPL_PARAMÇ©ÇÁéÊìæ */
	if( getWindowID() == Window_Copying ){
		m_percent = APL_PARAM_GET_DATA(AplParamPlayGeneralProgressBar);
	} else {
		int tempTotal = m_totalValue;
		if (tempTotal == 0) {
			tempTotal = 1;
		}
		m_percent = (m_changeValue * 100) / tempTotal;
	}

    if(m_percent < 0){
       m_pProgressBar->setPercent(0);
    }else if(m_percent > 100){
       m_pProgressBar->setPercent(100);
    }else{
       m_pProgressBar->setPercent(m_percent);
    }
    
    sprintf(str,"%d",m_percent);
    strncat( str, "%", 1);
    m_pLabel->setText(str);

	char total[16] = { 0 };
	char change[16] = { 0 };
	if (m_totalValue > 9999) {
		sprintf(total, "%s", "9999+");
	}
	else {
		sprintf(total, "%d", m_totalValue);
	}
	if (m_changeValue > 9999) {
		sprintf(change, "%s", "9999+");
	}
	else {
		sprintf(change, "%d", m_changeValue);
	}
    sprintf(str," : %s / %s",change,total);
	for( int i = 0 ; str[i] ; i++){
		clip[len++] = (unsigned short)str[i];
	}
    m_pDown->setText(clip);
    return;
}

bool CtThumbNailDialog_DelAndCopy::handleButtonEvent(const CtEventButton& Button)
{
    CtWindow* pWindow = NULL;
    CtFuncID FuncId = FuncID_MAX;
    bool bRet = false;

	/* ReleaseÇ≈ÇÃÇ›èàóù */
	if (Button.getPressType() != CtEventButton::Release) {
		return false;
	}
    if( m_pCancel != NULL && Button.getWidget() == m_pCancel ){
        switch(getWindowID()){
            case Window_Deleting:
                FuncId = FuncID_DELETE_CANCEL;
                bRet = true;
                break;
            case Window_Copying:
                FuncId = FuncID_COPY_CANCEL;
                bRet = true;
                break;
            default: 
                break;
        }

    } 

    if( FuncId != FuncID_MAX ){
		CtWindow *pWindow = NULL;
		if ((pWindow = m_pCancel->getWindow()) != NULL) {
			CtEventInterface::requestFuncCmd(FuncId, m_pWin);
            bRet = true;
        }
	}
    return bRet;
    
}

bool CtThumbNailDialog_DelAndCopy::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;

    if( pContents == NULL ) return mRet;
    m_pThumb = new CtWindowContentsThumbConfirm((CtWindowContentsThumbConfirm&)*pContents);

    if (m_pThumb != NULL){

        switch( m_pThumb->getType() ){
            case Window_Deleting:
                setWindowID(m_pThumb->getType());
                m_totalValue = m_pThumb->getContentsThumbConfirmInfo().cnt;
                m_changeValue = m_pThumb->getContentsThumbConfirmInfo().ClipNum;
                updateProgressBar();
                mRet = true;
            break;
            case Window_Copying:
    	        setWindowID(m_pThumb->getType());
                m_totalValue = m_pThumb->getContentsThumbConfirmInfo().cnt;
                m_changeValue = m_pThumb->getContentsThumbConfirmInfo().ClipNum;
                updateProgressBar();
                mRet = true;
            break;
        default:    
            break;
        }
    }

    return mRet;
}

CtThumbNailDialog_DelAndCopy::~CtThumbNailDialog_DelAndCopy()
{
    destroyWindow();
}

bool CtThumbNailDialog_DelAndCopy::destroyWindow()
{
     if(m_pThumb != NULL){
         delete m_pThumb;
         m_pThumb = NULL;
     }
	return true;
}

bool CtThumbNailDialog_DelAndCopy::handleParamEvent(const CtEventParam& Param)
{
    bool bRet = false;
    int t_Id = Param.getParamId();
    int int_Data = Param.getParamVal();
	
	switch(t_Id){
	case AplParamPlayGeneralProgressBar:
		updateProgressBar();
		bRet = true;
		break;
	default:
		break;
	}

	return bRet;
}

bool CtThumbNailDialog_DelAndCopy::updateContents() {
	updateProgressBar();
	return true;
}