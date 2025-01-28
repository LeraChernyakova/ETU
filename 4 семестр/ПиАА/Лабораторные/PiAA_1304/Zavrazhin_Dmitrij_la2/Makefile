#!/usr/bin/make -f

SHELL = /bin/sh
.SUFFIXES:

blank :=
define newline

$(blank)
endef
# project name(s)
PROJ  := la2
PROJS := $(PROJ)

# compilation flags:
# OPTFLAGS   --- flags pertaining to optimization
# WERFLAGS   --- flags pertaining to warnings and errors
# CCSTDFLAG  --- flag that declares C standard being used
# CXXSTDFLAG --- flag that declares C++ standard being used
OPTFLAGS    := -pg -g # -O3 -ffast-math
WERFLAGS    := -Wall -Wpedantic -Werror
CLIBFLAGS   :=
CXXLIBFLAGS := # -fPIC 
CCSTDFLAG   := -std=c99
CXXSTDFLAG  := -std=c++17
CFLAGS      := $(OPTFLAGS) $(WERFLAGS) $(CLIBFLAGS) $(CCSTDFLAG)
CXXFLAGS    := $(OPTFLAGS) $(WERFLAGS) $(CXXLIBFLAGS) $(CXXSTDFLAG)
# DEPFLAGS is a macro used to produce flags used to generate dependency files
DEPFLAGS    = -MT $(1) -MMD -MP -MF $(2)

CC     := clang $(CFLAGS)
CXX    := clang++ $(CXXFLAGS)
MKDIR  := mkdir
RM     := rm -f
RMDIR  := rm -fr

# define project layout directories 
# SRCDIR --- directory that contains source code, must already exist
# ASMDIR --- directory that contains illustratory assembly code 
# OBJDIR --- directory that contains intermediate object files
# DEPDIR --- directory that contains files related to autodependency handling
# BINDIR --- directory that contains produced binaries
SRCDIR := src
ASMDIR := asm
OBJDIR := obj
DEPDIR := dep
BINDIR := bin
ifeq ($(shell test -d $(SRCDIR); echo $$?),1)
$(error Source code directory not found)
endif
# find out SRCDIR directory subdirectory structure, create mirroring structures
# for other  directories
SRCSUBDIRS := $(shell find $(SRCDIR) -type d)
SRCSUBDIRS := $(SRCSUBDIRS:%=%/)
OBJSUBDIRS := $(SRCSUBDIRS:$(SRCDIR)/%=$(OBJDIR)/%)
ASMSUBDIRS := $(SRCSUBDIRS:$(SRCDIR)/%=$(ASMDIR)/%)
DEPSUBDIRS := $(SRCSUBDIRS:$(SRCDIR)/%=$(DEPDIR)/%)
# Create lists of directories and subdirectories:
# DIRS    --- contains all project layout directories that should be cleaned using `make clean'
# SUBDIRS --- contains all (sub)directories that are potentially should be created
DIRS    := $(ASMDIR) $(BINDIR) $(DEPDIR) $(OBJDIR)
SUBDIRS := $(ASMSUBDIRS) $(BINDIR) $(DEPSUBDIRS) $(OBJSUBDIRS)

# define file extensions associated with C and C++
C_SUFFIXES   := .c
CXX_SUFFIXES := .C .cc .cp .cpp .CPP .cxx .c++
CPP_SUFFIXES := $(C_SUFFIXES) $(CXX_SUFFIXES)
# find all C and C++ source files located in SRCSUBDIRS
CPP_SRCS := $(strip $(foreach SUFF,$(CPP_SUFFIXES),$(foreach DIR,$(SRCSUBDIRS),$(wildcard $(DIR)*$(SUFF)))))
$(info $$CPP_SRCS is [${CPP_SRCS}])
CPP_INCS := $(CPP_SRCS:$(SRCDIR)/%=#include "%";)
# convert found C and C++ source files to other extensions
CPP_OBJS := $(CPP_SRCS)
$(foreach SUFF,$(CPP_SUFFIXES),$(eval\
	CPP_OBJS := $(CPP_OBJS:$(SRCDIR)/%$(SUFF)=$(OBJDIR)/%.o\
)))
CPP_ASMS := $(CPP_OBJS:$(OBJDIR)/%.o=$(ASMDIR)/%.s)
CPP_DEPS := $(CPP_OBJS:$(OBJDIR)/%.o=$(DEPDIR)/%.d)
$(info $$CPP_OBJS is [${CPP_OBJS}])

SRCS  := $(CPP_SRCS)
OBJS  := $(CPP_OBJS)
ASMS  := $(CPP_ASMS)
DEPS  := $(CPP_DEPS)
PROJS := $(foreach proj, $(PROJS), $(BINDIR)/$(proj))

# check for naming conflicts between .c and .cpp files
CONFLICTS := $(shell echo -n "\n$(OBJS)" | sed -e "s/ /\n/g" | sort | uniq -d)
ifneq ($(CONFLICTS),)
$(error There are conflicting object files: $(CONFLICTS))
endif

all: $(SUBDIRS) $(PROJS)

$(SUBDIRS):
	$(MKDIR) $@

# $(BINDIR)/$(PROJ): $(SRCS)
$(BINDIR)/$(PROJ): $(OBJS)
	$(CXX) $^ -o $@

-include $(DEPS)

# C object file compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@$(CC) -S $< -o $(ASMDIR)/$*.s
	$(CC) $(call DEPFLAGS,$@,$(DEPDIR)/$*.d) -c $< -o $@

# C++ object file compilation
define cxx_compilation_rule
$$(OBJDIR)/%.o: $$(SRCDIR)/%$1
	@$$(CXX) -S $$< -o $$(ASMDIR)/$$*.s
	$$(CXX) $$(call DEPFLAGS,$$@,$$(DEPDIR)/$$*.d) -c $$< -o $$@
endef
$(foreach SUFF,$(CXX_SUFFIXES),$(eval $(call cxx_compilation_rule,$(SUFF))))

# this autodependency handling method is not inspired by the approach found at
# http://www.scottmcpeak.com/autodepend/autodepend.html

doxygen:
	echo '$(CPP_INCS)' | sed -e "s/; /\n/g" | sed -e "s/;//g" > src/dummy.h
	doxygen ./Doxyfile
	rm src/dummy.h

.PHONY: all doxygen clean tree
clean:
	$(RMDIR) $(DIRS)
# this implementation of clean relies on the precondition that all files created
# by this makefile are located in merely four directories

tree:
	tree -a --dirsfirst

