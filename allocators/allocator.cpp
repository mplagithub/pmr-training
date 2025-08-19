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
  // print data on all operations
 public:
  void* allocate(std::size_t size) {
    if (offset + size > bufferSize) {
      throw std::bad_alloc{};
    }

    void* ptr = buffer + offset;
    std::cout << "MyAllocator::allocate, allocating " << size
              << ", ptr: " << ptr << std::endl;
    offset += size;
    return ptr;
  }

  void deallocate(void* ptr) {
    std::cout << "MyAllocator::deallocate --> DO NOTHING at" << ptr
              << std::endl;
  }

 private:
  std::size_t offset = 0;
  static constexpr std::size_t bufferSize = 64;
  unsigned char buffer[bufferSize];
};

MyAllocator alloc{};

// 2.) Use MyAllocator to allocate/deallocate memory
void* operator new(std::size_t size) { return alloc.allocate(size); }
void operator delete(void* ptr) noexcept { return alloc.deallocate(ptr); }

int main() {
  std::cout << "--- Allocating/Deallocating A ---\n";
  A* a = new A;
  delete a;

  std::cout << "--- std::vector<int> allocation ---\n";
  std::vector<int> v;
  for (int i = 0; i < 123; ++i) v.push_back(i);

  std::cout << "--- END OF MAIN ---\n";
  return 0;
}