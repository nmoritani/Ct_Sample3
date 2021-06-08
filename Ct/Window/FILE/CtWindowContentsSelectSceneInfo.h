#ifndef __CtWindowContentsSelectSceneInfo_H__
#define __CtWindowContentsSelectSceneInfo_H__

#include "CtWindowContents.h"

class CtWindowContentsSelectSceneInfo : public CtWindowContents {
public :
	
	typedef enum ScenefileNo{
		ScenefileNo_All,
		ScenefileNo_1,
		ScenefileNo_2,
		ScenefileNo_3,
		ScenefileNo_4,
		ScenefileNo_5,
		ScenefileNo_6,
	}ScenefileNo;
	
	CtWindowContentsSelectSceneInfo(const CtWindowID WindowID);
	CtWindowContentsSelectSceneInfo(CtWindowContentsSelectSceneInfo& contentsFile);
	virtual ~CtWindowContentsSelectSceneInfo();

    ScenefileNo getSceneFileNo();
	void setSceneFileNo(ScenefileNo No);

private :
    ScenefileNo m_SceneFileNo;

};

#endif
