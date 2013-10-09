### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libsdk

LOCAL_SRC_FILES        :=sdk_module.c

LOCAL_INCLUDE_DIRS     :=$(ATS_SERVER_ROOT)/include osa_include

include $(BUILD_HOST_STATIC_LIBRARY)
