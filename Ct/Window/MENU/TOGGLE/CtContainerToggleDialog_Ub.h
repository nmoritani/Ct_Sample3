/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */

#ifndef __CtContainerToggleDialog_Ub_H__
#define __CtContainerToggleDialog_Ub_H__

#include "CtContainerToggleDialog.h"
#include "CtContainerMenuTitle.h"

class CtContainerToggleDialog_Ub : public CtContainerToggleDialog
{
/*** �萔 ***************************************/
public:

protected:

private:

/*** ���\�b�h ***********************************/
public:
	CtContainerToggleDialog_Ub(CtWindowID id);
	virtual ~CtContainerToggleDialog_Ub();

protected:
	virtual CtLayout* createTitle();
	virtual CtLayout* createToggle();

	virtual bool executionSet();
	virtual bool executionReset();

private:

/*** �����o   ***********************************/
public:

protected:

private:

};

#endif
