### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libosa

common_srcs:=src/common/osa_mem.c \
			src/common/osa_msg.c \
			src/common/osa_random.c \
			src/common/osa_log.c
			
linux_srcs:=src/linux/osa_file.c\
			src/linux/osa_dir.c \
			src/linux/osa_socket.c \
			src/linux/osa_select.c \
			src/linux/osa_dll.c \
			src/linux/osa_process.c \
			src/linux/osa_thread.c \
			src/linux/osa_timer.c \
			src/linux/osa_time.c
			
win32_srcs:=src/win32/osa_file.c \
			src/win32/osa_dll.c \
			src/win32/osa_socket.c \
			src/win32/osa_select.c \
			src/win32/osa_dir.c \
			src/win32/osa_thread.c \
			src/win32/osa_timer.c \
			src/win32/osa_time.c \
			src/win32/osa_cvt.c

ifeq (MINGW32, $(TOOL))
srcs:=$(common_srcs) $(win32_srcs)
else
srcs:=$(common_srcs) $(linux_srcs)
endif

LOCAL_SRC_FILES		   :=$(srcs)

LOCAL_INCLUDE_DIRS     :=$(LOCAL_PATH)/include

LOCAL_EXPORT_HEADER_TO	 :=osa_include
LOCAL_EXPORT_HEADER_DIRS :=$(LOCAL_PATH)/include


ifeq (MINGW32, $(TOOL))
LOCAL_ARLIBS	:=$(TOOL_ROOT)/lib/libws2_32.a
endif

ifeq (MINGW32, $(TOOL))
LOCAL_LDLIBS		:=dl pthread
else
LOCAL_LDLIBS		:=dl pthread
endif

include $(BUILD_HOST_STATIC_LIBRARY)

