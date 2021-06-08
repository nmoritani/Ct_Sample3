/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element: CtTimeStamp
 */
#include "CtTimeStamp.h"
#include "gdi_local.h"
#include "TclIf.h"

#define TIME_DEFAULT		(0xff)
#define TC_DELAY			(1)

//#define DEBUG_TIMESTAMP	(1)

#ifdef DEBUG_TIMESTAMP
 #define TsDebugPrint(...) CtDebugPrint(CtDbg,__VA_ARGS__)
#else
 #define TsDebugPrint(x)
#endif

CtTimeStamp::CtTimeStamp(CtSize size, CtColorFormat colorFormat, int colorDepth, CtTsDisp dispMode) :
	m_Size(size),
	m_ColorFormat(colorFormat),
	m_ColorDepth(colorDepth),
	m_DispMode(dispMode),
	m_Current(-1),
	m_State(StateInit)
{
	// 前景色と背景色
	BgColor = CtColor::Black;
	FgColor = CtColor::White;

	m_CharSize = getCharSize();
	m_DateFormat = getDateFormat();

	memset(&m_Drawables, 0, sizeof(m_Drawables));
	memset(&m_DateDrawables, 0, sizeof(m_DateDrawables));
	memset(&m_Base, 0, sizeof(m_Base));
	memset(&m_BaseLow, 0, sizeof(m_BaseLow));
	memset(&m_Time, TIME_DEFAULT, sizeof(m_Time));
	memset(&m_CurTime, TIME_DEFAULT, sizeof(m_CurTime));

	for (int i = 0; i < BASE_COUNT; i++) {
		m_bReformat[i] = false;
	}
}

CtTimeStamp::~CtTimeStamp()
{
	CtDraw *pDraw = CtDraw::getInstance();
	GDI_HANDLER h;

	for (int i = 0; i < 3; i++) {
		if ((h = m_Drawables.Month[i]) != GDI_INVALID_ID)
			pDraw->deleteDrawable(h);
	}

	for (int i = 0; i < 10; i++) {
		if ((h = m_Drawables.Dec[i]) != GDI_INVALID_ID)
			pDraw->deleteDrawable(h);
	}

	for (int i = 0; i < BASE_COUNT; i++) {
		if ((h = m_Base[i]) != GDI_INVALID_ID)
			pDraw->deleteDrawable(h);
	}

	if ((h = m_BaseLow) != GDI_INVALID_ID)
		pDraw->deleteDrawable(h);
	
	if ((h = m_Drawables.Separator) != GDI_INVALID_ID)
		pDraw->deleteDrawable(h);
	
	if ((h = m_Drawables.Space) != GDI_INVALID_ID)
		pDraw->deleteDrawable(h);
}

bool CtTimeStamp::create()
{
	// 現在時ケ・チイ・	SYS_DATE_TIME date1, date2;
	if (TCL_GetDateTimeDelay(&date1, TC_DELAY) != TCL_ER_OK) {
		SYS_DateTime_GetAddSec(&date2, &date1, 1);
		m_CurTime = date1;
		return false;
	}
	
	CtDraw::getInstance()->getDrawing(true);
	createBase();
	createDrawables();
	createDrawablesMonth(date1.Month);
	CtDraw::getInstance()->freeDrawing();

	setState(StateReqUpdate);
	drawDateTime(date1, 0);

	setState(StateReqUpdate);
	drawDateTime(date2, 1);

	setCurrent(0);
	
#ifdef DEBUG_TIMESTAMP		// ・ォ・鬘シ・ミ。シ、ヌウホヌァ
	clearTest();
#endif
	return true;
}

bool CtTimeStamp::destroy()
{
	m_State = StateInit;

#ifdef DEBUG_TIMESTAMP		// ・ォ・鬘シ・ミ。シ、ヌウホヌァ
	clearTest();
#endif
	return true;
}

bool CtTimeStamp::setInvalid()
{
	m_State = StateInvalid;
	return true;
}

/*
  ・ソ・、・爭ケ・ソ・ラケケソキヘラオ・*/
bool CtTimeStamp::update()
{
	// ・ォ・・ネ、ネクスコ゜サEホ・チ・ァ・テ・ッ ヒ鏃クニ、ヨ、ネスナ、、。ゥ
	//	TsDebugPrint(" now: %d:%d\n", now.Min, now.Sec);
	
	SYS_DATE_TIME now;
	if (TCL_GetDateTimeDelay(&now, TC_DELAY) != TCL_ER_OK) {
		return false;
	}
	
	// 1ノテク螟ホニ・ユ、チイ・	SYS_DATE_TIME date;
	SYS_DateTime_GetAddSec(&date, &now, 1);

	int next = getNextIndex();
	if (memcmp(&m_Time[next], &date, sizeof(date)) == 0) {
		return false;
	}
	
	// キ閒セハムイスサD疋暠・ヨ・・ニケステロ
	if (m_CurTime.Month != now.Month) {
		CtDraw::getInstance()->getDrawing(true);
		createDrawablesMonth(now.Month);
		CtDraw::getInstance()->freeDrawing();
	}
	m_CurTime = now;
	
	setState(StateReqUpdate);
	bool ret = drawDateTime(date, next);
	setState(StateFinUpdate);
	
	if (memcmp(&m_Time[m_Current], &now, sizeof(now)) != 0) {
		setCurrent(next);
	}
	
	return ret;
}

/*
・ォ・・ネ、ホ・ソ・、・爭ケ・ソ・ラセ霹タ
、ソ、ヨ、鏃クニ、ミ、・・*/
bool CtTimeStamp::getCurrent(GUI_TS_INFO *info)
{
	if (!info) return false;
	if ((m_State == StateInit) || (m_State == StateInvalid)) return false;
	if (m_Current == -1) return false;

#ifdef DEBUG_TIMESTAMP
	TsDebugPrint("CtTimeStamp::getCurrent(current:%#x)\n", m_Base[m_Current]);
#endif
	CtTsPBuffer buf = BaseToPbuffer(m_Base[m_Current]);

	info->ts_format.rect_w = m_Size.width;
	info->ts_format.rect_h = m_Size.height;
	info->ts_format.col_depth = (m_ColorDepth == 10) ? GUI_COLOR_DEPTH_10BIT : GUI_COLOR_DEPTH_8BIT;
	info->ts_format.col_type = (m_ColorFormat == Format_YUV422) ? GUI_COLOR_TYPE_422 : GUI_COLOR_TYPE_420;

	info->ts_meminfo.MemWidth = (UH)buf.MemWidth;
	info->ts_meminfo.Yaddr = (UW)buf.Yaddr & 0x7fffffff;
	info->ts_meminfo.Caddr = (UW)buf.Caddr & 0x7fffffff;

	if (m_ColorDepth == 10) {
		CtTsPBuffer low = BaseToPbuffer(m_BaseLow);
		info->ts_meminfo_lower.MemWidth = (UH)low.MemWidth;
		info->ts_meminfo_lower.Yaddr = (UW)low.Yaddr & 0x7fffffff;
		info->ts_meminfo_lower.Caddr = (UW)low.Caddr & 0x7fffffff;
	} else {
		info->ts_meminfo_lower.MemWidth = (UH)0;
		info->ts_meminfo_lower.Yaddr = (UW)NULL;
		info->ts_meminfo_lower.Caddr = (UW)NULL;
	}

#ifdef DEBUG_TIMESTAMP
	TsDebugPrint(" [0]: %d:%d\n", m_Time[0].Min, m_Time[0].Sec);
	TsDebugPrint(" [1]: %d:%d\n", m_Time[1].Min, m_Time[1].Sec);
#endif
	return true;
}

void CtTimeStamp::setCurrent(int idx)
{
#ifdef DEBUG_TIMESTAMP
	TsDebugPrint("CtTimeStamp::curret(%d -> %d)\n", m_Current, idx);
#endif
	m_Current = idx;
}

/*
  ・ソ・、・爭ケ・ソ・ラノチイ霓靉*/
#include "CtTimeMesure.h"
bool CtTimeStamp::drawDateTime(SYS_DATE_TIME& date, int tgt)
{
	int tgt;

#ifdef DEBUG_TIMESTAMP		// 時間測ト・	unsigned long time1, time2;
	time1 = CtGetTime();
#endif

	if ((tgt == -1) {
		return false;
	}

	//	chg_pri(0, 71);

	// ヌッキ鏆・ツ、モ、ホハムケケヘュフオウホヌァ
	if (m_DateFormat != getDateFormat()) {
		m_DateFormat = getDateFormat();
		for (int i = 0; i < BASE_COUNT; i++) {
			m_bReformat[i] = true;
		}
	}
		
	// ニ・ユ、ォ、鬣ノ・愠・ヨ・・D、リハムエケ
	DateTimeDrawabales dateDrawables = getDateTimeDrawables(date);

	// ノチイ雉ォサマコツノク、ホキ霪・	GDI_HANDLER drawBase = m_Base[tgt];
	int x = (short)(m_CharSize.width / 2);	// 0.5ハクサ巐・	int y = (short)((m_Size.height - m_CharSize.height) / 2);
	int idx = 0;
	bool bFirst = (m_Time[tgt].Sec == TIME_DEFAULT) ? true : false;
	bool bReformat = m_bReformat[tgt];
	m_bReformat[tgt] = false;
	short width = m_CharSize.width;

	if (m_DispMode & CtTsDispDate) {
		// ヌッキ鏆・ホノチイ・		const char * format = NULL;

		switch (m_DateFormat) {
		case CtDateFormatYMD: format = "YMD";	break;
		case CtDateFormatMDY: format = "MDY";	break;
		case CtDateFormatDMY: format = "DMY";	break;
		default:
			return false;
		}

		if (bReformat == true) {
			for (int j = 0; j < 3; j++) {
				// space
				if (j != 0) {	
					drawDrawable(drawBase, x + width * idx, y, m_Drawables.Space);
					idx++;
				}
				if (format[j] == 'Y') {
					for (int i = 0; i < 4; i++, idx++) {
						drawDrawable(drawBase, x + width * idx, y, dateDrawables.Year[i]);
					}
				}
				else if (format[j] == 'M') {
					for (int i = 0; i < 3; i++, idx++) {
						drawDrawable(drawBase, x + width * idx, y, dateDrawables.Month[i]);
					}
				}
				else if (format[j] == 'D') {
					for (int i = 0; i < 2; i++, idx++) {
						drawDrawable(drawBase, x + width * idx, y, dateDrawables.Day[i]);
					}
				}
			}
			
		} else {
			for (int j = 0; j < 3; j++) {
				// space
				if (j != 0) {	
					idx++;
				}

				if (format[j] == 'Y') {
					if (m_Time[tgt].Year != date.Year) {
						// year
						for (int i = 0; i < 4; i++, idx++) {
							if (m_DateDrawables[tgt].Year[i] != dateDrawables.Year[i])
								drawDrawable(drawBase, x + width * idx, y, dateDrawables.Year[i]);
						}
					}
					else {
						idx += 4;
					}
				}
				else if (format[j] == 'M') {
					if(m_Time[tgt].Month != date.Month) {
						// month
						for (int i = 0; i < 3; i++, idx++) {
							drawDrawable(drawBase, x + width * idx, y, dateDrawables.Month[i]);
						}
					}
					else {
						idx += 3;
					}
				}
				else if (format[j] == 'D') {
					if (m_Time[tgt].Day != date.Day) {
						// day
						for (int i = 0; i < 2; i++, idx++) {
							if (m_DateDrawables[tgt].Day[i] != dateDrawables.Day[i])
								drawDrawable(drawBase, x + width * idx, y, dateDrawables.Day[i]);
						}
					}
					else {
						idx += 2;
					}
				}
			}
		}
	}
		
	// ヌッキ鏆・ネサEヨ、ホ・ケ・レ。シ・ケ
	if (m_DispMode == CtTsDispDateTime) idx++;

	if (m_DispMode & CtTsDispTime) {
		// サEホノチイ・
		for (int i = 0; i < 2; i++, idx++) 
			if (m_DateDrawables[tgt].Hour[i] != dateDrawables.Hour[i])
				drawDrawable(drawBase, x + width * idx, y, dateDrawables.Hour[i]);

		if(bFirst) drawDrawable(drawBase, x + width * idx, y, m_Drawables.Separator); 
		idx++;

		for (int i = 0; i < 2; i++, idx++)
			if (m_DateDrawables[tgt].Min[i] != dateDrawables.Min[i])
				drawDrawable(drawBase, x + width * idx, y, dateDrawables.Min[i]);

		if (bFirst) drawDrawable(drawBase, x + width * idx, y, m_Drawables.Separator);
		idx++;

		for (int i = 0; i < 2; i++, idx++)
			if (m_DateDrawables[tgt].Sec[i] != dateDrawables.Sec[i])
				drawDrawable(drawBase, x + width * idx, y, dateDrawables.Sec[i]);
	}

#ifdef DEBUG_TIMESTAMP		// サE	time2 = CtGetTime();
	TsDebugPrint("drawDateTime(%d %d/%d/%d %d:%d:%d) ... %2dms\n", tgt, date.Year, date.Month, date.Day, date.Hour, date.Min, date.Sec, time2-time1);
#endif
	
	// コ」イチイ隍キ、ソ・ノ・愠・ヨ・・ネサEンサ	m_DateDrawables[tgt] = dateDrawables;
	m_Time[tgt] = date;
	
#ifdef DEBUG_TIMESTAMP		// ・ォ・鬘シ・ミ。シ、ヌウホヌァ
	drawTest(dateDrawables.Sec[1]);
#endif
	
	return true;
}

int CtTimeStamp::getNextIndex()
{
	return (m_Current + 1) % BASE_COUNT;
}

/*
* ハクサ妺鬣ル・・ホ・オ・、・コキ霪・*/
CtSize CtTimeStamp::getCharSize()
{
	CtSize ret;

	// ケ筅オ
	// 。。チエツホ、ホ70%
	ret.height = (short)(0.7f * m_Size.height);

	// ノ	// 全体の左右に0.5文字の空白を入、・・	short len = getTimeStampLength() + 1;	// +1、マコクアヲ、ホカ・.5*2
	ret.width = (short)(m_Size.width / len);	/* pgr0351 */

	return ret;
}

CtTimeStamp::CtDateFormat CtTimeStamp::getDateFormat()
{
	switch (APL_PARAM_GET_DATA(AplParamDateFormatMode)) {
	case 0:	return CtDateFormatYMD;
	case 1:	return CtDateFormatMDY;
	case 2:	return CtDateFormatDMY;
	default:
		break;
	}

	return CtDateFormatYMD;
}

CtTimeStamp::CtTsDisp CtTimeStamp::getDispMode()
{
	switch (APL_PARAM_GET_DATA(AplParamIndicatorDateTime)) {
#if 0
	case APL_SYS_PARAM_INDICATOR_DATETIME_OFF:
		return CtTsDispOff;
#endif
	case APL_SYS_PARAM_INDICATOR_DATETIME_DATE:
		return CtTsDispDate;
	case APL_SYS_PARAM_INDICATOR_DATETIME_TIME:
		return CtTsDispTime;
	case APL_SYS_PARAM_INDICATOR_DATETIME_DATE_TIME:
		return CtTsDispDateTime;
	}

	return CtTsDispDateTime;
}

/*
 ・ソ・、・爭ケ・ソ・ラ、ネ、キ、ニノチイ隍ケ、・クサ昀ケ、霹タ
*/
short CtTimeStamp::getTimeStampLength()
{
	const int DateLength = 4 + 1 + 3 + 1 + 2;	// Year + Space + Month + Space + Day
	const int TimeLength = 2 + 1 + 2 + 1 + 2;	// Hour + Colon + Minute + Colon + Sec

	switch (m_DispMode) {
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

/* ・ノ・愠・ヨ・・鋿ョス靉・ル。シ・ケノ・ */
void CtTimeStamp::createBase()
{
	CtTsInterface *pIf = CtTsInterface::getInstance();
	CtSize size = m_Size;

	pIf->setFormat(m_ColorFormat);

	for (int i = 0; i < BASE_COUNT; i++) {
		m_Base[i] = pIf->createBase(size, BgColor);
	}

	if (m_ColorDepth == 10) {	//10bit、ホセ・遉マ。「lowヘム、ホ・ル。シ・ケ、鋿ョ
		CtSize lowSize = m_Size;
		lowSize.width = (short)(m_Size.width / 4);	/* pgr0351 */
		m_BaseLow = pIf->createBase(lowSize, BgColor);
	}
}

/*
 ・ノ・愠・ヨ・・鋿ョス靉ソヘ、ネオュケ・
*/
void CtTimeStamp::createDrawables()
{
	CtTsInterface *pIf = CtTsInterface::getInstance();

	pIf->setFormat(m_ColorFormat);

	// ソ・'0'-'9'、ホ・ノ・愠・ヨ・・鋿ョ
	for (char i = 0; i < 10; i++) {
		m_Drawables.Dec[i] = pIf->createDrawable('0' + i, m_CharSize, BgColor, FgColor);	/* pgr0398 */
		DrawChar(m_Drawables.Dec[i], '0' + i);	/* pgr0397 */
	}

	// サEホ・サ・ム・・シ・ソ
	m_Drawables.Separator = pIf->createDrawable(':', m_CharSize, BgColor, FgColor);
	// カ・	m_Drawables.Space = pIf->createDrawable(' ', m_CharSize, BgColor, FgColor);
	
	DrawChar(m_Drawables.Separator, ':');
}

/*
・ノ・愠・ヨ・・鋿ョス靉キ閒セ、ホ・「・・ユ・。・ル・テ・ネ)
*/
void CtTimeStamp::createDrawablesMonth()
{
	SYS_DATE_TIME date;
	if (TCL_GetDateTimeDelay(&date, TC_DELAY) != TCL_ER_OK) {
		date.Month = 0;
	}

	createDrawablesMonth(date.Month);
}

/*
 ・ノ・愠・ヨ・・鋿ョス靉キ閒セ、ホ・「・・ユ・。・ル・テ・ネ)
*/
void CtTimeStamp::createDrawablesMonth(int month)
{
	static const char* monthStr[] = { "!!!", "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JLY", "AUG", "SEP", "OCT", "NOV", "DEC" };
	CtTsInterface *pIf = CtTsInterface::getInstance();

	if (month > 12)
		month = 0;

	pIf->setFormat(m_ColorFormat);

	for (int i = 0; i < 3; i++) {
		if (m_Drawables.Month[i] != GDI_INVALID_ID) {
			CtDraw::getInstance()->deleteDrawable(m_Drawables.Month[i]);
		}

		m_Drawables.Month[i] = pIf->createDrawable(monthStr[month][i], m_CharSize, BgColor, FgColor);
		DrawChar(m_Drawables.Month[i], monthStr[month][i]);
	}
}

/*
  クスコ゜サEォ、颯ateTimeDrawabales(ノチイ隍ケ、・ノ・愠・ヨ・・、リ、ホハムエケ
*/
CtTimeStamp::DateTimeDrawabales CtTimeStamp::getDateTimeDrawables(const SYS_DATE_TIME &date)
{
	CtTimeStamp::DateTimeDrawabales ret;

	// ー惞ate、ホニ・ユ,サEォ、鯔チイ隍ケ、・ノ・愠・ヨ・・D、ェツ・	ret.Year[0] = m_Drawables.Dec[date.Year / 1000];
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

/*
 1pixel、ホbyte・オ・、・コシ霹タ
*/
int CtTimeStamp::getBytePerPixel(CtColorFormat format)
{
	switch (format) {
	case Format_RGBA8888:
		return 4;
	case Format_RGBA4444:
		return 2;
	case Format_YUV422:
	case Format_YUV420:
		return 1;	// Y、ホ、゜ケヘホク
	default:
		break;
	}

	return 1;
}

CtTimeStamp::CtTsPBuffer CtTimeStamp::BaseToPbuffer(GDI_HANDLER handle)
{
	CtTsPBuffer ret;
	memset(&ret, 0x00, sizeof(ret));

	gdi_pbuffer_context *pbuffer = reinterpret_cast<gdi_pbuffer_context*>(handle);
	if (pbuffer == NULL)
		return ret;
	
	ret.Width = m_Size.width;
	ret.Height = m_Size.height;
	ret.MemWidth = pbuffer->aln_width;
	ret.Yaddr = pbuffer->color_buffer0;
	ret.Caddr = pbuffer->color_buffer1;

	return ret;
}

CtTimeStamp::CtTsPBuffer CtTimeStamp::DrawableToPbuffer(GDI_HANDLER handle)
{
	CtTsPBuffer ret;
	memset(&ret, 0x00, sizeof(ret));

	gdi_pbuffer_context *pbuffer = reinterpret_cast<gdi_pbuffer_context*>(handle);
	if (pbuffer == NULL)
		return ret;
	
	ret.Width = pbuffer->width;
	ret.Height = pbuffer->height;
	ret.MemWidth = pbuffer->aln_width;
#if 1 // readツヲ、マ・ュ・罕テ・キ・衾ホー・10ヌワー网ヲ、・
	ret.Yaddr = (unsigned char*)((unsigned long)pbuffer->color_buffer0 & 0x7fffffff);
	ret.Caddr = (unsigned char*)((unsigned long)pbuffer->color_buffer1 & 0x7fffffff);
#else
	ret.Yaddr = pbuffer->color_buffer0;
	ret.Caddr = pbuffer->color_buffer1;
#endif
	return ret;
}

/*
 _dest・ミ・テ・ユ・。ホホー隍ホx,yコツノク、リ_src、チイ・*/
void CtTimeStamp::drawDrawable(GDI_HANDLER _dest, int x, int y, GDI_HANDLER _src)
{
	CtTsPBuffer dst = BaseToPbuffer(_dest);
	CtTsPBuffer src = DrawableToPbuffer(_src);
	int bpp = getBytePerPixel(m_ColorFormat);

	//printf("drawDrawable(%#x, %d, %d, %#x)\n", _dest, x, y, _src);

	for (unsigned int i = 0; i < src.Height; i++, y++) {
		void *srcaddrY = src.Yaddr + i * src.MemWidth;
		void *dstaddrY = dst.Yaddr + y * dst.MemWidth + x * bpp;
		memcpy(dstaddrY, srcaddrY, src.Width * bpp);

		void *srcaddrC;
		void *dstaddrC;
		switch (m_ColorFormat) {
		case Format_YUV420:
			if ((i % 2) != 0)
				break;
			srcaddrC = src.Caddr + i/2 * src.MemWidth;
			dstaddrC = dst.Caddr + y * dst.MemWidth + x * bpp;
			memcpy(dstaddrC, srcaddrC, src.Width);
			break;
		case Format_YUV422:
			srcaddrC = src.Caddr + i * src.MemWidth;
			dstaddrC = dst.Caddr + y * dst.MemWidth + x * bpp;
			memcpy(dstaddrC, srcaddrC, src.Width);
			break;
		default:
			break;
		}
	}
}

/*
  ・ォ・鬘シ・ミ。シ、ホホホー隍ヒナセチキ、ニセ。シ熙ヒ・ニ・ケ・ネ
*/
void CtTimeStamp::clearTest()
{
	unsigned char* dstY = (unsigned char*)(0xfe1ccc00);
	unsigned char* dstC = (unsigned char*)(0xfea3cc00);
	unsigned int dstW = 4096;
	unsigned int dstH = 2160;
	unsigned int i;

	for (i = 0; i < dstH; i++) {
		memset((dstY + (i*dstW)), 0xb0, dstW);
		memset((dstC + (i*dstW)), 0x00, dstW);
	}
}

void CtTimeStamp::drawTest(GDI_HANDLER drawable)
{
	unsigned char* dstY = (unsigned char*)(0xfe1ccc00);
	unsigned char* dstC = (unsigned char*)(0xfea3cc00);
	unsigned int dstW = 4096;
	
	CtTsPBuffer src = BaseToPbuffer(m_Base[m_Current]);

	for (unsigned int i = 0; i < src.Height; i++) {
		void *srcaddrY = src.Yaddr + i * src.MemWidth;
		void *dstaddrY = dstY + (400 +i) * dstW + 100;

		memcpy(dstaddrY, srcaddrY, src.Width);

		void *srcaddrC;
		void *dstaddrC;
		switch (m_ColorFormat) {
		case Format_YUV420:
			if ((i % 2) == 0) {
				srcaddrC = src.Caddr + i/2 * src.MemWidth;
				dstaddrC = dstC + ((400 +i)/2) * dstW + 100;
				memcpy(dstaddrC, srcaddrC, src.Width);
			}
			break;
		case Format_YUV422:
			srcaddrC = src.Caddr + i * src.MemWidth;
			dstaddrC = dstC + (400 +i) * dstW + 100;
			memcpy(dstaddrC, srcaddrC, src.Width);
			break;
		default:
			break;
		}
	}

	if (drawable == GDI_INVALID_ID)
		return;
	
	src = DrawableToPbuffer(drawable);
	
	for (unsigned int i = 0; i < src.Height; i++) {
		void *srcaddrY = src.Yaddr + i * src.MemWidth;
		void *dstaddrY = dstY + (800 +i) * dstW + 300;

		memcpy(dstaddrY, srcaddrY, src.Width);

		void *srcaddrC = src.Caddr + i * src.MemWidth;
		void *dstaddrC;
		switch (m_ColorFormat) {
		case Format_YUV420:
			if ((i % 2) == 0) {
				dstaddrC = dstC + ((800 +i)/2) * dstW + 300;
				memcpy(dstaddrC, srcaddrC, src.Width);
			}
			break;
		case Format_YUV422:
			dstaddrC = dstC + (800 +i) * dstW + 300;
			memcpy(dstaddrC, srcaddrC, src.Width);
			break;
		default:
			break;
		}
	}

	GUI_TS_INFO Info;
	getCurrent(&Info);

	CtDebugPrint(CtDbg, "******************************** getTimeStampInfo ********************************\n");
	switch (m_ColorFormat) {
	case Format_YUV420:
		CtDebugPrint(CtDbg, "    Format        : YUV420\n");
		break;
	case Format_YUV422:
		CtDebugPrint(CtDbg, "    Format        : YUV422\n");
		break;
	default:
		CtDebugPrint(CtDbg, "    Format        : unknown\n");
		break;
	}
	CtDebugPrint(CtDbg, "    RECT Width    : %3d\n", Info.ts_format.rect_w);
	CtDebugPrint(CtDbg, "    RECT Height   : %3d\n", Info.ts_format.rect_h);
	CtDebugPrint(CtDbg, "      MemWidth    : %3d\n", Info.ts_meminfo.MemWidth);
	CtDebugPrint(CtDbg, "      YAddr       : %p\n", Info.ts_meminfo.Yaddr);
	CtDebugPrint(CtDbg, "      CAddr       : %p\n", Info.ts_meminfo.Caddr);
	CtDebugPrint(CtDbg, "      YAddr(low)  : %p\n", Info.ts_meminfo_lower.Yaddr);
	CtDebugPrint(CtDbg, "      CAddr(low)  : %p\n", Info.ts_meminfo_lower.Caddr);
	CtDebugPrint(CtDbg, "**********************************************************************************\n");
	
}


void CtTimeStamp::setState(CtTsState state)
{
#ifdef DEBUG_TIMESTAMP
	static const char* str[] = { "Init", "ReqUpdate", "FinUPdate" };
#endif
	m_State = state;
}

/*
 <・キ・゜・螂・シ・ソ・ニ・ケ・ネヘム>
 gdi_context_pbuffer、ホcolor_buf0、ヒ」キ・サ・ー、ヌハクサ妤ッ
*/
void CtTimeStamp::DrawChar(GDI_HANDLER handle, char c)
{
#if !defined(DEBUG_TIMESTAMP) || !defined(WIN32_GUI_SIM)
	return;
#else
	if (m_ColorFormat != Format_RGBA8888) return;


	gdi_pbuffer_context *p = (gdi_pbuffer_context*)handle;

	// ・ミ・テ・ユ・。、ホセ蟯シコクアヲ-2、ホホホー隍ヒノチイ・	int width = p->width - 4;
	int height = p->height - 4;
	int *buf = (int*)p->color_buffer0;
	char seg[7] = { 0 };

	// ウォサマーフテヨ、・,2、ヒ、ケ、・	buf += p->width * 2 + 2;

	switch (c) {
	case '0':	seg[0] = seg[1] = seg[2] = seg[3] = seg[4] = seg[5] = 1;			break;
	case '1':	seg[1] = seg[2] = 1;												break;
	case '2':	seg[0] = seg[1] = seg[3] = seg[4] = seg[6] = 1;						break;
	case '3':	seg[0] = seg[1] = seg[2] = seg[3] = seg[6] = 1;						break;
	case '4':	seg[1] = seg[2] = seg[5] = seg[6] = 1;								break;
	case '5':	seg[0] = seg[2] = seg[3] = seg[5] = seg[6] = 1;						break;
	case '6':	seg[0] = seg[2] = seg[3] = seg[4] = seg[5] = seg[6] = 1;			break;
	case '7':	seg[0] = seg[1] = seg[2] = 1;										break;
	case '8':	seg[0] = seg[1] = seg[2] = seg[3] = seg[4] = seg[5] = seg[6] = 1;	break;
	case '9':	seg[0] = seg[1] = seg[2] = seg[3] = seg[5] = seg[6] = 1;			break;
	case '-':	seg[6] = 1;															break;
	case ':':	seg[6] = 1;															break;
	case 'A':	seg[0] = seg[1] = seg[2] = seg[4] = seg[5] = seg[6] = 1;			break;
	case 'B':	seg[2] = seg[3] = seg[4] = seg[5] = seg[6] = 1;						break;
	case 'C':	seg[0] = seg[3] = seg[4] = seg[5] = seg[6] = 1;						break;
	case 'D':	seg[1] = seg[2] = seg[3] = seg[4] = seg[6] = 1;						break;
	case 'E':	seg[0] = seg[3] = seg[4] = seg[5] = seg[6] = 1;						break;
	case 'F':	seg[0] = seg[4] = seg[5] = seg[6] = 1;								break;
	case 'G':	seg[0] = seg[2] = seg[3] = seg[4] = seg[5] = 1;						break;
	case 'J':	seg[0] = seg[1] = seg[2] = seg[3] = 1;								break;
	case 'L':	seg[3] = seg[4] = seg[5] = 1;										break;
	case 'M':	seg[0] = seg[1] = seg[2] = seg[4] = seg[5] = 1;						break;
	case 'N':	seg[2] = seg[4] = seg[6] = 1;										break;
	case 'O':	seg[2] = seg[3] = seg[4] = seg[6] = 1;								break;
	case 'P':	seg[0] = seg[1] = seg[4] = seg[5] = seg[6] = 1;						break;
	case 'R':	seg[4] = seg[6] = 1;												break;
	case 'S':	seg[2] = seg[3] = seg[5] = seg[6] = 1;								break;
	case 'T':	seg[3] = seg[4] = seg[5] = seg[6] = 1;								break;
	case 'U':	seg[2] = seg[3] = seg[4] = 1;										break;
	case 'V':	seg[0] = seg[1] = seg[2] = seg[3] = seg[4] = 1;						break;
	case 'Y':	seg[1] = seg[2] = seg[3] = seg[5] = seg[6] = 1;						break;
	default:
		return;
	}

	/*
	 7・サ・ー、ネナコ、ィサ妤ホツミア鑁		-----0-----
		|         |
		5         1
		|	      |
		-----6-----
		|	      |
		4         2
		|	      |
		-----3-----
	*/

	if (seg[0]) {
		for (int i = 0; i < 2; i++)
			memset(buf + p->width * i, 0xff, width * 4);
	}
	if (seg[1]) {
		for (int i = 0; i < height / 2; i++)
			memset(buf + p->width * i + width - 2, 0xff, 8);
	}
	if (seg[2]) {
		for (int i = height / 2; i < height; i++)
			memset(buf + p->width * i + width - 2, 0xff, 8);
	}
	if (seg[3]) {
		for (int i = height - 2; i < height; i++)
			memset(buf + p->width * i, 0xff, width * 4);
	}
	if (seg[4]) {
		for (int i = height / 2; i < height; i++)
			memset(buf + p->width * i, 0xff, 8);
	}
	if (seg[5]) {
		for (int i = 0; i < height / 2; i++)
			memset(buf + p->width * i, 0xff, 8);
	}
	if (seg[6]) {
		for (int i = height / 2 - 1; i < height / 2 + 1; i++)
			memset(buf + p->width * i, 0xff, width * 4);
	}
#endif
}
