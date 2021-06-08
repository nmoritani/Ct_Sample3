/**
 *  Persol AVC Technology
 *  Element:	Comfortable Toolkit Data Type
 */

#ifndef __CtType_H__
#define __CtType_H__

#include "CtClass.h"
#include "../gdi/gdi.h"
#include "../ws/CtObject.h"
#include "../ws/CtFastObject.h"
#include "../Window/CtWindowID.h"
#include "../Window/CtFuncID.h"

///tk/Window/ws
struct CtPosition {
	short x;
	short y;

	CtPosition() {
		x = 0;
		y = 0;
	}
	CtPosition(short _x, short _y) {
		x = _x;
		y = _y;
	}
	void setPosition(short _x, short _y) {
		x = _x;
		y = _y;
	}
	bool operator==(const CtPosition& _pos) {
		if ((x == _pos.x) &&
			(y == _pos.y)) {
			return true;
		}
		return false;
	}
	bool operator!=(const CtPosition& _pos) {
		if ((x == _pos.x) &&
			(y == _pos.y)) {
			return false;
		}
		return true;
	}
};

//Container/tk/Window/ws
struct CtSize {
	short width;
	short height;

	CtSize() {
		width = 0;
		height = 0;
	}
	CtSize(short _width, short _height) {
		width = _width;
		height = _height;
	}
	void setSize(short _width, short _height) {
		width = _width;
		height = _height;
	}
	void setSize(CtSize _size) {
		width = _size.width;
		height = _size.height;
	}
	CtSize& operator=(const CtSize& _size) {
		setSize(_size);
		return *this;
	}
	bool operator==(const CtSize& _size) {
		if ((_size.width == width) && (_size.height == height))
			return true;
		return false;
	}
	bool operator!=(const CtSize& _size) {
		if ((_size.width == width) && (_size.height == height))
			return false;
		return true;
	}
	bool isAuto() {
		if ((width == 0) && (height == 0))
			return true;
		return false;
	}
	bool isValid() {
		if ((width <= 0) || (height <= 0))
			return false;
		return true;
	}
};

struct CtRegion {
	short x;
	short y;
	short width;
	short height;

	CtRegion() {
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}
	CtRegion(short _x, short _y, short _width, short _height) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}
	void setRegion(short _x, short _y, short _width, short _height) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
	}
	void setRegion(const CtRegion& _region) {
		x = _region.x;
		y = _region.y;
		width = _region.width;
		height = _region.height;
	}
	bool operator&(const CtRegion& _region) {
		if (_region.width <= 0 || _region.height <= 0)
			return false;
		
		if ((_region.x                    <= x +width -1)  &&
			(_region.y                    <= y +height -1) &&
			(_region.x +_region.width -1  >= x) &&
			(_region.y +_region.height -1 >= y)) {
			return true;
		}
		return false;
	}
	bool operator&(const CtPosition& _pos) {
		if ((x <= _pos.x) && (_pos.x <= (x + width -1)) &&
			(y <= _pos.y) && (_pos.y <= (y + height -1))) {
			return true;
		}
		return false;
	}
	CtRegion& operator|=(const CtRegion& _region) {
		if (_region.width <= 0 || _region.height <= 0) 
			return *this;

		if (width <= 0 || height <= 0) {
			x = _region.x;
			y = _region.y;
			width = _region.width;
			height = _region.height;
			return *this;
		}
		
		//x0 (左端)
		int x0 = (x < _region.x) ? x : _region.x;
		//y0 (上端)
		int y0 = (y < _region.y) ? y : _region.y;
		//x1 (右端)
		int x1 = ((x + width) > (_region.x + _region.width)) ? (x + width) : (_region.x + _region.width);
		//y1 (下端)
		int y1 = ((y + height) > (_region.y + _region.height)) ? (y + height) : (_region.y + _region.height);

		x = x0;/* pgr0351 */
		y = y0;/* pgr0351 */
		width = x1 - x0;/* pgr0351 */
		height = y1 - y0;/* pgr0351 */
		if (width < 0) width = 0;
		if (height < 0) height = 0;
		
		return *this;
		
	}
	CtRegion& operator&=(const CtRegion& _region) {
		if (_region.width <= 0 || _region.height <= 0)
			return *this;
		if (width <= 0 || height <= 0) {
			x = _region.x;
			y = _region.y;
			width = _region.width;
			height = _region.height;
			return *this;
		}
		
		//x0 (左端)
		int x0 = (x > _region.x) ? x : _region.x;
		//y0 (上端)
		int y0 = (y > _region.y) ? y : _region.y;
		//x1 (右端)
		int x1 = ((x + width) < (_region.x + _region.width)) ? (x + width) : (_region.x + _region.width);
		//y1 (下端)
		int y1 = ((y + height) < (_region.y + _region.height)) ? (y + height) : (_region.y + _region.height);

		x = x0;/* pgr0351 */
		y = y0;/* pgr0351 */
		width = x1 - x0;/* pgr0351 */
		height = y1 - y0;/* pgr0351 */
		if (width < 0) width = 0;
		if (height < 0) height = 0;
		
		return *this;
	}
	bool isContains(const CtRegion& _region) const {
		if ((_region.x     <= x) &&
			(x +width -1   <= _region.x +_region.width -1) &&
			(_region.y     <= y) &&
			(y + height -1 <= _region.y +_region.height -1)) {
			return true;
		}
		return false;
	}
	bool isContains(const CtPosition& _pos) const {
		if ((x <= _pos.x) && (_pos.x <= (x + width -1)) &&
			(y <= _pos.y) && (_pos.y <= (y + height -1))) {
			return true;
		}
		return false;
	}
	bool isValid() const {
		if ((width <= 0) || (height <= 0))
			return false;
		return true;
	}
	bool isAuto() const{
		if ((width == 0) || (height == 0))
			return true;
		return false;
	}
	CtRegion& operator=(const CtRegion& _region) {
		setRegion(_region);
		return *this;
	}
	bool operator==(const CtRegion& _region) {
		if ((x != _region.x) ||
			(y != _region.y) ||
			(width != _region.width) ||
			(height != _region.height)) {
			return false;
		}
		return true;
	}
	bool operator!=(const CtRegion& _region) {
		if ((x != _region.x) ||
			(y != _region.y) ||
			(width != _region.width) ||
			(height != _region.height)) {
			return true;
		}
		return false;
	}
};

struct CtMargin {
	short Top;
	short Bottom;
	short Left;
	short Right;

	CtMargin() {
		Top = 0;
		Bottom = 0;
		Left = 0;
		Right = 0;
	}
	CtMargin(short margin) {
		Top = margin;
		Bottom = margin;
		Left = margin;
		Right = margin;
	}
	CtMargin(short vmargin, short hmargin) {
		Top = vmargin;
		Bottom = vmargin;
		Left = hmargin;
		Right = hmargin;
	}
	CtMargin(short top, short bottom, short left, short right) {
		Top = top;
		Bottom = bottom;
		Left = left;
		Right = right;
	};		
	CtMargin(const CtMargin& _margin) {
		Top = _margin.Top;
		Bottom = _margin.Bottom;
		Left = _margin.Left;
		Right = _margin.Right;
	}
	void setMargin(short margin) {
		Top = margin;
		Bottom = margin;
		Left = margin;
		Right = margin;
	}
	void setMargin(short vmargin, short hmargin) {
		Top = vmargin;
		Bottom = vmargin;
		Left = hmargin;
		Right = hmargin;
	}
	void setMargin(short top, short bottom, short left, short right) {
		Top = top;
		Bottom = bottom;
		Left = left;
		Right = right;
	}
	void setMargin(const CtMargin& _margin) {
		Top = _margin.Top;
		Bottom = _margin.Bottom;
		Left = _margin.Left;
		Right = _margin.Right;
	}
	CtMargin& operator=(const CtMargin& _margin) {
		Top = _margin.Top;
		Bottom = _margin.Bottom;
		Right = _margin.Right;
		Left = _margin.Left;
		return *this;
	}
	bool operator==(const CtMargin& _margin) {
		if ((Top == _margin.Top) &&
			(Bottom == _margin.Bottom) &&
			(Right == _margin.Right) &&
			(Left == _margin.Left)) {
			return true;
		}
		return false;
	}
	bool operator!=(const CtMargin& _margin) {
		if ((Top == _margin.Top) &&
			(Bottom == _margin.Bottom) &&
			(Right == _margin.Right) &&
			(Left == _margin.Left)) {
			return false;
		}
		return true;
	}
};

//tk
enum CtAlign {
	AlignInvalid	= 0x00,		// 無効値(使えない値)
	AlignVCenter	= 0x01,
	AlignTop		= 0x02,
	AlignBottom		= 0x03,
	AlignHCenter	= 0x10,
	AlignLeft		= 0x20,
	AlignRight		= 0x30,
	AlignCenter		= (AlignVCenter|AlignHCenter),
	AlignVMask		= (AlignVCenter|AlignTop|AlignBottom),
	AlignHMask		= (AlignHCenter|AlignLeft|AlignRight)

};

enum CtAspectRatio {
	AspectRatio_Default,
	AspectRatio_Original,
	AspectRatio_Same,
	AspectRatio_Wide,
	AspectRatio_Narrow,
	AspectRatio_Special
};


enum CtColorFormat {
	Format_RGBA8888,
	Format_RGBA4444,
	Format_YUV422,
	Format_YUV420,
	Format_Window,
	Format_None
};

//tk/ws
enum CtNotifyType {
	CtNotifyError,
	CtNotifyTransitionComplete,
};

enum CtScreenSel {
	ScreenNone 		= 0x00,
	ScreenMaster  	= 0x01,
	ScreenLCD		= ScreenMaster,
	ScreenSlave1 	= 0x02,
	ScreenLOUT		= ScreenSlave1,
	ScreenSlave2	= 0x04,
	ScreenSlave3	= 0x08,
	ScreenAll  		= (ScreenLCD | ScreenLOUT)
};

struct CtScreenInfo {
	CtScreenSel			ScreenSel;
	bool				Valid;
	CtColorFormat		Format;
	CtSize				Size;
	GDI_HANDLER			Handler;
};

enum CtEventFilter {
	EventNone    = 0x00,
	EventKey     = (1<<0),
	EventTouch   = (1<<1),
	EventParam   = (1<<2),
	EventTimer   = (1<<3),
	EventFlash   = (1<<4),
	EventButton  = (1<<5),
	EventWidget	 = (1<<6),
	EventInvalid = (1<<7),

	EventDefault	= (EventKey|EventTouch|EventButton|EventParam|EventTimer),
	EventAll		= (EventKey|EventTouch|EventParam|EventTimer|EventFlash|EventButton|EventWidget),
	EventDelivery	= (EventKey|EventTouch|EventParam|EventButton)
};

struct CtWindowInfo {
	CtWindowID		WindowID;
	CtScreenSel		ScreenSel;
	CtEventFilter 	EventFilter;
	bool			TransView;
	bool			TransEvent;
	bool			FocusSilent;
#if 1
	CtWindowInfo() {
		WindowID = WindowNone;
		ScreenSel = ScreenNone;
		EventFilter = EventDefault;
		TransEvent = false;
		TransView = false;
		FocusSilent = true;
	}
#endif

};

typedef void(*CtNotifyFunc)(CtScreenSel screen, CtWindowID id, CtNotifyType type, void* param);
typedef void(*CtWindowFunc)(CtScreenSel screen, CtWindowID id_win, CtFuncID id_func, CtWindowContents* contents);

struct CtScreenConfig {
	int 				ScreenNo;
	GDI_COLOR_FORMAT	Format;
	CtSize				Size;
	GFX_PLANE_ID		PlaneId;
};

#endif
