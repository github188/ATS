### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libcjson

LOCAL_SRC_FILES        :=cJSON.c

LOCAL_INCLUDE_DIRS     :=$(LOCAL_PATH)

LOCAL_EXPORT_HEADER_TO	 :=cjson_include
LOCAL_EXPORT_HEADER_DIRS :=$(LOCAL_PATH)

LOCAL_LDLIBS	:=

include $(BUILD_HOST_STATIC_LIBRARY)
