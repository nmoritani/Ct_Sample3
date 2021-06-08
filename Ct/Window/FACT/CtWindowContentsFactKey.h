#pragma once
#ifndef __CtWindowContentsFactKeyTest_H__
#define __CtWindowContentsFactKeyTest_H__

#include "CtWindowContents.h"

class CtWindowContentsFactKey : public CtWindowContents {
public:
	typedef enum _FACT_KEYRECT_STATE {
		KEYRECT_INVISIBLE = 0,
		KEYRECT_WHITE,
		KEYRECT_GREEN,
		KEYRECT_RED,
		KEYRECT_MAX,
	} KEYRECT_STATE;

	typedef struct _FactKeyTestItem {
		char *name;
		KEYRECT_STATE state1;
		KEYRECT_STATE state2;
		KEYRECT_STATE state3;
		KEYRECT_STATE state4;
	} FactKeyTestItem;

	typedef unsigned char FACT_TOUCH_POS;

	const static FACT_TOUCH_POS FACT_TOUCH__POS_LEFT_NONE		= 0x00;
	const static FACT_TOUCH_POS FACT_TOUCH__POS_LEFT_TOP		= 0x01;
	const static FACT_TOUCH_POS FACT_TOUCH__POS_LEFT_BOTTOM		= 0x02;
	const static FACT_TOUCH_POS FACT_TOUCH__POS_RIGHT_TOP		= 0x04;
	const static FACT_TOUCH_POS FACT_TOUCH__POS_RIGHT_BOTTOM	= 0x08;
	const static FACT_TOUCH_POS FACT_TOUCH__POS_CENTER			= 0x10;
	const static FACT_TOUCH_POS FACT_TOUCH__POS_DISABLE			= FACT_TOUCH__POS_LEFT_NONE;
	const static FACT_TOUCH_POS FACT_TOUCH__POS_ABLE			= FACT_TOUCH__POS_LEFT_TOP + FACT_TOUCH__POS_LEFT_BOTTOM + FACT_TOUCH__POS_RIGHT_TOP + FACT_TOUCH__POS_RIGHT_BOTTOM + FACT_TOUCH__POS_CENTER;

	typedef struct _FactTouchPos {
		FACT_TOUCH_POS Pos;
		int x;
		int y;
	} FactTouchPos;

	CtWindowContentsFactKey(const CtWindowID WindowID);
	virtual ~CtWindowContentsFactKey();

	int GetKeyTestItemCountMax();	//画面に配置できる項目数の最大値取得用(1画面最大14項目まで)

	//キー検査用(APL⇒GUIへの通知)
	void setKeyTestItems(FactKeyTestItem * keyTestItem, int count);													//APL側：複数項目まとめてセット用
	void setKeyTestItem(int index, char * str, KEYRECT_STATE state1, KEYRECT_STATE state2, KEYRECT_STATE state3, KEYRECT_STATE state4 = KEYRECT_INVISIBLE);		//APL側：1項目セット用
	void setKeyTestState(int index, KEYRECT_STATE state1, KEYRECT_STATE state2, KEYRECT_STATE state3, KEYRECT_STATE state4 = KEYRECT_INVISIBLE);					//APL側：1項目分の■状態セット用
	FactKeyTestItem * GetKeyTestItems();																				//GUI側：セットされた項目を取り出す

	//タッチ検査用(GUI⇒APLへの通知)
	void setContentsFactTouchPos(FACT_TOUCH_POS pos, int x, int y);		//GUI側：タッチ位置をセットする
	FactTouchPos getContentsFactTouchPos();								//APL側：タッチ位置情報を取得

	//タッチ検査用(APL⇒GUIへの通知)
	void setFactTouchTestPos(FACT_TOUCH_POS type);						//APL側：タッチ調整用ボタンを非表示にする位置をセットする
	FACT_TOUCH_POS getFactTouchTestPos();								//GUI側：タッチ位置のボタンを非表示にする

	//レイアウト変更用(APL⇒GUIへの通知)
	void setFactTouchAdjust(bool TouchAdjust);							//APL側：タッチ調整画面かどうかをセットする
	bool getFactTouchAdjust(void);										//GUI側：タッチ調整画面かどうかでレイアウトを変更する
	
	//結果通知メッセージ用(APL⇒GUIへの通知)
	void setMessage(const char* message);								//APL側：出したいメッセージをセットする(メッセージを出さない場合はNULL)
																		//英数字のみ使用可能。改行コード(\n)は使用可能(ただし、10行まで)
	const char* getMessage();											//GUI側：メッセージがNULL以外なら半透明黒背景にして文字を画面中央に表示する

private:
	void InitKeyTestItem();

protected:

private:
#define FACT_KEYTEST_ITEM_MAX (14)	//1画面に登録可能な項目の数 = 14個まで。
	FactKeyTestItem m_KeyTestItem[FACT_KEYTEST_ITEM_MAX];

	FactTouchPos m_TouchPos;
	FACT_TOUCH_POS m_touchPos;
	bool m_TouchAdjust;

	const char* m_message;
};

#endif

