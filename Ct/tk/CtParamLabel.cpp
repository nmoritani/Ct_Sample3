/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtParamLabel
 */

#include "CtParamLabel.h"
#include "CtLanguage.h"
#include "str_id.h"
#include "string_api.h"

void CtParamLabel::ctor(int ParamID, const CtFontSet& fSet)
{
	setClassType(CtClassType_ParamLabel);

	m_DataStack.resize(0);
	for (int i = 0; i < m_DataStack.size(); i++) {
		m_DataStack[i] = NULL;
	}

	setEventFilter(EventParam);
	m_ParamId = ParamID;
	m_ParamData = APL_PARAM_INVALID;
	m_Type = TypeNumeric;
	m_Offset = 0;
	m_Modulus = 1.0f;
	m_Min = 0;
	m_Max = 0;
	m_Step = 1;
	m_pString = NULL;
	m_pForm = NULL;
	m_pFormSign = NULL;
	m_bInvalid = false;
	
	m_FontSet = fSet;
	m_FontSet.strokeWidth = fSet.strokeWidth;
	m_pInvalid = new CtString("----", m_FontSet);
}

CtParamLabel::CtParamLabel()
{
	ctor(APL_PARAM_INVALID, CtFontSet(FontTypeNormal_alignCenter, CtColor::White));
}

CtParamLabel::CtParamLabel(int ParamID)
{
	ctor(ParamID, CtFontSet(FontTypeNormal_alignCenter, CtColor::White));
}

CtParamLabel::CtParamLabel(int ParamID, const CtFontSet& fSet)
{
	ctor(ParamID, fSet);
}

CtParamLabel::CtParamLabel(const CtSize& Size, int ParamID, const CtFontSet& fSet) :
	CtStackLabel(Size)
{
	ctor(ParamID, fSet);
}

CtParamLabel::CtParamLabel(const CtSize& Size, int ParamID) :
	CtStackLabel(Size)
{
	ctor(ParamID, CtFontSet(FontTypeNormal_alignCenter, CtColor::White));
}

CtParamLabel::~CtParamLabel()
{
	if (m_pInvalid)	delete m_pInvalid;
	if (m_pString) delete m_pString;
	if (m_pForm) operator delete(m_pForm);
	if (m_pFormSign) operator delete(m_pFormSign);
}


bool CtParamLabel::setFontSet(const CtFontSet& fSet)
{
	m_FontSet = fSet;
	format(getValue());
	return true;
}

bool CtParamLabel::setLayout(int Screen)
{
	bool bRet = false;

	bRet = format(getValue());
	
	if (CtStackLabel::setLayout(Screen) == true)
		bRet = true;

	return bRet;
}

bool CtParamLabel::refresh()
{
	format(getValue());
	return true;
}
	
bool CtParamLabel::setLabelType(CtParamLabel::LabelType Type)
{
	m_Type = Type;
	format(getValue());
	return true;
}

bool CtParamLabel::setColor(const CtColor& fillColor)
{
	bool bRet = false;
	
	if (CtStackLabel::setColor(fillColor) == true)
		bRet = true;

	if ((m_pInvalid != NULL) && (m_pInvalid->setColor(fillColor) == true))
		bRet = true;
	
	if ((m_pString != NULL) && (m_pString->setColor(fillColor) == true))
		bRet = true;

	return bRet;
}

bool CtParamLabel::setColor(const CtColor& fillColor, const CtColor& edgeColor)
{
	bool bRet = false;
	
	if (CtStackLabel::setColor(fillColor, edgeColor) == true)
		bRet = true;

	if ((m_pInvalid != NULL) && (m_pInvalid->setColor(fillColor, edgeColor) == true))
		bRet = true;
	
	if ((m_pString != NULL) && (m_pString->setColor(fillColor, edgeColor) == true))
		bRet = true;

	return bRet;
}


bool CtParamLabel::setInvalidValue(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor)
{
	if (m_pInvalid != NULL) {
		delete m_pInvalid;
	}
	m_pInvalid = new CtSVG(ImageID, fillColor, edgeColor);
	return true;
}

bool CtParamLabel::setInvalidValue(const GDI_IMAGE_ID ImageID)
{
	return setInvalidValue(ImageID, CtColor::NoColor, CtColor::NoColor);
}

bool CtParamLabel::setInvalidValue(const GDI_HANDLER DrawableID)
{
	if (m_pInvalid != NULL) {
		delete m_pInvalid;
	}
	m_pInvalid = new CtDrawable(DrawableID);
	return true;
}

bool CtParamLabel::setInvalidValue(const char* ucStr, const CtFontSet& fSet)
{
	if (m_pInvalid != NULL) {
		delete m_pInvalid;
	}
	m_pInvalid = new CtString(ucStr, fSet);	/* pgr0541 */
	return true;
}

bool CtParamLabel::setInvalidValue(const char* ucStr)
{
	if (m_pInvalid != NULL) {
		delete m_pInvalid;
	}
	m_pInvalid = new CtString(ucStr, m_FontSet);	/* pgr0541 */
	return true;
}

bool CtParamLabel::setInvalidValue(const unsigned short* usStr, const CtFontSet& fSet)
{
	if (m_pInvalid != NULL) {
		delete m_pInvalid;
	}
	m_pInvalid = new CtString(usStr, fSet);	/* pgr0541 */
	return true;
}

bool CtParamLabel::setInvalidValue(const unsigned short* usStr)
{
	if (m_pInvalid != NULL) {
		delete m_pInvalid;
	}
	m_FontSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	m_pInvalid = new CtString(usStr, m_FontSet);	/* pgr0541 */
	return true;
}

bool CtParamLabel::setInvalidValue(const GDI_STRING_ID StringID, const CtFontSet& fSet)
{
	if (m_pInvalid != NULL) {
		delete m_pInvalid;
	}
	m_pInvalid = new CtString(StringID, fSet);
	return true;
}

bool CtParamLabel::setInvalidValue(const GDI_STRING_ID StringID)
{
	if (m_pInvalid != NULL) {
		delete m_pInvalid;
	}
	m_FontSet = CtFontSet(FontTypeNormal_alignCenter, CtColor::White);
	m_pInvalid = new CtString(StringID, m_FontSet);
	return true;
}

bool CtParamLabel::setInvalid(bool bInvalid)
{
	if (m_bInvalid != bInvalid) {
		m_bInvalid = bInvalid;
		format(getValue());
		return true;
	}
	return false;
}

bool CtParamLabel::addData(int Data, short Index)
{
	if (Index == -1) {
		m_DataStack.push_back(Data);
	} else {
		int size = m_DataStack.size();
		if (size <= Index) {
			m_DataStack.resize(Index+1);
			for (int i = size; i < m_DataStack.size(); i++) {
				m_DataStack[i] = 0;
			}
		}
		m_DataStack[Index] = Data;
	}
	return true;
}

bool CtParamLabel::addLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor, int Data, short Index)
{
	if (CtStackLabel::addLabel(ImageID, fillColor, edgeColor) == true) {
		return addData(Data, Index);
	}
	return false;
}

bool CtParamLabel::addLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, int Data, short Index)
{
	return addLabel(ImageID, fillColor, CtColor::NoColor, Data, Index);
}

bool CtParamLabel::addLabel(const GDI_IMAGE_ID ImageID, int Data, short Index)
{
	return addLabel(ImageID, CtColor::NoColor, CtColor::NoColor, Data, Index);
}

bool CtParamLabel::addLabel(const GDI_HANDLER DrawableID, int Data, short Index)
{
	if (CtStackLabel::addLabel(DrawableID) == true) {
		return addData(Data, Index);
	}
	return false;
}

bool CtParamLabel::addLabel(const char* ucStr, const CtFontSet& fSet, int Data, short Index)
{
	if (CtStackLabel::addLabel(ucStr, fSet, Index) == true) {
		return addData(Data, Index);
	}
	return false;
}

bool CtParamLabel::addLabel(const char* ucStr, int Data, short Index)
{
	if (CtStackLabel::addLabel(ucStr, Index) == true) {
		return addData(Data, Index);
	}
	return false;
}

bool CtParamLabel::addLabel(const unsigned short* usStr, const CtFontSet& fSet, int Data, short Index)
{
	if (CtStackLabel::addLabel(usStr, fSet, Index) == true) {
		return addData(Data, Index);
	}
	return false;
}

bool CtParamLabel::addLabel(const unsigned short* usStr, int Data, short Index)
{
	if (CtStackLabel::addLabel(usStr, Index) == true) {
		return addData(Data, Index);
	}
	return false;
}

bool CtParamLabel::addLabel(const GDI_STRING_ID StringID, const CtFontSet& fSet, int Data, short Index)
{
	if (CtStackLabel::addLabel(StringID, fSet, Index) == true) {
		return addData(Data, Index);
	}
	return false;
}

bool CtParamLabel::addLabel(const GDI_STRING_ID StringID, int Data, short Index)
{
	if (CtStackLabel::addLabel(StringID, Index) == true) {
		return addData(Data, Index);
	}
	return false;
}

bool CtParamLabel::setRange(int min, int max, int split)
{
	m_Min = min;
	m_Max = max;
	if (split > 0) {
		m_Step = (max - min)/split;
	}

	if ((m_Min < 0) && (m_pForm != NULL)) { 
		setFormSign();
		format(getValue());
	}

	return true;
}

bool CtParamLabel::setForm(const char* pForm)
{
	int len;
	bool bRet = false;
	
	if (pForm == NULL)
		return bRet;

	if (pForm == m_pForm) {
		if (m_pFormSign == NULL) {
			setFormSign();
			bRet = true;
		}
		return bRet;
	}
	
	if (m_pForm != NULL)	operator delete(m_pForm);

	len = get_char_string_length(pForm);
	if ((m_pForm = (char*)operator new(len + 1)) != NULL) {
		memcpy(m_pForm, pForm, len);
		m_pForm[len] = NULL;
		if (m_Min < 0) {
			setFormSign();
		}
		format(getValue());
		bRet = true;
	}
	return bRet;
}

bool CtParamLabel::setFormSign()
{
	int r, w, len, pos;

	if (m_pFormSign != NULL) {
		operator delete(m_pFormSign);
		m_pFormSign = NULL;
	}
	
	if (m_Min >= 0)
		return false;

	pos = getSignPos(m_pForm);
	len = get_char_string_length(m_pForm);
	if ((m_pFormSign = (char*)operator new(len + 2)) == NULL)
		return false;

	memset(m_pFormSign, 0, len+2);
	
	for (r = 0, w = 0; r < len; r++) {
		if (r == pos)
			m_pFormSign[w++] = '+';
		m_pFormSign[w++] = m_pForm[r];
	}
	return true;
}

int CtParamLabel::getSignPos(const char* pForm)
{
	int i, count = -1;
	int len = get_char_string_length(pForm);

	if (pForm == NULL)
		return count;
	
	for (i = 0, count = -1; i < len; i++) {
		if (count >= 0) {
			if (pForm[i] == 'd' ||
				pForm[i] == 'f') {
				break;
				
			} else if (pForm[i] == '0' ||
					   pForm[i] == '1' ||
					   pForm[i] == '2' ||
					   pForm[i] == '3' ||
					   pForm[i] == '4' ||
					   pForm[i] == '5' ||
					   pForm[i] == '6' ||
					   pForm[i] == '7' ||
					   pForm[i] == '8' ||
					   pForm[i] == '9' ||
					   pForm[i] == '.' ||
					   pForm[i] == '-' ||
					   pForm[i] == ' ' ||
					   pForm[i] == 'l' ) {
			} else if (pForm[i] == '+') {
				count = -1;
				break;
			} else {
				count = -1;
				break;
			}
		}
		if (pForm[i] == '%') {
			count = i;
		}
	}
	return count;
}



bool CtParamLabel::setCorrection(int offset, float modulus)
{
	m_Offset = offset;
	m_Modulus = modulus;
	format(getValue());
	
	return true;
}
	
bool CtParamLabel::handleParamEvent(const CtEventParam& Param)
{
	if (m_ParamId != Param.getParamId())
		return false;
	
	format(getValue());
	return true;
}
	
CtParamLabel::Attribute CtParamLabel::getAttribute(int ParamID, int ParamValue)
{
	AplParamService::AplParamMainItem* pMain = APL_PARAM()->getParamState(ParamID);
	AplParamService::AplParamSubItem* pSub = NULL;
	
	if (NULL == pMain) {
		return AttribVisible;
	}

	switch (pMain->mState) {
	case AplParamState_VisibleValid:		/* 有効表示 */
		break;
	case AplParamState_VisibleInvalid:		/* 無効表示  */
		return AttribInvalid;
	case AplParamState_Invisible:			/* 非表示 */
		return AttribInvisible;
	default:
		break;
	}
	
	if (((pSub = pMain->sub_item) == NULL) || (ParamValue == APL_PARAM_INVALID)) {
		return AttribVisible;
	}

	while (pSub->state != AplParamState_End) {
		if (pSub->value != ParamValue) {
			pSub++;
			continue;
		}
		switch (pSub->state) {
		case AplParamState_VisibleValid:	
			return AttribVisible;
		case AplParamState_VisibleInvalid:	
			return AttribInvalid;
		case AplParamState_Invisible:		
			return AttribInvisible;
		default:
			break;
		}
	}
		
	return AttribVisible;
}

CtParamLabel::Attribute CtParamLabel::getAttribute(int ParamID)
{
	return getAttribute(ParamID, APL_PARAM_INVALID);
}

CtParamLabel::Attribute CtParamLabel::getAttribute()
{
	return getAttribute(m_ParamId, m_ParamData);
}

int CtParamLabel::getValue()
{
	int value = APL_PARAM_GET_DATA(m_ParamId);

	if (m_Type == TypeNumeric) {
		if (getMin() < 0) {
			AplParamService::AplParamMainItem* Item = NULL;
			if ((Item = APL_PARAM()->getParamState(m_ParamId)) != NULL) {
				if (Item->size == 1) {
					char dat = APL_PARAM_GET_DATA(m_ParamId);
					value = (int)dat;
				} else if (Item->size == 2) {
					short dat = APL_PARAM_GET_DATA(m_ParamId);
					value = (int)dat;
				}
			}
		}
	}

	return getValue(value);
}

int CtParamLabel::getValue(int ParamData)
{
	int value = ParamData - m_Offset;

	if (m_Type == TypeStacked) {
		if (m_DataStack.size() > 0) {
			for (int i = 0; i < m_DataStack.size(); i++) {
				if (value == m_DataStack[i]) {
					return i;
				}
			}
		}
		if (m_Stack.size() > 0) {
			if (value < 0) {	// 最小値より小さければ0
				value = 0;
				
			} else if (value >= m_Stack.size()) {	// 最大値より大きければListの最終Index
				value = m_Stack.size() -1;
			}
			value = m_Stack.size()-1 - value;
		}
	}
	
	return value;
}

bool CtParamLabel::format(int value)
{
	bool bRet = false;
	int	id_len = 0;

	if (m_bInvalid == true) {
		setInvalidate();
		return true;
	}
	
	m_ParamData = APL_PARAM_GET_DATA(m_ParamId);

	switch (getAttribute(m_ParamId)) {
	case AttribInvalid:
		bRet = true;
		break;
	case AttribInvisible:
		bRet = true;
		break;
	default:
		switch (m_Type) {
		case TypeNumeric: {
			char str[100] = {0};
			int idat = 0;
			float fdat = 0;
			
			if (m_pForm != NULL) {
				if (m_Modulus == (int)m_Modulus) {
					if (m_pFormSign != NULL && value > 0) {
						sprintf(str, m_pFormSign, (int)(value * m_Modulus));
					} else {
						sprintf(str, m_pForm, (int)(value * m_Modulus));
					}
				} else {
					if (m_pFormSign != NULL && value > 0) {
						sprintf(str, m_pFormSign, (value * m_Modulus));
					} else {
						sprintf(str, m_pForm, (value * m_Modulus));
					}
				}
			} else {
				if (m_Modulus == (int)m_Modulus) {
					sprintf(str, "%d", (int)(value * m_Modulus));
				} else {
					sprintf(str, "%f", (value * m_Modulus));
				}
			}
			if (m_pString)	m_pString->setString(str);
			else			m_pString = new CtString(str, m_FontSet);
			bRet = true;
			break;
		}
		case TypeStacked:
			bRet = true;
			break;
		case TypeIP: {
			unsigned char ip[4] = {0,0,0,0};
			char str[16] = {NULL};
			AplParamService::AplParamMainItem* AplParamItem = NULL;
			if ((AplParamItem = APL_PARAM()->getParamState(m_ParamId)) != NULL) {
				APL_PARAM_GET_DATA_AREA(m_ParamId, (unsigned char*)ip, sizeof(ip));
				sprintf(str, "%3d.%3d.%3d.%3d", ip[0], ip[1], ip[2], ip[3]);

				if (m_pString)	m_pString->setString(str);
				else			m_pString = new CtString(str, m_FontSet);
				bRet = true;
			}
			break;
		}
		case TypeStrings: {
			char dat[100] = {NULL};
			char str[120] = {NULL};
			AplParamService::AplParamMainItem* AplParamItem = NULL;
			if ((AplParamItem = APL_PARAM()->getParamState(m_ParamId)) != NULL) {
				APL_PARAM_GET_DATA_AREA(m_ParamId, (unsigned char*)dat, AplParamItem->size);

				if (m_pForm)	sprintf(str, m_pForm, dat);

				if (m_pString)	m_pString->setString(str);
				else			m_pString = new CtString(str, m_FontSet);
				bRet = true;
			}
			break;
		}
		default:
			break;
		}
	}
	
	if ((bRet == true) && (isVisible() == true))
		setInvalidate();

	return bRet;
}
	
/*
  AplParamのみかた
  1.MainItemを取得する
  2.MainItemのstateを見てVisible/Invisible/Invalidを判断する
  3.Visibleなら、SubItemがあるか見てみる
    ※SubItemはValue値分の配列になっていて、Value値それぞれのVisible/Invisibleの情報を持っている
  4.SubItemから、表示するValue値のstateを見てVisible/Invisible/Invalidを判断する
  終わり！！
*/


int CtParamLabel::getMin()
{
	if (m_Type == TypeStacked) {
		return 0;
	}
	return m_Min;
}

int CtParamLabel::getMax()
{
	if (m_Type == TypeStacked) {
		return m_Stack.size() -1;
	}
	return m_Max;
}

CtDrawInfo* CtParamLabel::getStackDrawInfo(const CtRegion& Clip, int Screen)
{
	if (isVisible() != true)
		return NULL;

	CtDrawInfo* pDraw = NULL;

	if (m_bInvalid == true) {
		pDraw = m_pInvalid;
	}
	
	switch (getAttribute(m_ParamId)) {
	case AttribInvalid:
		pDraw = m_pInvalid;
		break;
	case AttribInvisible:
		break;
	default:
		switch (m_Type) {
		case TypeStacked: {
			int value = getValue();
			if ((0 <= value) && (value < m_Stack.size()) && (m_Stack[value] != NULL))
				pDraw = m_Stack[value]->m_pDrawInfo;
			break;
		}
		default:
			pDraw = m_pString;
			break;
		}
	}
	if (pDraw != NULL) {
		pDraw->setRegion(m_Region[Screen]);
		pDraw->setClip(Clip);
		pDraw->setTrans(isTrans());
	}
	return pDraw;
}

