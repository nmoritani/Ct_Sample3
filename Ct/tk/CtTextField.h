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
	/* �J�[�\���ʒu�̏����l�w��p */
	enum InitialCursorPos {
		CursorEnd,
		CursorStart,
		DefaultCursor = CursorEnd
	};

	enum CursorShape {
		ShapeBlock,				/* �� */
		ShapeUnderscore,		/* �Q */
		ShapeVertialLine,		/* �h ���Ή��ł��邩�c�H */
		ShapeNone,				/* �J�[�\���Ȃ� (�\�������Ȃ�) */
		DefaultShape = ShapeBlock
	};

	virtual ~CtTextField();
	/* �R���X�g���N�^�ɏȗ��\�ȃp�����[�^������� (�p�����[�^��-1)^2 (�H) �������Ȃ��Ƃ����Ȃ��̂�
	   ��{�I�ɏȗ��\�ȃp�����[�^�� set �֐��Őݒ肵�Ă��炤�B */
	CtTextField();
	CtTextField(const char* str, const CtFontSet& fontset);

	/* �����p�����[�^�ݒ� */
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
	char m_PasswordChar;		/* Password �\������ */

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
		unsigned int getLength() {return m_Length + 1;} /* �J�[�\���\���p ' ' ���܂߂���������Ԃ� */
		unsigned int getMaxCurPos() {return m_Length;} /* �J�[�\����������ő�ʒu��Ԃ� */
		CtFontSet& getFontSet() {return m_FontSet;}
		GDI_FONT_STYLE* getFontStyle() {return &m_FontSet.fontStyle;}
		char* cloneSubString(unsigned int start, unsigned int end);

	private:
		void init(const char* str);
		unsigned int calcLength(const char* str);
	};

	struct VisibleText {		/* �\���͈͊Ǘ��f�[�^ */
		enum State {
			INITIALIZE,
			READY
		};
		enum PasswordView {
			PASSWORD_CHAR_WITHOUT_LAST,
			PASSWORD_CHAR_ALL,
		};
		enum Direction {
			SHIFT_LEFT,		 /* start �����炵�Ă���A end �����炷 */
			SHIFT_RIGHT,	 /* end �𑝂₵����A start �𑝂₷ */
			SET_END,		 /* end ��ݒ肵����A start �𒲐� */
			ADJUST_START,	 /* end �͕ς����ɁA start �𑝌� */
			ADJUST_END		 /* start �͕ς����ɁA end �𑝌� */
		};
		State state;
		PasswordView passview;
		unsigned int start;
		unsigned int end;
	};

	struct Cursor {
		unsigned int pos;		/* �J�[�\���ʒu */
		CursorShape shape;		/* �`�� */
		bool isOnSideBlinking;	/* (�_�Œ���) �\�� ON �� */

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

	struct Draw {				/* �����`���� */
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

	AdjustText m_AllText;		/* �S������ */
	VisibleText m_VisibleText;	/* �\���ʒu���� */
	Cursor m_Cursor;			/* �J�[�\�� */
	Draw m_DrawLeft;			/* �`���� (�J�[�\����荶) */
	Draw m_DrawRight;			/* �`���� (�J�[�\�����E) */

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
