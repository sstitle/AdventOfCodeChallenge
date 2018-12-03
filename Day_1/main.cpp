#include <vector>
#include <iostream>
#include <fstream>
#include <map>

#include <assert.h>

using namespace std;


void PrintMap(map<int,int> input_map) {
  for (std::map<int,int>::iterator it=input_map.begin(); it!=input_map.end(); ++it) {
    std::cout << it->first << " " << it->second << std::endl;
  }
}

void PrintList(vector<int> list) {
  for (int i = 0; i < list.size(); i++) {
    std::cout << list[i] << std::endl;
  }
  std::cout << std::endl;
}

bool inList(int value, vector<int> list) {
  bool res = false;
  for (int i = 0; i < list.size(); i++) {
    if (list[i] == value) {
      res = true;
    }
  }
  return res;
}

int findTwiceReachedFreq(vector<int> list) {
  int list_len = list.size();
  int sum = 0;
  vector<int> sums;
  int counter = 0;
  while(!inList(sum,sums)) {
    // std::cout << "Acc : " << sum;
    sums.push_back(sum);
    int inc = list[counter%list_len];
    // std::cout << ", Inc : " << inc << std::endl;
    sum += inc;
    counter++;
    // PrintList(sums);
  }
  std::cout << "twice-reached frequency : " << sum << std::endl;
  return sum;
}


void test() {
  vector<int> list1 = {1,-1};
  assert(findTwiceReachedFreq(list1)==0);
  vector<int> list2 = {3,3,4,-2,-4};
  assert(findTwiceReachedFreq(list2)==10);
  vector<int> list3 = {-6,3,8,5,-6};
  assert(findTwiceReachedFreq(list3)==5);
  vector<int> list4 = {7,7,-2,-7,-4};
  assert(findTwiceReachedFreq(list4)==14);
  std::cout << "Passed all tests!" << std::endl;
}


int main(int argc, char const *argv[]) {
  // test();
  vector<int> list;
  ifstream inFile;
  inFile.open("/home/samtitle/Desktop/adventofcode/Day_1/input.txt");
  if (!inFile) {
    std::cout << "Error couldn't open file." << std::endl;
  } else {
    int x;
    int sum = 0;
    while (inFile >> x) {
      sum += x;
      list.push_back(sum);
    }
    inFile.close();
  }
  std::cout << "First twice-repeated number : " << findTwiceReachedFreq(list) << std::endl;
  return 0;
}
