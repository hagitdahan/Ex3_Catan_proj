CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

SRCS = Board.cpp Card.cpp Catan.cpp Player.cpp Main.cpp
HDRS = Board.hpp Card.hpp Catan.hpp Land.hpp Piece.hpp Player.hpp Vertex.hpp

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

# valgrind: $(TARGET) $(TESTTARGET)
# 	valgrind --leak-check=full --track-origins=yes --log-file=valgrind-report.txt ./$(TARGET)
# 	valgrind --leak-check=full --track-origins=yes --log-file=valgrind-test-report.txt ./$(TESTTARGET)
valgrind: $(TARGET) 
	valgrind --leak-check=full --track-origins=yes --log-file=valgrind-report.txt ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) $(TESTOBJS) $(TESTTARGET) valgrind-report.txt valgrind-test-report.txt

distclean: clean

.PHONY: all clean distclean
