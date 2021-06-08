/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowHome_AudioTop
 */


#ifndef __CtWindowHome_AudioTop_H__
#define __CtWindowHome_AudioTop_H__

#include "CtWindowCommon.h"
#include "CtButton.h"
#include "CtStackLabel.h"

#define CH1_INDEX 0
#define CH2_INDEX 1
#define SEL1_INDEX 2
#define SEL2_INDEX 3
#define EXIT_INDEX 4


class CtWindowHome_AudioTop : public CtWindowMain
{
	
public:
    CtWindowHome_AudioTop();

    ~CtWindowHome_AudioTop();

    CtLayout* create3BtnLayoutTop();

    CtLayout* create3BtnLayoutBottom();

    CtLayout* create3BtnNameLayoutTop();

    CtLayout* create3BtnNameLayoutBottom();

    virtual bool handleParamEvent(const CtEventParam& Param);

    bool handleButtonEvent(const CtEventButton& Button);

    virtual bool handleKeyEvent(const CtEventKey& Key);
    
    bool handleTouchEvent(const CtEventTouch& Touch);
private:
    
    void InitDisplay();

    CtWindow* createWindow();

    bool destroyWindow();

    int updateCh2In(int int_Data);

    int updateCh1In(int int_Data);

    int updateSelInput1(int int_Data);

    int updateSelInput2(int int_Data);

    void keyActionEvent();

    void keyCodeEvent(CtEventKey::KeyCode KeyCode,int i);

    bool isFocused();
    
    void focusedColorChange();/* 現在foucusと前回のfocus色の設定 */

    CtWindow* m_pWin;

    CtStackLabel* m_pLabelCh1In;

    CtStackLabel* m_pLabelCh2In;

    CtStackLabel* m_pLabelInput1;

    CtStackLabel* m_pLabelInput2;

    CtButton* m_pButtonExit;

    CtButton* m_pButtonCh1;
    
    CtButton* m_pButtonCh2;

    CtButton* m_pButtonSel1;

    CtButton* m_pButtonSel2;

    int m_bFocused;
    
    /* 「DIAL_ENTER」を押下して、「m_bFocusedCanMove」がFALSEの場合、「DIAL_UP/DIAL_DOWN」が応答できなくて、フォーカス遷移できません */
    bool m_bFocusedCanMove;
	
	/* m_bTouchButton = true 時、touch対象はbuttonである m_bTouchButton = false 時、 touch対応はbuttonではない  */
    bool m_bTouchButton;
    
    static CtColor ImagColor;

    static CtColor LabelColor;  

    static CtColor CommonBaseColor;

    static CtColor CommonSelectStrokeColor;
    
    static CtColor LineColor;

    CtVector::Vector<CtButton*> m_Vector;
};

#endif
