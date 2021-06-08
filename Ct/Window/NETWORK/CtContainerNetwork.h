/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			_CtContainerNetwork
 */


#ifndef __CtContainerNetwork_H__
#define __CtContainerNetwork_H__

#include "CtContainer.h"
#include "CtWindowCommon.h"
#include "CtVector.h"
#include "CtMenuButton.h"
#include "CtWindowContentsApInfo.h"
#include "CtWindowContentsSelectSceneInfo.h"

#include "CtContainerVariableMenuList.h"

class CtContainerNetwork : public CtContainer
{
public :

    CtContainerNetwork( CtWindowID id, CtWindowContents* pContents );

    virtual ~CtContainerNetwork();

	CtLayout* createContainer();

    bool setContents(const CtWindowContents* pContents);

    void updateContents();

	bool destroyContainer();

	bool handleButtonEvent(const CtEventButton& Button);


	
protected:

private :

    CtLayout*       getApInfoLayout( int index );

    void            update_ListView();

public:

protected:

private:

    CtWindowID						m_id;

    CtWindowContentsApInfo*			m_pContents;

	CtContainerVariableMenuList*	m_MenuList;
};

#endif
