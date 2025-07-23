#include <iostream>
#include <new>
#include <vector>

// Test classes
class A {
  int x;

 public:
  A() : x(1) { std::cout << "A constructed\n"; }
  ~A() { std::cout << "A destructed\n"; }
};

class MyAllocator {
  // 1.) Write body -> should be linear allocator, using fixed size buffer
};

// 2.) Use MyAllocator to allocate/deallocate memory
void* operator new(std::size_t size) {}
void operator delete(void* ptr) noexcept {}

int main() {
  std::cout << "--- Allocating/Deallocating A ---\n";
  A* a = new A;
  delete a;

  std::cout << "--- std::vector<int> allocation ---\n";
  std::vector<int> v;
  for (int i = 0; i < 3; ++i) v.push_back(i);

  return 0;
}