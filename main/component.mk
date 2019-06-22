#
# Main component makefile.
#
# This Makefile can be left empty. By default, it will take the sources in the 
# src/ directory, compile them and link them into lib(subdirectory_name).a 
# in the build directory. This behaviour is entirely configurable,
# please read the ESP-IDF documents if you need to do this.
#
# 

#COMPONENT_OBJS := file1.o file2.o thing/filea.o thing/fileb.o anotherthing/main.o
COMPONENT_SRCDIRS +=  ../main/ble_libs/
COMPONENT_SRCDIRS +=  ../main/

COMPONENT_ADD_INCLUDEDIRS +=  ../main/ble_libs/
COMPONENT_ADD_INCLUDEDIRS +=  ../main/



