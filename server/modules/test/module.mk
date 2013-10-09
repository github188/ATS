### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libtest

LOCAL_SRC_FILES        :=test_module.c test_event.c

LOCAL_INCLUDE_DIRS     :=$(ATS_SERVER_ROOT)/include osa_include tinyxml_include  $(LOCAL_PATH) $(LOCAL_PATH)/test_point

LOCAL_LDLIBS           :=

include $(BUILD_HOST_STATIC_LIBRARY)
