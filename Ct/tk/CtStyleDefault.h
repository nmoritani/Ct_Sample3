/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:          CtStyleDefault
 */

#ifndef __CtStyleDefault_H__
#define __CtStyleDefault_H__

#include "CtStyle.h"

static const CtStyle::CtProperty CtStyleDefault =
{
	{// Window
		CtStyle::DefaultRegion,	// Region
		CtColor::Black,			// Background
	},
	{// Button
		2,		// StrokeWidth
		10,		// ArcWidth
		CtSize(78, 66),
		{ CtColor(0, 0, 0, 0xff),		CtColor(134, 134, 134, 0xff),	CtColor::NoColor },				// Normal (Base, Stroke, Label)
		{ CtColor(255, 216, 0, 0xff),	CtColor(255, 216, 0, 0xff),		CtColor(0, 0, 0, 0xff) },		// Selected (Base, Stroke, Label)
		{ CtColor(0, 0, 0, 0xff),		CtColor(255, 216, 0, 0xff),	CtColor::NoColor },				// Focused (Base, Stroke, Label)
		{ CtColor(46, 46, 46, 0xff),	CtColor(46, 46, 46, 0xff),		CtColor(0, 0, 0, 0xff) },		// Invalid (Base, Stroke, Label)
	},
	{// ListView
		2,		// StrokeWidth
		10,		// ArcWidth
		//		{ CtColor(0, 0, 0, 0xff),		CtColor(134, 134, 134, 0xff),	CtColor(212, 212, 212, 0xff) },	// Normal (Base, Stroke, Label)
		{ CtColor(0, 0, 0, 0xff),		CtColor(134, 134, 134, 0xff),	CtColor::NoColor },	// Normal (Base, Stroke, Label)
		{ CtColor(255, 216, 0, 0xff),	CtColor(255, 216, 0, 0xff),		CtColor(0, 0, 0, 0xff) },		// Selected (Base, Stroke, Label)
		{ CtColor(46, 46, 46, 0xff),	CtColor(46, 46, 46, 0xff),		CtColor(0, 0, 0, 0xff) },		// Invalid (Base, Stroke, Label)
	},
	{// MenuList
		2,		// StrokeWidth
		10,		// ArcWidth
		//		{ CtColor(0, 0, 0, 0xff),		CtColor(134, 134, 134, 0xff),	CtColor(212, 212, 212, 0xff) },	// Normal (Base, Stroke, Label)
		{ CtColor(0, 0, 0, 0xff),		CtColor(134, 134, 134, 0xff),	CtColor::NoColor },	// Normal (Base, Stroke, Label)
		{ CtColor(255, 216, 0, 0xff),	CtColor(255, 216, 0, 0xff),		CtColor(0, 0, 0, 0xff) },		// Selected (Base, Stroke, Label)
		{ CtColor(46, 46, 46, 0xff),	CtColor(46, 46, 46, 0xff),		CtColor(0, 0, 0, 0xff) },		// Invalid (Base, Stroke, Label)
	},
	{// ParamLabel
		{ CtColor::White,	CtColor::White,		CtColor::White },					// Valid (Base, Stroke, Label)
		{ CtColor::Cyan,	CtColor::Gray,		CtColor::Gray },					// Invalid (Base, Stroke, Label)
	},
	// FontSet
	CtFontSet(FontTypeNormal_alignCenter, CtColor::White)
};

#endif
