/**
 *  Copyright (c) AVC Multimedia Soft
 *  Element:			CtParamLabel
 */


#ifndef __CtParamLabel_H__
#define __CtParamLabel_H__

#include "CtStackLabel.h"
#include "AplParamService.h"
#define APL_PARAM_INVALID 0xCBCBCBCB

class CtParamLabel : public CtStackLabel {
public :
	enum LabelType {
		TypeNumeric,
		TypeStacked,
		TypeIP,
		TypeStrings,
	};

	enum Attribute {
		AttribVisible,
		AttribInvisible,
		AttribInvalid,
	};

	CtParamLabel();
    CtParamLabel(const int ParamID, const CtFontSet& fSet);
    CtParamLabel(const int ParamID);
    CtParamLabel(const CtSize& Size, const int ParamID, const CtFontSet& fSet);
    CtParamLabel(const CtSize& Size, const int ParamID);
	virtual ~CtParamLabel();

	virtual bool setLayout(int Screen = 0);
	virtual bool isParamLabel() const;
	
	bool refresh();
	bool setFontSet(const CtFontSet& fSet);
	bool setForm(const char* pForm);
	bool setCorrection(int offset, float modulus = 1.0f);
	bool setRange(int min, int max, int split = 0);

	bool setInvalid(bool bInvalid);
	bool setInvalidValue(const GDI_IMAGE_ID ImageID);
	bool setInvalidValue(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor = CtColor::NoColor);
	bool setInvalidValue(const GDI_HANDLER DrawableID);
	bool setInvalidValue(const char* ucStr, const CtFontSet& fSet);
	bool setInvalidValue(const char* ucStr);
	bool setInvalidValue(const unsigned short* usStr, const CtFontSet& fSet);
	bool setInvalidValue(const unsigned short* usStr);
    bool setInvalidValue(const GDI_STRING_ID StringID, const CtFontSet& fSet);
    bool setInvalidValue(const GDI_STRING_ID StringID);

	bool addLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, int Data, short Index = -1);
	bool addLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor, int Data, short Index = -1);
	bool addLabel(const GDI_IMAGE_ID ImageID, int Data, short Index = -1);
	bool addLabel(const GDI_HANDLER DrawableID, int Data, short Index = -1);
	bool addLabel(const GDI_STRING_ID StringID, int Data, short Index = -1);
	bool addLabel(const GDI_STRING_ID StringID, const CtFontSet& FontSet, int Data, short Index = -1);
	bool addLabel(const char* pStr, int Data, short Index = -1);
	bool addLabel(const char* pStr, const CtFontSet& FontSet, int Data, short Index = -1);
	bool addLabel(const unsigned short* pStr, int Data, short Index = -1);
	bool addLabel(const unsigned short* pStr, const CtFontSet& FontSet, int Data, short Index = -1);
	bool addData(int Data, short Index);
	
	virtual CtDrawInfo* getStackDrawInfo(const CtRegion& Clip, int Screen = 0);
	
	virtual bool handleParamEvent(const CtEventParam& Param);
	int getParamID();
	int getParamData() const;
	bool setLabelType(CtParamLabel::LabelType Type);
	CtParamLabel::LabelType getLabelType() const;
	Attribute getAttribute();

	bool setColor(const CtColor& fillColor);
	bool setColor(const CtColor& fillColor, const CtColor& edgeColor);
	
protected:
	void ctor(int ParamId, const CtFontSet& fSet);
	virtual int getValue();
	virtual int getValue(int ParamData);
	Attribute getAttribute(int ParamID, int ParamValue);
	Attribute getAttribute(int ParamID);
	virtual int getMin();
	virtual int getMax();

	bool format(int value);

private:
	bool setFormSign();
	int getSignPos(const char* str);

	
	// ëÆê´
protected:
	int					m_ParamId;
	int					m_ParamData;
	int					m_Min;
	int					m_Max;
	int					m_Step;
	
	LabelType			m_Type;
	int					m_Offset;
	float				m_Modulus;
	char*				m_pForm;
	char*				m_pFormSign;

	bool				m_bInvalid;
	CtFontSet			m_FontSet;
	CtDrawInfo*			m_pInvalid;
	CtString*			m_pString;
	
	CtVector::Vector<int> 	m_DataStack;
};

inline bool CtParamLabel::isParamLabel() const
{
	return true;
}

inline int CtParamLabel::getParamID()
{
	return m_ParamId;
}

inline int CtParamLabel::getParamData() const
{
	return m_ParamData;
}

inline CtParamLabel::LabelType CtParamLabel::getLabelType() const
{
	return m_Type;
}
#endif
