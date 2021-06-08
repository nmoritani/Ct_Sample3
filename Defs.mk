# ---------------------------------------------------------------------------
# GUI�u���b�N���ʃr���h�ݒ�
# ---------------------------------------------------------------------------

# �v���W�F�N�g��makefile�p�ݒ�i�ڍׂ͐݌v�����̃r���h���Q�Ƃ̂��Ɓj
#----------------------------------------------------------------------------
TOP_DIR		= $(ARCH_DIR)
include		$(TOP_DIR)/mk/cond.mk

BLOCK_NAME	= Gui
OBJ_DIR		= $(BUILD_DIR)/Mid/$(BLOCK_NAME)

# make�ϐ��̃f�t�H���g�ݒ�
#----------------------------------------------------------------------------
### �f�o�b�O���O�o�� ###
# YES : ���O�o�͂���
# NO  : ���O�o�͂��Ȃ�
GUI_DEBUG = NO

### �f�o�b�O���O�`�� (����L GUI_DEBUG �� YES �̂Ƃ��̂ݗL��) ###
# YES  : �֐����o��
# NO   : �t���O���o��
GUI_DEBUG_PRINT_FUNC = NO

### ASSERT ���Ƀu���[�N���邩 (����L GUI_DEBUG �� YES �̂Ƃ��̂ݗL��) ###
# YES : �u���[�N����
# NO  : �u���[�N���Ȃ�
GUI_ASSERT = NO

### DebugTask�N�����邩 (����L GUI_DEBUG �� YES �̂Ƃ��̂ݗL��) ###
# YES : �u���[�N����
# NO  : �u���[�N���Ȃ�
GUI_DBG_TSK = NO

# �V�F���ϐ��ɂ��make�ϐ��̐؂�ւ��imake�̈����Ńf�t�H���g�ȊO�̒l�ɂ���j
#----------------------------------------------------------------------------

# make�ϐ��Ԃ̈ˑ��֌W�i�ꏏ�ɐݒ肪����K�v��������̂͂����œ��A��ɂ���j
#----------------------------------------------------------------------------

# �R���p�C���t���O�̒ǉ�
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

# �C���N���[�h�p�X�̒ǉ�
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

