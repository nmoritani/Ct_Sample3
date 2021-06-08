#include "CtWindowContentsUserInfo.h"

CtUserInfo::CtUserInfo() {
    memset(&m_UserInfo, 0, sizeof(m_UserInfo));
}

CtUserInfo::CtUserInfo(CtUserInfo& obj) {  /*•Ï”‚ÆŠÖ”“¯–¼‚Å‚·*//* pgr2222 */
    memset(&m_UserInfo, 0, sizeof(m_UserInfo));
	m_UserInfo = obj.getUserInfo();		/* pgr2222 */
}

CtUserInfo::~CtUserInfo() {
}

CtUserInfo::UserInfo CtUserInfo::getUserInfo() {
    return m_UserInfo;
}

void CtUserInfo::setUserInfo(CtUserInfo::UserInfo& info) {
	m_UserInfo = info;
}

CtWindowContentsUserInfo::CtWindowContentsUserInfo(const CtWindowID WindowID) : CtWindowContents(WindowID), m_UserInfoList(0), m_Index(0)  {
}

CtWindowContentsUserInfo::CtWindowContentsUserInfo(CtWindowContentsUserInfo& contents) : CtWindowContents(contents.getType()) {
    
    m_Index = contents.getCurrentIndex();
    UserInfoList& list = contents.getUserInfoList();

    for (UserInfoListItr Itr = list.begin(); Itr != list.end(); ++Itr) {
        CtUserInfo* UserInfo = new CtUserInfo(*(*Itr));
        m_UserInfoList.push_back(UserInfo);
    }
}

void CtWindowContentsUserInfo::setUserInfoList(CtUserInfo* pCtUserInfo){

    if (pCtUserInfo == NULL) return;
    CtUserInfo* p1 = pCtUserInfo;
    int index = this->getCurrentIndex();
    int i = 0;
    if( p1 !=NULL ){
        for (; p1 != NULL; p1++,i++){	/* pgr0689 */
            if (i > index){
                break;
            }else{
                m_UserInfoList.push_back(p1);
            }
        }
    }
}

CtWindowContentsUserInfo::~CtWindowContentsUserInfo() {
    removeAllUserInfo();
}
    
CtWindowContentsUserInfo::UserInfoList& CtWindowContentsUserInfo::getUserInfoList() {
    return m_UserInfoList;
}

void CtWindowContentsUserInfo::removeAllUserInfo() {
    for (int i = 0; i< m_UserInfoList.size(); i++) {
        if (m_UserInfoList[i] != NULL) {
            delete m_UserInfoList[i];
            m_UserInfoList[i] = NULL;
        }
    }
}

void CtWindowContentsUserInfo::setCurrentIndex(unsigned long Index) {
    m_Index = Index;
}

unsigned long CtWindowContentsUserInfo::getCurrentIndex() {
    return m_Index;
}
