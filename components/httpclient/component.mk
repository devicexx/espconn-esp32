#
# Main Makefile. This is basically the same as a component makefile.
#
# This Makefile should, at the very least, just include $(SDK_PATH)/make/component_common.mk. By default, 
# this will take the sources in the src/ directory, compile them and link them into 
# lib(subdirectory_name).a in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#

CFLAGS +=  -DCS_PLATFORM=3 \
           -DMG_NO_BSD_SOCKETS \
           -DMG_DISABLE_FILESYSTEM \
           -DRTOS_SDK -DMG_LWIP -DLWIP_TIMEVAL_PRIVATE=0 \
           -DMG_INTERNAL=

COMPONENT_ADD_INCLUDEDIRS := .

COMPONENT_SRCDIRS := .

include $(IDF_PATH)/make/component_common.mk
