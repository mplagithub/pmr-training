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

class B {
  int y, z;

 public:
  B() : y(2), z(3) { std::cout << "B constructed\n"; }
  ~B() { std::cout << "B destructed\n"; }
};

// 1. Overload global operator new/delete here (print pointer and size)

// 2. Declare static buffer for C here

class C {
  int a, b;

 public:
  C() : a(4), b(5) { std::cout << "C constructed\n"; }
  ~C() { std::cout << "C destructed\n"; }

  // 3. Overload operator new/delete just for class C (print pointer and size)
  // 4. Placement new using static buffer (print pointer)
};

int main() {
  // 5. Allocate and delete A, B, C
  std::cout << "--- Allocating/Deallocating A ---\n";

  std::cout << "--- Allocating/Deallocating B ---\n";

  std::cout << "--- Allocating/Deallocating C (class-specific new) ---\n";

  std::cout << "--- Allocating/Deallocating C with placement new (static "
               "buffer) ---\n";

  // 6. Play with std::vector<int> (insert some elements, so how allocations are
  // working)

  return 0;
}