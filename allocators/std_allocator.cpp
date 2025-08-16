#include <iostream>
#include <list>
#include <new>
#include <vector>

// Test classes
class A {
  int x;

 public:
  A() : x(1) { std::cout << "A constructed\n"; }
  ~A() { std::cout << "A destructed\n"; }
};

template <typename T>
class MyAllocator {};

int main() {
  std::cout << "--- Allocating/Deallocating A ---\n";
  A* a = new A;
  delete a;

  std::cout << "--- std::vector<int> allocation ---\n";
  std::vector<int> v1{};
  for (int i = 0; i < 3; ++i) {
    v1.push_back(i);
  }
  std::cout << "--- END OF MAIN ---\n";
  return 0;
}