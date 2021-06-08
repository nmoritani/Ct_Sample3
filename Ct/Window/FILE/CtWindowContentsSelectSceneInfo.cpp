#include "CtWindowContentsSelectSceneInfo.h"

CtWindowContentsSelectSceneInfo::CtWindowContentsSelectSceneInfo(const CtWindowID WindowID) : CtWindowContents(WindowID) {
	m_SceneFileNo = CtWindowContentsSelectSceneInfo::ScenefileNo_All;
}

CtWindowContentsSelectSceneInfo::CtWindowContentsSelectSceneInfo(CtWindowContentsSelectSceneInfo& contentsFile) : CtWindowContents(contentsFile.getType()) {
	
   m_SceneFileNo = contentsFile.getSceneFileNo();
}

	
CtWindowContentsSelectSceneInfo::~CtWindowContentsSelectSceneInfo() {
}

void CtWindowContentsSelectSceneInfo::setSceneFileNo(CtWindowContentsSelectSceneInfo::ScenefileNo No) {
	m_SceneFileNo = No;
}

CtWindowContentsSelectSceneInfo::ScenefileNo CtWindowContentsSelectSceneInfo::getSceneFileNo() {
	return m_SceneFileNo;
}
