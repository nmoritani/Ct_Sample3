/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtStyle
 */


#ifndef __CtStyle_H__
#define __CtStyle_H__

#include "Ct.h"
#include "CtObject.h"
#include "CtColor.h"
#include "CtDrawInfo.h"

class CtStyle : public CtObject {
public :
	enum Style {
		Default,
		White,
	};

	struct ColorSet {
		const CtColor Base;
		const CtColor Stroke;
		const CtColor Label;
	};

	struct CtProperty {
		struct {
			const CtRegion Region;
			const CtColor  Background;
		} Window;
		struct {
			const int StrokeWidth;
			const int ArcWidth;
			const CtSize Size;
			const ColorSet Normal;
			const ColorSet Selected;
			const ColorSet Focused;
			const ColorSet Invalid;
		} Button;
		struct {
			const int StrokeWidth;
			const int ArcWidth;
			const ColorSet Normal;
			const ColorSet Selected;
			const ColorSet Invalid;
		} ListView;
		
		struct {
			const int StrokeWidth;
			const int ArcWidth;
			const ColorSet Normal;
			const ColorSet Selected;
			const ColorSet Invalid;
		} MenuList;
		struct {
			const ColorSet Valid;
			const ColorSet Invalid;
		} ParamLabel;

		const CtFontSet FontSet;

		const CtColor ShapeColor;
	};

	static void setStyle(Style style);
	static CtStyle::Style getStyle(void);
	static const CtProperty& getProperty(void);
	static const CtRegion DefaultRegion;

private:

	static const CtProperty m_Properties[];

	static CtStyle::Style m_Style;
	
};

#endif
