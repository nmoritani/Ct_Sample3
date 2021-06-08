/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtFastDrawContainerTcgWarning
 */


#ifndef __CtFastDrawContainerTcgWarning_H__
#define __CtFastDrawContainerTcgWarning_H__

#include "CtContainer.h"
#include "CtWindowCommon.h"

class CtFastDrawContainerTcgWarning : public CtContainer {

	typedef CtVector::Vector<GDI_HANDLER> GDIHandlerList;

	typedef enum IconParts {
		IconParts_TCG,
		IconParts_TCG_SLAVE,
		IconParts_UBG,
		IconParts_DUR,
		IconParts_WARNING,
		IconParts_ALERT,
		IconParts_Max
	}IconParts;

public :
    CtFastDrawContainerTcgWarning();
    virtual ~CtFastDrawContainerTcgWarning();

	CtLayout* createContainer();
	bool destroyContainer();

	bool updateFastDraw();
	bool initialFastDraw();
	bool cleanupFastDraw();

protected:

private :
	CtLabel*	   m_pLabel;
	GDIHandlerList m_hList;
	
	bool isDispWarningAlert();
	bool isDispWarning();
	bool isDispAlert();
	
};


#endif
