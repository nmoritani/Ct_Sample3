/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtAreaSettingConfirm
 */

#include "CtAreaSettingConfirm.h"
#include "CtDebugPrint.h"
#include "CtWindowCommon.h"
#include "CtWindowContentsAreaSettingConfirm.h"

#define FACTORY_SETTING 0   // �uEnter�v�ƁuCancel�v�{�^�����Ȃ�
#define MENU_SETTING    1   // �uEnter�v�ƁuCancel�v�{�^��������

CtAreaSettingConfirm::CtAreaSettingConfirm(CtWindowContents *pContents) : 
    m_pWin(NULL),
    m_pConfirm(NULL),
    m_pCancel(NULL)
{
    CtWindowContentsAreaSettingConfirm* pContentsTemp = static_cast<CtWindowContentsAreaSettingConfirm*>(pContents);
    if(pContentsTemp != NULL){
        m_nUseArea = pContentsTemp->getContentsAreaSetting();
        m_nAreaSettingType = pContentsTemp->getAreaSettingType();
    }else{
        // To Be Delete
        // �ꎞContentsAreaSetting_NTSC2�ɂ��āA�uEnter�v�ƁuCancel�v�{�^��������悤�ɂ���
        m_nUseArea = ContentsAreaSetting_AREA3;
        m_nAreaSettingType = MENU_SETTING;
    }
	setClassType(CtClassType_WindowAreaSetting);
}


CtWindow* CtAreaSettingConfirm::createWindow()
{
    CtFontSet fSet_Center = CtFontSet(FontTypeNormal_alignCenter,CtColor::White);
    CtFontSet fSet_Left = CtFontSet(FontTypeNormal,CtColor::White);
    CtFontSet fSet_Right = CtFontSet(FontTypeNormal_alignRight,CtColor::White);

    CtVLayout *pAreaSettingConfirm = new CtVLayout(CtColor(ColorRGBA, 0x021527ff, NULL));      // �X�|�C�g��RGB�̒l���擾����
    // "AREA SETTINGS"
    pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_10599, fSet_Left), AlignLeft, 80);
    // ��
    pAreaSettingConfirm->addStretch(100);

    switch(m_nUseArea){
        case ContentsAreaSetting_AREA1:
            // "This device is set with NTSC1.\nAre you sure?"
            pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_10896, fSet_Center), AlignCenter, 140);
            break;
        case ContentsAreaSetting_AREA2:
            // "This device is set with NTSC2.\nAre you sure?"
            pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_10897, fSet_Center), AlignCenter, 140);
            break;
		case ContentsAreaSetting_AREA3:
			// "This device is set with PAL.\nAre you sure?"
			pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_10898, fSet_Center), AlignCenter, 140);
			break;
		case ContentsAreaSetting_AREA4:
			// "This device is set with AREA 4.\nAre you sure?"
			pAreaSettingConfirm->addWidget(new CtLabel(STR_ID_NO_11564, fSet_Center), AlignCenter, 140);
			break;
		default:
            // ��
            pAreaSettingConfirm->addStretch(140);
            break;
    }

    // ��
    pAreaSettingConfirm->addStretch(160);

    CtHLayout *pTwoBtn = new CtHLayout(CtColor(ColorRGBA, 0x021527ff, NULL));
    m_pConfirm = new CtButton(CtSize(200, 50), STR_ID_MSG_YES, fSet_Center);
    m_pCancel = new CtButton(CtSize(200, 50), STR_ID_MSG_NO, fSet_Center);
    pTwoBtn->addWidget(m_pConfirm);
    pTwoBtn->addWidget(m_pCancel);
    pAreaSettingConfirm->addWidget(pTwoBtn, 50);

    // ��
    pAreaSettingConfirm->addStretch(10);

    // Window
    m_pWin = new CtWindow();
    m_pWin->addWidget(pAreaSettingConfirm);
    /*m_pWin->setRegion(CtRegion(0,0,960,540));*/
    m_pWin->setVisible(true);
    m_pWin->setLayout();
    /* �����t�H�[�J�X��Cancel */
	// TODO m_pWin->setInitialFocusType(FocusNormal);
    m_pWin->setDefaultFocus(m_pCancel);
    
    return m_pWin;
}

CtAreaSettingConfirm::~CtAreaSettingConfirm()
{
    destroyWindow();
}


bool CtAreaSettingConfirm::destroyWindow()
{
    return true;
}

bool CtAreaSettingConfirm::handleButtonEvent(const CtEventButton& Button)
{
    bool bFlag = false;

    /* Release�ł̂ݏ��� */
    if( Button.getPressType() != CtEventButton::Release ){
        return false;
    }

	int value;
	switch (m_nUseArea){
	case ContentsAreaSetting_AREA1:
		value = APL_SYS_PARAM_USE_AREA_1;
		break;
	case ContentsAreaSetting_AREA2:
	default:
		value = APL_SYS_PARAM_USE_AREA_2;
		break;
	case ContentsAreaSetting_AREA3:
		value = APL_SYS_PARAM_USE_AREA_3;
		break;
	case ContentsAreaSetting_AREA4:
		value = APL_SYS_PARAM_USE_AREA_4;
		break;
	}

    if(m_nAreaSettingType == FACTORY_SETTING){
        if(Button.getWidget() == m_pConfirm){
            // �I�������f�[�^��AplParam�ɕۑ����āA�u���Ԑݒ�v��ʂɑJ�ڂ���
        	if( APL_PARAM_GET_DATA(AplParamUSeAreaSettings) != value) {
            	APL_PARAM_SET_DATA(AplParamUSeAreaSettings, value);
        	} else {
        		APL_PARAM_EXEC_FAKE_UPDATE(AplParamUSeAreaSettings);
        	}
            bFlag = true;
        }else if(Button.getWidget() == m_pCancel){
            // �I�������f�[�^��AplParam�ɕۑ����Ȃ��āA����AreaSetting��ʂɖ߂�
            // �uEnter�v�ƁuCancel�v�{�^�����Ȃ�
			CtEventInterface::requestWindowCmd(CtEventWindow::Return, WindowNone);
            bFlag = true;
        }else{
            // No Operation
        }
    }else if(m_nAreaSettingType == MENU_SETTING){
        if(Button.getWidget() == m_pConfirm){
            // �I�������f�[�^��AplParam�ɕۑ����āAMenu��Option��ʂɑJ�ڂ���
        	if( APL_PARAM_GET_DATA(AplParamUSeAreaSettings) != value) {
            	APL_PARAM_SET_DATA(AplParamUSeAreaSettings, value);
        	} else {
        		APL_PARAM_EXEC_FAKE_UPDATE(AplParamUSeAreaSettings);
        	}
            // Menu��Option��ʂɖ߂�i�J����AreaSetting��ʂ������A�\���j
			CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
            bFlag = true;
        }else if(Button.getWidget() == m_pCancel){
            // �I�������f�[�^��AplParam�ɕۑ����Ȃ��āA����AreaSetting��ʂɖ߂�
            // �uEnter�v�ƁuCancel�v�{�^��������iMenu�����AreaSetting��ʁj
			CtEventInterface::requestWindowCmd(CtEventWindow::Return, WindowNone);
            bFlag = true;
        }
    }

    return bFlag;
}

bool CtAreaSettingConfirm::handleKeyEvent(const CtEventKey& Key){
    bool bRet = false;

    switch (Key.getKeyAction()) {
        case CtEventKey::Press:
            switch ( Key.getKeyCode() ) {
                case CtEventKey::KeyCode_Exit:
                case CtEventKey::KeyCode_GripUser1:
                    if(m_nAreaSettingType != FACTORY_SETTING){
                        if ( NULL != m_pWin ) {
							CtEventInterface::requestWindowCmd(CtEventWindow::Close, WindowNone);
							return true;
                        }
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    return bRet;
}





