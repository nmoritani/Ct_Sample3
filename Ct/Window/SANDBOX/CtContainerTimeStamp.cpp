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
	
	// ��\���̏ꍇ�͉������Ȃ�
	if (m_Disp == CtTsDispOff) {
		// AplParam��OFF�̏ꍇ�AAVC����X�^�[�g�����Ȃ��H�H�H
		return false;
	}

	// �����ω����͍č\�z
	if (m_Month != date.Month) {
		createDrawablesMonth();
	}

	// ���t����h�����u��ID�֕ϊ�
	DateTimeDrawabales dateDrawables = getDateTimeDrawables(date);

	int idx = 0;

#if 1
	// ���x���ɑ΂��ăh�����u����ݒ�
	if (m_Disp & CtTsDispDate) {
		// ���t
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
		// ���t,�����Ԃ̃X�y�[�X
		if (m_Disp & CtTsDispDate) m_Label[idx++]->setDrawable(m_Drawables.Space);
		// ����
		for (int i = 0; i < 2; i++) m_Label[idx++]->setDrawable(dateDrawables.Hour[i]);
		m_Label[idx++]->setDrawable(m_Drawables.Separator);
		for (int i = 0; i < 2; i++) m_Label[idx++]->setDrawable(dateDrawables.Min[i]);
		m_Label[idx++]->setDrawable(m_Drawables.Separator);
		for (int i = 0; i < 2; i++) m_Label[idx++]->setDrawable(dateDrawables.Sec[i]);
	}
#endif

	// ����`�悵���h�����u����ێ�
	m_DateDrawables = dateDrawables;

	return true;
}

/*
* �������x���̃T�C�Y����
*/
CtSize CtContainerTimeStamp::getLabelSize()
{
	CtSize ret;

	// ����
	// �@�S�̂�50%
	ret.height = (short)(0.5f * m_Size.height);

	// ��
	// �S�̂̍��E��0.5�����̋󔒂�����
	int len = getTimeStampLength() + 1;	// 1�͍��E��0.5*2
	ret.width = m_Size.width / len;

	return ret;
}

CtContainerTimeStamp::CtDateFormat CtContainerTimeStamp::getFormat()
{
	// @todo aplparam�Ή�
	return CtDateFormatYMD;
}

CtContainerTimeStamp::CtTsDisp CtContainerTimeStamp::getDispMode()
{
	// @todo aplparam�Ή�
	return CtTsDispDateTime;
}

/*
 �^�C���X�^���v�Ƃ��ĕ`�悷�镶���񒷂��擾
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
 createContainer����Layout�쐬����
*/
CtLayout* CtContainerTimeStamp::createLayout()
{
	CtHLayout *pLayout = new CtHLayout(m_Size, CtColor::Blue);
	CtSize labelSize = getLabelSize();
	int labelCount = getTimeStampLength();

	// layout���[��0.5�������̃X�y�[�X�ǉ�
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
 createContainer�����h�����u���쐬����(���l�ƋL��)
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
 �h�����u���쐬����(�����̃A���t�@�x�b�g)
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
  ���ݎ�������DateTimeDrawabales(�`�悷��h�����u��)�ւ̕ϊ�
*/
CtContainerTimeStamp::DateTimeDrawabales CtContainerTimeStamp::getDateTimeDrawables(const SYS_DATE_TIME &date)
{
	CtContainerTimeStamp::DateTimeDrawabales ret;

	// ���݂̓��t,��������`�悷��h�����u��ID��I��
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
