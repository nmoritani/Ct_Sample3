#include "CtTsInterface.h"
#include "CtLayout.h"
#include "gdi_local.h"

CtTsInterface* CtTsInterface::m_pInstance = NULL;

CtTsInterface::CtTsInterface()
{
	setClassType(CtClassType_Interface);

	m_Format = Format_RGBA4444;
}


CtTsInterface::~CtTsInterface()
{
}

CtTsInterface* CtTsInterface::getInstance()
{
	if (!m_pInstance) {
		m_pInstance = new CtTsInterface();
	}
	return m_pInstance;
}


int CtTsInterface::setFormat(CtColorFormat format)
{
	switch (format) {
	case Format_RGBA8888:
	case Format_RGBA4444:
	case Format_YUV422:
	case Format_YUV420:
		break;
	default:
		return -1;
	}

	m_Format = format;

	return 0;
}

GDI_HANDLER CtTsInterface::createBase(const CtSize &size, const CtColor &fillColor)
{
	CtLabel *base = new CtLabel(size, CtFill(fillColor));

	// @todo 10bit‘Î‰ž
	GDI_HANDLER ret = CtDraw::getInstance()->convertDrawable(base, m_Format);

	delete base;

	return ret;
}

GDI_HANDLER CtTsInterface::createDrawable(char c, const CtSize &size, const CtColor &fillColor, const CtColor& fontColor)
{
	char str[2] = { 0 };

	str[0] = c;

	return createDrawable(str, size, fillColor, fontColor);
}

GDI_HANDLER CtTsInterface::createDrawable(const char *str, const CtSize &size, const CtColor &fillColor, const CtColor& fontColor)
{
	CtFontSet fSet = CtRecViewFontSet(FontTypeNormal_alignCenter, fontColor);
	CtLayout *layout = new CtLayout(size, fillColor);
	CtLabel *label = new CtLabel(size, str, fSet);	/* pgr0541 */

	layout->addWidget(label, AlignCenter);

	GDI_HANDLER ret = CtDraw::getInstance()->convertDrawable(layout, m_Format);

	delete layout;
	delete label;

	return ret;
}



