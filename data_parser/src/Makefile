DESTINATION := libdataparser.so 
LIBPATH := -L../lib -Wl,-Bdynamic#增加自已的动态库

LIBS := dl pthread #增加系统库
INCLUDES := ../inc 
BIN := ../lib
RM := rm -rf
SHAREDFLAG := -shared 

PS = cpp

CC = g++
CPPFLAGS = -g -Wall -O0 -fPIC
CPPFLAGS += $(addprefix -I, $(INCLUDES))
CPPFLAGS += -MMD

SOURCE := $(wildcard *.$(PS))
OBJS := $(patsubst %.$(PS), %.o, $(SOURCE))
DEPS := $(patsubst %.o, %.d, $(OBJS))
MISSING_DEPS := $(filter-out $(wildcard $(DEPS)), $(DEPS))
MISSING_DEPS_SOURCES := $(wildcard $(patsubst %.d, %,$(PS), $(MISSING_DEPS)))

.PHONY: all deps objs clean rebuild uttest 
#rebuild uttest
all: $(DESTINATION)
deps: $(DEPS)
	$(CC) -MM -MMD $(SOURCE)
objs: $(OBJS)
clean:
	@$(RM) *.o
	@$(RM) *.d
	@$(RM) $(BIN)/$(DESTINATION)
clear:
	@$(RM) *.o
	@$(RM) *.d
rebuild: clean all
ifneq ($(MISSING_DEPS),)
$(MISSING_DEPS):
	@$(RM) $(patsubst %.d, %.o, $@)
endif
-include $(DEPS)
$(DESTINATION): $(OBJS)
	$(CC) $(SHAREDFLAG) -o $(BIN)/$(DESTINATION) $(LIBPATH) $(OBJS) $(addprefix -l, $(LIBS))
uttest: $(OBJS)
	$(CC) -o $(BIN)/$(DESTINATION) $(OBJS) -D_UNIT_TEST_

