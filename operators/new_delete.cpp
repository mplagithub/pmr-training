#include <iostream>
#include <new>
#include <vector>

// buffer to be used for non heap placement allocation
static unsigned char buffer[8];

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
void* operator new(std::size_t count) {
  void* ptr = malloc(count);
  if (!ptr) {
    throw std::bad_alloc{};
  }

  std::cout << "Allocating " << count << " bytes, at" << ptr << std::endl;
  return ptr;
}

void operator delete(void* ptr) noexcept {
  std::cout << "Deallocating " << ptr << std::endl;
  free(ptr);
}

class C {
  int a, b;

 public:
  C() : a(4), b(5) { std::cout << "C constructed\n"; }
  ~C() { std::cout << "C destructed\n"; }

  // 2. Overload operator new/delete just for class C (print class C as name +
  // pointer and size)

  void* operator new(std::size_t count) {
    void* ptr = malloc(count);
    if (!ptr) {
      throw std::bad_alloc{};
    }

    std::cout << "CLASS C: Allocating " << count << " bytes, at" << ptr
              << std::endl;
    return ptr;
  }

  void operator delete(void* ptr) noexcept {
    std::cout << "CLASS C: Deallocating " << ptr << std::endl;
    free(ptr);
  }

  // 3. Placement new using static buffer - see line 6 (print pointer)
  void* operator new(std::size_t count, void* ptr) {
    std::cout << "CLASS C [PLACEMENT]: Allocating " << count << " bytes, at"
              << ptr << std::endl;

    return ptr;
  }
};

int main() {
  // Allocate and delete A, B, C
  std::cout << "--- Allocating/Deallocating A ---\n";
  A* a = new A;
  delete a;

  std::cout << "--- Allocating/Deallocating B ---\n";
  B* b = new B;
  delete b;

  std::cout << "--- Allocating/Deallocating C (class-specific new) ---\n";
  C* c = new C;
  delete c;

  std::cout << "--- Allocating/Deallocating C with placement new (static "
               "buffer) ---\n";
  C* c2 = new (buffer) C;
  c2->~C();  // Manual destructor call, no delete needed

  // Checking what container uses
  std::cout << "--- std::vector<C> allocations ---\n";
  std::vector<C> v;
  for (int i = 0; i < 10; ++i) v.push_back(C{});

  std::cout << "--- END OF MAIN ---\n";
  return 0;
}