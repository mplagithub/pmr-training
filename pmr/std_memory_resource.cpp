#include <iostream>
#include <list>
#include <memory_resource>
#include <new>
#include <vector>

int main() {
  unsigned char buffer[16];
  std::pmr::monotonic_buffer_resource buf_res{buffer, 16,
                                              std::pmr::null_memory_resource()};

  std::pmr::vector<int> vec{4, &buf_res};

  for (int i = 0; i < 4; ++i) {
    vec.push_back(i);
  }

  std::cout << "Buffer address " << static_cast<void*>(buffer) << std::endl;
  std::cout << "Vector address " << static_cast<void*>(vec.data()) << std::endl;
  std::cout << "--- END OF MAIN ---\n";
  return 0;
}