LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

RPC_INC:=rpc_inc

source_files:= \
	src/loc_api_rpc_glue.c \
	src/loc_api_sync_call.c \
	src/loc_apicb_appinit.c \
	src/loc_api_fixup.c

LOCAL_SRC_FILES:= $(source_files)

LOCAL_CFLAGS:=-fno-short-enums
LOCAL_CFLAGS+=-DDEBUG -DUSE_QCOM_AUTO_RPC
LOCAL_CFLAGS+=$(GPS_FEATURES)

# for loc_api_fixup.c
LOCAL_CFLAGS+=-DADD_XDR_FLOAT -DADD_XDR_BOOL

LOCAL_SHARED_LIBRARIES:= \
	librpc \
	libutils \
	libcutils \
	libcommondefs

LOCAL_STATIC_LIBRARIES := \
	libloc_api_rpcgen

LOCAL_PRELINK_MODULE:= false

LOCAL_C_INCLUDES:= \
	$(LOCAL_PATH) \
	$(LOCAL_PATH)/rpc_inc \
	$(TARGET_OUT_HEADERS)/loc_api/rpcgen/inc \
	$(TARGET_OUT_HEADERS)/libcommondefs-rpc \
	$(TARGET_OUT_HEADERS)/libcommondefs/rpcgen/inc \
	$(TARGET_OUT_HEADERS)/librpc \
	$(TARGET_OUT_HEADERS)/libloc-rpc/rpc_inc \
	hardware/msm7k/librpc \

LOCAL_COPY_HEADERS_TO:= libloc_api-rpc-qc/$(RPC_INC)
LOCAL_COPY_HEADERS:= \
	$(RPC_INC)/loc_api_rpc_glue.h \
	$(RPC_INC)/loc_api_fixup.h \
	$(RPC_INC)/loc_api_sync_call.h \
	$(RPC_INC)/loc_apicb_appinit.h

LOCAL_MODULE:= libloc_api-rpc-qc

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)