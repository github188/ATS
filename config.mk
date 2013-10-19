PROJECT_OUT            :=$(PROJECT_TOP_DIR)/out
PROJECT_VERSION        :=1.1.1
PROJECT_BUILD_ID       :=1234
PROJECT_BUILD_TYPE     :=debug
PROJECT_COMPANY        :=TuoAn
PROJECT_MODULE_OWNER   :=hello



# mingw32
TOOL:=MINGW32
# gcc
#TOOL:=GNUC


$(if $(strip $(TOOL)), , $(error TOOL is null!)) 


OS_ARCHLINUX:=$(shell uname -a | grep -i "arch")
OS_UBUNTU:=$(shell uname -a | grep -i "ubuntu")
OS_FEDORA:=$(shell uname -a | grep -i "fedora")


# for archlinux
ifneq (x, x$(strip $(OS_ARCHLINUX)))
_PREFIX:=i486-mingw32
endif

# for ubuntu
ifneq (x, x$(strip $(OS_UBUNTU)))
_PREFIX:=i586-mingw32msvc
endif

# for fedora



ifeq (MINGW32, $(strip $(TOOL)))
TOOL_ROOT        :=/usr/$(_PREFIX)
CROSS_COMPILE    :=$(_PREFIX)-
else
TOOL_ROOT        :=/usr
CROSS_COMPILE    :=
endif

export C_INCLUDE_PATH="$(TOOL_ROOT)/include  /usr/include"


AR              :=$(CROSS_COMPILE)ar
CC              :=$(CROSS_COMPILE)gcc
CPP             :=$(CROSS_COMPILE)gcc
CXX             :=$(CROSS_COMPILE)g++
LD              :=$(CROSS_COMPILE)g++


ATS_GUI_ROOT    :=$(PROJECT_TOP_DIR)/gui
ATS_SERVER_ROOT :=$(PROJECT_TOP_DIR)/server
ATS_UTILS_ROOT  :=$(PROJECT_TOP_DIR)/utils


ifeq (MINGW32, $(strip $(TOOL)))
CFLAGS+=-DWIN32
endif

ifeq (GNUC, $(strip $(TOOL)))
CFLAGS+=-DLINUX
endif


CFLAGS          += -fno-builtin -Wall
CXXFLAGS        += -fno-builtin -Wall
