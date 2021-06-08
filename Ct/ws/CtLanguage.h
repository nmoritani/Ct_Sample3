#if !defined(__CTLANGUAGE_H__)
#define __CTLANGUAGE_H__

#include "language_id.h"
#include "fontapi.h"
#include "gdi_string.h"

class CtLanguage {

public:
	static FONT_LOCALE getLocale(LANGUAGE_ID lang);
	static LANGUAGE_ID getLanguageID();
	static LANGUAGE_ID getLanguageID(int lang);
	static LANGUAGE_ID getLanguageID(GDI_STRING_ID STR_ID);

private:
	CtLanguage(){}


};

#endif // !defined(__CTLANGUAGE_H__)
