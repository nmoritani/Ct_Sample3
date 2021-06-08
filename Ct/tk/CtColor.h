/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtColor
 */


#ifndef __CtColor_H__
#define __CtColor_H__

	//#include "Ct.h"
enum CtColorType {
	ColorNone,
	ColorRGBA,
	ColorGradient,
	
	ColorType_MAX
};

enum CtFuncColorType {
	FuncColorNone 		= 0,
	FuncColorNormal 	= (1<<0),
	FuncColorTouched 	= (1<<1),
	FuncColorFocused	= (1<<2),
	
	FuncColorProcessing = (1<<3),
	FuncColorWarning 	= (1<<4),
	FuncColorError		,
	
	FuncColorType_MAX
};

	struct CtColor {
		CtColorType		Type;
		unsigned int 	RGBA;
		void*			Gradient;

		CtColor() {
			Type = ColorNone;
			RGBA = 0;
			Gradient = NULL;
		}
		CtColor(unsigned int _rgba) {
			Type = ColorRGBA;
			RGBA = _rgba;
			Gradient = NULL;
		}
		CtColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
			Type = ColorRGBA;
			RGBA = ((unsigned int)((((unsigned int)(r)) << 24) + (((unsigned int)(g)) << 16) + (((unsigned int)(b)) << 8) + ((unsigned int)(a))));
			Gradient = NULL;
		}
		CtColor(void* _gradient) {
			Type = ColorGradient;
			RGBA = 0;
			Gradient = _gradient;
		}
		CtColor(CtColorType _type, unsigned int _rgba, void* _gradient) {
			Type = _type;
			RGBA = _rgba;
			Gradient = _gradient;
		}
		void setColor(unsigned int _rgba) {
			Type = ColorRGBA;
			RGBA = _rgba;
			Gradient = NULL;
		}
		void setColor(void* _gradient) {
			Type = ColorGradient;
			RGBA = 0;
			Gradient = _gradient;
		}
		void setColor(CtColorType _type, unsigned int _rgba, void* _gradient) {
			Type = _type;
			RGBA = _rgba;
			Gradient = _gradient;
		}

		bool isNoColor() const {
			if (Type == ColorNone)	return true;
			return false;
		}
		bool isTransColor() const {
			if ((Type == ColorRGBA) && ((RGBA & 0xff) == 0xff)) {
				return false;
			}
			return true;
		}
		bool isInvisibleColor() const {
			if ((Type == ColorRGBA) && ((RGBA & 0xff) == 0)) {
				return true;
			}
			return false;
		}
		unsigned int getRGBA(CtColor& _color) {
			if (_color.Type == ColorNone)
				return 0;
			if (_color.Gradient != NULL) {
				return 0;
			}
			return _color.RGBA;
		}
		bool operator==(const CtColor& Color) const {
			if ((Type == Color.Type) && (RGBA == Color.RGBA) && (Gradient == Color.Gradient))
				return true;
			return false;
		}
		bool operator!=(const CtColor& Color) const {
			if ((Type == Color.Type) && (RGBA == Color.RGBA) && (Gradient == Color.Gradient))
				return false;
			return true;
		}
		
		static const CtColor NoColor;
		static const CtColor Trans;
		static const CtColor White;
		static const CtColor Black;
		static const CtColor Red;
		static const CtColor darkRed;
		static const CtColor Green;
		static const CtColor darkGreen;
		static const CtColor Blue;
		static const CtColor darkBlue;
		static const CtColor Cyan;
		static const CtColor darkCyan;
		static const CtColor Magenta;
		static const CtColor darkMagenta;
		static const CtColor Yellow;
		static const CtColor darkYellow;
		static const CtColor Gray;
		static const CtColor lightGray;
		static const CtColor darkGray;
		
		static const CtColor IconNormal;
		static const CtColor IconProcessing;
		static const CtColor IconWarning;
		static const CtColor ButtonBase;
		static const CtColor ButtonStroke;
		static const CtColor ButtonBaseTouched;
		static const CtColor ButtonStrokeFocused;
		static const CtColor ButtonInvalid;
		static const CtColor KeyButtonBase;
		static const CtColor KeyButtonStroke;
		static const CtColor KeyButtonBaseTouched;
		static const CtColor KeyButtonStrokeFocused;
		static const CtColor SlideBarBase;
		static const CtColor SlideBar;
		static const CtColor AdjustBarBase;
		static const CtColor AdjustBar;

		static const CtColor white;
		static const CtColor whitesmoke;
		static const CtColor gainsboro;
		static const CtColor lightgray;
		static const CtColor silver;
		static const CtColor darkgray;
		static const CtColor gray;
		static const CtColor dimgray;
		static const CtColor black;
		static const CtColor ivory;
		static const CtColor lightyellow;
		static const CtColor cornsilk;
		static const CtColor lightgoldenrodyellow;
		static const CtColor lemonchiffon;
		static const CtColor beige;
		static const CtColor palegoldenrod;
		static const CtColor khaki;
		static const CtColor yellow;
		static const CtColor gold;
		static const CtColor goldenrod;
		static const CtColor darkgoldenrod;
		static const CtColor darkkhaki;
		static const CtColor saddlebrown;
		static const CtColor sienna;
		static const CtColor chocolate;
		static const CtColor peru;
		static const CtColor tan;
		static const CtColor burlywood;
		static const CtColor orange;
		static const CtColor darkorange;
		static const CtColor sandybrown;
		static const CtColor lightsalmon;
		static const CtColor darksalmon;
		static const CtColor coral;
		static const CtColor orangered;
		static const CtColor tomato;
		static const CtColor salmon;
		static const CtColor lightcoral;
		static const CtColor indianred;
		static const CtColor rosybrown;
		static const CtColor darkred;
		static const CtColor maroon;
		static const CtColor brown;
		static const CtColor firebrick;
		static const CtColor crimson;
		static const CtColor red;
		static const CtColor floralwhite;
		static const CtColor oldlace;
		static const CtColor seashell;
		static const CtColor linen;
		static const CtColor antiquewhite;
		static const CtColor papayawhip;
		static const CtColor blanchedalmond;
		static const CtColor wheat;
		static const CtColor bisque;
		static const CtColor moccasin;
		static const CtColor navajowhite;
		static const CtColor peachpuff;
		static const CtColor mintcream;
		static const CtColor honeydew;
		static const CtColor palegreen;
		static const CtColor lightgreen;
		static const CtColor mediumspringgreen;
		static const CtColor springgreen;
		static const CtColor lime;
		static const CtColor limegreen;
		static const CtColor forestgreen;
		static const CtColor green;
		static const CtColor darkgreen;
		static const CtColor seagreen;
		static const CtColor mediumseagreen;
		static const CtColor darkseagreen;
		static const CtColor chartreuse;
		static const CtColor lawngreen;
		static const CtColor greenyellow;
		static const CtColor yellowgreen;
		static const CtColor olivedrab;
		static const CtColor darkolivegreen;
		static const CtColor olive;
		static const CtColor paleturquoise;
		static const CtColor powderblue;
		static const CtColor aquamarine;
		static const CtColor mediumaquamarine;
		static const CtColor cyan;
		static const CtColor turquoise;
		static const CtColor mediumturquoise;
		static const CtColor darkturquoise;
		static const CtColor lightseagreen;
		static const CtColor cadetblue;
		static const CtColor darkcyan;
		static const CtColor teal;
		static const CtColor darkslategray;
		static const CtColor aliceblue;
		static const CtColor azure;
		static const CtColor lightcyan;
		static const CtColor lightblue;
		static const CtColor skyblue;
		static const CtColor lightskyblue;
		static const CtColor deepskyblue;
		static const CtColor dodgerblue;
		static const CtColor cornflowerblue;
		static const CtColor lightsteelblue;
		static const CtColor royalblue;
		static const CtColor steelblue;
		static const CtColor slategray;
		static const CtColor lightslategray;
		static const CtColor darkslateblue;
		static const CtColor midnightblue;
		static const CtColor navy;
		static const CtColor darkblue;
		static const CtColor mediumblue;
		static const CtColor blue;
		static const CtColor slateblue;
		static const CtColor mediumslateblue;
		static const CtColor mediumpurple;
		static const CtColor darkviolet;
		static const CtColor blueviolet;
		static const CtColor darkorchid;
		static const CtColor mediumorchid;
		static const CtColor orchid;
		static const CtColor violet;
		static const CtColor magenta;
		static const CtColor plum;
		static const CtColor thistle;
		static const CtColor lavender;
		static const CtColor ghostwhite;
		static const CtColor snow;
		static const CtColor lavenderblush;
		static const CtColor mistyrose;
		static const CtColor pink;
		static const CtColor lightpink;
		static const CtColor palevioletred;
		static const CtColor hotpink;
		static const CtColor deeppink;
		static const CtColor mediumvioletred;
		static const CtColor purple;
		static const CtColor darkmagenta;
		static const CtColor indigo;
	};
#endif
