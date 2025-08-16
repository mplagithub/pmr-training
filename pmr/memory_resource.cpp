#include <iostream>
#include <list>
#include <memory_resource>
#include <new>
#include <vector>

class A {
  int x;

 public:
  A() : x(1) { std::cout << "A constructed\n"; }
  ~A() { std::cout << "A destructed\n"; }
};

int main() {
  std::cout << "--- END OF MAIN ---\n";
  return 0;
}