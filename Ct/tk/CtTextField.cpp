/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtTextField
 */

#include "CtTextField.h"

const CtFontSet CtTextField::m_DefaultFontSet(FontTypeNormal);
const CtAlign CtTextField::m_DefaultAlign = AlignLeft;
const char CtTextField::m_NotPassword = '\0';

/* �R���X�g���N�^ */
/* CtLabel �֓n�������� (�\�����镶����) �́A�\���͈͂��v�Z����O�Ȃ̂ŋ󕶎���ŏ��������Ă��� */
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

/* �f�X�g���N�^ */
CtTextField::~CtTextField()
{
	CtTextField::deleteArray(m_pText);
}

/* �R���X�g���N�^���������邽�߁A���ʂ̏������������܂Ƃ߂� */
void CtTextField::init()
{
	setClassType(CtClassType_TextField);

	/* �J�[�\���̏����� */
	setInitParam(DefaultCursor);
	setInitParam(DefaultShape);
	m_Cursor.isOnSideBlinking = true;

	/* �\�������͈͂̏����� */
	m_VisibleText.start = 0;
	m_VisibleText.end = 0;
	m_VisibleText.state = VisibleText::INITIALIZE;
	m_VisibleText.passview = VisibleText::PASSWORD_CHAR_ALL;

	/* m_pDrawInfo ��p�����`��͂��Ȃ� */
	CtTextField::deleteArray(m_pDrawInfo);
	m_pDrawInfo = NULL;
}

/* �p�����[�^�����ݒ� (�J�[�\���ʒu) */
void CtTextField::setInitParam(InitialCursorPos curPos)
{
	m_Cursor.pos = (curPos == CursorEnd) ? m_AllText.getMaxCurPos() : 0;
}

/* �p�����[�^�����ݒ� (�J�[�\���`��) */
void CtTextField::setInitParam(CursorShape curShape)
{
	m_Cursor.shape = curShape;
	blinkCursor((m_Cursor.shape == ShapeNone) ? false : true);
}

/* �p�����[�^�����ݒ� (�p�X���[�h�\��) */
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

	if (m_VisibleText.state != VisibleText::READY) { /* �ŏ��̈��̂ݕK�v�B getRegion ���ł���悤�ɂȂ��Ă�����{ */
		initVisibleText(getRegion());
	}

	CtRegion baseRegion = getRegion(Screen);

	if (m_Cursor.shape != ShapeNone) {
		/**
		 *                    |���\���͈́�|
		 * m_AllText:     �`�a|�b�c�d�e�f�g|�h�i
		 *                    |��  ��    ��|
		 * m_Cursor:          |�b  pos   �b|
		 * m_VisibleText:     |start    end|
		 *                    |�����́�����|
		 * m_pDrawInfo:       |left : right|
		 *                         Cursor
		 */
		/* �J�[�\�����̕`������쐬 (�J�[�\�����擪�Ȃ�쐬�s�v) */
		if (m_Cursor.pos > m_VisibleText.start) {
			createDrawSide(m_DrawLeft, baseRegion, m_VisibleText.start, m_Cursor.pos - 1, 0);
			m_DrawLeft.info.setClip(Clip);
			m_DrawLeft.info.setTrans(isTrans());
			m_DrawLeft.info.draw();
		} else {
			/* Region �͌�̌v�Z�ŕK�v�Ȃ̂Őݒ肵�Ă��� */
			m_DrawLeft.region.x = baseRegion.x;
			m_DrawLeft.region.width = 0;
		}

		/* �J�[�\���`������쐬 */
		createDrawCursor(baseRegion, m_DrawLeft.region.width);

		/* �J�[�\���E�̕`������쐬 (�J�[�\���������̏ꍇ�͍쐬�s�v) */
		if (m_Cursor.pos < m_VisibleText.end) {
			createDrawSide(m_DrawRight, baseRegion, m_Cursor.pos + 1, m_VisibleText.end, m_DrawLeft.region.width + m_Cursor.draw.region.width);
			m_DrawRight.info.setClip(Clip);
			m_DrawRight.info.setTrans(isTrans());
			m_DrawRight.info.draw();
		}
		/* �J�[�\���n�͍Ō�ɒǉ� */
		m_Cursor.draw.info.background.setClip(Clip);
		m_Cursor.draw.info.background.setTrans(isTrans());
		m_Cursor.draw.info.foreground.setClip(Clip);
		m_Cursor.draw.info.foreground.setTrans(isTrans());
		m_Cursor.draw.info.background.draw();
		m_Cursor.draw.info.foreground.draw();
	} else {
		/* �J�[�\����`�悵�Ȃ��ꍇ */
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

/* �ҏW��̕������Ԃ� */
char* CtTextField::getString()
{
	/**
	 * m_AllText �Ǘ��̕����񖖔��� ' ' �Ȃ̂ŁA '\0' �ɕύX����K�v������B
	 * �Ȃ̂ŁA�V�K�ɗ̈������ĕԂ��K�v������B������̈�̓f�X�g���N�^�ŉ��
	 */
	if (m_pText) {				/* ���ɍ���Ă������������Ă���쐬 */
		CtTextField::deleteArray(m_pText);
	}
	unsigned int arraySize = m_AllText.getLength(); /* ' ' ���܂߂���������Ԃ� */
	unsigned int strLength = arraySize - 1;
	m_pText = CtTextField::newArray<char>(arraySize);
	memcpy(m_pText, m_AllText.getString(), strLength);
	m_pText[strLength] = '\0';	/* '\0' �^�[�~�l�[�g */ /* parasoft-suppress BD-PB-NP */
	return m_pText;
}

/* �J�[�\���ʒu�� 1 �����}�� (INS) */
void CtTextField::insertChar(const char character)
{
	m_AllText.insertChar(m_Cursor.pos, character);
	m_Cursor.pos++;	/* �������������Ă�̂ŁA�J�[�\�������������z���邱�Ƃ͂Ȃ� */
	m_VisibleText.passview = VisibleText::PASSWORD_CHAR_WITHOUT_LAST;

	/* �\���͈͂̒��� */
	if (getDrawWidth(m_VisibleText.start, m_VisibleText.end + 1) <= getRegion().width) {
		adjustVisibleText(VisibleText::SET_END, m_VisibleText.end + 1);
	} else {
		if (m_Cursor.pos >= m_VisibleText.end) { /* �J�[�\���ʒu==�E�[�̏ꍇ�� start ���𒲐� */
			adjustVisibleText(VisibleText::SET_END, m_Cursor.pos);
		} else {
			adjustVisibleText(VisibleText::ADJUST_END);
		}
	}
	setInvalidate();
}

/* �J�[�\���ʒu�̕��������� (DEL) */
void CtTextField::deleteChar()
{
	if ((m_Cursor.pos != 0) && (m_Cursor.pos >= m_AllText.getMaxCurPos())) { /* �J�[�\������ԍŌ�̋󔒂�I�����Ă���Ƃ��͈ꕶ���O�ɖ߂��č폜 */
		m_Cursor.pos--;
	}
	m_VisibleText.passview = VisibleText::PASSWORD_CHAR_ALL;
	m_AllText.deleteChar(m_Cursor.pos);

	/* �\���͈͂̒��� */
	if (m_VisibleText.end > m_AllText.getMaxCurPos()) {
		adjustVisibleText(VisibleText::SET_END, m_AllText.getMaxCurPos());
	} else {
		adjustVisibleText(VisibleText::ADJUST_START);
	}
	setInvalidate();
}

/* �J�[�\���ʒu�̈�O���������� (BS) */
void CtTextField::backspaceChar()
{
	if (m_Cursor.pos > 0) { /* �ꕶ���O�ɖ߂��č폜 */
		m_Cursor.pos--;
	} else {
		return;
	}
	m_VisibleText.passview = VisibleText::PASSWORD_CHAR_ALL;
	m_AllText.deleteChar(m_Cursor.pos);

	/* �\���͈͂̒��� */
	if (m_VisibleText.end > m_AllText.getMaxCurPos()) {
		adjustVisibleText(VisibleText::SET_END, m_AllText.getMaxCurPos());
	} else {
		adjustVisibleText(VisibleText::ADJUST_START);
	}
	setInvalidate();
}

/* �J�[�\����i�߂� */
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

/* �J�[�\����߂� */
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

/* �e�L�X�g�͈͂̕`�敝��Ԃ� */
int CtTextField::getDrawWidth(unsigned int start, unsigned int end)
{
	unsigned int max = m_AllText.getMaxCurPos();
	if ((max < start) || (max < end) || (start > end)) {
		CtDebugPrint(CtDbg, "parameter error!! max=%d start=%d end=%d\n", max, start, end);
		return 0;
	}

	/**
	 * GDI �ɂ� short �̕����񂪕K�v
	 * char �̕������ short �̕�����ɕϊ����� API �����邪 (convert_char_str_to_ushort_str)
	 * �ǂ݂̂� char �̕�������������K�v������ (API �ɓn��������� '\0' �I�[���K�v) �̂�
	 * ����Ȃ� short �̕�����𒼐ڍ������������
	 */
	unsigned int length = end - start + 1; /* �ʒu���當�������v�Z����̂� +1 */
	unsigned short* newStr;
	if (m_PasswordChar == m_NotPassword) {
		char* srcStr = m_AllText.getString() + start;
		newStr = CtTextField::newArray<unsigned short>(length + 1); /* ������ + '\0' �̕� */
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

/* �`����쐬 */
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

/* �J�[�\���`����쐬 */
void CtTextField::createDrawCursor(const CtRegion& baseRegion, int offset)
{
	/* ������A�u���b�N�^�̃J�[�\�������Ή��ł��ĂȂ� */

	/* �O�i�E�w�i���ʏ�� */
	m_Cursor.draw.string.start = m_Cursor.pos;
	m_Cursor.draw.string.end = m_Cursor.pos;
	m_Cursor.draw.region.x = baseRegion.x + offset;
	m_Cursor.draw.region.width = getDrawWidth(m_Cursor.draw.string.start, m_Cursor.draw.string.end);

	/* �O�i (�e�L�X�g) �̏����쐬 */
	CtFontSet fontset = m_AllText.getFontSet();
	CtColor frontColor;
	CtColor backColor;

	if (m_Cursor.isOnSideBlinking) { /* �J�[�\���_�łœ_�����Ă���Ƃ� */
		/* �O�i�Ɣw�i�̐F������ */
		frontColor = getParentColor();
		backColor = fontset.fontColor;
	} else {
		frontColor = fontset.fontColor;
		backColor = CtColor::NoColor; /* �\�����Ȃ��̂ŐF�ݒ肵�Ȃ� */
	}

	char* subStr = m_AllText.cloneSubString(m_Cursor.draw.string.start, m_Cursor.draw.string.end);
	CtTextField::deleteArray(subStr);

	/* �w�i�̏����쐬 */
	CtRegion drawRegion = baseRegion;
	drawRegion.x = m_Cursor.draw.region.x;/* pgr0351 */
	drawRegion.width = m_Cursor.draw.region.width;/* pgr0351 */
#if 1
	//	m_Cursor.draw.rect.setRect(backColor);
	//	m_Cursor.draw.rect.setRegion(drawRegion);
	// �w�i�p��RECT���Z�b�g
	//	(GDI_BLEND_MODE_SRC, drawRegion, m_Cursor.draw.rect);
	m_Cursor.draw.info.background.setRegion(drawRegion);
	m_Cursor.draw.info.background.setColor(backColor);
	m_Cursor.draw.info.background.setTrans(false);
	// �J�[�\�����Ԃ蕶�����Z�b�g
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

/* ������͈͂�ݒ� */
void CtTextField::initVisibleText(const CtRegion& region)
{
	/* ������������́A�I�[�ɃJ�[�\���`��p�� ' '(\x20) ��t�������`�ŉ^�p���遚 */

	unsigned int startPos = 0;
	unsigned int endPos = m_Cursor.pos;

	/* �܂��A�ŏ��̕�������J�[�\���ʒu�܂ł��`��͈͓��������� */
	if (region.width > getDrawWidth(startPos, endPos)) {
		/* �J�[�\���ʒu�܂ŕ\���ł���ꍇ */
		unsigned int MaxCurPos = m_AllText.getMaxCurPos();
		if (MaxCurPos) {		/* �ŏI�J�[�\���ʒu�� 1 �����O */
			MaxCurPos--;
		}
		for (; endPos < MaxCurPos; endPos++) { /* �J�[�\���ȍ~�̕������ł��邾���o�� */
			if (region.width < getDrawWidth(startPos, endPos + 1)) {
				break;
			}
		}
	} else {
		/* �J�[�\���ʒu���\���͈͊O */
		for (startPos = 1; startPos < endPos; startPos++) { /* startPos = 0 �͌����ς� (NG �����炱���ɗ���) */
			if (region.width > getDrawWidth(startPos, endPos)) {
				break;
			}
		}
	}
	m_VisibleText.start = startPos;
	m_VisibleText.end = endPos;
	m_VisibleText.state = VisibleText::READY;
}

/* ������͈͂𒲐� */
void CtTextField::adjustVisibleText(VisibleText::Direction dir, unsigned int pos)
{
	if (m_VisibleText.state != VisibleText::READY) {
		CtDebugPrint(CtDbg, "error!! m_VisibleText not initialized.\n");
		return;
	}

	const CtRegion& region = getRegion();

	/* �Б����g�����A���Α���\���������ɉ����Ē��� */
	switch (dir) {
	case VisibleText::SHIFT_LEFT: /* start �����炵�Ă���A end �����炷 */
		if (m_VisibleText.start) {
			m_VisibleText.start--;
		}
		while (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end)) {
			m_VisibleText.end--;
		}
		break;
	case VisibleText::SHIFT_RIGHT: /* end �𑝂₵����A start �𑝂₷ */
		if (m_VisibleText.end < m_AllText.getMaxCurPos()) {
			m_VisibleText.end++;
		}
		while (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end)) {
			m_VisibleText.start++;
		}
		break;
	case VisibleText::SET_END: /* end �� pos �Őݒ肵����A start �𒲐� */
		m_VisibleText.end = pos;
		if (region.width < getDrawWidth(m_VisibleText.start, m_VisibleText.end)) {
			m_VisibleText.start++;
		}
		adjustVisibleText(VisibleText::ADJUST_START);
		break;
	case VisibleText::ADJUST_START: /* end �͕ς����ɁA start �𑝌� */
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
	case VisibleText::ADJUST_END: /* start �͕ς����ɁA end �𑝌� */
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
	default:					/* �z��O�̂Ƃ��͉������Ȃ� */
		CtDebugPrint(CtDbg, "parameter error!! dir=%d\n", dir);
		return;
	}
}

/**
 * �p�X���[�h�p�����񐶐�
 * ��������������͌Ăяo�����ŉ�����邱��!!
 */
template <typename TYPE>
TYPE* CtTextField::generatePasswordStr(unsigned int num)
{
	TYPE* newStr = CtTextField::newArray<TYPE>(num + 1); /* '\0' �̕����₷ */
	for (unsigned int ii = 0; ii < num; ii++) {
		newStr[ii] = m_PasswordChar; /* parasoft-suppress BD-PB-NP */
	}
	newStr[num] = '\0';			/* parasoft-suppress BD-PB-NP */
	return newStr;
}

/* �J�[�\���_�Ő��� */
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
	m_Cursor.isOnSideBlinking = true; /* �J�[�\�����������܂܂ɂȂ�Ȃ��悤�_����Ԃɂ��Ă��� */
}

/* �^�C�}�[���� (�J�[�\���_�ŗp) */
bool CtTextField::handleTimerEvent(const CtEventTimer& Timer)
{
#if 0
	if (m_Cursor.shape != ShapeNone) { /* �J�[�\���Ȃ����͖��� */
		m_Cursor.isOnSideBlinking = !m_Cursor.isOnSideBlinking;
		setInvalidate();
	}
	return true;
#else
	return false;
#endif
}

/* �e�L�X�g�ҏW�p�N���X */
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

/* ���ʏ��������� */
void CtTextField::AdjustText::init(const char* str)
{
	/**
	 * ������������́A�I�[�ɃJ�[�\���`��p�� ' '(\x20) ��t�������`�ŉ^�p���遚
	 * ��'\0' �I�[�ł͂Ȃ��̂Œ���!!��
	 * m_Length �́A�w������ ' ' ���܂܂Ȃ��������x��ێ�����
	 */
	if (str == NULL)	m_Length = 0;
	else				m_Length = calcLength(str);
	m_pStr = CtTextField::newArray<char>(m_Length + 1); /* ������ ' ' �̕� */
	if (str) {
		memcpy(m_pStr, str, m_Length);
	}
	m_pStr[m_Length] = ' ';		/* parasoft-suppress BD-PB-NP */
	m_FontSet.fontStyle.auto_adjust = AUTO_ADJUST_DISABLE; /* �t�H���g�T�C�Y���Œ�ɂ��� */
	m_FontSet.fontStyle.halign = HALIGN_LEFT; /* ���l�߂��������Ȃ� */
}


void CtTextField::AdjustText::insertChar(unsigned int insertPos, const char character)
{
	/* ������������́A�I�[�ɃJ�[�\���`��p�� ' '(\x20) ��t�������`�ŉ^�p���遚 (��'\0' �I�[�ł͂Ȃ�!!��) */

	if (insertPos > m_Length) {
		CtDebugPrint(CtDbg, "Parameter error!! insertPos=%d strlen=%d\n", insertPos, m_Length);
		insertPos = m_Length;
	}

	char* newStr = CtTextField::newArray<char>(m_Length + 2); /* + �}�����镶���� + ' ' */
	memcpy(newStr, m_pStr, insertPos);	   /* ���̕����񂩂�O�����R�s�[ */
	newStr[insertPos] = character;		   /* �}�� */ /* parasoft-suppress BD-PB-NP */
	memcpy(newStr + insertPos + 1, m_pStr + insertPos, m_Length - insertPos); /* �㔼���R�s�[ */
	newStr[m_Length + 1] = ' ';
	setString(newStr);
	m_Length++;
}

void CtTextField::AdjustText::deleteChar(unsigned int deletePos)
{
	/* ������������́A�I�[�ɃJ�[�\���`��p�� ' '(\x20) ��t�������`�ŉ^�p���遚 (��'\0' �I�[�ł͂Ȃ�!!��) */

	if (deletePos >= m_Length) {
		CtDebugPrint(CtDbg, "Parameter error!! deletePos=%d strlen=%d\n", deletePos, m_Length);
		if (m_Length != 0) {
			deletePos = m_Length - 1;
		}
	}

	if (m_Length == 0) {		/* �����������Ȃ� */
		return;
	}

	char* newStr = CtTextField::newArray<char>(m_Length); /* - �폜���镶���� + ' ' */
	memcpy(newStr, m_pStr, deletePos); /* ���̕�����̑O�����R�s�[ */
	memcpy(newStr + deletePos, m_pStr + deletePos + 1, m_Length - deletePos - 1); /* �㔼���R�s�[ */
	newStr[m_Length - 1] = ' ';	/* parasoft-suppress BD-PB-NP */
	setString(newStr);
	m_Length--;
}

/**
 * ���������� (' ' �^�[�~�l�[�g�܂�) �� start ���� end �܂ł𕡐����ĕԂ�
 * ����������������͌Ăяo�����ŉ�����邱��!!
 */
char* CtTextField::AdjustText::cloneSubString(unsigned int start, unsigned int end)
{
	if ((m_Length < start) || (m_Length < end) || (start > end)) {
		CtDebugPrint(CtDbg, "parameter error!! strlen=%d start=%d end=%d\n", m_Length, start, end);
		return NULL;
	}

	unsigned int copyLength = end - start + 1; /* ������ */
	char* newStr = CtTextField::newArray<char>(copyLength + 1); /* ������ + '\0' �̕� */
	memcpy(newStr, m_pStr + start, copyLength);
	newStr[copyLength] = '\0';	/* parasoft-suppress BD-PB-NP */
	return newStr;
}

/* ������̒�����Ԃ� */
unsigned int CtTextField::AdjustText::calcLength(const char* str)
{
	return str ? get_char_string_length(str) : 0; /* str �� NULL �̂Ƃ��� API �g���Ȃ� (�g���Ă͂����Ȃ�) */
}
