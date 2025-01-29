# project settings
SRCDIR					:= src
INCDIR					:= include
BUILDDIR				:= build
TARGETDIR				:= target
SRCEXT					:= cpp
OBJEXT					:= o
DEPEXT					:= d

# compiler settings
CC						:= LANG=en_US g++
OPTIMIZATION			:= -O0 -g3
OPTIONS					:=
CXXFLAGS				:= -Wall -Wextra -Wpedantic $(OPTIONS)
STANDART				:= -std=c++14
LIB						:= -pthread
INC						:= -I$(INCDIR) -I/usr/local/include
INCDEP					:= -I$(INCDIR)
CXX						:= $(CC) $(OPTIMIZATION) $(CXXFLAGS) $(STANDART)

# threading files
LAB_SRC					:= $(SRCDIR)/main.cpp
LAB_OBJ					:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(LAB_SRC:.$(SRCEXT)=.$(OBJEXT)))
LAB_TARGET				:= $(TARGETDIR)/lab4

# sources and objects list
SOURCES					:= $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS					:= $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))


all: directories $(LAB_TARGET)

# link objects
$(LAB_TARGET): $(LAB_OBJ)
	$(CC) -o $(LAB_TARGET) $^ $(LIB)

# remake
remake: cleaner all

# make directories
directories:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(TARGETDIR)

# clean only objects
clean:
	@rm -fr $(BUILDDIR)
	@rm -fr $(TARGETDIR)

# full clean: objects and binaries
cleaner: clean

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
