CXX := g++
CXXFLAGS := -std=c++17 -Wall -Werror

TARGET := memory_resource
SRC := memory_resource.cpp

TARGET2 := std_memory_resource
SRC2 := std_memory_resource.cpp

all: $(TARGET) $(TARGET2)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

$(TARGET2): $(SRC2)
	$(CXX) $(CXXFLAGS) -o $(TARGET2) $(SRC2)

clean:
	rm -f $(TARGET) $(TARGET2)