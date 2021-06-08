/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtStyleWhite
 */

#ifndef __CtStyleWhite_H__
#define __CtStyleWhite_H__

#include "CtStyle.h"

static const CtStyle::CtProperty CtStyleWhite =
{
	{// Window
		CtStyle::DefaultRegion,	// Region
		CtColor::Red,				// Background
	},
	{// Button
		2,		// StrokeWidth
		10,		// ArcWidth
		CtSize(78, 66),
		{ CtColor::White,	CtColor(134, 134, 134, 0xff),	CtColor::Black },		// Normal (Base, Stroke, Label)
		{ CtColor::Cyan,	CtColor::Blue,		CtColor::White },					// Selected (Base, Stroke, Label)
		{ CtColor::Cyan,	CtColor::Gray,		CtColor::White },					// Invalid (Base, Stroke, Label)
	},
	{// ListView
		2,		// StrokeWidth
		10,		// ArcWidth
		{ CtColor::White,	CtColor(134, 134, 134, 0xff),	CtColor::Black },		// Normal (Base, Stroke, Label)
		{ CtColor::Cyan,	CtColor::Blue,		CtColor::White },					// Selected (Base, Stroke, Label)
		{ CtColor::Cyan,	CtColor::Gray,		CtColor::White },					// Invalid (Base, Stroke, Label)
	},
	{// MenuList
		2,		// StrokeWidth
		10,		// ArcWidth
		{ CtColor::White,	CtColor(134, 134, 134, 0xff),	CtColor::Black },		// Normal (Base, Stroke, Label)
		{ CtColor::Cyan,	CtColor::Blue,		CtColor::White },					// Selected (Base, Stroke, Label)
		{ CtColor::Cyan,	CtColor::Gray,		CtColor::White },					// Invalid (Base, Stroke, Label)
	},
	{// ParamLabel
		{ CtColor::White,	CtColor::White,	    CtColor::White },					// Valid (Base, Stroke, Label)
		{ CtColor::Cyan,	CtColor::Gray,		CtColor::White },					// Invalid (Base, Stroke, Label)
	},

	// FontSet
	CtFontSet(FontTypeNormal_alignCenter, CtColor::Red)
};

#endif
