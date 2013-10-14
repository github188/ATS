### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=server

all_srcs:= \
src/sys_bus.c  \
src/test_drv.c  \
src/main.c  \
module/test/test_module.c  \
module/test/test_event.c  \
module/test/test.c  \
module/erp/erp_module.c  \
module/sys/sys.c  \
module/sys/sys_module.c  \
module/sys/sys_business.c  \
module/dev_prober/prober/table.c  \
module/dev_prober/prober/netcamera_prober.c  \
module/dev_prober/dev_prober_module.c  \
module/report/report_module.c  \
module/report/socket_report.c  \
src/xml.cpp \
module/test/test_event/xml_parse.cpp \
module/dev_prober/dev_prober.cpp

LOCAL_SRC_FILES        :=$(all_srcs)


LOCAL_INCLUDE_DIRS     :=$(LOCAL_PATH)/inc \
						$(PROJECT_TOP_DIR)/inc \
						$(LOCAL_PATH)/src \
						osa_include \
						tinyxml_include \
						cjson_include
						
LOCAL_STATIC_LIBRARIES :=libosa libtinyxml libcjson libcommon


LOCAL_ARLIBS           :=
LOCAL_LDLIBS           :=

LOCAL_CFLAGS           :=
LOCAL_CXXFLAGS         :=
LOCAL_LDFLAGS          :=

include $(BUILD_HOST_EXECUTABLE)

