
#ifndef _CtMplDbg_H_
#define _CtMplDbg_H_

// MPL�̉���R��A���d����`�F�b�N���s���ꍇ�͉��L��L����
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

	static list<mpl_info*> m_List;		//!< �擾�ς�mpl�A�h���X���X�g
	static list<void*> m_DFList;		//!< ���d����A�h���X���X�g
	static int m_LeakCnt;				//!< ���J����mpl�A�h���X��
	static int m_DoubleFreeCnt;			//!< �擾���ĂȂ��̂ɉ������mpl�A�h���X��
	static void* m_DelTrigerAddress;	//!< �w��A�h���X��delete��trace_point�Ăяo��
	
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

