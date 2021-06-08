/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:           CtContainerFile
 */
#include "CtContainerFile.h"
#include "CtEventInterface.h"


#define LIST_MAX            1000
#define WidgetFILE_OFFSET   (1000)


CtContainerFile::CtContainerFile( CtWindowID id, CtWindowContents* pContents ) :
    m_id(id),
    m_pContentsFile(NULL),
	m_MenuList(NULL)
{
    if (pContents != NULL) {
        m_pContentsFile = new CtWindowContentsFileInfo((CtWindowContentsFileInfo&)*pContents);
    }
}
bool CtContainerFile::destroyContainer()
{
	return true;
}
CtContainerFile::~CtContainerFile()
{
	if (m_pContentsFile != NULL) {
		delete m_pContentsFile;
		m_pContentsFile = NULL;
	}
}

CtLayout* CtContainerFile::createContainer()
{
	m_MenuList = new CtContainerVariableMenuList(m_id);
	update_ListView();

	CtLayout* pAll = new CtLayout();
	pAll->addContainer(m_MenuList);

    return pAll;
}

bool CtContainerFile::setContents(const CtWindowContents* pContents)
{
    bool mRet = false;

    if( m_pContentsFile != NULL ){
        delete m_pContentsFile;
        m_pContentsFile = NULL;
    }

    if( pContents == NULL ) return mRet;

    m_pContentsFile = new CtWindowContentsFileInfo((CtWindowContentsFileInfo&)*pContents);

    mRet = true;

    return mRet;

}

void CtContainerFile::updateContents()
{
    update_ListView();
}

/* ================================================================================== */
/* File ListXV ==================================================================== */
/* ================================================================================== */
void CtContainerFile::update_ListView()
{
    CtDebugPrint(CtDbg, "%s %d ------------\n",__FUNCTION__,__LINE__); 

    if( m_pContentsFile == NULL ) return;
    if(m_MenuList == NULL ) return ;

    /* ‘O‰ñ•\Ž¦•”•i‚ð”jŠü */
	m_MenuList->cleanupList();

    CtWindowContentsFileInfo::FileInfoList &list = m_pContentsFile->getFileInfoList();

    for(int i = 0; i < list.size() && i < LIST_MAX; i++) {
        if( list[i] != NULL ){
			CtMenuButton *pBtn = new CtMenuButton(AutoSize, getFileInfoLayout(i), CtButton::Rect);
            pBtn->setWidgetID(i+1+WidgetFILE_OFFSET);
			pBtn->setButtonColors(CtColor::Trans, CtColor::Trans, CtColor::NoColor);

			m_MenuList->addButton(pBtn);
		}
    }
	m_MenuList->setCurrentIndex(1);
	m_MenuList->updateEnd();
}


/* ================================================================================== */
/* FileInfo Layout•`‰æ ============================================================== */
/* ================================================================================== */
CtLayout* CtContainerFile::getFileInfoLayout( int index )
{
	/* Layout\’z 960                                                                               */
    /*  |       |--|-----80-----|----|-------170-------|----|-------190-------|----|------160------|--|  */
    /*  |       |15|            | 66 |                 | 80 |                 | 66 |               |15|  */
    /*  |- 126 -|  |   FileNum  |    |     FileName    |    |     FileDate    |    |    FileTime   |  |  */
    /*  |       |__|____________|____|_________________|____|_________________|____|_______________|__|  */

	
	static const char* pMonth[12] = {
        "JAN",
        "FEB",
        "MAR",
        "APR",
        "MAY",
        "JUN",
        "JUL",
        "AUG",
        "SEP",
        "OCT",
        "NOV",
        "DEC"
    }; 

    CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);

    CtLayout* pItemLayout = new CtHLayout();

    if ( m_pContentsFile != NULL ) {

        CtWindowContentsFileInfo::FileInfoListItr Itr;
        Itr = m_pContentsFile->getFileInfoList().begin();

        char fileNum[20] = {0};
        char fileName[20] = {0};
        char fileDate[20] = {0};
        char fileTime[20] = {0};

        CtLabel* pNumLabel = new CtLabel();     //Number
        CtLabel* pNameLabel = new CtLabel();    //FileName
        CtLabel* pDateLabel = new CtLabel();    //FileDate
        CtLabel* pTimeLabel = new CtLabel();    //FileTime

        /* Number Label */
        sprintf(fileNum, "%d", index+1);
        pNumLabel->setText(fileNum);
        pNumLabel->setFontSet(fSet);

		CtVLayout* pNumberLayout = new CtVLayout();
		pNumberLayout->addStretch(10);
		pNumberLayout->addWidget(pNumLabel, AlignLeft, 70);
		pNumberLayout->addStretch(20);

        /* Name Label */
        memcpy( fileName, (*(Itr+index))->getFileInfo().FileName, 8 );
        pNameLabel->setText(fileName);
        pNameLabel->setFontSet(fSet);

		CtVLayout* pNameLayout = new CtVLayout();
		pNameLayout->addStretch(10);
		pNameLayout->addWidget(pNameLabel, AlignCenter, 70);
		pNameLayout->addStretch(20);

        /* Date Label */
        int year = (*(Itr+index))->getFileInfo().Date.Year;
        int month = (*(Itr+index))->getFileInfo().Date.Month;
        int date = (*(Itr+index))->getFileInfo().Date.Day;
        
         switch(APL_PARAM_GET_DATA(AplParamDateFormatMode)){
            case APL_SYS_PARAM_DATE_FORMAT_YEAR:
            default:
                sprintf(fileDate,"%4d-%s-%2d",
                    year,
                    pMonth[(month >= 1) ? month-1 : 0 ],
                    date);
                break;
            case APL_SYS_PARAM_DATE_FORMAT_MONTH:
                sprintf(fileDate,"%s-%2d-%4d",
                    pMonth[(month >= 1) ? month-1 : 0],
                    date,
                    year);
                break;
            case APL_SYS_PARAM_DATE_FORMAT_DATE:
                sprintf(fileDate,"%2d-%s-%4d",
                    date,
                    pMonth[(month >= 1) ? month-1 : 0],
                    year);
                break;
        }
        pDateLabel->setText(fileDate);
        pDateLabel->setFontSet(fSet);

		CtVLayout* pDateLayout = new CtVLayout();
		pDateLayout->addStretch(10);
		pDateLayout->addWidget(pDateLabel, AlignCenter, 70);
		pDateLayout->addStretch(20);

        /* Time Label */
        sprintf(fileTime,"%02d:%02d:%02d",
            (*(Itr+index))->getFileInfo().Time.Hour,
            (*(Itr+index))->getFileInfo().Time.Min,
            (*(Itr+index))->getFileInfo().Time.Sec
            );
        pTimeLabel->setText(fileTime);
        pTimeLabel->setFontSet(fSet);

		CtVLayout* pTimeLayout = new CtVLayout();
		pTimeLayout->addStretch(10);
		pTimeLayout->addWidget(pTimeLabel, AlignCenter, 70);
		pTimeLayout->addStretch(20);

		pItemLayout->addStretch(15);
		pItemLayout->addWidget(pNumberLayout, 80);
		pItemLayout->addStretch(66);
		pItemLayout->addWidget(pNameLayout, 170);
		pItemLayout->addStretch(80);
		pItemLayout->addWidget(pDateLayout, 190);
		pItemLayout->addStretch(66);
		pItemLayout->addWidget(pTimeLayout, 160);
		pItemLayout->addStretch(15);

    }
	CtLayout* pLayout = new CtLayout();
	pLayout->addWidget(pItemLayout);
	pLayout->addWidget(new CtLabel(CtLine(UnderLine, 1, CtColor::White)), AlignBottom);
	pLayout->addWidget(new CtLabel(CtLine(UpperLine, 1, CtColor::White)), AlignTop);

    return pLayout;
}

bool CtContainerFile::handleButtonEvent(const CtEventButton& Button)
{
    bool bFlag = false;

    /* Release‚Å‚Ì‚Ýˆ— */
    if ((Button.getPressType() != CtEventButton::Release) &&
        (Button.getPressType() != CtEventButton::RepeatPress)) {
        return false;
    }

    if (m_pContentsFile != NULL) {
        unsigned long select_index = Button.getWidgetID() - WidgetFILE_OFFSET - 1;
        m_pContentsFile->setCurrentIndex(select_index);
    }

    switch(Button.getWidgetID()) {
    case WidgetID_UP:
    case WidgetID_DOWN:
    case WidgetID_RET:
        break;
    default: {
		CtWindow* pWindow = m_pLayout->getWindow();
		if (pWindow == NULL)
			break;
			
		CtScreenSel sel = pWindow->getScreenSel();
		CtWindowID id = pWindow->getWindowID();
			
        switch( m_id ) {
        case WindowID_Menu_SCENE_FILE_SAVE:
			CtEventInterface::requestFuncCmd(sel, id, FuncID_SELECT_FILE_NUMBER, m_pContentsFile);
			CtEventInterface::requestWindowCmd(CtEventWindow::Change, sel, Window_Menu_SCENE_FILE_SAVE_KEYBOARD, m_pContentsFile, NULL, true);
            bFlag = true;
            break;
        case WindowID_Menu_SETUP_FILE_SAVE:
			CtEventInterface::requestFuncCmd(sel, id, FuncID_SELECT_FILE_NUMBER, m_pContentsFile);
			CtEventInterface::requestWindowCmd(CtEventWindow::Change, sel, Window_Menu_SETUP_FILE_SAVE_KEYBOARD, m_pContentsFile, NULL, true);
            bFlag = true;
            break; 
        case WindowID_Menu_SCENE_FILE_LOAD:
			CtEventInterface::requestFuncCmd(sel, id, FuncID_SELECT_FILE_NUMBER, m_pContentsFile);
			//CtEventInterface::requestWindowCmd(CtEventWindow::Change, sel, Window_Menu_SCENE_FILE_LOAD_SCENELIST, m_pContentsFile, NULL, true);
            bFlag = true;
            break; 
        case WindowID_Menu_SETUP_FILE_LOAD:
			CtEventInterface::requestFuncCmd(sel, id, FuncID_SELECT_FILE_NUMBER, m_pContentsFile);
			CtEventInterface::requestWindowCmd(CtEventWindow::Change, sel, Window_Menu_SETUP_FILE_LOAD_CONFIRM, m_pContentsFile, NULL, true);
            bFlag = true;
            break; 
        } 
        break;
	}
	}
	return bFlag;
}
