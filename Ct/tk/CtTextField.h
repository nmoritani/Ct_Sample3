/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtTextField
 */
#ifndef __CtTextField_H__
#define __CtTextField_H__

#include "CtLabel.h"
#include "CtDebugPrint.h"

const int CT_TEXT_FIELD_TIMER_ID = 0;

class CtTextField : public CtLabel {
public:
	/* カーソル位置の初期値指定用 */
	enum InitialCursorPos {
		CursorEnd,
		CursorStart,
		DefaultCursor = CursorEnd
	};

	enum CursorShape {
		ShapeBlock,				/* ■ */
		ShapeUnderscore,		/* ＿ */
		ShapeVertialLine,		/* Ｉ ※対応できるか…？ */
		ShapeNone,				/* カーソルなし (表示させない) */
		DefaultShape = ShapeBlock
	};

	virtual ~CtTextField();
	/* コンストラクタに省略可能なパラメータを入れると (パラメータ数-1)^2 (？) だけ作らないといけないので
	   基本的に省略可能なパラメータは set 関数で設定してもらう。 */
	CtTextField();
	CtTextField(const char* str, const CtFontSet& fontset);

	/* 初期パラメータ設定 */
	void setInitParam(InitialCursorPos curPos);
	void setInitParam(CursorShape curShape);
	void setInitParam(char passwordChar);

	bool draw(const CtRegion& Clip, int Screen = 0);
	bool drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen = 0);
	
	void insertChar(const char character);
	void deleteChar();
	void backspaceChar();
	void forwardCursor();
	void backwardCursor();
	char* getString();
	virtual bool handleTimerEvent(const CtEventTimer& Timer);

private:
	static const CtFontSet m_DefaultFontSet;
	static const CtAlign m_DefaultAlign;
	static const char m_NotPassword;
	char* m_pText;
	char m_PasswordChar;		/* Password 表示文字 */

	void init();
	int getDrawWidth(unsigned int start, unsigned int end);
	template <typename TYPE> TYPE* generatePasswordStr(unsigned int num);
	void blinkCursor(bool isOn);
	template <typename TYPE> static TYPE* newArray(unsigned int size);
	static void deleteArray(void* array);

	class AdjustText : public CtObject {
		char* m_pStr;
		unsigned int m_Length;
		CtFontSet m_FontSet;

	public:
		AdjustText();
		AdjustText(const char* str, const CtFontSet& fontset);
		~AdjustText();
		void insertChar(unsigned int insertPos, const char character);
		void deleteChar(unsigned int deletePos);
		void setString(char* newStr) {CtTextField::deleteArray(m_pStr); m_pStr = newStr;}
		char* getString() {return m_pStr;}
		unsigned int getLength() {return m_Length + 1;} /* カーソル表示用 ' ' を含めた文字数を返す */
		unsigned int getMaxCurPos() {return m_Length;} /* カーソルが動ける最大位置を返す */
		CtFontSet& getFontSet() {return m_FontSet;}
		GDI_FONT_STYLE* getFontStyle() {return &m_FontSet.fontStyle;}
		char* cloneSubString(unsigned int start, unsigned int end);

	private:
		void init(const char* str);
		unsigned int calcLength(const char* str);
	};

	struct VisibleText {		/* 表示範囲管理データ */
		enum State {
			INITIALIZE,
			READY
		};
		enum PasswordView {
			PASSWORD_CHAR_WITHOUT_LAST,
			PASSWORD_CHAR_ALL,
		};
		enum Direction {
			SHIFT_LEFT,		 /* start を減らしてから、 end を減らす */
			SHIFT_RIGHT,	 /* end を増やした後、 start を増やす */
			SET_END,		 /* end を設定した後、 start を調整 */
			ADJUST_START,	 /* end は変えずに、 start を増減 */
			ADJUST_END		 /* start は変えずに、 end を増減 */
		};
		State state;
		PasswordView passview;
		unsigned int start;
		unsigned int end;
	};

	struct Cursor {
		unsigned int pos;		/* カーソル位置 */
		CursorShape shape;		/* 形状 */
		bool isOnSideBlinking;	/* (点滅中の) 表示 ON 時 */

		struct {
			struct {
				unsigned int start;
				unsigned int end;
			} string;
			struct {
				unsigned int x;
				unsigned int width;
			} region;
			struct {
				CtString foreground;
				CtRect background;
			} info;
			CtRect rect;
		} draw;
	};

	struct Draw {				/* 部分描画情報 */
		struct {
			unsigned int start;
			unsigned int end;
		} string;
		struct {
			unsigned int x;
			unsigned int width;
		} region;
		CtString info;
	};

	AdjustText m_AllText;		/* 全文字列 */
	VisibleText m_VisibleText;	/* 表示位置制御 */
	Cursor m_Cursor;			/* カーソル */
	Draw m_DrawLeft;			/* 描画情報 (カーソルより左) */
	Draw m_DrawRight;			/* 描画情報 (カーソルより右) */

	void initVisibleText(const CtRegion& region);
	void adjustVisibleText(VisibleText::Direction dir, unsigned int pos = 0);
	void createDrawSide(Draw& draw, const CtRegion& baseRegion, unsigned int txtStart, unsigned int txtEnd, int offset);
	void createDrawCursor(const CtRegion& baseRegion, int offset);
};

template<typename TYPE>
inline TYPE* CtTextField::newArray(unsigned int size)
{
	return static_cast<TYPE*>(operator new(sizeof(TYPE) * size));
}

inline void CtTextField::deleteArray(void* array)
{
	if(array) operator delete(array);
}

#endif	/* __CtTextField_H__ */
