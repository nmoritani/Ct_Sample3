/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtContainerTimeStamp
 */
#include "CtContainerTimeStamp.h"
#include "CtEvent.h"
#include "CtHLayout.h"
#include "CtWindow.h"
#include "CtTsInterface.h"

/* memo 
 AplParamDateFormatMode
   0: Y-M-D
   1: M-D-Y
   2: D-M-Y

 AplParamTimeStamp
  APL_SYS_PARAM_TIMESTAMP_OFF = 0,
  APL_SYS_PARAM_TIMESTAMP_DATE = 1,
  APL_SYS_PARAM_TIMESTAMP_TIME = 2,
  APL_SYS_PARAM_TIMESTAMP_DATETIME = 3,

*/

CtContainerTimeStamp::CtContainerTimeStamp(CtSize size, CtColorFormat colorFormat, int colorDepth) : 
	m_Size(size),
	m_ColorFormat(colorFormat),
	m_ColorDepth(colorDepth),
	m_Month(-1)
{
	memset(&m_Drawables, 0, sizeof(m_Drawables));
	memset(&m_DateDrawables, 0, sizeof(m_DateDrawables));
	memset(&m_Label, 0, sizeof(m_Label));

	m_Disp = getDispMode();
	m_Format = getFormat();
}

CtContainerTimeStamp::~CtContainerTimeStamp()
{
	CtDraw *pDraw = CtDraw::getInstance();
	GDI_HANDLER h;

	for (int i = 0; i < 3; i++) {
		h = m_Drawables.Month[i];
		pDraw->deleteDrawable(h);
	}

	for (int i = 0; i < 10; i++){
		h = m_Drawables.Dec[i];
		pDraw->deleteDrawable(h);
	}

	h = m_Drawables.Separator;
	pDraw->deleteDrawable(h);
}

CtLayout* CtContainerTimeStamp::createContainer()
{
	CtLayout *layout = createLayout();

	createDrawables();
	createDrawablesMonth();

#if 0 /* for test */
	int idx = 0;
	m_Label[idx++]->setDrawable(m_Drawables.Dec[2]);
	m_Label[idx++]->setDrawable(m_Drawables.Dec[0]);
	m_Label[idx++]->setDrawable(m_Drawables.Dec[1]);
	m_Label[idx++]->setDrawable(m_Drawables.Dec[8]);

	m_Label[idx++]->setDrawable(m_Drawables.Space);

	m_Label[idx++]->setDrawable(m_Drawables.Month[0]);
	m_Label[idx++]->setDrawable(m_Drawables.Month[1]);
	m_Label[idx++]->setDrawable(m_Drawables.Month[2]);

	m_Label[idx++]->setDrawable(m_Drawables.Space);

	m_Label[idx++]->setDrawable(m_Drawables.Dec[1]);
	m_Label[idx++]->setDrawable(m_Drawables.Dec[7]);

	m_Label[idx++]->setDrawable(m_Drawables.Space);

	m_Label[idx++]->setDrawable(m_Drawables.Dec[1]);
	m_Label[idx++]->setDrawable(m_Drawables.Dec[8]);
	m_Label[idx++]->setDrawable(m_Drawables.Separator);
	m_Label[idx++]->setDrawable(m_Drawables.Dec[3]);
	m_Label[idx++]->setDrawable(m_Drawables.Dec[9]);
	m_Label[idx++]->setDrawable(m_Drawables.Separator);
	m_Label[idx++]->setDrawable(m_Drawables.Dec[5]);
	m_Label[idx++]->setDrawable(m_Drawables.Dec[9]);
#endif

	return layout;
}

bool CtContainerTimeStamp::destroyContainer()
{
	return false;
}


bool CtContainerTimeStamp::startupWindow()
{
	return false;
}

bool CtContainerTimeStamp::updateFastDraw()
{
	SYS_DATE_TIME date = SYS_DateTime_GetValue();
	
	// 非表示の場合は何もしない
	if (m_Disp == CtTsDispOff) {
		// AplParamがOFFの場合、AVCからスタートが来ない？？？
		return false;
	}

	// 月名変化時は再構築
	if (m_Month != date.Month) {
		createDrawablesMonth();
	}

	// 日付からドロワブルIDへ変換
	DateTimeDrawabales dateDrawables = getDateTimeDrawables(date);

	int idx = 0;

#if 1
	// ラベルに対してドロワブルを設定
	if (m_Disp & CtTsDispDate) {
		// 日付
		if (m_Format == CtDateFormatYMD) {
			for (int i = 0; i < 4; i++) m_Label[idx++]->setDrawable(dateDrawables.Year[i]);
			m_Label[idx++]->setDrawable(m_Drawables.Space);
			for (int i = 0; i < 3; i++) m_Label[idx++]->setDrawable(dateDrawables.Month[i]);
			m_Label[idx++]->setDrawable(m_Drawables.Space);
			for (int i = 0; i < 2; i++) m_Label[idx++]->setDrawable(dateDrawables.Day[i]);
		}
		else if (m_Format == CtDateFormatMDY) {
			for (int i = 0; i < 3; i++) m_Label[idx++]->setDrawable(dateDrawables.Month[i]);
			m_Label[idx++]->setDrawable(m_Drawables.Space);
			for (int i = 0; i < 2; i++) m_Label[idx++]->setDrawable(dateDrawables.Day[i]);
			m_Label[idx++]->setDrawable(m_Drawables.Space);
			for (int i = 0; i < 4; i++) m_Label[idx++]->setDrawable(dateDrawables.Year[i]);
		}
		else if(m_Format == CtDateFormatDMY) {
			for (int i = 0; i < 2; i++) m_Label[idx++]->setDrawable(dateDrawables.Day[i]);
			m_Label[idx++]->setDrawable(m_Drawables.Space);
			for (int i = 0; i < 3; i++) m_Label[idx++]->setDrawable(dateDrawables.Month[i]);
			m_Label[idx++]->setDrawable(m_Drawables.Space);
			for (int i = 0; i < 4; i++) m_Label[idx++]->setDrawable(dateDrawables.Year[i]);
		}
	}

	if (m_Disp & CtTsDispTime) {
		// 日付,時刻間のスペース
		if (m_Disp & CtTsDispDate) m_Label[idx++]->setDrawable(m_Drawables.Space);
		// 時刻
		for (int i = 0; i < 2; i++) m_Label[idx++]->setDrawable(dateDrawables.Hour[i]);
		m_Label[idx++]->setDrawable(m_Drawables.Separator);
		for (int i = 0; i < 2; i++) m_Label[idx++]->setDrawable(dateDrawables.Min[i]);
		m_Label[idx++]->setDrawable(m_Drawables.Separator);
		for (int i = 0; i < 2; i++) m_Label[idx++]->setDrawable(dateDrawables.Sec[i]);
	}
#endif

	// 今回描画したドロワブルを保持
	m_DateDrawables = dateDrawables;

	return true;
}

/*
* 文字ラベルのサイズ決定
*/
CtSize CtContainerTimeStamp::getLabelSize()
{
	CtSize ret;

	// 高さ
	// 　全体の50%
	ret.height = (short)(0.5f * m_Size.height);

	// 幅
	// 全体の左右に0.5文字の空白を入れる
	int len = getTimeStampLength() + 1;	// 1は左右の0.5*2
	ret.width = m_Size.width / len;

	return ret;
}

CtContainerTimeStamp::CtDateFormat CtContainerTimeStamp::getFormat()
{
	// @todo aplparam対応
	return CtDateFormatYMD;
}

CtContainerTimeStamp::CtTsDisp CtContainerTimeStamp::getDispMode()
{
	// @todo aplparam対応
	return CtTsDispDateTime;
}

/*
 タイムスタンプとして描画する文字列長を取得
*/
int CtContainerTimeStamp::getTimeStampLength()
{
	const int DateLength = 4 + 1 + 3 + 1 + 2;
	const int TimeLength = 2 + 1 + 2 + 1 + 2;

	switch (getDispMode()) {
	case CtTsDispDate:
		return DateLength;
	case CtTsDispTime:
		return TimeLength;
	case CtTsDispDateTime:
		return DateLength + 1 + TimeLength;
	default:
		break;
	}
	return 0;
}

/*
 createContainer向けLayout作成処理
*/
CtLayout* CtContainerTimeStamp::createLayout()
{
	CtHLayout *pLayout = new CtHLayout(m_Size, CtColor::Blue);
	CtSize labelSize = getLabelSize();
	int labelCount = getTimeStampLength();

	// layout左端へ0.5文字分のスペース追加
	pLayout->addSpacing(CtSize(labelSize.width / 2, labelSize.height));

	for (int i = 0; i < labelCount; i++) {
		m_Label[i] = new CtLabel(labelSize);
#if 1
		m_Label[i]->setFastDraw(true);
#endif
		pLayout->addWidget(m_Label[i], 0);
	}
#if 1
	pLayout->setFastDraw(true);
#endif
	return pLayout;
}

/*
 createContainer向けドロワブル作成処理(数値と記号)
*/
void CtContainerTimeStamp::createDrawables()
{
	CtSize drawableSize = getLabelSize();
	CtTsInterface *pIf = CtTsInterface::getInstance();

	for (int i = 0; i < 10; i++) {
		m_Drawables.Dec[i] = pIf->createDrawable('0' + i, drawableSize, CtColor::Black, CtColor::White);
	}

	m_Drawables.Separator = pIf->createDrawable(':', drawableSize, CtColor::Black, CtColor::White);
	m_Drawables.Space = pIf->createDrawable(' ', drawableSize, CtColor::Black, CtColor::White);
}

/*
 ドロワブル作成処理(月名のアルファベット)
*/
void CtContainerTimeStamp::createDrawablesMonth()
{
	static const char* monthStr[] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JLY", "AUG", "SEP", "OCT", "NOV", "DEC" };
	SYS_DATE_TIME date = SYS_DateTime_GetValue();
	CtSize drawableSize = getLabelSize();
	CtTsInterface *pIf = CtTsInterface::getInstance();

	m_Month = date.Month;

	for (int i = 0; i < 3; i++) {
		if (m_Drawables.Month[i] != GDI_INVALID_ID) {
			CtDraw::getInstance()->deleteDrawable(m_Drawables.Month[i]);
		}

		m_Drawables.Month[i] = pIf->createDrawable(monthStr[m_Month - 1][i], drawableSize, CtColor::Black, CtColor::White);
	}
}

/*
  現在時刻からDateTimeDrawabales(描画するドロワブル)への変換
*/
CtContainerTimeStamp::DateTimeDrawabales CtContainerTimeStamp::getDateTimeDrawables(const SYS_DATE_TIME &date)
{
	CtContainerTimeStamp::DateTimeDrawabales ret;

	// 現在の日付,時刻から描画するドロワブルIDを選択
	ret.Year[0] = m_Drawables.Dec[date.Year / 1000];
	ret.Year[1] = m_Drawables.Dec[date.Year % 1000 / 100];
	ret.Year[2] = m_Drawables.Dec[date.Year % 100 / 10];
	ret.Year[3] = m_Drawables.Dec[date.Year % 10];

	ret.Month[0] = m_Drawables.Month[0];
	ret.Month[1] = m_Drawables.Month[1];
	ret.Month[2] = m_Drawables.Month[2];

	ret.Day[0] = m_Drawables.Dec[date.Day / 10];
	ret.Day[1] = m_Drawables.Dec[date.Day % 10];

	ret.Hour[0] = m_Drawables.Dec[date.Hour / 10];
	ret.Hour[1] = m_Drawables.Dec[date.Hour % 10];

	ret.Min[0] = m_Drawables.Dec[date.Min / 10];
	ret.Min[1] = m_Drawables.Dec[date.Min % 10];

	ret.Sec[0] = m_Drawables.Dec[date.Sec / 10];
	ret.Sec[1] = m_Drawables.Dec[date.Sec % 10];

	return ret;
}
