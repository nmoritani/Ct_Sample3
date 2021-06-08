/**
*  Copyright(c) 2018 Persol AVC Technology.
*  Element:			CtTsInterface
*/

#ifndef __CtTsInterface_H__
#define __CtTsInterface_H__

#include "Ct.h"
#include "CtClass.h"
#include "CtObject.h"
#include "CtLabel.h"
#include "gdi.h"

class CtTsInterface : public CtObject
{
public:
	virtual ~CtTsInterface();
	static CtTsInterface* getInstance();

	/// タイムスタンプ描画関連
	int setFormat(CtColorFormat format);
	GDI_HANDLER createBase(const CtSize &size, const CtColor &fillColor);
	GDI_HANDLER createDrawable(char c, const CtSize &size, const CtColor &fillColor, const CtColor &fontColor);
	GDI_HANDLER createDrawable(const char *str, const CtSize &size, const CtColor &fillColor, const CtColor &fontColor);

private:
	CtTsInterface();
	static CtTsInterface* m_pInstance;

	CtColorFormat m_Format;
};

#endif
