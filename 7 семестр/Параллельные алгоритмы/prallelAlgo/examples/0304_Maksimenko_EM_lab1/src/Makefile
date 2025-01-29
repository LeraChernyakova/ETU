# project settings
SRCDIR					:= src
INCDIR					:= include
BUILDDIR				:= build
TARGETDIR				:= target
RESDIR					:= assets
SRCEXT					:= cpp
OBJEXT					:= o
DEPEXT					:= d

# compiler settings
CC						:= LANG=en_US g++
OPTIMIZATION			:= -O0 -g3
CXXFLAGS				:= -Wall -Wextra -Wpedantic
STANDART				:= -std=c++11
LIB						:=
INC						:= -I$(INCDIR) -I/usr/local/include
INCDEP					:= -I$(INCDIR)
CXX						:= $(CC) $(OPTIMIZATION) $(CXXFLAGS) $(STANDART)

# common files
COMMON_SRC				:= $(SRCDIR)/common/matrix.cpp
IPC_SRC					:= $(SRCDIR)/ipc/socket.cpp $(SRCDIR)/ipc/matrix_algorithms.cpp
THREADS_SRC				:= $(SRCDIR)/threads/tasks.cpp $(SRCDIR)/threads/matrix_algorithms.cpp

PROCESSING_SRC			:= $(SRCDIR)/ipc/processing.cpp $(COMMON_SRC) $(IPC_SRC)
PROCESSING_OBJ			:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(PROCESSING_SRC:.$(SRCEXT)=.$(OBJEXT)))
PROCESSING_TARGET		:= $(TARGETDIR)/processing

# threading files
THREADING_SRC			:= $(SRCDIR)/threads/threads.cpp $(COMMON_SRC) $(THREADS_SRC)
THREADING_OBJ			:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(THREADING_SRC:.$(SRCEXT)=.$(OBJEXT)))
THREADING_TARGET		:= $(TARGETDIR)/threading

# threading extended files
EXTENDED_SRC			:= $(SRCDIR)/threads/threads_extended.cpp $(COMMON_SRC) $(THREADS_SRC)
EXTENDED_OBJ			:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(EXTENDED_SRC:.$(SRCEXT)=.$(OBJEXT)))
EXTENDED_TARGET			:= $(TARGETDIR)/threading_extended

# sources and objects list
SOURCES					:= $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS					:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))


all: processing threading threading_extended

processing: resources $(PROCESSING_TARGET)
threading: resources $(THREADING_TARGET)
threading_extended: resources $(EXTENDED_TARGET)

# link objects
$(PROCESSING_TARGET): $(PROCESSING_OBJ)
	$(CC) -o $(PROCESSING_TARGET) $^ $(LIB)

$(THREADING_TARGET): $(THREADING_OBJ)
	$(CC) -o $(THREADING_TARGET) $^ $(LIB)

$(EXTENDED_TARGET): $(EXTENDED_OBJ)
	$(CC) -o $(EXTENDED_TARGET) $^ $(LIB)

# remake
remake: cleaner all

# copy resources
resources: directories
	@cp -r $(RESDIR)/* $(TARGETDIR)/$(RESDIR)/

# make directories
directories:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)
	@mkdir -p $(TARGETDIR)/$(RESDIR)/

# clean only objects
clean:
	@rm -fr $(BUILDDIR)

# full clean: objects and binaries
cleaner: clean
	@rm -fr $(TARGETDIR)

# set dependency info for .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

# compile sources
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@echo $@
	@mkdir -p $(dir $@)
	$(CXX) $(INC) -c $< -o $@
	@$(CXX) $(INCDEP) -MM $< > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$@:|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp