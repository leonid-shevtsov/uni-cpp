CPP = g++
CPPFLAGS = -lstdc++ -I.

GTEST_DIR = /Users/leonid/vendor/gtest-1.6.0
GTEST_FLAGS = -I$(GTEST_DIR)/include -L$(GTEST_DIR)/lib/.libs -lgtest
GTEST_DYLD_PATH = $(GTEST_DIR)/lib/.libs
GTEST_ENV = DYLD_LIBRARY_PATH=$(GTEST_DYLD_PATH)

SOURCES = *.cpp
TEST_SOURCES = ../shared/test_harness.cpp $(filter-out main.cpp, $(shell echo *.cpp)) test/*.cpp

BIN = bin/$(APP)$(BINEXT)
TEST_BIN = bin/$(APP)_test$(BINEXT)

$(BIN): $(SOURCES)
	mkdir -p bin
	$(CPP) $(CPPFLAGS) $(SOURCES) -o $(BIN)

$(TEST_BIN): $(TEST_SOURCES)
	mkdir -p bin
	$(CPP) $(CPPFLAGS) $(GTEST_FLAGS) $(TEST_SOURCES) -o $(TEST_BIN) 
	$(GTEST_ENV) $(TEST_BIN) 

flowchart.dummy:
	mkdir -p flowchart.out
	$(foreach dot, $(shell echo flowchart/*.dot), dot -Tsvg $(dot) -o flowchart.out/$(notdir $(basename $(dot))).svg;)
	$(foreach svg, $(shell echo flowchart.out/*.svg), java -jar ~/bin/batik/batik-rasterizer.jar -dpi 300 $(svg);)

test: $(TEST_BIN) 

flowchart: flowchart.dummy

clean:
	rm bin/*


