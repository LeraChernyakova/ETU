# Need to define variables:
# SOURCES  - names of cpp sources without file extensions
# INCLUDES - names of include directories
# LIBS     - libraries to be linked
# TARGET   - name of executable target

CXX      ?= g++
CXXFLAGS ?= -g3

all: $(TARGET)

$(TARGET): $(addsuffix .o,$(SOURCES))
	$(CXX) $(CXXFLAGS) -o $(TARGET) $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(addprefix -I,$(INCLUDES)) -c $< -o $@

clean:
	@rm -f $(addsuffix .o,$(SOURCES))
	@rm -f $(TARGET)
