# ---------------------------------------------------------------------------
# GUIブロック共通ビルド設定
# ---------------------------------------------------------------------------

# プロジェクトのmakefile用設定（詳細は設計資料のビルド下参照のこと）
#----------------------------------------------------------------------------
TOP_DIR		= $(ARCH_DIR)
include		$(TOP_DIR)/mk/cond.mk

BLOCK_NAME	= Gui
OBJ_DIR		= $(BUILD_DIR)/Mid/$(BLOCK_NAME)

# make変数のデフォルト設定
#----------------------------------------------------------------------------
### デバッグログ出力 ###
# YES : ログ出力する
# NO  : ログ出力しない
GUI_DEBUG = NO

### デバッグログ形式 (※上記 GUI_DEBUG が YES のときのみ有効) ###
# YES  : 関数名出力
# NO   : フラグ名出力
GUI_DEBUG_PRINT_FUNC = NO

### ASSERT 時にブレークするか (※上記 GUI_DEBUG が YES のときのみ有効) ###
# YES : ブレークする
# NO  : ブレークしない
GUI_ASSERT = NO

### DebugTask起動するか (※上記 GUI_DEBUG が YES のときのみ有効) ###
# YES : ブレークする
# NO  : ブレークしない
GUI_DBG_TSK = NO

# シェル変数によるmake変数の切り替え（makeの引数でデフォルト以外の値にする）
#----------------------------------------------------------------------------

# make変数間の依存関係（一緒に設定がする必要があるものはここで道連れにする）
#----------------------------------------------------------------------------

# コンパイルフラグの追加
#----------------------------------------------------------------------------
ifeq ($(strip $(GUI_DEBUG)), YES)
LCFLAGS += -DCT_DEBUG_ENABLE

ifeq ($(strip $(GUI_DEBUG_PRINT_FUNC)), YES)
LCFLAGS += -DCT_DEBUG_PRINT_FUNC
endif

ifeq ($(strip $(GUI_ASSERT)), YES)
LCFLAGS += -DCT_ASSERT_ENABLE
endif

ifeq ($(strip $(GUI_DBG_TSK)), YES)
LCFLAGS += -DCT_DBG_TSK_ACT
endif

endif

# EOF

# インクルードパスの追加
#----------------------------------------------------------------------------
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/gdi/DigiType/includes
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/gdi/PHLOX/include
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/gdi/PHLOX/include/EGL
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/gdi/PHLOX/include/VG
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/include
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/image
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/string
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/gdi
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui

LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/Ct/tk
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Include
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/tk
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/ws
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window

ifeq ($(strip $(GUI_DBG_TSK)), YES)
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/dbg
endif


LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/AREASETTING
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/COMMON
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/FACT
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/FILE
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/MENU
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/MENU/DIALOG
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/KEYBOARD
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/MENU/OTHER
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/MENU/SPINBOX
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/MENU/TOGGLE
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/MESSAGE
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/NETWORK
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/PLAYVIEW
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/RECVIEW
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Gui/Ct/Window/THUMBNAIL


# For Ct
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/Arch/Rhapsody/oxf
LCFLAGS	+= -I$(SOURCE_TREE_TOP)/Arch/Rhapsody/osconfig
LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/App/Apl/Foundation/
LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/App/Apl/Foundation/Camera
LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/App/Apl/Foundation/Manager
LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/App/Apl/Foundation/Network
LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/App/Apl/Foundation/Wrapper
LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/App/Apl/Foundation/Mount
LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/App/Apl/Rec/CommonRec
#LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/Sys/AsciiDebug

