CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

SRCS = Board.cpp Card.cpp Catan.cpp Player.cpp Main.cpp
HDRS = Board.hpp Card.hpp Catan.hpp Land.hpp Piece.hpp Player.hpp Vertex.hpp

OBJS = $(SRCS:.cpp=.o)

TARGET = catan

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

valgrind: $(TARGET)
	valgrind --leak-check=full --track-origins=yes --log-file=valgrind-report.txt ./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET) valgrind-report.txt

distclean: clean

.PHONY: all clean distclean
