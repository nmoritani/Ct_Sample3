/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			_CtContainerNetworkUser
 */


#ifndef __CtContainerNetworkUser_H__
#define __CtContainerNetworkUser_H__

#include "CtWindowCommon.h"
#include "CtContainer.h"
#include "CtVLayout.h"
#include "CtHLayout.h"
#include "CtMenuListView.h"
#include "CtVector.h"
#include "CtWindowContentsUserInfo.h"

#include "CtContainerVariableMenuList.h"

class CtContainerNetworkUser : public CtContainer
{
public :

    CtContainerNetworkUser( CtWindowID id, CtWindowContents* pContents );

    virtual ~CtContainerNetworkUser();

	CtLayout* createContainer();

    bool setContents(const CtWindowContents* pContents);

    void updateContents();

	bool destroyContainer();

	bool handleButtonEvent(const CtEventButton& Button);

protected:

private :

    CtLayout*       getUserInfoLayout( int index );

    void            update_ListView();

public:

protected:

private:

    CtWindowID						m_id;
	
    CtWindowContentsUserInfo*		m_pContents;

	CtContainerVariableMenuList*	m_MenuList;

};

#endif
