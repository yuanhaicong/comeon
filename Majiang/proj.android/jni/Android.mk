LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
                   ../../Classes/CCLoginReader.cpp \
                   ../../Classes/CCLogin.cpp \
                   ../../Classes/PlayerInfoLayer.cpp \
                   ../../Classes/SelectEntryScene.cpp \
				   ../../Classes/StateLayer.cpp \
				   ../../Classes/StaticData.cpp \
				   ../../Classes/UserData.cpp  \
				   ../../Classes/jansson/dump.c \
				   ../../Classes/jansson/error.c \
				   ../../Classes/jansson/hashtable.c \
				   ../../Classes/jansson/jansson_config.h \
				   ../../Classes/jansson/load.c \
				   ../../Classes/jansson/memory.c \
				   ../../Classes/jansson/pack_unpack.c \
				   ../../Classes/jansson/strbuffer.c \
				   ../../Classes/jansson/strconv.c \
				   ../../Classes/jansson/utf.c \
				   ../../Classes/jansson/value.c \
				   ../../Classes/NDKHelper/NDKCallbackNode.cpp \
				   ../../Classes/NDKHelper/NDKHelper.cpp 
				   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/jansson \

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
