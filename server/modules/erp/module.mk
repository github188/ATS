### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=liberp

LOCAL_SRC_FILES        :=erp_module.c

LOCAL_INCLUDE_DIRS     :=$(ATS_SERVER_ROOT)/include osa_include tinyxml_include /usr/include/c++/4.4

include $(BUILD_HOST_STATIC_LIBRARY)

