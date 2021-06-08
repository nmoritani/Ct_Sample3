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

# BLOCK_NAME	= Gui

# "TOP_DIR" specifies relative path to Paprika root directory.
#
TOP_DIR		= $(ARCH_DIR)

## Block Common
include     $(SOURCE_TREE_TOP)/MovieSoft/Mid/Gui/Defs.mk

# "OBJ_DIR" specifies directory where object file is generated in.
#
OBJ_DIR		= $(BUILD_DIR)/Mid/$(BLOCK_NAME)


# "RELEASE" specifies type of release object. You can choose either
# "lib" or "ex". If you specify "lib", it generates a TGT_NAME archive
# file in release/ directory that collects all object file in $(OBJ_DIR).
# Nothing is specified, no release objects are generated.
#
#RELEASE		= lib
#TGT_NAME	= ../../../../../lib$(BLOCK_NAME)

# "LCFLAGS" and "LASFLAGS" specify compiling option for local directory.
#
LCFLAGS		+=
LASFLAGS	=


# "CSRC" and "ASRC" specify C and Assembler source file name.
#
CSRC		= DcwIconFont.c \
			  UCS-CNS-IWATA-LATIN-Part.c \
			  UCS-CNS-PUD_W4_SYMBOL_MIX.c \
			  UCS-CNS-Ascii500_sample.c
ASRC		=


# "CFGSRC" specifies Configuration file that describes static APIs.
#
CFGSRC		=


# Don't modify. It includes common make file here.
#
include		$(TOP_DIR)/mk/env.mk

clean-subs:


