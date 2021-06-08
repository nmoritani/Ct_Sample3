#include "CtWindowContentsFactDistination.h"

CtFactDistination::CtFactDistination() {
	memset(&m_FactDistination, 0, sizeof(m_FactDistination));
}

CtFactDistination::CtFactDistination(CtFactDistination& obj) {	/* pgr2222 */
	memset(&m_FactDistination, 0, sizeof(m_FactDistination));
	m_FactDistination = obj.getFactDistination();
}

CtFactDistination::~CtFactDistination() {
}

CtFactDistination::FactDistination CtFactDistination::getFactDistination() {
	return m_FactDistination;
}

void CtFactDistination::setFactDistination(CtFactDistination::FactDistination& info) {
	m_FactDistination = info;
}

CtWindowContentsFactDistination::CtWindowContentsFactDistination(const CtWindowID WindowID) : CtWindowContents(WindowID), m_FactDistinationList(0), m_Index(0)  {
}

CtWindowContentsFactDistination::CtWindowContentsFactDistination(CtWindowContentsFactDistination& contents) : CtWindowContents(contents.getType()) {
	
	m_Index = contents.getCurrentIndex();
    FactDistinationList& list = contents.getFactDistinationList();

	for (FactDistinationListItr Itr = list.begin(); Itr != list.end(); ++Itr) {
		CtFactDistination* FactDistination = new CtFactDistination(*(*Itr));
		m_FactDistinationList.push_back(FactDistination);
	}
}

void CtWindowContentsFactDistination::setFactDistinationList(CtFactDistination* pCtFactDistination){

    CtFactDistination* p1 = pCtFactDistination;
    int index = this->getCurrentIndex();
    int i = 0;
	
	if( p1 != NULL ){
	    for (; p1 != NULL; p1++,i++){	/* pgr0689 */
	        if (i > index){
	            break;
	        }else{
	            m_FactDistinationList.push_back(p1);
	        }
	    }
	}
}

CtWindowContentsFactDistination::~CtWindowContentsFactDistination() {
	removeAllFactDistination();
}
	
CtWindowContentsFactDistination::FactDistinationList& CtWindowContentsFactDistination::getFactDistinationList() {
	return m_FactDistinationList;
}

void CtWindowContentsFactDistination::removeAllFactDistination() {
	for (int i = 0; i< m_FactDistinationList.size(); i++) {
		if (m_FactDistinationList[i] != NULL) {
			delete m_FactDistinationList[i];
			m_FactDistinationList[i] = NULL;
		}
	}
}

void CtWindowContentsFactDistination::setCurrentIndex(unsigned long Index) {
	m_Index = Index;
}

unsigned long CtWindowContentsFactDistination::getCurrentIndex() {
	return m_Index;
}
