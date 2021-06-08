#   Copyright (c) 2017 Panasonic Corporation
#
#   GNU make only.
#
#-----------------------------------------------------------------------------

BLOCK_NAME = Gui
BLOCK_TOP_DIR = ..

# "TOP_DIR" specifies relative path to OS root directory.
#
TOP_DIR = $(ARCH_DIR)

include $(TOP_DIR)/mk/cond.mk
-include $(BLOCK_TOP_DIR)/Defs.mk

# "OBJ_DIR" specifies directory where object file is generated in.
#
OBJ_DIR = $(BUILD_DIR)/Mid/$(BLOCK_NAME)

# "RELEASE" specifies type of release object. You can choose either
# "lib" or "ex". If you specify "lib", it generates a TGT_NAME archive
# file in release/ directory that collects all object file in $(OBJ_DIR).
# Nothing is specified, no release objects are generated.
#
RELEASE =
TGT_NAME =

# "LCFLAGS" and "LASFLAGS" specify compiling option for local directory.
#
LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/Include
LCFLAGS += -I$(SOURCE_TREE_TOP)/MovieSoft/Mid/Include
LCFLAGS += -I$(BLOCK_TOP_DIR)
LASFLAGS =

# "CSRC" and "ASRC" specify C and Assembler source file name.
#
CSRC = $(wildcard *.c)
ASRC =

# "CFGSRC" specifies Configuration file that describes static APIs.
#
CFGSRC = gui_dma.cfg

# "SUBDIRS" specifies directory list that executes make command recursively.
#
SUBDIRS =

# Don't modify. It includes common make file here.
#
include $(TOP_DIR)/mk/env.mk

clean-subs:
