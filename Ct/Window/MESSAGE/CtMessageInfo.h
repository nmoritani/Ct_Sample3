/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

#ifndef __CtMessageInfo_H__
#define __CtMessageInfo_H__

/*******************************************************************************
    �C���N���[�h�t�@�C��
*******************************************************************************/
#include "CtObject.h"
#include "CtWindow.h"

#include "str_id.h"

#include "CtWindowCommon.h"

/*******************************************************************************
  �萔�̒�`
*******************************************************************************/

/*******************************************************************************
  �N���X�錾
*******************************************************************************/
class CtMessageInfo : public CtObject
{
/*******************
  �萔 
*******************/
public:

#define DIALOG_LINES 7
#define TELOP_LINES 14

	typedef enum TitleType {
		TitleType_Normal,
		TitleType_Battery,
		TitleType_Menu,
		TitleType_Not,
	}TitleType;

	typedef enum BgColler {
		Auto,
		Right,
		Middle,
		Dark,
		Black,
	}BgColer;

	typedef enum MessageDesign {
		Telop,
		Dialog,
		Full,
		Design_Max,
	}MessageDesign;

	typedef enum NextStringType {
		NextUnder,			//����������ɒǉ�
		NextRight,			//��������E�ɒǉ�
		//	Nextbrackets,	//<������>���E�ɒǉ�
	}NextStringType;

	typedef struct StringInfo {
		GDI_STRING_ID        id;
		char*                str;
	}StringInfo;

	typedef struct TitleInfo {
		TitleType            Type;
		GDI_STRING_ID        id;
		char*                str;
	}TitleInfo;

	typedef struct ButtonInfo {
		bool					valid;
		CtFuncID				FuncID;
		CtWindowID				WindowID;
		CtOpenType				OpenType;// TODO CtEventWindow::WinCmd�֕ύX���邱��
	}ButtonInfo;

	typedef struct MessageInfo {
		CtWindowID              WindowID;
		MessageDesign           Design;
		BgColer					Coler;
		TitleInfo			    Title;
		StringInfo              Msg;
		ButtonInfo              set;
		ButtonInfo              ret;
		unsigned int            time;
		bool                    touch;
		bool                    current;
	} MessageInfo;

	typedef struct NextStringInfo {
		CtWindowID				WindowID;
		NextStringType			NextType;
		GDI_STRING_ID			id;
		char*					str;
		AplParamEepromId        ParamID;
		char*					SubScr;
	}NextStringInfo;


/*******************
  ���\�b�h 
*******************/
/* ---------------- ���J ---------------------------------------------------- */
public:
	CtMessageInfo() {};
	virtual ~CtMessageInfo() {};

	static MessageInfo* getMessageInfo(CtWindowID id);
	static NextStringInfo* getMessageNext(CtWindowID id);
	static MessageDesign getMessageDesign(CtWindowID id);

	static bool chackWindow(CtWindowID id);
	
	static CtColor getBgColor(CtWindowID id);
	static CtFontSet getMessageFont(CtWindowID id);
	static void getTelopPosition(CtWindowID id, unsigned int& top, unsigned int& pos, unsigned int& bottom);
	static void getMessagePosition(CtWindowID id, unsigned int& top, unsigned int& pos, unsigned int& bottom);

	static unsigned int getMessageLineNum(CtWindowID id);
	static short checkIndention(GDI_STRING_ID STR_ID);
	static short checkIndention(char* str);

/* ---------------- ����J -------------------------------------------------- */
private :

/* ---------------- ����J -------------------------------------------------- */
protected :

/*******************
  �����o 
*******************/
/* ---------------- ���J ---------------------------------------------------- */
public:

/* ---------------- ����J -------------------------------------------------- */
private :
	static MessageInfo Info[];

	static NextStringInfo Next[];

/* ---------------- ����J -------------------------------------------------- */
protected :

};


#endif /* __CtMessageInfo_H__ */
/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
