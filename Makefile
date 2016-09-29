CXX = g++
CFLAGS = -g -std=c++0x -Isrc/backend/
LDFLAGS = -lgsl -lgslcblas -lcairo
WARNINGS = -Wall -Wno-unused-variable
SOURCES = $(shell find src/ -name *.cpp)
OBJECTS = $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
EXECUTABLE = graphcat

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@echo Linking
	@$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

obj/%.o: src/%.cpp
	@echo Compiling $<
	@mkdir obj -p
	@$(CXX) -c $< -o $@ $(CFLAGS) $(WARNINGS)

obj/%.o: src/backend/%.cpp
	@echo Compiling backend $<
	@mkdir obj -p
	@$(CXX) -c $< -o $@ $(CFLAGS) $(WARNINGS)

clean:
	@rm -rf $(EXECUTABLE) $(OBJECTS)

qformat:
	@clang-format-3.8 -i $(SOURCES) $(shell find src/ -name *.hpp)
