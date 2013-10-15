### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libcommon

srcs:= \
		bus.c \
		device.c \
		image.c \
		log.c \
		module.c \
		xml.cpp \
		test_drv.c \
		test_event.c

LOCAL_SRC_FILES        :=$(srcs)

LOCAL_INCLUDE_DIRS     :=$(PROJECT_TOP_DIR)/inc osa_include tinyxml_include


LOCAL_STATIC_LIBRARIES :=
LOCAL_SHARED_LIBRARIES :=

LOCAL_ARLIBS           :=
LOCAL_LDLIBS           :=

include $(BUILD_HOST_STATIC_LIBRARY)
