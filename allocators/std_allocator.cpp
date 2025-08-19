#include <iostream>
#include <list>
#include <memory>
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
class MyAllocator {
 public:
  MyAllocator(std::size_t identifier) : id(identifier) {}

  using value_type = T;
  using propagate_on_container_copy_assignment = std::true_type;

  T* allocate(std::size_t n) {
    std::cout << "MyAllocator id = " << id << " allocating: " << n * sizeof(T)
              << " bytes" << std::endl;

    return static_cast<T*>(::operator new(n * sizeof(T)));
  }

  void deallocate(T* p, std::size_t n) {
    std::cout << "MyAllocator id = " << id << " deallocating: " << n * sizeof(T)
              << " bytes" << std::endl;

    ::operator delete(p, n * sizeof(T));
  }

  bool operator==(const MyAllocator& other) { return this == &other; }
  bool operator!=(const MyAllocator& other) { return this != &other; }

  template <typename U>
  MyAllocator(const MyAllocator<U>& other) : id(other.id) {}

  template <typename>
  friend class MyAllocator;

 private:
  std::size_t id = 0;
};

int main() {
  MyAllocator<int> my_alloc{1};

  std::cout << "--- Allocating/Deallocating A ---\n";

  // A* a = new A;
  // delete a;

  auto a = std::allocate_shared<A>(my_alloc);

  std::cout << "--- std::vector<int> allocation ---\n";
  std::vector<int, MyAllocator<int>> v1{my_alloc};
  for (int i = 0; i < 3; ++i) {
    v1.push_back(i);
  }

  std::vector<int, MyAllocator<int>> v2{MyAllocator<int>{2}};
  for (int i = 0; i < 7; ++i) {
    v2.push_back(i);
  }

  std::cout << "--- std::vector<int> copy assignment ---\n";
  v1 = v2;

  std::cout << "--- std::list<int> allocation ---\n";
  std::list<int, MyAllocator<int>> my_list{MyAllocator<int>{99}};
  for (int i = 0; i < 3; ++i) {
    my_list.push_back(i);
  }

  std::cout << "--- std::vector<double> allocation ---\n";
  std::vector<double> vec_double{4};

  std::cout << "--- END OF MAIN ---\n";
  return 0;
}