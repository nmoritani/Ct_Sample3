#include "CtWindowContentsApInfo.h"

CtApInfo::CtApInfo() {
    memset(&m_ApInfo, 0, sizeof(m_ApInfo));
}

CtApInfo::CtApInfo(CtApInfo& obj) {  /*•Ï”‚ÆŠÖ”“¯–¼‚Å‚·*//* pgr2222 */
    memset(&m_ApInfo, 0, sizeof(m_ApInfo));
	m_ApInfo = obj.getApInfo();	/* pgr2222 */
}

CtApInfo::~CtApInfo() {
}

CtApInfo::ApInfo CtApInfo::getApInfo() {
    return m_ApInfo;
}

void CtApInfo::setApInfo(CtApInfo::ApInfo& info) {
	m_ApInfo = info;
}

CtWindowContentsApInfo::CtWindowContentsApInfo(const CtWindowID WindowID) : CtWindowContents(WindowID), m_ApInfoList(0), m_Index(0)  {
}

CtWindowContentsApInfo::CtWindowContentsApInfo(CtWindowContentsApInfo& contents) : CtWindowContents(contents.getType()) {
    
    m_Index = contents.getCurrentIndex();
    ApInfoList& list = contents.getApInfoList();

    for (ApInfoListItr Itr = list.begin(); Itr != list.end(); ++Itr) {
        CtApInfo* ApInfo = new CtApInfo(*(*Itr));
        m_ApInfoList.push_back(ApInfo);
    }
}

void CtWindowContentsApInfo::setApInfoList(CtApInfo* pCtApInfo){

    if (pCtApInfo == NULL) return;
    CtApInfo* p1 = pCtApInfo;
    int index = this->getCurrentIndex();
    int i = 0;
    if( p1 !=NULL ){
        for (; p1 != NULL; p1++,i++){	/* pgr0689 */
            if (i > index){
                break;
            }else{
                m_ApInfoList.push_back(p1);
            }
        }
    }
}
    
CtWindowContentsApInfo::~CtWindowContentsApInfo() {
    removeAllApInfo();
}
    
CtWindowContentsApInfo::ApInfoList& CtWindowContentsApInfo::getApInfoList() {
    return m_ApInfoList;
}

void CtWindowContentsApInfo::removeAllApInfo() {
    for (int i = 0; i< m_ApInfoList.size(); i++) {
        if (m_ApInfoList[i] != NULL) {
            delete m_ApInfoList[i];
        }
    }
}

void CtWindowContentsApInfo::setCurrentIndex(unsigned long Index) {
    m_Index = Index;
}

unsigned long CtWindowContentsApInfo::getCurrentIndex() {
    return m_Index;
}
