
#include "CtContainerCtrlButton.h"
#include "CtWindowDecorate.h"

void CtContainerCtrlButton::ctor()
{
	memset(&m_Info, 0, sizeof(m_Info));
	for (int i = 0; i < Button_Max; i++) {
		m_Info[i].Valid = false;
		m_Info[i].pButton = NULL;
	}
	int value = APL_PARAM_GET_DATA(AplParamDeckMode);

	if (CtWindowDecorate::isThumbnail()) {
		InvalidBaseColor = CtColor(0, 0, 0, 255);
		InvalidStrokeColor = CtColor(54, 54, 54, 255);
		InvalidLabelColor = CtColor(86, 86, 86, 255);
	}
	else {
		InvalidBaseColor = CtColor(0, 0, 0, (unsigned char)(255 * 0.4));
		InvalidStrokeColor = CtColor(134, 134, 134, (unsigned char)(255 * 0.4));
		InvalidLabelColor = CtColor(212, 212, 212, (unsigned char)(255 * 0.4));
		m_bTrans = false;
	}
}

CtContainerCtrlButton::CtContainerCtrlButton(bool bSet, bool bUp, bool bDown, bool bRet) :
	m_bFocusable(false),
	m_bTrans(true)
{
	ctor();
	m_Info[Button_Set].Valid = bSet;
	m_Info[Button_Up].Valid = bUp;
	m_Info[Button_Down].Valid = bDown;
	m_Info[Button_Ret].Valid = bRet;
}

CtContainerCtrlButton::~CtContainerCtrlButton()
{
}

bool CtContainerCtrlButton::destroyContainer() {
	return true;
}

CtLayout* CtContainerCtrlButton::createContainer(){

	/* V Layout 640 */
	CtVLayout* pV = new CtVLayout();
	pV->addStretch(80);
	pV->addStretch(16);
	if (m_Info[Button_Set].Valid) {
		pV->addWidget(createButton(Button_Set), 78);
	}
	else {
		pV->addStretch(78);
	}
	pV->addStretch(65);
	if (m_Info[Button_Up].Valid) {
		pV->addWidget(createButton(Button_Up), 78);
	}
	else {
		pV->addStretch(78);
	}
	pV->addStretch(86);
	if (m_Info[Button_Down].Valid) {
		pV->addWidget(createButton(Button_Down), 78);
	}
	else {
		pV->addStretch(78);
	}
	pV->addStretch(65);
	if (m_Info[Button_Ret].Valid) {
		pV->addWidget(createButton(Button_Ret), 78);
		m_Info[Button_Ret].pButton->setFocus(false);
	}
	else {
		pV->addStretch(78);
	}
	pV->addStretch(16);

	CtLayout* pLayout = new CtLayout();
	if (CtWindowDecorate::isThumbnail()) {
		CtVLayout* pBack = new CtVLayout();
		pBack->addStretch(219);
		pBack->addWidget(new CtLabel(CtColor::Black), 282);
		pBack->addStretch(139);
		pLayout->addWidget(pBack);
	}
	pLayout->addWidget(pV);

	/* H Layout 960 */
	CtHLayout* pH = new CtHLayout();
	pH->addStretch(14);
	pH->addWidget(pLayout, 78);
	pH->addStretch(960 - 14 - 78);

	return pH;
}

CtButton* CtContainerCtrlButton::createButton(ButtonID id)
{
	if (idErrCheck(id)) return NULL;
	m_Info[id].pButton = new CtButton(CtSize(78, 78), getImage(id));
	m_Info[id].pButton->setWidgetID(WidgetID_OFFSET + id);
	m_Info[id].pButton->setFocusable(m_bFocusable);
	m_Info[id].pButton->setTrans(m_bTrans);
	m_Info[id].pButton->setInvalidButtonColors(InvalidBaseColor, InvalidStrokeColor, InvalidLabelColor);
	return m_Info[id].pButton;
}

GDI_IMAGE_ID CtContainerCtrlButton::getImage(ButtonID id)
{
	switch (id){
	case Button_Set:
		return IC_MENU_SET;
	case Button_Up:
		return IC_MENU_UP;
	case Button_Down:
		return IC_MENU_DOWN;
	case Button_Ret:
		return IC_MENU_RETURN;
	default:
		break;
	}
	return IMAGE_ID_MAX;
}

bool CtContainerCtrlButton::idErrCheck(ButtonID id)
{
	if (0 > id || id >= Button_Max) {
		return true;
	}
	return false;
}

void CtContainerCtrlButton::setFocusable(bool bFocusable)
{
	m_bFocusable = bFocusable;
}
void CtContainerCtrlButton::setTrans(bool bTrans)
{
	m_bTrans = bTrans;
}
void CtContainerCtrlButton::setTransColor(bool bTrans)
{
	if (bTrans)
	{
		InvalidBaseColor = CtColor(0, 0, 0, (unsigned char)(255 * 0.4));
		InvalidStrokeColor = CtColor(134, 134, 134, (unsigned char)(255 * 0.4));
		InvalidLabelColor = CtColor(212, 212, 212, (unsigned char)(255 * 0.4));
	}
	else
	{
		InvalidBaseColor = CtColor(0, 0, 0, 255);
		InvalidStrokeColor = CtColor(54, 54, 54, 255);
		InvalidLabelColor = CtColor(86, 86, 86, 255);
	}
}

bool CtContainerCtrlButton::setInvalid(int widgetID, bool bInvalid)
{
	int id = widgetID - WidgetID_OFFSET;

	if (idErrCheck((ButtonID)id)) return false;

	if (m_Info[id].pButton != NULL) {
		return m_Info[id].pButton->setInvalid(bInvalid);
	}

	return false;
}
