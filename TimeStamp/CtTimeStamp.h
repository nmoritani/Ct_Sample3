/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtContainer
 */


#ifndef __CtTimeStamp_H__
#define __CtTimeStamp_H__

#include "CtObject.h"
#include "CtTsInterface.h"

#include "SysIf.h"
#include "gui_timestamp_api.h"

class CtTimeStamp : public CtObject {
public:
	enum CtTsDisp {
		CtTsDispDate = (1 << 0),
		CtTsDispTime = (1 << 1),
		CtTsDispDateTime = CtTsDispDate | CtTsDispTime,
	};

public :
    CtTimeStamp(CtSize size, CtColorFormat colorFormat, int colorDepth, CtTsDisp dispMode);
    virtual ~CtTimeStamp();

	bool create();
	bool destroy();
	bool update();
	bool setInvalid();
	bool getCurrent(GUI_TS_INFO *info);
	bool isCreated() { return m_State != StateInit; }

private :
	enum CtDateFormat {
		CtDateFormatYMD,
		CtDateFormatMDY,
		CtDateFormatDMY,
	};

	enum CtTsState {
		StateInit,			// Init初期化完了、Create待ち
		StateReqUpdate,		// update待ち
		StateFinUpdate,		// getCurrent待ち
		StateInvalid,
	};

	struct CtTsPBuffer {
		unsigned char *Yaddr;
		unsigned char *Caddr;	
		unsigned int MemWidth;
		unsigned int Width;
		unsigned int Height;
	};

	CtColor FgColor;		// 前景色(文字色)
	CtColor BgColor;		// 背景色
	static const int BASE_COUNT = 2;	// バッファ面数

	struct drawables {
		GDI_HANDLER Month[3];
		GDI_HANDLER Separator;
		GDI_HANDLER Dec[10];
		GDI_HANDLER Space;
	} m_Drawables;

	struct DateTimeDrawabales {
		GDI_HANDLER Year[4];
		GDI_HANDLER Month[3];
		GDI_HANDLER Day[2];
		GDI_HANDLER Hour[2];
		GDI_HANDLER Min[2];
		GDI_HANDLER Sec[2];
	} m_DateDrawables[BASE_COUNT];

	CtTsState m_State;						// 
	GDI_HANDLER m_Base[BASE_COUNT];			// 描画対象領域
	GDI_HANDLER m_BaseLow;					// 10bit用描画対象領域
	SYS_DATE_TIME m_Time[BASE_COUNT];		// 描画完了済みの時刻
	SYS_DATE_TIME m_CurTime;
	int m_Current;							// 描画完了済みのm_Baseインデックス
	CtSize m_Size;							// Baseサイズ
	CtSize m_CharSize;						// １文字のサイズ
	CtColorFormat m_ColorFormat;			// タイムスタンプのカラーフォーマット(YUV422,YUV420,RGB8888,RGB4444)
	int m_ColorDepth;						// タイムスタンプの色深度
	CtDateFormat m_DateFormat;				// 日付表示フォーマット(YMD/DMY/MDY)
	CtTsDisp m_DispMode;					// 日付表示モード(OFF/Date/Time/Date&Time)
	bool m_bReformat[BASE_COUNT];			// 年月日フォーマット変更有無

private:
	CtSize getCharSize();
	CtDateFormat getDateFormat();
	CtTsDisp getDispMode();
	short getTimeStampLength();
	int getBytePerPixel(CtColorFormat format);
	CtTsPBuffer BaseToPbuffer(GDI_HANDLER handle);
	CtTsPBuffer DrawableToPbuffer(GDI_HANDLER handle);
	int getNextIndex();
	void setCurrent(int idx);
	void setState(CtTsState state);

	void createBase();
	void createDrawables();
	void createDrawablesMonth();
	void createDrawablesMonth(int month);
	bool drawDateTime(SYS_DATE_TIME& date, int index);
	void drawDrawable(GDI_HANDLER dest, int x, int y, GDI_HANDLER src);
	
	void clearTest();
	void drawTest(GDI_HANDLER drawable);
	
	DateTimeDrawabales getDateTimeDrawables(const SYS_DATE_TIME &date);

	// for TEST
	void DrawChar(GDI_HANDLER handle, char c);
};

#endif
