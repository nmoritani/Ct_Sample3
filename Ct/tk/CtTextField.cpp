/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtTextField
 */

#include "CtTextField.h"

const CtFontSet CtTextField::m_DefaultFontSet(FontTypeNormal);
const CtAlign CtTextField::m_DefaultAlign = AlignLeft;
const char CtTextField::m_NotPassword = '\0';

/* コンストラクタ */
/* CtLabel へ渡す文字列 (表示する文字列) は、表示範囲を計算する前なので空文字列で初期化しておく */
CtTextField::CtTextField() :
	CtLabel("", m_DefaultFontSet),
	m_pText(NULL),
	m_DrawLeft(),
	m_DrawRight(),
	m_AllText("", m_DefaultFontSet),
	m_Cursor(),
	m_VisibleText(),
	m_PasswordChar(m_NotPassword)
{
	init();
}

CtTextField::CtTextField(const char* str, const CtFontSet& fontset) :
	CtLabel("", fontset),
	m_pText(NULL),
	m_DrawLeft(),
	m_DrawRight(),
	m_AllText(str, fontset),
	m_Cursor(),
	m_VisibleText(),
	m_PasswordChar(m_NotPassword)
{
	init();
}

/* デストラクタ */
CtTextField::~CtTextField()
{
	CtTextField::deleteArray(m_pText);
}

/* コンストラクタが複数あるため、共通の初期化処理をまとめた */
void CtTextField::init()
{
	setClassType(CtClassType_TextField);

	/* カーソルの初期化 */
	setInitParam(DefaultCursor);
	setInitParam(DefaultShape);
	m_Cursor.isOnSideBlinking = true;

	/* 表示文字範囲の初期化 */
	m_VisibleText.start = 0;
	m_VisibleText.end = 0;
	m_VisibleText.state = VisibleText::INITIALIZE;
	m_VisibleText.passview = VisibleText::PASSWORD_CHAR_ALL;

	/* m_pDrawInfo を用いた描画はしない */
	CtTextField::deleteArray(m_pDrawInfo);
	m_pDrawInfo = NULL;
}

/* パラメータ初期設定 (カーソル位置) */
void CtTextField::setInitParam(InitialCursorPos curPos)
{
	m_Cursor.pos = (curPos == CursorEnd) ? m_AllText.getMaxCurPos() : 0;
}

/* パラメータ初期設定 (カーソル形状) */
void CtTextField::setInitParam(CursorShape curShape)
{
	m_Cursor.shape = curShape;
	blinkCursor((m_Cursor.shape == ShapeNone) ? false : true);
}

/* パラメータ初期設定 (パスワード表示) */
void CtTextField::setInitParam(char passwordChar)
{
	m_PasswordChar = passwordChar;
}

bool CtTextField::draw(const CtRegion& Clip, int Screen)
{
	if (isCollision(Clip, Screen) != true)
		return false;
	
	clearInvalidate(Screen);
	
	if (isVisible(Screen) != true)
		return false;

	if (m_VisibleText.state != VisibleText::READY) { /* 最初の一回のみ必要。 getRegion ができるようになってから実施 */
		initVisibleText(getRegion());
	}

	CtRegion baseRegion = getRegion(Screen);

	if (m_Cursor.shape != ShapeNone) {
		/**
		 *                    |←表示範囲→|
		 * m_AllText:     ＡＢ|ＣＤＥＦＧＨ|ＩＪ
		 *                    |↑  ▲    ↑|
		 * m_Cursor:          |｜  pos   ｜|
		 * m_VisibleText:     |start    end|
		 *                    |←→⇔←─→|
		 * m_pDrawInfo:       |left : right|
		 *                         Cursor
		 */
		/* カーソル左の描画情報を作成 (カーソルが先頭なら作成不要) */
		if (m_Cursor.pos > m_VisibleText.start) {
			createDrawSide(m_DrawLeft, baseRegion, m_VisibleText.start, m_Cursor.pos - 1, 0);
			m_DrawLeft.info.setClip(Clip);
			m_DrawLeft.info.setTrans(isTrans());
			m_DrawLeft.info.draw();
		} else {
			/* Region は後の計算で必要なので設定しておく */
			m_DrawLeft.region.x = baseRegion.x;
			m_DrawLeft.region.width = 0;
		}

		/* カーソル描画情報を作成 */
		createDrawCursor(baseRegion, m_DrawLeft.region.width);

		/* カーソル右の描画情報を作成 (カーソルが末尾の場合は作成不要) */
		if (m_Cursor.pos < m_VisibleText.end) {
			createDrawSide(m_DrawRight, baseRegion, m_Cursor.pos + 1, m_VisibleText.end, m_DrawLeft.region.width + m_Cursor.draw.region.width);
			m_DrawRight.info.setClip(Clip);
			m_DrawRight.info.setTrans(isTrans());
			m_DrawRight.info.draw();
		}
		/* カーソル系は最後に追加 */
		m_Cursor.draw.info.background.setClip(Clip);
		m_Cursor.draw.info.background.setTrans(isTrans());
		m_Cursor.draw.info.foreground.setClip(Clip);
		m_Cursor.draw.info.foreground.setTrans(isTrans());
		m_Cursor.draw.info.background.draw();
		m_Cursor.draw.info.foreground.draw();
	} else {
		/* カーソルを描画しない場合 */
		createDrawSide(m_DrawLeft, baseRegion, m_VisibleText.start, m_VisibleText.end, 0);
		m_DrawLeft.info.setClip(Clip);
		m_DrawLeft.info.setTrans(isTrans());
		m_DrawLeft.info.draw();
	}

	return true;
}

bool CtTextField::drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen)
{
	return false;
}

/* 編集後の文字列を返す */
char* CtTextField::getString()
{
	/**
	 * m_AllText 管理の文字列末尾は ' ' なので、 '\0' に変更する必要がある。
	 * なので、新規に領域を作って返す必要がある。作った領域はデストラクタで解放
	 */
	if (m_pText) {				/* 既に作ってあったら解放してから作成 */
		CtTextField::deleteArray(m_pText);
	}
	unsigned int arraySize = m_AllText.getLength(); /* ' ' を含めた文字数を返す */
	unsigned int strLength = arraySize - 1;
	m_pText = CtTextField::newArray<char>(arraySize);
	memcpy(m_pText, m_AllText.getString(), strLength);
	m_pText[strLength] = '\0';	/* '\0' ターミネート */ /* parasoft-suppress BD-PB-NP */
	return m_pText;
}

/* カーソル位置に 1 文字挿入 (INS) */
void CtTextField::insertChar(const char character)
{
	m_AllText.insertChar(m_Cursor.pos, character);
	m_Cursor.pos++;	/* 文字数が増えてるので、カーソルが文字数を越えることはない */
	m_VisibleText.passview = VisibleText::PASSWORD_CHAR_WITHOUT_LAST;

	/* 表示範囲の調整 */
	if (getDrawWidth(m_VisibleText.start, m_VisibleText.end + 1) <= getRegion().width) {
		adjustVisibleText(VisibleText::SET_END, m_VisibleText.end + 1);
	} else {
		if (m_Cursor.pos >= m_VisibleText.end) { /* カーソル位置==右端の場合は start 側を調整 */
			adjustVisibleText(VisibleText::SET_END, m_Cursor.pos);
		} else {
			adjustVisibleText(VisibleText::ADJUST_END);
		}
	}
	setInvalidate();
}

/* カーソル位置の文字を消す (DEL) */
void CtTextField::deleteChar()
{
	if ((m_Cursor.pos != 0) && (m_Cursor.pos >= m_AllText.getMaxCurPos())) { /* カーソルが一番最後の空白を選択しているときは一文字前に戻して削除 */
		m_Cursor.pos--;
	}
	m_VisibleText.passview = VisibleText::PASSWORD_CHAR_ALL;
	m_AllText.deleteChar(m_Cursor.pos);

	/* 表示範囲の調整 */
	if (m_VisibleText.end > m_AllText.getMaxCurPos()) {
		adjustVisibleText(VisibleText::SET_END, m_AllText.getMaxCurPos());
	} else {
		adjustVisibleText(VisibleText::ADJUST_START);
	}
	setInvalidate();
}

/* カーソル位置の一つ前文字を消す (BS) */
void CtTextField::backspaceChar()
{
	if (m_Cursor.pos > 0) { /* 一文字前に戻して削除 */
		m_Cursor.pos--;
	} else {
		return;
	}
	m_VisibleText.passview = VisibleText::PASSWORD_CHAR_ALL;
	m_AllText.deleteChar(m_Cursor.pos);

	/* 表示範囲の調整 */
	if (m_VisibleText.end > m_AllText.getMaxCurPos()) {
		adjustVisibleText(VisibleText::SET_END, m_AllText.getMaxCurPos());
	} else {
		adjustVisibleText(VisibleText::ADJUST_START);
	}
	setInvalidate();
}

/* カーソルを進める */
void CtTextField::forwardCursor()
{
	if (m_Cursor.pos < m_AllText.getMaxCurPos()) {
		m_Cursor.pos++;

		if (m_Cursor.pos > m_VisibleText.end) {
			m_VisibleText.passview = VisibleText::PASSWORD_CHAR_ALL;
			adjustVisibleText(VisibleText::SHIFT_RIGHT);
		}
		setInvalidate();
	}
}

/* カーソルを戻す */
void CtTextField::backwardCursor()
{
	if (m_Cursor.pos) {
		m_Cursor.pos--;

		if (m_Cursor.pos < m_VisibleText.start) {
			m_VisibleText.passview = VisibleText::PASSWORD_CHAR_ALL;
			adjustVisibleText(VisibleText::SHIFT_LEFT);
		}
		setInvalidate();
	}
}

/* テキスト範囲の描画幅を返す */
int CtTextField::getDrawWidth(unsigned int start, unsigned int end)
{
	unsigned int max = m_AllText.getMaxCurPos();
	if ((max < start) || (max < end) || (start > end)) {
		CtDebugPrint(CtDbg, "parameter error!! max=%d start=%d end=%d\n", max, start, end);
		return 0;
	}

	/**
	 * GDI には short の文字列が必要
	 * char の文字列を short の文字列に変換する API もあるが (convert_char_str_to_ushort_str)
	 * どのみち char の部分文字列を作る必要がある (API に渡す文字列は '\0' 終端が必要) ので
	 * それなら short の文字列を直接作った方が早い
	 */
	unsigned int length = end - start + 1; /* 位置から文字数を計算するので +1 */
	unsigned short* newStr;
	if (m_PasswordChar == m_NotPassword) {
		char* srcStr = m_AllText.getString() + start;
		newStr = CtTextField::newArray<unsigned short>(length + 1); /* 文字数 + '\0' の分 */
		for (unsigned int ii = 0; ii < length; ii++) {
			newStr[ii] = srcStr[ii]; /* parasoft-suppress BD-PB-NP */
		}
		newStr[length] = '\0';
	} else {
		newStr = generatePasswordStr<unsigned short>(length);
		if( m_VisibleText.passview == VisibleText::PASSWORD_CHAR_WITHOUT_LAST) {
			char* srcStr = m_AllText.getString() + start;
			newStr[length-1] = (unsigned short)srcStr[length-1];
		}
	}

	unsigned short int width, height;
	GDI_ERRCODE err = GDI_GetDrawRect(m_AllText.getFontStyle(), newStr, &width, &height);
	if (err != GDI_NO_ERROR) {
		CtDebugPrint(CtDbg, "error of GDI_GetDrawRect(%08x, %s)\n", m_AllText.getFontStyle(), newStr);
		width = 0;
	}
	CtTextField::deleteArray(newStr);
	return static_cast<int>(width);
}

/* 描画情報作成 */
void CtTextField::createDrawSide(Draw& _draw, const CtRegion& baseRegion, unsigned int txtStart, unsigned int txtEnd, int offset)
{
	_draw.string.start = txtStart;
	_draw.string.end = txtEnd;
	_draw.region.x = baseRegion.x + offset;
	_draw.region.width = getDrawWidth(_draw.string.start, _draw.string.end);

	CtRegion drawRegion = baseRegion;
	drawRegion.x = _draw.region.x;/* pgr0351 */
	drawRegion.width = _draw.region.width;/* pgr0351 */

	char* subStr;
	if (m_PasswordChar == m_NotPassword) {
		subStr = m_AllText.cloneSubString(_draw.string.start, _draw.string.end);
    } else {
		subStr = generatePasswordStr<char>(_draw.string.end - _draw.string.start + 1);
		if( m_VisibleText.passview == VisibleText::PASSWORD_CHAR_WITHOUT_LAST) {
			char* srcStr = m_AllText.getString() + _draw.string.start;
			subStr[_draw.string.end - _draw.string.start] = srcStr[_draw.string.end - _draw.string.start];
		}
	}

#if 1
	_draw.info.setString(subStr, m_AllText.getFontSet());
	CtTextField::deleteArray(subStr);
	_draw.info.setTrans(false);
	_draw.info.setRegion(drawRegion);
#else	
	CtString drawString(subStr, m_AllText.getFontSet());
	CtTextField::deleteArray(subStr);
	_draw.info.set(GDI_BLEND_MODE_SRC, drawRegion, drawString);
#endif
}

/* カーソル描画情報作成 */
void CtTextField::createDrawCursor(const CtRegion& baseRegion, int offset)
{
	/* ※現状、ブロック型のカーソルしか対応できてない */

	/* 前景・背景共通情報 */
	m_Cursor.draw.string.start = m_Cursor.pos;
	m_Cursor.draw.string.end = m_Cursor.pos;
	m_Cursor.draw.region.x = baseRegion.x + offset;
	m_Cursor.draw.region.width = getDrawWidth(m_Cursor.draw.string.start, m_Cursor.draw.string.end);

	/* 前景 (テキスト) の情報を作成 */
	CtFontSet fontset = m_AllText.getFontSet();
	CtColor frontColor;
	CtColor backColor;

	if (m_Cursor.isOnSideBlinking) { /* カーソル点滅で点灯しているとき */
		/* 前景と背景の色を交換 */
		frontColor = getParentColor();
		backColor = fontset.fontColor;
	} else {
		frontColor = fontset.fontColor;
		backColor = CtColor::NoColor; /* 表示しないので色設定しない */
	}

	char* subStr = m_AllText.cloneSubString(m_Cursor.draw.string.start, m_Cursor.draw.string.end);
	CtTextField::deleteArray(subStr);

	/* 背景の情報を作成 */
	CtRegion drawRegion = baseRegion;
	drawRegion.x = m_Cursor.draw.region.x;/* pgr0351 */
	drawRegion.width = m_Cursor.draw.region.width;/* pgr0351 */
#if 1
	//	m_Cursor.draw.rect.setRect(backColor);
	//	m_Cursor.draw.rect.setRegion(drawRegion);
	// 背景用のRECTをセット
	//	(GDI_BLEND_MODE_SRC, drawRegion, m_Cursor.draw.rect);
	m_Cursor.draw.info.background.setRegion(drawRegion);
	m_Cursor.draw.info.background.setColor(backColor);
	m_Cursor.draw.info.background.setTrans(false);
	// カーソルかぶり文字をセット
	m_Cursor.draw.info.foreground.setRegion(drawRegion);
	m_Cursor.draw.info.foreground.setString(subStr, fontset);
	m_Cursor.draw.info.foreground.setColor(frontColor);
	m_Cursor.draw.info.foreground.setTrans(false);
#else
	m_Cursor.draw.rect.setRect(drawRegion.x, drawRegion.y, drawRegion.width, drawRegion.height, backColor, 0, CtColor::NoColor);
	
	m_Cursor.draw.info.background.set(GDI_BLEND_MODE_SRC, drawRegion, m_Cursor.draw.rect);
	m_Cursor.draw.info.foreground.set(GDI_BLEND_MODE_SRC, drawRegion, drawString);
#endif
}

/* 見える範囲を設定 */
void CtTextField::initVisibleText(const CtRegion& region)
{
	/* ★内部文字列は、終端にカーソル描画用の ' '(\x20) を付加した形で運用する★ */

	unsigned int startPos = 0;
	unsigned int endPos = m_Cursor.pos;

	/* まず、最初の文字からカーソル位置までが描画範囲内かを見る */
	if (region.width > getDrawWidth(startPos, endPos)) {
		/* カーソル位置まで表示できる場合 */
		unsigned int MaxCurPos = m_AllText.getMaxCurPos();
		if (MaxCurPos) {		/* 最終カーソル位置の 1 文字前 */
			MaxCurPos--;
		}
		for (; endPos < MaxCurPos; endPos++) { /* カーソル以降の文字をできるだけ出す */
			if (region.width < getDrawWidth(startPos, endPos + 1)) {
				break;
			}
		}
	} else {
		/* カーソル位置が表示範囲外 */
		for (startPos = 1; startPos < endPos; startPos++) { /* startPos = 0 は検査済み (NG だからここに来た) */
			if (region.width > getDrawWidth(startPos, endPos)) {
				break;
			}
		}
	}
	m_VisibleText.start = startPos;
	m_VisibleText.end = endPos;
	m_VisibleText.state = VisibleText::READY;
}

/* 見える範囲を調整 */
void CtTextField::adjustVisibleText(VisibleText::Direction dir, unsigned int pos)
{
	if (m_VisibleText.state != VisibleText::READY) {
		CtDebugPrint(CtDbg, "error!! m_VisibleText not initialized.\n");
		return;
	}

	const CtRegion& region = getRegion();

	/* 片側を拡張し、反対側を表示文字数に応じて調整 */
	switch (dir) {
	case VisibleText::SHIFT_LEFT: /* start を減らしてから、 end を減らす */
		if (m_VisibleText.start) {
			m_VisibleText.start--;
		}
		while (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end)) {
			m_VisibleText.end--;
		}
		break;
	case VisibleText::SHIFT_RIGHT: /* end を増やした後、 start を増やす */
		if (m_VisibleText.end < m_AllText.getMaxCurPos()) {
			m_VisibleText.end++;
		}
		while (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end)) {
			m_VisibleText.start++;
		}
		break;
	case VisibleText::SET_END: /* end を pos で設定した後、 start を調整 */
		m_VisibleText.end = pos;
		if (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end)) {
			m_VisibleText.start++;
		}
		adjustVisibleText(VisibleText::ADJUST_START);
		break;
	case VisibleText::ADJUST_START: /* end は変えずに、 start を増減 */
		if (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end)) {
			m_VisibleText.start++;
			while (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end)) {
				m_VisibleText.start++;
			}
		} else {
			for (; m_VisibleText.start > 0; m_VisibleText.start--) {
				if (region.width < getDrawWidth(m_VisibleText.start - 1, m_VisibleText.end)) {
					break;
				}
			}
		}
		break;
	case VisibleText::ADJUST_END: /* start は変えずに、 end を増減 */
		if (!m_VisibleText.end) {
			break;
		}
		if (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end)) {
			for (; m_VisibleText.end > 0; m_VisibleText.end--) {
				if (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end - 1)) {
					break;
				}
			}
		} else {
			while (region.width > getDrawWidth(m_VisibleText.start, m_VisibleText.end + 1)) {
				m_VisibleText.end++;
			}
		}
		break;
	default:					/* 想定外のときは何もしない */
		CtDebugPrint(CtDbg, "parameter error!! dir=%d\n", dir);
		return;
	}
}

/**
 * パスワード用文字列生成
 * 生成した文字列は呼び出し側で解放すること!!
 */
template <typename TYPE>
TYPE* CtTextField::generatePasswordStr(unsigned int num)
{
	TYPE* newStr = CtTextField::newArray<TYPE>(num + 1); /* '\0' の分増やす */
	for (unsigned int ii = 0; ii < num; ii++) {
		newStr[ii] = m_PasswordChar; /* parasoft-suppress BD-PB-NP */
	}
	newStr[num] = '\0';			/* parasoft-suppress BD-PB-NP */
	return newStr;
}

/* カーソル点滅制御 */
void CtTextField::blinkCursor(bool isOn)
{
	if (isOn) {
		bool result = CtTimer::getInstance()->startCyclic(NULL, 500, this);
		if (result != true) {
			CtDebugPrint(CtDbg, "fail cyclic timer start\n");
		}
	} else {
		CtTimer::getInstance()->stopCyclic(CT_TEXT_FIELD_TIMER_ID, this);
	}
	m_Cursor.isOnSideBlinking = true; /* カーソルが消えたままにならないよう点灯状態にしておく */
}

/* タイマー処理 (カーソル点滅用) */
bool CtTextField::handleTimerEvent(const CtEventTimer& Timer)
{
#if 0
	if (m_Cursor.shape != ShapeNone) { /* カーソルなし時は無効 */
		m_Cursor.isOnSideBlinking = !m_Cursor.isOnSideBlinking;
		setInvalidate();
	}
	return true;
#else
	return false;
#endif
}

/* テキスト編集用クラス */
CtTextField::AdjustText::AdjustText() :
	m_pStr(NULL),
	m_Length(0),
	m_FontSet(CtFontSet(FontTypeNormal))
{
	init(NULL);
}

CtTextField::AdjustText::AdjustText(const char* str, const CtFontSet& fontset) :
	m_pStr(NULL),
	m_Length(0),
	m_FontSet(fontset)
{
	init(str);
}

CtTextField::AdjustText::~AdjustText()
{
	CtTextField::deleteArray(m_pStr);
}

/* 共通初期化処理 */
void CtTextField::AdjustText::init(const char* str)
{
	/**
	 * ★内部文字列は、終端にカーソル描画用の ' '(\x20) を付加した形で運用する★
	 * ★'\0' 終端ではないので注意!!★
	 * m_Length は、『末尾の ' ' を含まない文字数』を保持する
	 */
	if (str == NULL)	m_Length = 0;
	else				m_Length = calcLength(str);
	m_pStr = CtTextField::newArray<char>(m_Length + 1); /* 末尾の ' ' の分 */
	if (str) {
		memcpy(m_pStr, str, m_Length);
	}
	m_pStr[m_Length] = ' ';		/* parasoft-suppress BD-PB-NP */
	m_FontSet.fontStyle.auto_adjust = AUTO_ADJUST_DISABLE; /* フォントサイズを固定にする */
	m_FontSet.fontStyle.halign = HALIGN_LEFT; /* 左詰めしか扱えない */
}


void CtTextField::AdjustText::insertChar(unsigned int insertPos, const char character)
{
	/* ★内部文字列は、終端にカーソル描画用の ' '(\x20) を付加した形で運用する★ (★'\0' 終端ではない!!★) */

	if (insertPos > m_Length) {
		CtDebugPrint(CtDbg, "Parameter error!! insertPos=%d strlen=%d\n", insertPos, m_Length);
		insertPos = m_Length;
	}

	char* newStr = CtTextField::newArray<char>(m_Length + 2); /* + 挿入する文字分 + ' ' */
	memcpy(newStr, m_pStr, insertPos);	   /* 元の文字列から前半をコピー */
	newStr[insertPos] = character;		   /* 挿入 */ /* parasoft-suppress BD-PB-NP */
	memcpy(newStr + insertPos + 1, m_pStr + insertPos, m_Length - insertPos); /* 後半をコピー */
	newStr[m_Length + 1] = ' ';
	setString(newStr);
	m_Length++;
}

void CtTextField::AdjustText::deleteChar(unsigned int deletePos)
{
	/* ★内部文字列は、終端にカーソル描画用の ' '(\x20) を付加した形で運用する★ (★'\0' 終端ではない!!★) */

	if (deletePos >= m_Length) {
		CtDebugPrint(CtDbg, "Parameter error!! deletePos=%d strlen=%d\n", deletePos, m_Length);
		if (m_Length != 0) {
			deletePos = m_Length - 1;
		}
	}

	if (m_Length == 0) {		/* 消す文字がない */
		return;
	}

	char* newStr = CtTextField::newArray<char>(m_Length); /* - 削除する文字分 + ' ' */
	memcpy(newStr, m_pStr, deletePos); /* 元の文字列の前半をコピー */
	memcpy(newStr + deletePos, m_pStr + deletePos + 1, m_Length - deletePos - 1); /* 後半をコピー */
	newStr[m_Length - 1] = ' ';	/* parasoft-suppress BD-PB-NP */
	setString(newStr);
	m_Length--;
}

/**
 * 内部文字列 (' ' ターミネート含む) の start から end までを複製して返す
 * ※複製した文字列は呼び出し側で解放すること!!
 */
char* CtTextField::AdjustText::cloneSubString(unsigned int start, unsigned int end)
{
	if ((m_Length < start) || (m_Length < end) || (start > end)) {
		CtDebugPrint(CtDbg, "parameter error!! strlen=%d start=%d end=%d\n", m_Length, start, end);
		return NULL;
	}

	unsigned int copyLength = end - start + 1; /* 文字数 */
	char* newStr = CtTextField::newArray<char>(copyLength + 1); /* 文字数 + '\0' の分 */
	memcpy(newStr, m_pStr + start, copyLength);
	newStr[copyLength] = '\0';	/* parasoft-suppress BD-PB-NP */
	return newStr;
}

/* 文字列の長さを返す */
unsigned int CtTextField::AdjustText::calcLength(const char* str)
{
	return str ? get_char_string_length(str) : 0; /* str が NULL のときは API 使えない (使ってはいけない) */
}
