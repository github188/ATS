### module.mk

LOCAL_PATH             :=$(call MyDir)

LOCAL_MODULE           :=libdev_prober

prober_srcs:=prober/table.c \
			prober/dummy_prober.c \
			prober/IPC_Onvif_prober.c

LOCAL_SRC_FILES        :=dev_prober_module.c \
						dev_prober.c \
						$(prober_srcs)

LOCAL_INCLUDE_DIRS     :=$(ATS_SERVER_ROOT)/include osa_include tinyxml_include cjson_include

include $(BUILD_HOST_STATIC_LIBRARY)
