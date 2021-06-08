/******************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
 ******************************************************************************/

/*******************************************************************************
    インクルードファイル
*******************************************************************************/
#include "CtMessageInfo.h"
#include "CtLanguage.h"
#include "string_api.h"
#include "CtWindowDecorate.h"

/*******************************************************************************
  定数の定義
*******************************************************************************/

CtMessageInfo::MessageInfo CtMessageInfo::Info[] = {
#include "MessageInfo.def"
};

CtMessageInfo::NextStringInfo CtMessageInfo::Next[] = {
#include "MessageNextInfo.def"
};

CtMessageInfo::MessageInfo* CtMessageInfo::getMessageInfo(CtWindowID id)
{
	for (unsigned int i = 0; i < sizeof(Info) / sizeof(Info[0]); i++) {
		if (id == Info[i].WindowID) {
			return &Info[i];
		}
	}
	return NULL;
}

CtMessageInfo::NextStringInfo* CtMessageInfo::getMessageNext(CtWindowID id)
{
	for (unsigned int i = 0; i < sizeof(Next) / sizeof(Next[0]); i++) {
		if (id == Next[i].WindowID) {
			return &Next[i];
		}
	}
	return NULL;
}

bool CtMessageInfo::chackWindow(CtWindowID id)
{
	MessageInfo* pInfo = getMessageInfo(id);
	if (pInfo == NULL) {
		return false;
	}
	return true;
}
CtMessageInfo::MessageDesign CtMessageInfo::getMessageDesign(CtWindowID id)
{
	MessageInfo* pInfo = getMessageInfo(id);
	if (pInfo != NULL) {
		return pInfo->Design;
	}
	return Design_Max;
}

CtColor CtMessageInfo::getBgColor(CtWindowID id)
{
	CtColor color = CtColor(ColorRGBA, 0x000000B2, NULL);

	MessageInfo* pInfo = getMessageInfo(id);
	if (pInfo == NULL) {
		return color;
	}

	switch (pInfo->Coler) {
	case Auto:
	{
		bool bThumb = CtWindowDecorate::isThumbnail();
		if (pInfo->Design == Dialog ) {
			unsigned char Transmittance = bThumb ? 235 : 178;
			color = CtColor(0, 0, 0, Transmittance);
		}
		else if(pInfo->Design == Telop){
			unsigned char Transmittance = bThumb ? 178 : 102;
			color = CtColor(0, 0, 0, Transmittance);
		}
		break;
	}
	case Right:
		color = CtColor(0, 0, 0, (unsigned char)(255 * 0.4));
		break;
	case Middle:
		color = CtColor(ColorRGBA, 0x00000099, NULL);
		break;
	case Dark:
		color = CtColor(ColorRGBA, 0x000000B2, NULL);
		break;
	case Black:
		color = CtColor(CtColor::Black);
		break;
	default:
		break;
	}

	return color;
}
void CtMessageInfo::getTelopPosition(CtWindowID id, unsigned int& top, unsigned int& pos, unsigned int& bottom)
{
	unsigned int Num;

	MessageInfo* pInfo = getMessageInfo(id);
	if (pInfo == NULL) {
		top = 4;
		pos = 2;
		bottom = 8;
		return;
	}

	Num = getMessageLineNum(id);
	top = 4;
	pos = Num + 1;
	bottom = TELOP_LINES - top - Num;

	return;
}
CtFontSet CtMessageInfo::getMessageFont(CtWindowID id)
{
	CtFontSet fSet = CtFontSet(FontTypeNormal_alignAuto, CtColor::White);;
//	fSet.setSize(36);

	MessageInfo* pInfo = getMessageInfo(id);
	if (pInfo == NULL) {
		return fSet;
	}

	switch (pInfo->Design) {
	case Dialog:
		fSet = CtFontSet(FontTypeNormal_alignCenter_Middle, CtColor::White);
//		fSet.setSize(50);
		break;
	default:
		break;
	}

	return fSet;
}

unsigned int CtMessageInfo::getMessageLineNum(CtWindowID id)
{
	unsigned int Num = 1;

	MessageInfo* pInfo = getMessageInfo(id);
	if (pInfo == NULL) {
		return Num;
	}

	if (pInfo->Msg.id != STR_ID_MAX_SIZE) {
		Num += checkIndention(pInfo->Msg.id);
	}
	else {
		Num += checkIndention(pInfo->Msg.str);
	}

	NextStringInfo* pNext = getMessageNext(id);
	if (pNext == NULL) {
		return Num;
	}

	while (pNext->WindowID == id)
	{
		if (pNext->NextType == NextUnder) {
			pNext++;
			if (pNext->id != STR_ID_MAX_SIZE) {
				pNext += checkIndention(pNext->id);
			}
			else {
				pNext += checkIndention(pNext->str);
			}
		}
		pNext++;
	}

	return Num;
}

short CtMessageInfo::checkIndention(GDI_STRING_ID STR_ID)
{
	unsigned int Num = 0;

	if (STR_ID != STR_ID_MAX_SIZE) {
		unsigned short *gdistr = GDI_GetString(CtLanguage::getLanguageID(), STR_ID);
		if (gdistr != NULL) {
			for (int i = 0; gdistr[i]; i++) {
				if (gdistr[i] == 0xa) {
					Num++;
				}
			}
		}
	}
	return Num;
}
short CtMessageInfo::checkIndention(char* str)
{
	if (str == NULL) { return 1; }
	unsigned int Num = 0;

	for (int i = 0; str[i]; i++) {
		if (str[i] == 0xa) {
			Num++;
		}
	}
	return Num;

}


/**********************************************************************************
 * Copyright(c) 2018 Persol AVC Technology.
**********************************************************************************/
