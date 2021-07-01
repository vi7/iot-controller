#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := iot-controller
ESPPORT := $(shell ls -1 /dev/tty.usbserial*)

include $(IDF_PATH)/make/project.mk

