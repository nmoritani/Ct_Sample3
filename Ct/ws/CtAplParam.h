
#if !defined(__CTAPLPARAM_H__)
#define __CTAPLPARAM_H__

#include "AplParamService.h"

typedef enum _CtParamState {
	CtParamState_Visible,		/* 有効表示 */
	CtParamState_Invalid,		/* 無効表示 */
	CtParamState_Invisible,		/* 非表示   */
	CtParamState_End,			/* 終了     */
}CtParamState;

class CtAplParam {
public:
	static int getData(int id);
	static int getLanguage();
	static int getCharLuminance();
	static int getSdiIndicatorDisp();
	static int getHdmiIndicatorDisp();
	static CtParamState getState(int id, int val);

private:
	CtAplParam(){}
};

#endif // !defined(__CTAPLPARAM_H__)
