#include <iostream>
#include <random>

int Partition(int* s, int start, int end) {
  if(start == end) return start;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(start, end);
  int p_idx = distr(gen);
  int p = s[p_idx];
  std::cout << "partition index: " << p_idx << std::endl;
  int low = start, high = end;
  while(low < high) {
    while(low <= end && s[low] < p) {
      ++low;
    }
    while(high >= 0 && s[high] > p) {
      --high;
    }
    if(low >= high) break;
    int tmp = s[low];
    s[low] = s[high];
    s[high] = tmp;
  }
  return low;
}

void Quicksort(int* s, int start, int end) {
  if(start >= end) return;
  int idx = Partition(s, start, end);
  Quicksort(s, start, idx-1);
  Quicksort(s, idx+1, end);
}

void merge(int* s, int start, int mid, int end) {
  int n = end-start+1;
  int tmp[n];
  int i = start, j = mid+1, k = 0;
  // move through two sections, adding the smallest or leftmost equal to tmp array
  while(i <= mid && j <= end) {
    if(s[i] <= s[j]) {
      tmp[k] = s[i];
      ++i;
      ++k;
    } else {
      tmp[k] = s[j];
      ++j;
      ++k;
    }
  }
  // add any leftover on the left section to array
  while(i <= mid) {
    tmp[k] = s[i];
    ++i;
    ++k;
  }
  //add any leftover on the right section to array
  while(j <= end) {
    tmp[k] = s[j];
    ++j;
    ++k;
  }
  // copy tmp into interval of original array
  for(int i = start, j = 0; i <= end; ++i, ++j) {
    s[i] = tmp[j];
  }
}

void mergesort(int* s, int start, int end) {
  if(start == end) return;
  int mid = (start + end) / 2;
  mergesort(s, start, mid);
  mergesort(s, mid+1, end);
  merge(s, start, mid, end);
}

void insertionSort(int* s, int size) {
  for(int i = 1; i < size; ++i){
    int j = i-1;
    while(j >= 0 && s[i] < s[j]) --j;
    int val = s[i];
    for(int k = i-1; k > j; --k) {
      s[k+1] = s[k];
    }
    s[j+1] = val;
  }
}

int main() {
  int data[]{7, 3, 9, 2, 12, 5, 1, 8, 7, 2, 20, 19, 6};
  int n = 13;
  std::cout << "Before sorting: " << std::endl;
  for(int i = 0; i < n; ++i){
    std::cout << data[i] << std::endl;
  }
  //Quicksort(data, 0, n-1);
  //mergesort(data, 0, n-1);
  insertionSort(data, n);
  std::cout << "After sorting: " << std::endl;
  for(int i = 0; i < n; ++i){
    std::cout << data[i] << std::endl;
  }
  return 0;
}
