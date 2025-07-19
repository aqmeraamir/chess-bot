CXX = /usr/bin/clang++
CXXFLAGS = -std=c++17 -g -fdiagnostics-color=always -Iinclude

SRC = src/main.cpp src/chessboard.cpp src/evaluation.cpp
TARGET = bin/ChessBot

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)
