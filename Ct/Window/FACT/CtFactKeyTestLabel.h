/**
*  Copyright (c) 2018 Persol AVC Technology.
*  Element:			CtFactKeyTestLabel
*/


#ifndef __CtFactKeyTestLabel_H__
#define __CtFactKeyTestLabel_H__

#include "CtWindowCommon.h"
#include "CtWindowContentsFactKey.h"

class CtFactKeyTestLabel : public CtObject
{
public:
	typedef CtWindowContentsFactKey::KEYRECT_STATE KeyState;

	CtFactKeyTestLabel(CtWindowContentsFactKey::FactKeyTestItem *item);
	~CtFactKeyTestLabel();
	CtLayout * CreateLayout();
	void setItem(CtWindowContentsFactKey::FactKeyTestItem * item);
	void UpdateItem();
	void UpdateState(KeyState state1, KeyState state2, KeyState state3, KeyState state4);


private:
	CtLabel *m_label_str;

	CtLabel *m_state1;
	CtLabel *m_state2;
	CtLabel *m_state3;
	CtLabel *m_state4;

	CtWindowContentsFactKey::FactKeyTestItem m_item;

	char m_str[100];
	KeyState m_state1_color;
	KeyState m_state2_color;
	KeyState m_state3_color;
	KeyState m_state4_color;

private:
	void setState(CtLabel * stateLabel, KeyState value);
};

#endif
