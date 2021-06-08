#ifdef WIN32_GUI_SIM

// std::listを使用するためシミュレータ環境限定

#include "CtObject.h"
#include"CtMplDbg.h"
#include "windows.h"
#include "CtWidget.h"

#ifdef CT_CHECK_MPL_LEAK

list<mpl_info*> CtMplDbg::m_List;
list<void*> CtMplDbg::m_DFList;

int CtMplDbg::m_LeakCnt = 0;
int CtMplDbg::m_DoubleFreeCnt = 0;
void* CtMplDbg::m_DelTrigerAddress = NULL;

static bool m_Init = false;
static CRITICAL_SECTION m_CriticalSection;

void CtMplDbg::trace_point(void*addr, int size)
{
	// 次のコード上で 「右クリック」>「ブレークポイント」>「トレースポイントの挿入」 して
	// 以下の構文を入力するとnew呼び出し箇所のバックトレースが出力タブに表示される
	// トレースメッセージ構文:   addr{addr}, size:{size}, $CALLSTACK
	volatile int i = 0;
}

void CtMplDbg::Add(void* ptr, int size, ID mplid)
{
	if (!m_Init) {
		m_Init = true;
		InitializeCriticalSection(&m_CriticalSection);
	}

	EnterCriticalSection(&m_CriticalSection);

	mpl_info *info = new mpl_info();
	info->ptr = ptr;
	info->size = size;

	m_List.push_back(info);
	m_LeakCnt = m_List.size();

	// 呼び出し箇所のバックトレース出力(重いのでデフォルトOFF)
	// ONにする場合も特定Sizeに限定したほうがよい
	if (0) {
		trace_point(ptr, size);
	}

	// MPLの情報出力
	if (0) {
		T_RMPL rmpl;
		ref_mpl(mplid, &rmpl);
		printf("size: %d, rmpl.fblksz : %6d, fmplsz : %d, get:%p\n", size, rmpl.fblksz, rmpl.fmplsz, ptr);
	}

	LeaveCriticalSection(&m_CriticalSection);
}

// delete処理でトレース出力するアドレスの設定
void CtMplDbg::setDelTrigerAddress(void *ptr)
{
	m_DelTrigerAddress = ptr;
}

void CtMplDbg::Del(void* ptr)
{
	EnterCriticalSection(&m_CriticalSection);

	// 多重deleteチェック用
	// 指定アドレスのdelete処理でトレース出力する
	if( m_DelTrigerAddress && m_DelTrigerAddress == ptr ){
		trace_point(ptr, 0);
	}

	list<mpl_info*>::iterator itr = m_List.begin();
	for( list<mpl_info*>::iterator itr = m_List.begin(); itr != m_List.end(); ++itr){
		if( (*itr)->ptr == ptr ){
			m_List.remove(*itr);
			m_LeakCnt = m_List.size();
			goto end;
		}
	}

	m_DoubleFreeCnt++;

	for( list<void*>::iterator itr = m_DFList.begin(); itr != m_DFList.end(); ++itr){
		if( (*itr) == ptr ){		
			goto end;
		}
	}
	
	m_DFList.push_back(ptr);

end:
	LeaveCriticalSection(&m_CriticalSection);
}

#ifdef WIN32_GUI_SIM
#include <typeinfo.h>
#endif

void CtMplDbg::Output()
{
	EnterCriticalSection(&m_CriticalSection);

	list<mpl_info*> leaklist = m_List;
	int cnt = leaklist.size();

	printf("------ CtMplDbg ------\n");
	printf("--LeakAddress--\n");
	for(int i=0; i<cnt; i++){
		CtObject*pObj = reinterpret_cast<CtObject*>(leaklist.front()->ptr);
		CtClassType classtype = pObj->getClassType();

		const char* classname = NULL;
#ifdef WIN32_GUI_SIM
		if (classtype > CtClassType_WidgetMin && classtype < CtClassType_WidgetMax) {
			classname = typeid(*static_cast<CtWidget*>(pObj)).name();
		}
		else if (classtype > CtClassType_EventHandlerMin && classtype < CtClassType_EventHandlerMax) {
			classname = typeid(*static_cast<CtEventHandler*>(pObj)).name();
		}
		else if (classtype == CtClassType_DrawInfo) {
			classname = typeid(*static_cast<CtDrawInfo*>(pObj)).name();
		}
#endif
		printf("Adr:%#p, Size:%4d, Type:0x%08x(%s)", pObj, leaklist.front()->size, classtype, ClassType_to_Str(classtype));
		if(classname) printf(", Name:%s\n", classname);
		else printf("\n");

		leaklist.pop_front();
	}

	printf("--DoubleFreeAddress--\n");

	for( list<void*>::iterator itr = m_DFList.begin(); itr != m_DFList.end(); ++itr){
		printf("Adr:%#p\n", (*itr));
	}

	printf(" m_LeakCnt       : %d\n", cnt);
	printf(" m_DoubleFreeCnt : %d\n", m_DoubleFreeCnt);
	printf("----------------------\n");

	LeaveCriticalSection(&m_CriticalSection);
}

#define STR(x)  (#x)

const char* CtMplDbg::ClassType_to_Str(CtClassType type)
{
	static const char *list[] = {
		STR(CtClassType_MIN),
		STR(CtClassType_ListNodeBase),
		STR(CtClassType_ListNode),
		STR(CtClassType_List),
		STR(CtClassType_Vector),
		STR(CtClassType_VectorNode),
		STR(CtClassType_TimerInfoCyclic),
		STR(CtClassType_TimerInfoAlarm),
		STR(CtClassType_WindowController),
		STR(CtClassType_WindowFactory),
		STR(CtClassType_WindowList),
		STR(CtClassType_DrawInfo),
		STR(CtClassType_Interface),
		STR(CtClassType_Draw),
		STR(CtClassType_DbgCommandReceiver),
		STR(CtClassType_SysEventTranslator),
		STR(CtClassType_Element),
		STR(CtClassType_SplitElement),
		STR(CtClassType_SpanElement),

		STR(CtClassType_WindowContents),
		STR(CtClassType_ContentsParamSet),

		STR(CtClassType_EventHandlerMin),
		STR(CtClassType_EventHandler),
		STR(CtClassType_Container),
		STR(CtClassType_Container),
		STR(CtClassType_LayoutMain),
		STR(CtClassType_Flash),
		STR(CtClassType_FlashInfo),
		STR(CtClassType_Timer),
		STR(CtClassType_CacheControl),
		STR(CtClassType_EventHandlerMax),

		STR(CtClassType_WindowMain),
		STR(CtClassType_WindowMenuList),
		STR(CtClassType_WindowSpinBox),
		STR(CtClassType_WindowToggleDialog),
		STR(CtClassType_WindowDialog),
		STR(CtClassType_WindowKeyboard),
		STR(CtClassType_WindowMenu2List),
		STR(CtClassType_WindowFILE),
		STR(CtClassType_WindowNETWORK),
		STR(CtClassType_WindowNETWORK_USER),
		STR(CtClassType_WindowNETWORK_INFO),
		STR(CtClassType_WindowFACT),
		STR(CtClassType_WindowMessageDialog),
		STR(CtClassType_WindowMessageTelop),

		STR(CtClassType_WidgetMin),
		STR(CtClassType_Widget),
		STR(CtClassType_Label),
		STR(CtClassType_ScrollBar),
		STR(CtClassType_SlideLabel),
		STR(CtClassType_StackLabel),
		STR(CtClassType_StackLayout),
		STR(CtClassType_ParamLabel),
		STR(CtClassType_ParamIcon),
		STR(CtClassType_BarMeter),
		STR(CtClassType_Slider),
		STR(CtClassType_TextField),
		STR(CtClassType_TextArea),
		STR(CtClassType_Button),
		STR(CtClassType_MenuButton),
		STR(CtClassType_MenuCheckButton),
		STR(CtClassType_ParamBox),
		STR(CtClassType_LinkButton),
		STR(CtClassType_CheckBox),
		STR(CtClassType_RadioButton),
		STR(CtClassType_Layout),
		STR(CtClassType_Window),
		STR(CtClassType_ListView),
		STR(CtClassType_GridView),
		STR(CtClassType_WidgetMax),

		STR(CtClassType_Msg),
		STR(CtClassType_MsgDbgCommand),
		STR(CtClassType_EventCommand),
		STR(CtClassType_EventTimer),
		STR(CtClassType_EventParam),
		STR(CtClassType_EventWidget),
		STR(CtClassType_EventDrawResult),
		STR(CtClassType_MAX),
	};

	if (type >= CtClassType_MIN && type <= CtClassType_MAX) {
		return list[type - CtClassType_MIN] + 12 /* "CtClassType_" */;
	}

	return "unknown";
}

#endif // CT_CHECK_MPL_LEAK

#endif // WIN32_GUI_SIM

