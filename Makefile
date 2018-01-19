## -*- Makefile -*-
##
## User: woody
## Time: Jan 19, 2018 7:03:18 PM
## Makefile created by Oracle Developer Studio.
##
## This file is generated automatically.
##


#### Compiler and tool definitions shared by all build targets #####
CCC = g++
CXX = g++
BASICOPTS = -g
CCFLAGS = $(BASICOPTS)
CXXFLAGS = $(BASICOPTS)
CCADMIN = 
CCFLAGS_test_sm = -Iinclude

# Define the target directories.
TARGETDIR_test_sm=.


all: test_sm

## Target: test_sm
OBJS_test_sm =  \
	$(TARGETDIR_test_sm)/test_sm.o
SYSLIBS_test_sm = -static 
USERLIBS_test_sm = $(SYSLIBS_test_sm) 
DEPLIBS_test_sm =  
LDLIBS_test_sm = $(USERLIBS_test_sm)


# Link or archive
$(TARGETDIR_test_sm)/test_sm: $(TARGETDIR_test_sm) $(OBJS_test_sm) $(DEPLIBS_test_sm)
	$(LINK.cc) $(CCFLAGS_test_sm) $(CPPFLAGS_test_sm) -o $@ $(OBJS_test_sm) $(LDLIBS_test_sm)


# Compile source files into .o files
$(TARGETDIR_test_sm)/test_sm.o: $(TARGETDIR_test_sm) test/test_sm.cpp
	$(COMPILE.cc) $(CCFLAGS_test_sm) $(CPPFLAGS_test_sm) -o $@ test/test_sm.cpp



#### Clean target deletes all generated files ####
clean:
	rm -f \
		$(TARGETDIR_test_sm)/test_sm \
		$(TARGETDIR_test_sm)/test_sm.o
# Enable dependency checking
.KEEP_STATE:
.KEEP_STATE_FILE:.make.state.GNU-amd64-Linux

