## -*- Makefile -*-
##
## User: woody
## Time: Jan 20, 2018 8:17:37 PM
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CC = gcc
CCC = g++
CXX = g++
BASICOPTS = -g
CFLAGS = $(BASICOPTS)
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
CCADMIN = 


# Define the target directories.
TARGETDIR_test_sm_c=.
TARGETDIR_test_sm_cpp=.


all: test_sm_c test_sm_cpp

## Target: test_sm_c
CPPFLAGS_test_sm_c = \
	-Iinclude
OBJS_test_sm_c =  \
	$(TARGETDIR_test_sm_c)/statemachine.o \
	$(TARGETDIR_test_sm_c)/test_sm2.o
USERLIBS_test_sm_c = $(SYSLIBS_test_sm_c) 
DEPLIBS_test_sm_c =  
LDLIBS_test_sm_c = $(USERLIBS_test_sm_c)


# Link or archive
$(TARGETDIR_test_sm_c)/test_sm_c: $(TARGETDIR_test_sm_c) $(OBJS_test_sm_c) $(DEPLIBS_test_sm_c)
	$(LINK.c) $(CFLAGS_test_sm_c) $(CPPFLAGS_test_sm_c) -o $@ $(OBJS_test_sm_c) $(LDLIBS_test_sm_c)


# Compile source files into .o files
$(TARGETDIR_test_sm_c)/statemachine.o: $(TARGETDIR_test_sm_c) src/statemachine.c
	$(COMPILE.c) $(CFLAGS_test_sm_c) $(CPPFLAGS_test_sm_c) -o $@ src/statemachine.c

$(TARGETDIR_test_sm_c)/test_sm2.o: $(TARGETDIR_test_sm_c) test/test_sm2.c
	$(COMPILE.c) $(CFLAGS_test_sm_c) $(CPPFLAGS_test_sm_c) -o $@ test/test_sm2.c



## Target: test_sm_cpp
CPPFLAGS_test_sm_cpp = \
	-Iinclude
OBJS_test_sm_cpp =  \
	$(TARGETDIR_test_sm_cpp)/test_sm1.o
USERLIBS_test_sm_cpp = $(SYSLIBS_test_sm_cpp) 
DEPLIBS_test_sm_cpp =  
LDLIBS_test_sm_cpp = $(USERLIBS_test_sm_cpp)


# Link or archive
$(TARGETDIR_test_sm_cpp)/test_sm_cpp: $(TARGETDIR_test_sm_cpp) $(OBJS_test_sm_cpp) $(DEPLIBS_test_sm_cpp)
	$(LINK.cc) $(CCFLAGS_test_sm_cpp) $(CPPFLAGS_test_sm_cpp) -o $@ $(OBJS_test_sm_cpp) $(LDLIBS_test_sm_cpp)


# Compile source files into .o files
$(TARGETDIR_test_sm_cpp)/test_sm1.o: $(TARGETDIR_test_sm_cpp) test/test_sm1.cpp
	$(COMPILE.cc) $(CCFLAGS_test_sm_cpp) $(CPPFLAGS_test_sm_cpp) -o $@ test/test_sm1.cpp



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_test_sm_c)/test_sm_c \
		$(TARGETDIR_test_sm_c)/statemachine.o \
		$(TARGETDIR_test_sm_c)/test_sm2.o \
		$(TARGETDIR_test_sm_cpp)/test_sm_cpp \
		$(TARGETDIR_test_sm_cpp)/test_sm1.o
# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

