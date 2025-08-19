#include <iostream>
#include <list>
#include <memory>
#include <memory_resource>
#include <new>
#include <vector>

class A {
  int x;

 public:
  A() : x(1) { std::cout << "A constructed\n"; }
  ~A() { std::cout << "A destructed\n"; }
};

class MyMemoryResource : public std::pmr::memory_resource {
 public:
  void* do_allocate(std::size_t bytes, std::size_t alignment) override {
    std::cout << "MyMemoryResource::do_allocate, allocation no. "
              << ++alloc_count << " size: " << bytes << std::endl;
    return ::operator new(bytes, static_cast<std::align_val_t>(alignment));
  }
  void do_deallocate(void* p, std::size_t bytes,
                     std::size_t alignment) override {
    std::cout << "MyMemoryResource::do_deallocate " << " size: " << bytes
              << std::endl;

    ::operator delete(p, bytes, static_cast<std::align_val_t>(alignment));
  }

  bool do_is_equal(
      const std::pmr::memory_resource& other) const noexcept override {
    return this == &other;
  }

 private:
  std::size_t alloc_count = 0;
};

int main() {
  MyMemoryResource res{};

  auto a = std::allocate_shared<A, std::pmr::polymorphic_allocator<A>>(&res);

  set_default_resource(&res);

  std::pmr::vector<int>(4);
  std::pmr::vector<double>{8};
  std::pmr::list<int>(4);

  std::cout << "--- END OF MAIN ---\n";
  return 0;
}