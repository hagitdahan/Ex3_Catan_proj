CXX = g++
CXXFLAGS = -std=c++11 -g -Wall
VALGRIND_FLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=99

SRCS = Board.cpp Card.cpp Catan.cpp Player.cpp Main.cpp ResourceManager.cpp Deck.cpp DevCardManager.cpp
HDRS = Board.hpp Card.hpp Catan.hpp Land.hpp Piece.hpp Player.hpp Vertex.hpp ResourceManager.hpp Deck.hpp DevCardManager.hpp 

TESTSOURCES = TestCounter.cpp Test.cpp
TESTOBJS = $(TESTSOURCES:.cpp=.o)

OBJS = $(SRCS:.cpp=.o)

TARGET = catan
TESTTARGET = test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(TESTTARGET): $(TESTOBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TESTTARGET) $(TESTOBJS) $(filter-out Main.o, $(OBJS))

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

tidy:
	clang-tidy $(SRCS) $(HDRS) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --


valgrind_test: $(TARGET) 
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(TESTTARGET) 2>&1 | { egrep "lost| at " || true; }
	
valgrind_catan:
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./$(TARGET) 2>&1 | { egrep "lost| at " || true; }

clean:
	rm -f $(OBJS) $(TARGET) $(TESTOBJS) $(TESTTARGET) valgrind-report.txt valgrind-test-report.txt

distclean: clean

.PHONY: all clean distclean
