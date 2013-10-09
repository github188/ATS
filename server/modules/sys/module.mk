### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libsys

LOCAL_SRC_FILES        := sys.c sys_business.c sys_module.c

LOCAL_INCLUDE_DIRS     :=$(LOCAL_PATH) $(ATS_SERVER_ROOT)/include cjson_include osa_include

include $(BUILD_HOST_STATIC_LIBRARY)
