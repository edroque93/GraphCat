VERSION ?= Debug
CFLAGS_Debug = -g
CFLAGS_Release = -O2

CXX = g++
CFLAGS = -std=c++11 $(CFLAGS_${VERSION})
LDFLAGS = -lgsl -lgslcblas -lcairo
WARNINGS = -Wall -Wno-unused-variable
SOURCES = $(shell find src/ -name *.cpp)
HEADERS = $(shell find src/ -name *.hpp)
OBJECTS = $(SOURCES:src/%.cpp=obj/%.o)
DEPFILES = $(SOURCES:src/%.cpp=obj/%.deps)
EXECUTABLE = graphcat

CFORMAT = $(shell which clang-format >/dev/null 2>&1 \
		  && echo clang-format || echo clang-format-3.8)

.PHONY: all clean format

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(DEPFILES)
	@echo Linking
	@$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

obj/%.o: src/%.cpp
	@echo Compiling $<
	@mkdir -p $(@D)
	@$(CXX) -c $< -o $@ $(CFLAGS) $(WARNINGS)

obj/%.deps: src/%.cpp
	@mkdir -p $(@D)
	@$(CXX) -MM -MT $(@:%.deps=%.o) $< > $@

-include $(DEPFILES)

clean:
	@rm -rf $(EXECUTABLE) obj

format:
	@$(CFORMAT) -i $(SOURCES) $(HEADERS)
