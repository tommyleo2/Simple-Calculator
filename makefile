GCC := g++

INC := include
SRC := src
TEST:= test
BUILD := build
BIN := bin

CXXFLAG := -std=c++11 -g -I $(INC)

test_lexical: $(BUILD)/test_lexical.o $(BUILD)/lexical_analyzer.o
	@mkdir -p $(BIN)
	$(GCC) $(CXXFLAG) $^ -o $(BIN)/$@

$(BUILD)/%.o: $(SRC)/%.cpp
	@mkdir -p $(BUILD)
	$(GCC) $(CXXFLAG) -c $^ -o $@

$(BUILD)/test_lexical.o: $(TEST)/test_lexical.cpp
	@mkdir -p $(BUILD)
	$(GCC) $(CXXFLAG) -c $^ -o $@

clean:
	rm $(BUILD)/*
