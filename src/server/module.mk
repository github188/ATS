### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=server

all_srcs:= \
		module/dev_prober/dev_prober.c  \
		module/dev_prober/dev_prober_module.c  \
		module/dev_prober/prober/dummy_prober.c  \
		module/dev_prober/prober/Onvif_prober.c  \
		module/dev_prober/prober/table.c  \
		module/erp/erp_module.c  \
		module/report/report_module.c  \
		module/report/socket_report.c  \
		module/sdk/sdk_module.c  \
		module/sys/sys.c  \
		module/sys/sys_business.c  \
		module/sys/sys_module.c  \
		module/test/test_event/dummy_test.c  \
		module/test/test_event/table.c  \
		module/test/test_event/version_test.c  \
		module/test/test_event.c  \
		module/test/test_module.c  \
		module/test/test_event/xml_parse.cpp  \
		src/main.c  \
		src/test_drv.c  \
		src/conf_xml.cpp

LOCAL_SRC_FILES        :=$(all_srcs)


LOCAL_INCLUDE_DIRS     :=$(LOCAL_PATH)/inc \
						$(PROJECT_TOP_DIR)/inc \
						osa_include \
						tinyxml_include \
						cjson_include
						
LOCAL_STATIC_LIBRARIES :=libosa libtinyxml libcjson


LOCAL_ARLIBS           :=
LOCAL_LDLIBS           :=

LOCAL_CFLAGS           :=
LOCAL_CXXFLAGS         :=
LOCAL_LDFLAGS          :=

include $(BUILD_HOST_EXECUTABLE)

