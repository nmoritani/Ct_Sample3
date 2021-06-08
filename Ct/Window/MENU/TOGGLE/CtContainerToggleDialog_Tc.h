/**
 *  Copyright(c) 2018 Persol AVC Technology.
 *  Element:			CtListContainer
 */

#ifndef __CtContainerToggleDialog_Tc_H__
#define __CtContainerToggleDialog_Tc_H__

#include "CtContainerToggleDialog.h"
#include "CtContainerMenuTitle.h"

class CtContainerToggleDialog_Tc : public CtContainerToggleDialog
{
/*** �萔 ***************************************/
public:

protected:

private:

/*** ���\�b�h ***********************************/
public:
	CtContainerToggleDialog_Tc(CtWindowID id);
	virtual ~CtContainerToggleDialog_Tc();

protected:
	virtual CtLayout* createTitle();
	virtual CtLayout* createToggle();

	virtual bool executionSet();
	virtual bool executionReset();

private:
	ToggleButton createTch();
	ToggleButton createTcm();
	ToggleButton createTcs();
	ToggleButton createTcf();

/*** �����o   ***********************************/
public:

protected:

private:

};

#endif
