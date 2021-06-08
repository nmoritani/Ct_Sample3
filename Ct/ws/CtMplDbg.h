
#ifndef _CtMplDbg_H_
#define _CtMplDbg_H_

// MPLの解放漏れ、多重解放チェックを行う場合は下記を有効化
//#define CT_CHECK_MPL_LEAK

#if defined(WIN32_GUI_SIM) && defined(CT_CHECK_MPL_LEAK)

#include <list>
using namespace std;

struct mpl_info{
	void *ptr;
	int size;
};

class CtMplDbg
{
public:
	static void Add(void* ptr, int size, ID mplid);
	static void Del(void* ptr);
	static void Output();
	static const char* ClassType_to_Str(CtClassType type);
	static void setDelTrigerAddress(void*);

	static list<mpl_info*> m_List;		//!< 取得済みmplアドレスリスト
	static list<void*> m_DFList;		//!< 多重解放アドレスリスト
	static int m_LeakCnt;				//!< 未開放なmplアドレス数
	static int m_DoubleFreeCnt;			//!< 取得してないのに解放したmplアドレス数
	static void* m_DelTrigerAddress;	//!< 指定アドレスのdeleteでtrace_point呼び出す
	
private:
	static void trace_point(void*addr, int size);
};

#define MPLDBG_ADD(ptr,size,mplid)	CtMplDbg::Add(ptr,size,mplid);
#define MPLDBG_DEL(ptr)				CtMplDbg::Del(ptr)
#define MPLDBG_PRINT()				CtMplDbg::Output()

#else // defined(WIN32_GUI_SIM) && defined(CT_CHECK_MPL_LEAK)

#define MPLDBG_ADD(ptr,size,id)
#define MPLDBG_DEL(ptr)
#define MPLDBG_PRINT()

class CtMplDbg
{
public:
	static void Output() {}
};

#endif

#endif // _CtMplDbg_H_

