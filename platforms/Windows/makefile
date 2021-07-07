# 生成する実行ファイル名
TARGETS   = simulator.out

# ソースコードの位置
SRCROOT   = ../../

# WINDOWS用シミュレータの名称(指定フォルダ以下のコードをmake対象から除外する)
WINSIM_PRJ_DIR = '*/windows_lib*'

# 生成するファイルの出力先ディレクトリ
TARGETDIR = ./bin/

# 中間ファイルの出力先ディレクトリ
OBJROOT   = ./obj/

# インクルードファイルのパスの指定
INCLUDE   = -I/usr/local/include

###################################################

# コンパイラ指定
COMPILER  = g++
CFLAGS    = -g -MMD -MP -Wall -Wextra -Winit-self -Wno-missing-field-initializers -DEGL_STATIC_LIBRARY -DLINUX_GUI_SIM -DEGL_STATIC_LIBRARY -DUSE_AMANITH_VG -DFT2_BUILD_LIBRARY

# AmanithOpenVGのライブラリ置き場
# ※Amanithを使わない場合は外す
AMANITHVG_LIBS	= ./lib
AMANITHVG_COPY	= cp -f

# ライブラリ関係の指定
ifeq "$(shell getconf LONG_BIT)" "64"
  LDFLAGS = -L/usr/local/lib
else
  LDFLAGS = -L/usr/local/lib
endif
LDFLAGS += -lX11
LDFLAGS += -lm
LDFLAGS += -lpthread
LDFLAGS += -lfreetype

# AmanithOpenVGのライブラリを指定(使用しない場合は外す)
LDFLAGS += -L$(AMANITHVG_LIBS) -lAmanithVG

LIBS      =

###################################################
# SRCROOTの中をfindで走破してサブディレクトリまで階層リスト化
SRCDIRS  := $(shell find $(SRCROOT) ! -path $(WINSIM_PRJ_DIR) -type d)

# SRCROOTの階層リストを元に全cppファイルをリスト化
SOURCES   = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))

# 上記のcppファイルのリストを元にオブジェクトファイル名を決定
OBJECTS_WORK   = $(addprefix $(OBJROOT), $(SOURCES:.cpp=.o))
empty:=
OBJECTS   = $(subst $(SRCROOT),$(empty),$(OBJECTS_WORK))

# SRCROOTと同じ構造で中間ファイルの出力先ディレクトリをリスト化
#OBJDIRS   = $(addprefix src, obj, $SRCDIRS) 

# 依存ファイル.dを.oファイルから作る
DEPENDS   = $(OBJECTS:.o=.d)

###################################################

INCLUDE  += $(foreach dir, $(SRCDIRS), -I$(dir))




###################################################
# 依存ファイルを元に実行ファイルを作る
$(TARGETS): $(OBJECTS) $(LIBS)
	$(COMPILER) -o $(TARGETDIR)/$@ $^ $(LDFLAGS)
	$(AMANITHVG_COPY) $(AMANITHVG_LIBS)/libAmanithVG.so.4 $(TARGETDIR)

# 中間バイナリのディレクトリを掘りながら.cppを中間ファイル.oに
$(OBJROOT)%.o: $(SRCROOT)%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(COMPILER) $(CFLAGS) $(INCLUDE) -o $@ -c $<

all: 
	clean
	make

clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(TARGETDIR)/$(TARGETS) $(TARGETDIR)/libAmanithVG.so.4
	#$(info hoge)

# 依存関係ファイル
-include $(DEPENDS)
