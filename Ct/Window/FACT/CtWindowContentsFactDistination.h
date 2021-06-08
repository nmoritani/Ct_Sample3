#ifndef __CtWindowContentsFactDistination_H__
#define __CtWindowContentsFactDistination_H__

#include "CtWindowContents.h"
#include "CtVector.h"

class CtFactDistination : public CtObject {
public :

	typedef struct FactDistination {
		char name[50];
	} FactDistination;

	CtFactDistination();
	CtFactDistination(CtFactDistination& obj);
	virtual ~CtFactDistination();
	
	FactDistination getFactDistination();
	void setFactDistination(FactDistination& info);

private :
	FactDistination m_FactDistination;

};

class CtWindowContentsFactDistination : public CtWindowContents {
public :
	typedef CtVector::Vector<CtFactDistination*> FactDistinationList;
	typedef CtVector::Vector<CtFactDistination*>::iterator FactDistinationListItr;
	
	CtWindowContentsFactDistination(const CtWindowID WindowID);
	CtWindowContentsFactDistination(CtWindowContentsFactDistination& contents);
	virtual ~CtWindowContentsFactDistination();
	
	FactDistinationList& getFactDistinationList();

    void setFactDistinationList(CtFactDistination* pCtFactDistination);

    unsigned long getCurrentIndex();
	void setCurrentIndex(unsigned long Index);

private :
	void removeAllFactDistination();
	
	FactDistinationList m_FactDistinationList;

    unsigned long m_Index;
};

#endif
