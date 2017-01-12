VERSION ?= Debug
CFLAGS_Debug = -g
CFLAGS_Release = -O2

VERBOSE ?= 0
VERBOSE_0=@
V=$(VERBOSE_$(VERBOSE))

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

.PHONY: all clean format todo

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(DEPFILES)
	@echo Linking
	$V$(CXX) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

obj/%.o: src/%.cpp
	@echo Compiling $<
	@mkdir -p $(@D)
	$V$(CXX) $(CFLAGS) -c $(WARNINGS) -o $@ $<

obj/%.deps: src/%.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CFLAGS) -MM -MT $(@:%.deps=%.o) $< > $@

-include $(DEPFILES)

clean:
	@rm -rf $(EXECUTABLE) obj

format:
	@$(CFORMAT) -i $(SOURCES) $(HEADERS)

todo: $(SOURCES:%=todo/%) $(HEADERS:%=todo/%)

todo/%: %
	@grep -nH -e TODO $< | sed 's/\s*\/\/\/*\s*TODO\s*/ /'

