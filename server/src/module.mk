### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libcommon

LOCAL_SRC_FILES        :=conf.c module.c conf_xml.cpp device.c dev_bus.c test_drv.c log.c image.c


LOCAL_INCLUDE_DIRS     :=$(ATS_SERVER_ROOT)/include cjson_include osa_include  tinyxml_include $(LOCAL_PATH)

LOCAL_STATIC_LIBRARIES :=libosa libcjson libtinyxml

LOCAL_LDLIBS           :=


#LOCAL_CXXFLAGS         :=-DATS_CONFIG_FILE=\"$(ATS_SERVER_ROOT)/conf/ats.xml\"

include $(BUILD_HOST_STATIC_LIBRARY)


###################################################
include $(CLEAR_VARS)

LOCAL_MODULE           :=main

LOCAL_INCLUDE_DIRS     :=$(ATS_SERVER_ROOT)/include cjson_include osa_include  tinyxml_include $(LOCAL_PATH)

LOCAL_SRC_FILES :=ats_main.c

LOCAL_STATIC_LIBRARIES :=libcommon libdev_prober libtest libreport  liberp  libsys
LOCAL_LIBRARY_DIRS :=/usr/i586-mingw32msvc/lib

LOCAL_LDLIBS           :=
#LOCAL_ARLIBS		:=/usr/i586-mingw32msvc/lib/libws2_32.a \
	/usr/i586-mingw32msvc/lib/libwsock32.a

#LOCAL_CXXFLAGS         :=-DATS_CONFIG_FILE=\"$(ATS_SERVER_ROOT)/conf/ats.xml\"

include $(BUILD_HOST_EXECUTABLE)
