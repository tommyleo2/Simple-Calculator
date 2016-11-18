GCC := g++

INC := include
SRC := src
TEST:= test
BUILD := build
BIN := bin

SOURCES := $(shell find $(SRC) -type f -name *.cpp)
OBJECTS := $(patsubst $(SRC)/%,$(BUILD)/%,$(SOURCES:.cpp=.o))

CXXFLAG := -std=c++11 -g -I $(INC)

main: $(OBJECTS)
	@mkdir -p $(BIN)
	$(GCC) $(CXXFLAG) $^ -o $(BIN)/$@

test_parser: $(BUILD)/test_parser.o $(BUILD)/Parser.o $(BUILD)/lexical_analyzer.o
	@mkdir -p $(BIN)
	$(GCC) $(CXXFLAG) $^ -o $(BIN)/$@

test_lexical: $(BUILD)/test_lexical.o $(BUILD)/lexical_analyzer.o
	@mkdir -p $(BIN)
	$(GCC) $(CXXFLAG) $^ -o $(BIN)/$@

$(BUILD)/%.o: $(SRC)/%.cpp $(INC)/%.h
	@mkdir -p $(BUILD)
	$(GCC) $(CXXFLAG) -c $< -o $@

$(BUILD)/main.o: $(SRC)/main.cpp
	@mkdir -p $(BUILD)
	$(GCC) $(CXXFLAG) -c $^ -o $@

$(BUILD)/test_lexical.o: $(TEST)/test_lexical.cpp
	@mkdir -p $(BUILD)
	$(GCC) $(CXXFLAG) -c $^ -o $@

$(BUILD)/test_parser.o: $(TEST)/test_parser.cpp
	@mkdir -p $(BUILD)
	$(GCC) $(CXXFLAG) -c $^ -o $@

clean:
	rm $(BUILD)/*
