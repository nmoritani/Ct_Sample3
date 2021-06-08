/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:	CtStackLabel
 */


#ifndef __CtStackLabel_H__
#define __CtStackLabel_H__

#include <CtVector.h>
#include "Ct.h"
#include "CtLabel.h"
#include "CtLayout.h"

class CtEvent;

class CtStackLabel : public CtLabel {
protected:
	#define DefaultAlign	AlignInvalid
	#define DefaultMargin	CtMargin(0,0,0,0)
	
public :
    CtStackLabel();
	CtStackLabel(const CtColor& Color);
	CtStackLabel(const CtSize& Size, const CtColor& Color = CtColor::NoColor);
	CtStackLabel(const CtRegion& Region, const CtColor& Color = CtColor::NoColor);
	virtual ~CtStackLabel();

	virtual bool addLabel(CtLabel* pLabel, int Index = -1);
	virtual bool addLabel(CtLayout* pLayout, int Index = -1);
	virtual bool addLabel(CtLabel* pLabel, CtMargin Margin, CtAlign Align, int Index = -1);
	virtual bool addLabel(CtLayout* pLayout, CtMargin Margin, CtAlign Align, int Index = -1);
	virtual bool addLabel(const GDI_IMAGE_ID ImageID, int Index = -1);
	virtual bool addLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, int Index = -1);
	virtual bool addLabel(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor, int Index = -1);
	virtual bool addLabel(const GDI_HANDLER DrawableID, int Index = -1);
	virtual bool addLabel(const GDI_STRING_ID StringID, int Index = -1);
	virtual bool addLabel(const GDI_STRING_ID StringID, const CtFontSet& FontSet, int Index = -1);
	virtual bool addLabel(const char* pStr, int Index = -1);
	virtual bool addLabel(const char* pStr, const CtFontSet& FontSet, int Index = -1);
	virtual bool addLabel(const unsigned short* pStr, int Index = -1);
	virtual bool addLabel(const unsigned short* pStr, const CtFontSet& FontSet, int Index = -1);
	virtual bool addLabel(const CtLine& Line, int Index = -1);
	virtual bool addLabel(const CtRect& Rect, int Index = -1);
	virtual bool addLabel(const CtRoundRect& RoundRect, int Index = -1);
	virtual bool addLabel(const CtEllipse& Ellipse, int Index = -1);
	virtual bool addLabel(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type, int Index = -1);
	virtual bool addLabel(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type, int Index = -1);
	virtual bool addLabels(const char* pStr, const CtFontSet& FontSet);

	virtual bool addContainer(CtContainer* pContainer, int Index = -1);
	virtual bool addContainer(CtContainer* pContainer, CtMargin Margin, CtAlign Algin, int Index = -1);
	
	virtual bool getDrawInfo(CtList::list<CtDrawInfo*> &List, const CtRegion& Clip = NoRegion, int Screen = 0);
	
	virtual CtDrawInfo* getStackDrawInfo(const CtRegion& Clip, int Screen = 0);
	virtual bool draw(const CtRegion& Clip, int Screen = 0);
	virtual bool drawShift(short shift_x, short shift_y, const CtRegion& Clip, int Screen = 0);
	
	CtWidget* getStackWidget(int Index = -1) const;
	CtLayout* getStackLayout(int Index = -1) const;
	
    virtual bool getWidgets(SearchType SearchType, CtWidget::List* pList, const CtWidgetType WidgetType = WidgetAll, int Screen = 0, const CtRegion& Region = NoRegion);
    virtual bool existWidget(SearchType SearchType, const CtWidgetType WidgetType = WidgetAll, int Screen = 0, const CtRegion& Region = NoRegion);
	virtual bool isRegistered(CtWidget* pWidget);
	virtual bool setElementsParent(CtWidget* pParent);
	
	bool initialFastDraw();
	bool cleanupFastDraw();
	
	virtual bool setColor(const CtColor& fillColor);
	virtual bool setColor(const CtColor& fillColor, const CtColor& edgeColor);
	virtual bool setTrans(bool bTrans);
	virtual bool setFontSet(const CtFontSet& FontSet);

	bool inc();
	bool dec();
	bool index(int Index);
	int getIndex() const;
	int getIndexMax() const;

	bool includeEventHandler(int Index);
	
	virtual bool isStackLabel() const;
	virtual bool isLabel() const;
	virtual bool isLayout() const;

	virtual bool handleTouchEvent(const CtEventTouch& Touch);
	virtual bool handleKeyEvent(const CtEventKey& Key);
	virtual bool handleParamEvent(const CtEventParam& Param);
	virtual bool handleButtonEvent(const CtEventButton& Button);
	virtual bool handleWidgetEvent(const CtEventWidget& Widget);
	
	virtual CtVector::Vector<CtWidget::Element*>* getElements() const;
	virtual CtVector::Vector<CtWidget::Element*>* getVisibles() const;
	
	virtual bool getInvalidates(RegionArray& Array, int Screen);
	virtual bool clearInvalidate(int Screen);
	
	virtual void outputOutline(int depth, const char* header, int Screen = 0);
	
	virtual bool setAlign(const CtAlign Align);
	virtual bool setAspectRatio(const CtAspectRatio Ratio);
	virtual bool setAutoAdjust(bool bAdjust);
	
protected:
	void ctor();
	
	class Stack : public CtWidget::Element {
	public:
		Stack();
		Stack(CtDrawInfo* DrawInfo);
		Stack(CtLabel* pLabel, CtMargin Margin, CtAlign Align);
		Stack(CtLayout* pLayout, CtMargin Margin, CtAlign Align);
		virtual ~Stack();

		enum Type {
			TypeNormal,
			TypeLabel,
			TypeLayout,
			TypeMax
		};
		
		Type		m_Type;
		CtDrawInfo*	m_pDrawInfo;
	};
	
	bool addLabel(CtStackLabel::Stack* pStack, int Index);
	
	virtual bool setLayout(int Screen = 0);
	
	CtVector::Vector<Stack*> 				m_Stack;
	int 									m_Index;

private:
	CtLayout* getLayout();
	virtual bool setImage(const GDI_IMAGE_ID ImageID) {return false;}
	virtual bool setImage(const GDI_IMAGE_ID ImageID, const CtColor& fillColor, const CtColor& edgeColor) {return false;}
	virtual bool setImage(short Width, short Height, short BufWidth, short BufHeight, const unsigned char* Data, CtImageType Type) {return false;}
	virtual bool setImage(short Width, short Height, short YPlaneSize, short PlaneStride, short PlaneHeight, const unsigned char* pYPlane, const unsigned char* pCPlane, CtImageType Type) {return false;}
	virtual GDI_IMAGE_ID getImageID() {return IMAGE_ID_INVALID;}
	
	virtual bool setDrawable(const GDI_HANDLER DrawableID) {return false;}
	virtual GDI_HANDLER getDrawable() {return GDI_INVALID_ID;}
	
	virtual bool setStringID(const GDI_STRING_ID, const CtFontSet& FontSet) {return false;}
	virtual bool setStringID(const GDI_STRING_ID) {return false;}
	
	virtual bool setText(const char *ucStr) {return false;}
	virtual bool setText(const char *ucStr, const CtFontSet& FontSet) {return false;}
	virtual bool setText(const unsigned short *ucStr) {return false;}
	virtual bool setText(const unsigned short *ucStr, const CtFontSet& FontSet) {return false;}
	virtual unsigned short* getText() const {return NULL;}
	
	virtual bool setLine(const CtLine& Line) {return false;}
	virtual bool setLine(CtLineStyle Style, short lineWidth, const CtColor& lineColor) {return false;}
	
	virtual bool setFill(const CtFill& Fill) {return false;}
	virtual bool setRect(const CtRect& Rect) {return false;}
	virtual bool setRect(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor = CtColor::NoColor) {return false;}
	
	virtual bool setRoundRect(const CtRoundRect& RoundRect) {return false;}
	virtual bool setRoundRect(short ArcWidth, short ArcHeight, const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor = CtColor::NoColor) {return false;}
	
	virtual bool setEllipse(const CtEllipse& Ellipse) {return false;}
	virtual bool setEllipse(const CtColor& fillColor, short edgeWidth, const CtColor& edgeColor = CtColor::NoColor) {return false;}
};

inline bool CtStackLabel::isStackLabel() const
{
	return true;
}

inline bool CtStackLabel::isLabel() const
{
	return true;
}

inline CtVector::Vector<CtWidget::Element*>* CtStackLabel::getElements() const
{
	return (CtVector::Vector<CtWidget::Element*>*)&m_Stack;
}

inline CtVector::Vector<CtWidget::Element*>* CtStackLabel::getVisibles() const
{
	return (CtVector::Vector<CtWidget::Element*>*)&m_Stack;
}
#endif
