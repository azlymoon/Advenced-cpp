CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++17 -Iinclude
LDFLAGS = 

EXE = hw-02_huffman
TEST = test_hw-02_huffman
SRCDIR = src
BINDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(BINDIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXE) $(LDFLAGS)

.PHONY: test
test: $(TEST)

$(TEST): $(OBJECTS) obj/test.o
	$(CXX) $(filter-out obj/main.o, $(OBJECTS)) obj/test.o  -o test/$(TEST) $(LDFLAGS)

obj/test.o: test/test.cpp | obj
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(BINDIR)/*.d)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(BINDIR) $(EXE)

.PHONY: clean all
