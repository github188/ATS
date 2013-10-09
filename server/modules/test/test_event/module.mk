### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libtp.so
LOCAL_MODULE_OWNER     :=

event_srcs:=dummy_test.c \
			version_test.c

LOCAL_SRC_FILES        :=xml_parse.cpp  table.c $(event_srcs)

LOCAL_INCLUDE_DIRS     :=$(ATS_SERVER_ROOT)/include osa_include tinyxml_include  $(LOCAL_PATH) 

LOCAL_STATIC_LIBRARIES :=libcommon libreport libtest

include $(BUILD_HOST_SHARED_LIBRARY)
