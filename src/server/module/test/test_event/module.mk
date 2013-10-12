### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libtevent

srcs:= dummy_test.c \
		table.c \
		version_test.c \
		xml_parse.cpp

socket_report_srcs:=../../report/socket_report.c
		
LOCAL_SRC_FILES        :=$(srcs) $(socket_report_srcs)

LOCAL_INCLUDE_DIRS     :=$(LOCAL_PATH) \
						$(PROJECT_TOP_DIR)/inc \
						$(LOCAL_PATH)/../../../inc \
						osa_include \
						tinyxml_include

LOCAL_STATIC_LIBRARIES :=libcommon libosa libtinyxml
LOCAL_SHARED_LIBRARIES :=


include $(BUILD_HOST_SHARED_LIBRARY)
