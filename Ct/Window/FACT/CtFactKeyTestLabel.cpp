#include "CtFactKeyTestLabel.h"

CtFactKeyTestLabel::CtFactKeyTestLabel(CtWindowContentsFactKey::FactKeyTestItem *item)
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignRight, CtColor::White);
	char str[100] = { 0 };
	m_state1 = new CtLabel(CtSize(30, 30), CtRect());
	m_state2 = new CtLabel(CtSize(30, 30), CtRect());
	m_state3 = new CtLabel(CtSize(30, 30), CtRect());
	m_state4 = new CtLabel(CtSize(30, 30), CtRect());

	if (NULL == item) {
		UpdateState(CtWindowContentsFactKey::KEYRECT_INVISIBLE, CtWindowContentsFactKey::KEYRECT_INVISIBLE, CtWindowContentsFactKey::KEYRECT_INVISIBLE, CtWindowContentsFactKey::KEYRECT_INVISIBLE);
	} else {
		if (NULL != item->name) {
			sprintf(str, "%s", item->name);
		}
		UpdateState(item->state1, item->state2, item->state3, item->state4);
	}

	m_label_str = new CtLabel(str, fSet);

	//検査用項目の初期化
	m_str[0] = 0x00;
	m_state1_color = CtWindowContentsFactKey::KEYRECT_INVISIBLE;
	m_state2_color = CtWindowContentsFactKey::KEYRECT_INVISIBLE;
	m_state3_color = CtWindowContentsFactKey::KEYRECT_INVISIBLE;
	m_state4_color = CtWindowContentsFactKey::KEYRECT_INVISIBLE;
}

CtFactKeyTestLabel::~CtFactKeyTestLabel()
{
	if(NULL != m_label_str)
	{
		delete m_label_str;
		m_label_str = NULL;	
	}
	if(NULL != m_state1)
	{
		delete m_state1;
		m_state1 = NULL;
	}
	if(NULL != m_state2)
	{
		delete m_state2;
		m_state2 = NULL;
	}
	if (NULL != m_state3)
	{
		delete m_state3;
		m_state3 = NULL;
	}
	if (NULL != m_state4)
	{
		delete m_state4;
		m_state4 = NULL;
	}
}

CtLayout * CtFactKeyTestLabel::CreateLayout()
{
	CtHLayout *layout = new CtHLayout();
	layout->addStretch(10);
	layout->addWidget(m_label_str, AlignRight, 120);	//FACTの項目名
	layout->addStretch(10);
	layout->addWidget(m_state1, AlignLeft, 30);			//■(状態表示1)
	layout->addWidget(m_state2, AlignLeft, 30);			//■(状態表示2)
	layout->addWidget(m_state3, AlignLeft, 30);			//■(状態表示3)
	layout->addWidget(m_state4, AlignLeft, 30);			//■(状態表示3)
	layout->addStretch(30);

	return layout;
}

void CtFactKeyTestLabel::setItem(CtWindowContentsFactKey::FactKeyTestItem *item)
{
	if ((item == NULL) || (item->name == NULL)) {
		m_str[0] = 0x00;
		m_state1_color = CtWindowContentsFactKey::KEYRECT_INVISIBLE;
		m_state2_color = CtWindowContentsFactKey::KEYRECT_INVISIBLE;
		m_state3_color = CtWindowContentsFactKey::KEYRECT_INVISIBLE;
		m_state4_color = CtWindowContentsFactKey::KEYRECT_INVISIBLE;
		return;
	}

	{
		if (0x00 == item->name[0]) {
			m_str[0] = 0x20;
			m_str[1] = 0x00;
		} else {
			int len = 0;
			for (len = 0; len < 99; len++) {	//NULLを除いて99文字までコピーする
				if (0x00 == item->name[len]) {
					break;
				}
				m_str[len] = item->name[len];	//文字列終端にNULLセット
			}
			m_str[len] = 0x00;
		}
	}

	m_state1_color = item->state1;
	m_state2_color = item->state2;
	m_state3_color = item->state3;
	m_state4_color = item->state4;
}

void CtFactKeyTestLabel::UpdateItem()
{
	m_label_str->setText(m_str);
	setState(m_state1, m_state1_color);
	setState(m_state2, m_state2_color);
	setState(m_state3, m_state3_color);
	setState(m_state4, m_state4_color);
}

void CtFactKeyTestLabel::UpdateState(KeyState state1, KeyState state2, KeyState state3, KeyState state4)
{
	setState(m_state1, state1);
	setState(m_state2, state2);
	setState(m_state3, state3);
	setState(m_state4, state4);
}


void CtFactKeyTestLabel::setState(CtLabel *stateLabel, KeyState value)
{
    if(NULL == stateLabel){
        return;
    }

	switch (value) {
	case CtWindowContentsFactKey::KEYRECT_INVISIBLE:
		stateLabel->setColor(CtColor::Black);
		break;

	case CtWindowContentsFactKey::KEYRECT_WHITE:
		stateLabel->setColor(CtColor::White);
		break;

	case CtWindowContentsFactKey::KEYRECT_GREEN:
		stateLabel->setColor(CtColor::Green);
		break;

	case CtWindowContentsFactKey::KEYRECT_RED:
		stateLabel->setColor(CtColor::Red);
		break;

	default:
		break;
	}
}
