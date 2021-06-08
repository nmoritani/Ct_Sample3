
#ifndef CtClassType_H
#define CtClassType_H

typedef enum CtClassType {
	/* CtObject関連 */
    CtClassType_MIN = 0x8000,
    CtClassType_ListNodeBase,
    CtClassType_ListNode,
    CtClassType_List,
	CtClassType_Vector,
	CtClassType_VectorNode,
	CtClassType_TimerInfoCyclic,
	CtClassType_TimerInfoAlarm,
	CtClassType_WindowController,
	CtClassType_WindowFactory,
	CtClassType_WindowList,
	CtClassType_DrawInfo,
	CtClassType_Interface,
	CtClassType_Draw,
	CtClassType_DbgCommandReceiver,
	CtClassType_SysEventTranslator,
	CtClassType_Element,
	CtClassType_SplitElement,
	CtClassType_SpanElement,

	/* CtWindowContents関連 */
	CtClassType_WindowContents,
	CtClassType_ContentsParamSet,

	/* CtEventHandler関連 */
	CtClassType_EventHandlerMin,
	CtClassType_EventHandler,
	CtClassType_Container,
	CtClassType_LayoutMain,
	CtClassType_Flash,
	CtClassType_FlashInfo,
	CtClassType_Timer,
	CtClassType_CacheControl,
	CtClassType_EventHandlerMax,

	/* CtWindowMain関連*/
	CtClassType_WindowMain,
	CtClassType_WindowMenuList,
	CtClassType_WindowSpinBox,
	CtClassType_WindowToggleDialog,
	CtClassType_WindowDialog,
	CtClassType_WindowKeyboard,
	CtClassType_WindowMenu2List,
	CtClassType_WindowFILE,
	CtClassType_WindowNETWORK,
	CtClassType_WindowNETWORK_USER,
	CtClassType_WindowNETWORK_INFO,
	CtClassType_WindowFACT,
	CtClassType_WindowAreaSetting,
	CtClassType_WindowMessageDialog,
	CtClassType_WindowMessageTelop,

	/* CtWidget関連 */
	CtClassType_WidgetMin,
	CtClassType_Widget,
	CtClassType_Label,
	CtClassType_ScrollBar,
	CtClassType_SlideLabel,
	CtClassType_StackLabel,
	CtClassType_StackLayout,
	CtClassType_ParamLabel,
	CtClassType_ParamIcon,
	CtClassType_BarMeter,
	CtClassType_Slider,
	CtClassType_TextField,
	CtClassType_TextArea,
	CtClassType_Button,
	CtClassType_MenuButton,
	CtClassType_MenuCheckButton,
	CtClassType_ParamBox,
	CtClassType_LinkButton,
	CtClassType_CheckBox,
	CtClassType_RadioButton,
	CtClassType_Layout,
	CtClassType_Window,
	CtClassType_ListView,
	CtClassType_GridView,
	CtClassType_WidgetMax,
	
	/* CtMsg関連 */
	CtClassType_Msg,
	CtClassType_MsgDbgCommand,
	CtClassType_EventCommand,
	CtClassType_EventTimer,
	CtClassType_EventParam,
	CtClassType_EventWidget,
	CtClassType_EventDrawResult,

	CtClassType_MAX
} CtClassType;

#endif
