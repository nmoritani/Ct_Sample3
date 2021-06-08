#include "CtFastContainerTimeCode.h"
#include "CtHLayout.h"
#include "AplParamService.h"

#ifdef WIN32_GUI_SIM
static unsigned long m_simTime = 0;
#endif

CtFastContainerTimeCode::CtFastContainerTimeCode(bool bUserSuffix, CtWindowCommonType Type) :
	m_Type(Type),
	m_bUseSuffix(bUserSuffix),
	m_pLayoutAll(NULL),
	m_Mode(APL_PARAM_GET_DATA(AplParamCounterMode)),
	m_WindowID(Window_PlayView)
{
	memset(m_pLabel, 0, sizeof(m_pLabel));
}

CtFastContainerTimeCode::~CtFastContainerTimeCode() {
}

CtLayout* CtFastContainerTimeCode::createContainer() {

	CtColor fill_Color = (m_Type == CT_COMMON_TYPE_HOME) ? CtColor::Black : CtColor::Trans;
	CtLayout *pLayout = new CtLayout(fill_Color);

	m_pLayoutAll = new CtHLayout(fill_Color);
	pLayout->addWidget(m_pLayoutAll);

	if (m_bUseSuffix) {
		m_pSuffLayout = new CtLayout();
		// LCD Suffix
		m_pSuffixLcd = createSuffix();
		//m_pSuffixLcd->setScreenSel(ScreenLCD);
		m_pSuffLayout->addWidget(m_pSuffixLcd);

		//// LOUT Suffix
		//m_pSuffixLout = createSuffix(false);
		//m_pSuffixLout->setScreenSel(ScreenLOUT);
		//m_pSuffLayout->addWidget(m_pSuffixLout);

		m_pLayoutAll->addWidget(m_pSuffLayout, 4);
	}
	else {
		m_pLayoutAll->addStretch(4);
	}
	// CounterVal + Separator
	for (int i = 0; i < DigitNum; i++) {
		m_pLabel[i] = createCounter(isSeparator(i));
		m_pLayoutAll->addWidget(m_pLabel[i], 1);
		m_pLabel[i]->index(17);
	}
	
	return pLayout;
}

CtStackLabel* CtFastContainerTimeCode::createSuffix()
{
	const char* SuffixStrings[8] = { "TCR ", "TCG ", "UBR ", "UBG ", "CLIP", "    ", "TCG", NULL };// 6番目のTCGはSlave状態用Drawable作成用
	CtRecViewFontSet fSet = CtRecViewFontSet();
	const char* str = SuffixStrings[0];
	int index = 0;

	CtStackLabel *stkLabel = new CtStackLabel();
	while (str) {
		if (index == 6) {
			CtHLayout* pSuffixLcd = new CtHLayout();
			CtLayout* pSuffixLcdBg = new CtLayout(CtColor::White);
			
			CtRecViewFontSet tempfSet = fSet;
			tempfSet.setColor(CtColor::Black);
			tempfSet.edgeColor = CtColor::NoColor;
			pSuffixLcdBg->addWidget(new CtLabel(str, tempfSet));
			pSuffixLcdBg->setColor(CtColor::White);
			pSuffixLcd->addWidget(pSuffixLcdBg, 3);
			pSuffixLcd->addWidget(new CtLabel(""),1);
			stkLabel->addLabel(pSuffixLcd);
			str = SuffixStrings[++index];
		}
		else {
			stkLabel->addLabel(str, fSet);
			str = SuffixStrings[++index];
		}
		stkLabel->setFastDraw(true);
	}

	return stkLabel;
}

CtFontSet CtFastContainerTimeCode::getFontSet()
{
	CtFontSet fSet;

	if (m_Type == CT_COMMON_TYPE_HOME) {
		fSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	}
	else {
		fSet = CtRecViewFontSet();
	}

	return fSet;
}

CtStackLabel* CtFastContainerTimeCode::createCounter(bool _isSeparator)
{
	const char* CounterChars = "0123456789ABCDEF- ";
	const char* SeparatorChars = ":. ";

	const CtFontSet fSet = getFontSet();
	CtStackLabel* label = new CtStackLabel();

	if (!label) return NULL;
	label->setFastDraw(true);
	const char* chars = _isSeparator ? SeparatorChars : CounterChars;

	label->addLabels(chars, fSet);

	return label;
}

bool CtFastContainerTimeCode::startupContainer() {
	updateCounterMode();
	updateSuffix();
	return true;
}

bool CtFastContainerTimeCode::updateFastDraw()
{
	bool shiftlabel = false;

	char ValueLcd[DigitNum + 1];	// 数字
	char ValueSdi[DigitNum + 1];	// 数字

	memset(ValueLcd, 0, sizeof(ValueLcd));
	memset(ValueSdi, 0, sizeof(ValueSdi));

	int RecCounter = APL_PARAM_GET_DATA(AplParamRecCounter);

	switch (m_Mode)
	{
	case APL_SYS_PARAM_COUNTER_MODE_TC: // TC
		if (APL_PARAM_GET_DATA(AplParamTcInSlave) == APL_SYS_PARAM_SWITCH_ON) {
			m_bSlaveState = true;
			updateSuffix();
		}
		else {
			m_bSlaveState = false; 
			updateSuffix();
		}
		buildString((m_Type == CT_COMMON_TYPE_PLAY) ? AplParamTcPlayValueLcd : AplParamTcValueLcd, ValueLcd);
		buildString((m_Type == CT_COMMON_TYPE_PLAY) ? AplParamTcPlayValueSdi : AplParamTcValueSdi, ValueSdi);
		shiftlabel = true;
		break;
	case APL_SYS_PARAM_COUNTER_MODE_UB: // UB
		buildString((m_Type == CT_COMMON_TYPE_PLAY) ? AplParamUbPlayValueLcd : AplParamUbValueLcd, ValueLcd);
		buildString((m_Type == CT_COMMON_TYPE_PLAY) ? AplParamUbPlayValueSdi : AplParamUbValueSdi, ValueSdi);
		shiftlabel = true;
		break;
	case APL_SYS_PARAM_COUNTER_MODE_TIME: // CLIP/カウンター
		if (RecCounter == APL_SYS_PARAM_REC_COUNTER_CLIP || m_Type == CT_COMMON_TYPE_PLAY) {
			buildString((m_Type == CT_COMMON_TYPE_PLAY) ? AplParamRecCounterClipPlayValue : AplParamRecCounterClipValue, ValueLcd);
			buildString((m_Type == CT_COMMON_TYPE_PLAY) ? AplParamRecCounterClipPlayValue : AplParamRecCounterClipValue, ValueSdi);
		}
		else {
			buildString(AplParamRecCounterTotalValue, ValueLcd);
			buildString(AplParamRecCounterTotalValue, ValueSdi);
		}
		break;
	default:
		break;
	}

	char* NumStrs[] = { ValueLcd , ValueSdi };

	/* Counter + Separator */
	const char* CounterChars = "0123456789ABCDEF- ";
	const char* SeparatorChars = ":. ";

	for (int i = 0; i < DigitNum; i++) {
		char c = NumStrs[0][i];
		int idx = getCharIndex(c, isSeparator(i) ? SeparatorChars : CounterChars);
		if (idx >= 0) m_pLabel[i]->index(idx);
	}
	return true;
}

int CtFastContainerTimeCode::getModeStr(int counter_mode)
{
	switch (counter_mode)
	{
	case APL_SYS_PARAM_COUNTER_MODE_TC:
		m_pSuffLayout->setVisible(true);
		if (m_Type == CT_COMMON_TYPE_PLAY) {
			return 0;
		}
		else {
			if (m_bSlaveState == true) {
				return 6;
			}
			else {
				return 1;
			}
		}
		break;
	case APL_SYS_PARAM_COUNTER_MODE_UB:
		m_pSuffLayout->setVisible(true);
		if (m_Type == CT_COMMON_TYPE_PLAY) {
			return 2;
		}
		else {
			return 3;
		}
		break;
	case APL_SYS_PARAM_COUNTER_MODE_TIME:
		if (m_Type == CT_COMMON_TYPE_PLAY || APL_PARAM_GET_DATA(AplParamRecCounter) == APL_SYS_PARAM_REC_COUNTER_CLIP) {
			m_pSuffLayout->setVisible(true);
			// CLIP
			return 4;
		}
		else {
			m_pSuffLayout->setVisible(false);
			// カウンターのみ
			return 5;
		}
		break;
	default:
		m_pSuffLayout->setVisible(false);
		// 非表示
		return 5;
	}
}

int CtFastContainerTimeCode::getCharIndex(char c, const char* str)
{
	if (str == NULL) return -1;
	const char *p = str;
	while (*p) {
		if (*p == c) return p - str;
		p++;
	}
	return -1;
}

bool CtFastContainerTimeCode::isSeparator(int idx)
{
	switch (idx) {
	case 2:
	case 5:
	case 8:
		return true;
	default:
		return false;
	}
}

void CtFastContainerTimeCode::setWindowID(CtWindowID winId) {
	m_WindowID = winId;
}

bool CtFastContainerTimeCode::destroyContainer() {
	return true;
}

void CtFastContainerTimeCode::buildString(int t_Id, char *Str) {

	unsigned char Data[5];
	memset(Data, 0, sizeof(Data));

	unsigned char Valid = 0;
	unsigned char Value1 = 0, Value2 = 0, Value3 = 0, Value4 = 0;

	/* データの取得 */
#ifdef WIN32_GUI_SIM
	int hfr = 60 * 60 * 30, mfr = 60 * 30, sfr = 30;
	int h = 0, m = 0, s = 0, f = 0;
	int total = 0;
	m_simTime++;

	total = m_simTime / 4;
	Data[0] = 1;

	h = total / hfr;
	Data[1] = (unsigned char)(h % 100);

	m = (total - (h * hfr)) / mfr;
	Data[2] = (unsigned char)m;

	s = (total - (h * hfr) - (m * mfr)) / sfr;
	Data[3] = (unsigned char)s;

	f = (total - (h * hfr) - (m * mfr) - (s * sfr));
	Data[4] = (unsigned char)f;
#else
	APL_PARAM_GET_DATA_AREA(t_Id, Data, 5);
#endif
	Valid = Data[0];
	Value1 = Data[1] ;
	Value2 = Data[2] ;
	Value3 = Data[3] ;
	Value4 = Data[4] ;

	//int RecCounter = APL_PARAM_GET_DATA(AplParamRecCounter);

	switch (t_Id) {
	case AplParamTcValueLcd:
	case AplParamTcValueSdi:
	case AplParamDurationValueLcd:
	case AplParamDurationValueSdi:
		if (APL_PARAM_GET_DATA(AplParamDfMode) == APL_SYS_PARAM_SWITCH_ON) {
			if (Valid == 0) { // 無効値の場合--表示
				sprintf(Str, "--:--:--.--");	/* pgr0541 */
			}
			else {
				sprintf(Str, "%02d:%02d:%02d.%02d", (int)Value1 % 99, (int)Value2 % 99, (int)Value3 % 99, (int)Value4 % 99);	/* pgr0541 */
			}
		}
		else {
			if (Valid == 0) { // 無効値の場合--表示
				sprintf(Str, "--:--:--:--");	/* pgr0541 */
			}
			else {
				sprintf(Str, "%02d:%02d:%02d:%02d", (int)Value1 % 99, (int)Value2 % 99, (int)Value3 % 99, (int)Value4 % 99);	/* pgr0541 */
			}
		}
		break;
	case AplParamUbValueLcd:
	case AplParamUbValueSdi:
		if (Valid == 0) { // 無効値の場合--表示
			sprintf(Str, "-- -- -- --");	/* pgr0541 */
		}
		else {
			sprintf(Str, "%02X %02X %02X %02X", (int)Value1, (int)Value2, (int)Value3, (int)Value4);	/* pgr0541 */
		}
		break;
	case AplParamTcPlayValueLcd:
	case AplParamTcPlayValueSdi:
	case AplParamDurationPlayValueLcd:
	case AplParamDurationPlayValueSdi:
		if (APL_PARAM_GET_DATA(AplParamDfModePlay) == APL_SYS_PARAM_SWITCH_ON) {
			if (Valid == 0) { // 無効値の場合--表示
				sprintf(Str, "--:--:--.--");	/* pgr0541 */
			}
			else {
				sprintf(Str, "%02d:%02d:%02d.%02d", (int)Value1 % 99, (int)Value2 % 99, (int)Value3 % 99, (int)Value4 % 99);	/* pgr0541 */

			}
		}
		else {
			if (Valid == 0) { // 無効値の場合--表示
				sprintf(Str, "--:--:--:--");	/* pgr0541 */
			}
			else {
				sprintf(Str, "%02d:%02d:%02d:%02d", (int)Value1 % 99, (int)Value2 % 99, (int)Value3 % 99, (int)Value4 % 99);	/* pgr0541 */
			}
		}
		break;
	case AplParamUbPlayValueLcd:
	case AplParamUbPlayValueSdi:
		if (Valid == 0) { // 無効値の場合--表示
			sprintf(Str, "-- -- -- --");	/* pgr0541 */
		}
		else {
			sprintf(Str, "%02X %02X %02X %02X", (int)Value1, (int)Value2, (int)Value3, (int)Value4);	/* pgr0541 */
		}
		break;
	case AplParamRecCounterTotalValue:
	case AplParamRecCounterClipValue:
	case AplParamRecCounterClipPlayValue:
			if (APL_PARAM_GET_DATA(AplParamDfModePlay) == APL_SYS_PARAM_SWITCH_ON) {
				if (Valid == 0) { // 無効値の場合--表示
					sprintf(Str, " -:--:--.--");	/* pgr0541 */
				}
				else {
					sprintf(Str, "%2d:%02d:%02d.%02d", (int)Value1 % 99, (int)Value2 % 99, (int)Value3 % 99, (int)Value4 % 99);	/* pgr0541 */
				}
			}
			else {
				if (Valid == 0) { // 無効値の場合--表示
					sprintf(Str, " -:--:--:--");	/* pgr0541 */
				}
				else {
					sprintf(Str, "%2d:%02d:%02d:%02d", (int)Value1 % 99, (int)Value2 % 99, (int)Value3 % 99, (int)Value4 % 99);	/* pgr0541 */
				}
			}

		break;
	default:
		break;
	}
	return;
}

bool CtFastContainerTimeCode::setStatusMode(bool bStatusMode) {
	if (m_bStatusMode != bStatusMode) {
		m_bStatusMode = bStatusMode;
	}

	if (bStatusMode) {
		setVisible(true);
		if (m_Mode == APL_SYS_PARAM_COUNTER_MODE_OFF) m_Mode = APL_SYS_PARAM_COUNTER_MODE_TC;
	}
	else {
		return updateCounterMode();
	}
	return false;
}

bool CtFastContainerTimeCode::handleParamEvent(const CtEventParam& Param) {
	int t_Id = Param.getParamId();
	int int_Data = Param.getParamVal();
	switch (t_Id) {
	case AplParamCounterMode:
		return updateCounterMode(int_Data);
		break;
	//case AplParamTcInSlave:
		//m_bSlaveState = (int_Data == APL_SYS_PARAM_SWITCH_ON);
		//return updateSuffix();
		//break;
	case AplParamRecCounter:
		updateCounterMode(APL_PARAM_GET_DATA(AplParamCounterMode));
		return updateSuffix();
		break;
	default:
		break;
	}
	return false;
}

bool CtFastContainerTimeCode::updateCounterMode(int int_Data) {
	if (int_Data == -1) int_Data = APL_PARAM_GET_DATA(AplParamCounterMode);

	// 非表示ModeかつStatus表示はTCを表示する
	if (m_bStatusMode == true && int_Data == APL_SYS_PARAM_COUNTER_MODE_OFF) {
		int_Data = APL_SYS_PARAM_COUNTER_MODE_TC;
	}


	switch (int_Data) {
	case APL_SYS_PARAM_COUNTER_MODE_OFF:
		m_Mode = int_Data;
		m_pSuffLayout->setVisible(false);
		return setVisible(false);
		break;
	case APL_SYS_PARAM_COUNTER_MODE_TIME:
	case APL_SYS_PARAM_COUNTER_MODE_UB:
	case APL_SYS_PARAM_COUNTER_MODE_TC:
		m_Mode = int_Data;
		if( m_WindowID == Window_PlayView_RecCheck 
		 && APL_PARAM_GET_DATA(AplParamRecCounter) == APL_SYS_PARAM_REC_COUNTER_TOTAL
		 && m_Mode == APL_SYS_PARAM_COUNTER_MODE_TIME) 
		{
			setVisible(false);
			m_pSuffLayout->setVisible(false);
		}
		else {
			setVisible(true);
			updateSuffix();
		}
		return true;
		break;
	}
	return false;
}
bool CtFastContainerTimeCode::updateSuffix() {
	/* Suffix切替 */
	if (m_bUseSuffix) {
		m_pSuffixLcd->index(getModeStr(m_Mode));
		//m_pSuffixLout->index(getModeStr(m_Mode));
	}
	return true;
}
