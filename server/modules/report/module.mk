### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libreport

LOCAL_SRC_FILES        :=report_module.c socket_report.c

LOCAL_INCLUDE_DIRS     :=$(ATS_SERVER_ROOT)/include osa_include tinyxml_include cjson_include

include $(BUILD_HOST_STATIC_LIBRARY)
