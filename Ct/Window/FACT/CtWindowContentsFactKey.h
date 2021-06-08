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

	int GetKeyTestItemCountMax();	//��ʂɔz�u�ł��鍀�ڐ��̍ő�l�擾�p(1��ʍő�14���ڂ܂�)

	//�L�[�����p(APL��GUI�ւ̒ʒm)
	void setKeyTestItems(FactKeyTestItem * keyTestItem, int count);													//APL���F�������ڂ܂Ƃ߂ăZ�b�g�p
	void setKeyTestItem(int index, char * str, KEYRECT_STATE state1, KEYRECT_STATE state2, KEYRECT_STATE state3, KEYRECT_STATE state4 = KEYRECT_INVISIBLE);		//APL���F1���ڃZ�b�g�p
	void setKeyTestState(int index, KEYRECT_STATE state1, KEYRECT_STATE state2, KEYRECT_STATE state3, KEYRECT_STATE state4 = KEYRECT_INVISIBLE);					//APL���F1���ڕ��́���ԃZ�b�g�p
	FactKeyTestItem * GetKeyTestItems();																				//GUI���F�Z�b�g���ꂽ���ڂ����o��

	//�^�b�`�����p(GUI��APL�ւ̒ʒm)
	void setContentsFactTouchPos(FACT_TOUCH_POS pos, int x, int y);		//GUI���F�^�b�`�ʒu���Z�b�g����
	FactTouchPos getContentsFactTouchPos();								//APL���F�^�b�`�ʒu�����擾

	//�^�b�`�����p(APL��GUI�ւ̒ʒm)
	void setFactTouchTestPos(FACT_TOUCH_POS type);						//APL���F�^�b�`�����p�{�^�����\���ɂ���ʒu���Z�b�g����
	FACT_TOUCH_POS getFactTouchTestPos();								//GUI���F�^�b�`�ʒu�̃{�^�����\���ɂ���

	//���C�A�E�g�ύX�p(APL��GUI�ւ̒ʒm)
	void setFactTouchAdjust(bool TouchAdjust);							//APL���F�^�b�`������ʂ��ǂ������Z�b�g����
	bool getFactTouchAdjust(void);										//GUI���F�^�b�`������ʂ��ǂ����Ń��C�A�E�g��ύX����
	
	//���ʒʒm���b�Z�[�W�p(APL��GUI�ւ̒ʒm)
	void setMessage(const char* message);								//APL���F�o���������b�Z�[�W���Z�b�g����(���b�Z�[�W���o���Ȃ��ꍇ��NULL)
																		//�p�����̂ݎg�p�\�B���s�R�[�h(\n)�͎g�p�\(�������A10�s�܂�)
	const char* getMessage();											//GUI���F���b�Z�[�W��NULL�ȊO�Ȃ甼�������w�i�ɂ��ĕ�������ʒ����ɕ\������

private:
	void InitKeyTestItem();

protected:

private:
#define FACT_KEYTEST_ITEM_MAX (14)	//1��ʂɓo�^�\�ȍ��ڂ̐� = 14�܂ŁB
	FactKeyTestItem m_KeyTestItem[FACT_KEYTEST_ITEM_MAX];

	FactTouchPos m_TouchPos;
	FACT_TOUCH_POS m_touchPos;
	bool m_TouchAdjust;

	const char* m_message;
};

#endif

