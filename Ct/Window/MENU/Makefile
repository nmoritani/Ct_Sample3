#
#	Paprika ( Panasonic Application Platform and
#	                      Realtime-system Innovating Kernel Architecture )
#	Copyright (C) 2000-2000 by Matsushita Electric Industrial Co., Ltd.
#
#	$Id: Makefile,v 1.6 2005/03/25 11:32:22 chikaishi Exp $
#
#	GNU make only.
#
#-----------------------------------------------------------------------------

# BLOCK_NAME	= Ct

# "TOP_DIR" specifies relative path to Paprika root directory.
#
TOP_DIR		= $(ARCH_DIR)

## Block Common
include     $(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/Defs.mk


# "OBJ_DIR" specifies directory where object file is generated in.
#
#OBJ_DIR		= $(BUILD_DIR)/Mid/$(BLOCK_NAME)


# "RELEASE" specifies type of release object. You can choose either
# "lib" or "ex". If you specify "lib", it generates a TGT_NAME archive
# file in release/ directory that collects all object file in $(OBJ_DIR).
# Nothing is specified, no release objects are generated.
#
# RELEASE		= lib
# TGT_NAME	= ../../../lib$(BLOCK_NAME)

# "LCFLAGS" and "LASFLAGS" specify compiling option for local directory.
#
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Ct/gdi
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Ct/gdi/PHLOX/include
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Include
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Ct/Include
LCFLAGS		+= -I$(TOP_DIR)/../MovieSoft/Mid/Ct/ws

# "CSRC" and "ASRC" specify C and Assembler source file name.
#
CSRC		=
ASRC		=
CPPSRC		= $(wildcard *.cpp)


# "CFGSRC" specifies Configuration file that describes static APIs.
#
CFGSRC		= 


# "SUBDIRS" specifies directory list that executes make command recursively.
#
SUBDIRS		= SPINBOX DIALOG TOGGLE OTHER

# Don't modify. It includes common make file here.
#
include		$(TOP_DIR)/mk/env.mk

clean-subs:


