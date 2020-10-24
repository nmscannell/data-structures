#include <iostream>

int binarySearch(int* s, int e, int size) {
  int start = 0, end = size;
  while(start < end){
    int mid = (start + end) / 2;
    if(s[mid] == e) return mid;
    else if(e < s[mid]) end = mid;
    else start = mid + 1;
  }
  return -1;
}

int main() {
  int data[]{1, 3, 6, 19, 23, 46, 63, 78, 80, 88};
  int n = 10;
  std::cout << "data array: " << std::endl;
  for(int i = 0; i < n; ++i) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
  std::cout << "searching for 8" << std::endl;
  std::cout << "Index of 8: " << binarySearch(data, 8, n) << std::endl;
  std::cout << "searching for 33" << std::endl;
  std::cout << "Index of 33: " << binarySearch(data, 33, n) << std::endl;
  std::cout << "searching for 78" << std::endl;
  std::cout << "Index of 78: " << binarySearch(data, 78, n) << std::endl;
}
