
#include "CtContainerLevelBar.h"


CtContainerLevelBar::CtContainerLevelBar(int param, int max, int min):
	m_Param(param),
	m_Max(max),
	m_Min(min),
	m_Type(LevelBarType_Default)
{
}
CtContainerLevelBar::~CtContainerLevelBar()
{
	destroyContainer();
}
bool CtContainerLevelBar::destroyContainer() {
	return true;
}

CtLayout* CtContainerLevelBar::createContainer(){

    memset(m_pLevelBar, 0, sizeof(m_pLevelBar));
	CtVLayout* pLayout = new CtVLayout;

	int BarReduce = getBarReduce();

	for (int i = 0; i < (LEVEL_MAX - BarReduce); i++) {
		if (i == (LEVEL_MAX - BarReduce) / 2 ) {
			m_pLevelBar[i] = new CtLabel(CtSize(62, 10), CtRoundRect(5, 5, CtColor::Gray, 1, CtColor(ColorRGBA, 0x606060ff, NULL)));
		}
		else {
			m_pLevelBar[i] = new CtLabel(CtSize(44, 10), CtRoundRect(5, 5, CtColor::Gray, 1, CtColor(ColorRGBA, 0x606060ff, NULL)));
		}
		pLayout->addWidget(m_pLevelBar[i], AlignCenter);
	}
	pLayout->setElementsMargin(CtMargin(6, 6, 0, 0));


	int step = (m_Max - m_Min) / ((LEVEL_MAX - BarReduce) - 1);
	int count = (m_Max - m_Min) % ((LEVEL_MAX - BarReduce) - 1);
	int Center = (m_Max + m_Min) / 2;

	m_pLevelVal[(LEVEL_MAX - BarReduce) / 2] = Center;
	for (int i = 1; i <= (LEVEL_MAX - BarReduce) / 2; i++) {
		if (count > 0) {
			m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + i] = m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + i - 1] + (step*(-1)) - 1;
			m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + (i*(-1))] = m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + (i*(-1)) + 1] + step + 1;
			count = count - 2;
		}
		else {
			m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + i] = m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + i - 1] + (step*(-1));
			m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + (i*(-1))] = m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + (i*(-1)) + 1] + step;
		}
	}

	executionUpdateViewLebelBar();


	return pLayout;
}



void CtContainerLevelBar::executionUpdateViewLebelBar()
{
	int BarReduce = getBarReduce();

	for (int i = 0; i < (LEVEL_MAX - BarReduce); i++) {
		if (m_pLevelBar[i] == NULL) return;
	}

	int value = getValue(m_Param);
	int index = 0;

	if (value == m_pLevelVal[(LEVEL_MAX - BarReduce) / 2]) {
		index = (LEVEL_MAX - BarReduce) / 2;
	}
	else if (value > m_pLevelVal[(LEVEL_MAX - BarReduce) / 2]) {
		for (int i = 1; i <= (LEVEL_MAX - BarReduce) / 2; i++) {
			if (m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + (i*-1)] >= value) {
				index = (LEVEL_MAX - BarReduce) / 2 + (i*-1);
				break;
			}
		}
	}
	else if (value < m_pLevelVal[(LEVEL_MAX - BarReduce) / 2]) {
		for (int i = 1; i <= (LEVEL_MAX - BarReduce) / 2; i++) {
			if (m_pLevelVal[(LEVEL_MAX - BarReduce) / 2 + i] <= value) {
				index = (LEVEL_MAX - BarReduce) / 2 + i;
				break;
			}
		}
	}

	for (int i = 0; i < (LEVEL_MAX - BarReduce); i++) {
		if (i == index) {
			if (m_pLevelBar[i] != NULL) m_pLevelBar[i]->setColor(CtColor::Green);
		}
		else {
			if (m_pLevelBar[i] != NULL) m_pLevelBar[i]->setColor(CtColor::Gray);
		}
	}
}


bool CtContainerLevelBar::handleParamEvent(const CtEventParam& Param)
{
	int t_Id = Param.getParamId();

	if (m_Param == t_Id) {
		executionUpdateViewLebelBar();
		return true;
	}
	return false;
}

int CtContainerLevelBar::getValue(int ParamID)
{
	int value = APL_PARAM_GET_DATA(ParamID);
	AplParamService::AplParamMainItem* pMainItem = APL_PARAM()->getParamState(ParamID);
	int size = 0;

	if (pMainItem != NULL) {
		size = pMainItem->size;
	}
	int mask = (1 << (size * 8 - 1));

	// Value 更新の場合はマイナス値が保存されているのでマイナス値に変換
	if (size != 4) {
		if (value & mask) {
			for (int i = 4; i > size; i--) {
				value = value | (0xFF << ((8 * (i - 1))));
			}
		}
	}
	return value;
}

int CtContainerLevelBar::getBarReduce()
{
	switch (m_Type) {

	case LevelBarType_Short:
		return 2;
	case LevelBarType_Default:
	default:
		return 0;
	}
}
