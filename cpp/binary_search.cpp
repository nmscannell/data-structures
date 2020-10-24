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

int binarySearchRec(int* s, int e, int start, int end) {
  if(start >= end) return -1;
  int mid = (start + end) / 2;
  if(s[mid] == e) return mid;
  else if(e < s[mid]) return binarySearchRec(s, e, start, mid);
  else return binarySearchRec(s, e, mid+1, end);
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
  std::cout << "Index of 8: " << binarySearchRec(data, 8, 0, n) << std::endl;
  std::cout << "searching for 33" << std::endl;
  std::cout << "Index of 33: " << binarySearchRec(data, 33, 0, n) << std::endl;
  std::cout << "searching for 78" << std::endl;
  std::cout << "Index of 78: " << binarySearchRec(data, 78, 0, n) << std::endl;
}
