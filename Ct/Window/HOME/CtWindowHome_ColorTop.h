/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtWindowHome_ColorTop
 */

#ifndef __CtWindowHome_ColorTop_H__
#define __CtWindowHome_ColorTop_H__

#include "CtWindowCommon.h"

class CtWindowHome_ColorTop : public CtWindowMain
{
private:
    typedef enum ButtonId{
        ButtonIdMain,
        ButtonIdSub,
        ButtonIdExit,
        ButtonIdSdi,
        ButtonIdHdmi,
        ButtonIdLcd,
        /********** Žg—p‚µ‚È‚¢Ž– **************/
        ButtonIdMin = 0,
        ButtonIdMax = ButtonIdLcd
        /**************************************/
    }ButtonId;
public:
    CtWindowHome_ColorTop();
    ~CtWindowHome_ColorTop();
    CtLayout* createWindowTop();
    CtLayout* createWindowBottom();
    CtLayout* createWindowLayoutTop();
    CtLayout* createWindowLayoutBottom();
    bool handleButtonEvent(const CtEventButton& Button);
    bool handleKeyEvent(const CtEventKey& Key);
    bool handleParamEvent(const CtEventParam& Param);
    bool handleTouchEvent(const CtEventTouch& Touch);

private:
    CtWindow* createWindow();
    bool destroyWindow();
    void InitDisplay();
    void updateFocus();
    void dialFocus(bool bPlus,bool silent);
    void moveFocus(CtDirection Dir);
    int updateColorMain(int int_Data);
    int updateColorSub(int int_Data);
    int updateColorSdiOut(int int_Data);
    int updateColorHdmiOut(int int_Data);
    int updateColorLcdOut(int int_Data);
    bool checkMainColor();
    bool checkSdiRaw();
    bool checkSubRec();

    CtWindow *m_pWin;
    CtButton* m_pButtonSub;
    CtButton* m_pButtonSdi;
    CtButton* m_pButtonHdmi;
    CtButton* m_pButtonLcd;
    CtButton* m_pButtonMain;
    CtButton* m_pButtonExit;
    CtStackLabel* m_pLabelMainColor;
    CtStackLabel* m_pLabelSubColor;
    CtStackLabel* m_pLabelSdi;
    CtStackLabel* m_pLabelHdmi;
    CtStackLabel* m_pLabelLcd;
    CtVector::Vector<CtButton*> m_Vector;
    ButtonId m_FocusButton;
    bool m_PressButton;
    bool m_ManualFunction;

    static CtColor LabelColor;
    static CtColor ImagColor;
    static CtColor LineColor;

};


#endif
