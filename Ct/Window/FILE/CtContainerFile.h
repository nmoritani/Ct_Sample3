/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			_CtContainerFile
 */


#ifndef __CtContainerFile_H__
#define __CtContainerFile_H__

#include "CtContainer.h"
#include "CtMenuButton.h"
#include "CtVector.h"
#include "CtWindowContentsFileInfo.h"

#include "CtContainerVariableMenuList.h"


class CtContainerFile : public CtContainer
{
public :

    CtContainerFile( CtWindowID id, CtWindowContents* pContents );

    virtual ~CtContainerFile();

	CtLayout* createContainer();

    bool setContents(const CtWindowContents* pContents);

    void updateContents();

	bool destroyContainer();

	bool handleButtonEvent(const CtEventButton& Button);

protected:

private :

    CtLayout*       getFileInfoLayout( int index );

    void            update_ListView();

public:

protected:

private:

    CtWindowID						m_id;

    CtWindowContentsFileInfo*		m_pContentsFile;

	CtContainerVariableMenuList*	m_MenuList;

};

#endif
