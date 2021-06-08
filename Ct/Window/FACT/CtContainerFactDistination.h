/**
 *  Copyright (c) 2018 Persol AVC Technology.
 *  Element:			_CtContainerFactDistination
 */


#ifndef __CtContainerFactDistination_H__
#define __CtContainerFactDistination_H__

#include "CtContainer.h"
#include "CtMenuButton.h"
#include "CtMenuListView.h"
#include "CtVector.h"
#include "CtWindowCommon.h"
#include "CtWindowContentsFactDistination.h"

#include "CtContainerVariableMenuList.h"

class CtContainerFactDistination : public CtContainer
{
public :

    CtContainerFactDistination( CtWindowID id, CtWindowContents* pContents );

    virtual ~CtContainerFactDistination();

	CtLayout* createContainer();

    bool setContents(const CtWindowContents* pContents);

    bool updateContents();

	bool destroyContainer();

	bool handleButtonEvent(const CtEventButton& Button);

protected:

private :

    CtLayout*       getFactDistinationLayout( int index );

    void            update_ListView();

public:

protected:

private:

    CtWindowID      m_id;

    CtWindowContentsFactDistination*	m_pContents;

	CtContainerVariableMenuList*		m_MenuList;

};

#endif
