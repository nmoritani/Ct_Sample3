/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtListContainer
 */
#include "CtContainerSpinBoxSpecial.h"
//#include <stdlib.h>

CtContainerSpinBoxSpecial::CtContainerSpinBoxSpecial(CtWindowID id) : CtContainerSpinBox(id),
	m_pStack(NULL)
{
	setClassType(CtClassType_LayoutMain);
}
CtContainerSpinBoxSpecial::~CtContainerSpinBoxSpecial()
{
	destroyContainer();
}

//----------------------------------------------------------------------------------------------------
// Builder
//----------------------------------------------------------------------------------------------------

CtLayout* CtContainerSpinBoxSpecial::createLabel()
{
	CtMenuInfoSpinBox spinboxInfo;

	CtFontSet fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	m_pParamBox = new CtParamBox(m_Info->ParamId);
	m_pParamBox->setFontSet(fSet);


	m_pParamBox->setLabelType(CtParamLabel::TypeNumeric);
	m_pParamBox->setRange(m_Info->disp.min, m_Info->disp.max);
	m_pParamBox->setStep(m_Info->disp.step);
	m_pParamBox->setForm(m_Info->disp.str);
	m_pParamBox->setCorrection(0, m_Info->disp.coef);


	m_pStack = new CtStackLabel();
	m_pStack->addLabel(m_pParamBox, 0);
	m_pStack->addLabel(new CtLabel(STR_ID_NO_10009, fSet), 1);

	signed char value = APL_PARAM_GET_DATA(AplParamSceneChromaLevel);
	if (value == -100) {
		m_pStack->index(1);
	}
	else {
		m_pStack->index(0);
	}

	/* Layout */
	CtLayout *pLayout = createLabelLayout();
	pLayout->addWidget(m_pStack, CtMargin(5, 5), AlignCenter);

	return pLayout;

}

//----------------------------------------------------------------------------------------------------
// HandleEvent
//----------------------------------------------------------------------------------------------------
bool CtContainerSpinBoxSpecial::handleParamEvent(const CtEventParam& Param)
{
	return false;
}

//----------------------------------------------------------------------------------------------------
// Execution
//----------------------------------------------------------------------------------------------------
bool CtContainerSpinBoxSpecial::executionUp()
{
	bool bRet = CtContainerSpinBox::executionUp();
	
	if (m_Info->ParamId == AplParamSceneChromaLevel) {
		int value = m_pParamBox->getParam();
		if (value == -100) {
			m_pStack->index(1);
		}
		else {
			m_pStack->index(0);
		}
	}
	
	return bRet;
}

bool CtContainerSpinBoxSpecial::executionDown()
{
	bool bRet = CtContainerSpinBox::executionDown();

	if (m_Info->ParamId == AplParamSceneChromaLevel) {
		int value = m_pParamBox->getParam();
		if (value == -100) {
			m_pStack->index(1);
		}
		else {
			m_pStack->index(0);
		}
	}

	return bRet;
}