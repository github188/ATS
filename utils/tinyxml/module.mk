### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libtinyxml

tinyxml_srcs:=\
			tinyxml.cpp \
			tinyxmlerror.cpp \
			tinyxmlparser.cpp

LOCAL_SRC_FILES        :=$(tinyxml_srcs)

LOCAL_INCLUDE_DIRS     :=$(LOCAL_PATH)

LOCAL_EXPORT_HEADER_TO	 :=tinyxml_include
LOCAL_EXPORT_HEADER_DIRS :=$(LOCAL_PATH)

ifeq (MINGW32, $(TOOL))
#LOCAL_ARLIBS:=$(TOOL_ROOT)/lib/libstdc++.a
endif

include $(BUILD_HOST_STATIC_LIBRARY)
