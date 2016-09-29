CXX = g++
CFLAGS = -g -std=c++0x
LDFLAGS = -lgsl -lgslcblas -lcairo
WARNINGS = -Wall -Wno-unused-variable
SOURCES = $(shell find src/ -name *.cpp)
#OBJECTS = $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)
DEPFILES = $(SOURCES:src/%.cpp=obj/%.d)
EXECUTABLE = graphcat

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(DEPFILES)
	@echo Linking
	@$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

obj/%.o: src/%.cpp
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) -c $< -o $@ $(CFLAGS) $(WARNINGS)

obj/%.d: src/%.cpp
	@mkdir -p $(@D)
	@$(CXX) -MM -MT $(@:%.d=%.o) $< > $@

-include $(DEPFILES)

#obj/%.o: src/backend/%.cpp
#	@echo Compiling backend $<
#	@mkdir -p
#	@$(CXX) -c $< -o $@ $(CFLAGS) $(WARNINGS)

clean:
	@rm -rf $(EXECUTABLE) $(OBJECTS) $(DEPFILES)

qformat:
	@clang-format-3.8 -i $(SOURCES) $(shell find src/ -name *.hpp)
