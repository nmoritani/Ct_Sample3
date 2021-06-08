#include "CtWindowContentsFactKey.h"

CtWindowContentsFactKey::CtWindowContentsFactKey(const CtWindowID WindowID) :
	CtWindowContents(WindowID)
{
	InitKeyTestItem();
}

CtWindowContentsFactKey::~CtWindowContentsFactKey()
{
}

void CtWindowContentsFactKey::InitKeyTestItem()
{
	//キーテスト用項目の初期化
	int max = GetKeyTestItemCountMax();
	int index;
	for (index = 0; index < max; index++) {
		setKeyTestItem(index, NULL, KEYRECT_INVISIBLE, KEYRECT_INVISIBLE, KEYRECT_INVISIBLE);
	}

	//タッチテスト用項目の初期化
	m_TouchPos.Pos = FACT_TOUCH__POS_LEFT_NONE;
	m_TouchPos.x = 0;
	m_TouchPos.y = 0;

	m_touchPos = FACT_TOUCH__POS_LEFT_NONE;

	m_TouchAdjust = false;

	//メッセージの初期化
	m_message = NULL;
}

int CtWindowContentsFactKey::GetKeyTestItemCountMax()
{
	return FACT_KEYTEST_ITEM_MAX;
}

//キー検査用：項目をまとめてセット
void CtWindowContentsFactKey::setKeyTestItems(FactKeyTestItem * keyTestItem, int count)
{
	int index;
	int max = GetKeyTestItemCountMax();

	if (count < max) {
		max = count;
	}

    if (NULL == keyTestItem) {
        return;
    }
	for (index = 0; index < max; index++) {
        FactKeyTestItem *item = &keyTestItem[index];
		setKeyTestItem(index, item->name, item->state1, item->state2, item->state3);
	}

}

//キー検査用：指定したIndexの項目のみセット
void CtWindowContentsFactKey::setKeyTestItem(int index, char * str, KEYRECT_STATE state1, KEYRECT_STATE state2, KEYRECT_STATE state3, KEYRECT_STATE state4)
{
	if (GetKeyTestItemCountMax() <= index) {
		return;
	}
	m_KeyTestItem[index].name = str;
	setKeyTestState(index, state1, state2, state3, state4);
}

//キー検査用：指定したIndexの項目の■状態のみセット
void CtWindowContentsFactKey::setKeyTestState(int index, KEYRECT_STATE state1, KEYRECT_STATE state2, KEYRECT_STATE state3, KEYRECT_STATE state4)
{
	m_KeyTestItem[index].state1 = state1;
	m_KeyTestItem[index].state2 = state2;
	m_KeyTestItem[index].state3 = state3;
	m_KeyTestItem[index].state4 = state4;
}

CtWindowContentsFactKey::FactKeyTestItem * CtWindowContentsFactKey::GetKeyTestItems()
{
	return m_KeyTestItem;
}

//タッチ検査用
void CtWindowContentsFactKey::setContentsFactTouchPos(FACT_TOUCH_POS pos, int x, int y)
{
	m_TouchPos.Pos = pos;
	m_TouchPos.x = x;
	m_TouchPos.y = y;
}

CtWindowContentsFactKey::FactTouchPos CtWindowContentsFactKey::getContentsFactTouchPos()
{
	return m_TouchPos;
}

void CtWindowContentsFactKey::setFactTouchTestPos(FACT_TOUCH_POS type)
{
	m_touchPos = type;
}

CtWindowContentsFactKey::FACT_TOUCH_POS CtWindowContentsFactKey::getFactTouchTestPos()
{
	return m_touchPos;
}

void CtWindowContentsFactKey::setFactTouchAdjust(bool TouchAdjust)
{
	m_TouchAdjust = TouchAdjust;
}

bool CtWindowContentsFactKey::getFactTouchAdjust(void)
{
	return m_TouchAdjust;
}

void CtWindowContentsFactKey::setMessage(const char * message)
{
	m_message = message;
}

const char * CtWindowContentsFactKey::getMessage()
{
	return m_message;
}
