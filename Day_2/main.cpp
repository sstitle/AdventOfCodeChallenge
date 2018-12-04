#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>

#include <assert.h>

using namespace std;

void PrintList(vector<int> list) {
  for (int i = 0; i < list.size(); i++) {
    std::cout << list[i] << std::endl;
  }
  std::cout << std::endl;
}

void PrintMap(map<char,int> input_map) {
  for (std::map<char,int>::iterator it=input_map.begin(); it!=input_map.end(); ++it) {
    std::cout << it->first << " " << it->second << std::endl;
  }
}

int ProdFromTally(vector<int> tally) {
  int acc = 1;
  for (size_t k = 0; k < tally.size(); k++) {
    acc *= tally[k];
  }
  return acc;
}

int checksum(vector<string> list) {
  vector<int> running_tally; // 0 - two's, 1 - three's, 2 - four's and so on
  for (size_t i = 0; i < list.size(); i++) {
    //For each word in the list
    const char* current_entry = list[i].c_str();
    map<char,int> current_tally;
    // std::cout << "Examining entry " << i << " : " << current_entry << std::endl;
    char letter = *current_entry;
    while(letter != '\0') {
      //count the number of occurrences for each letter
      // std::cout << "letter " << letter << std::endl;
      auto search = current_tally.find(letter);
      if (search != current_tally.end()) {
        search->second++;
      } else {
        current_tally.insert(std::pair<char,int>(letter,1));
      }
      current_entry++;
      letter = *current_entry;
    }
    vector<int> to_increment;
    for (std::map<char,int>::iterator it=current_tally.begin(); it!=current_tally.end(); ++it) {
      // std::cout << it->first << " " << it->second << std::endl;
      if (it->second > 1) {
        // std::cout << "add to running tally of " << it->second << "'s" << std::endl;
        bool present = false;
        for (size_t j = 0; j < to_increment.size(); j++) {
          if (it->second == to_increment[j]) {
            present = true;
          }
        }
        if (!present) {
          if (it->second - 1 > running_tally.size()) {
            running_tally.resize(it->second - 1);
          }
          // std::cout << "size of runnig tally" << running_tally.size() << std::endl;
          // std::cout << running_tally[it->second -2] << std::endl;
          running_tally[it->second - 2] = running_tally[it->second - 2] + 1;
        }
        to_increment.push_back(it->second);
      }
    }
    // std::cout << "Running tally:" << std::endl;
    // PrintList(running_tally);

  }
  return ProdFromTally(running_tally);;
}

void test() {
  vector<string> test1 = {"abcdef", "bababc", "abbcde",
                          "abcccd", "aabcdd", "abcdee", "ababab"};
  assert(checksum(test1) == 12);
  std::cout << "Passed all tests!" << std::endl;
}

int WordDiff(std::string a, std::string b) {
  const char* ca = a.c_str();
  const char* cb = b.c_str();
  char first, second;
  int count = 0;
  for (size_t i = 0; i < std::max(a.length(),b.length()); i++) {
    first = ca[i];
    second = cb[i];
    // std::cout << first << " " << second << std::endl;
    if (first != second) {
      count++;
    }
  }
  return count;
}

void test2() {
  assert(WordDiff("dave","dive") == 1);
  assert(WordDiff("abc","abc") == 0);
  assert(WordDiff("what","whom") == 2);
  std::cout << "Passed all tests" << std::endl;
}

void part2(vector<string> list) {
  for (size_t i = 0; i < list.size(); i++) {
    for (size_t j = 0; j < list.size(); j++) {
      if (WordDiff(list[i],list[j]) == 1) {
        std::cout << "Found similar pair :" << list[i] << " and " << list[j] << std::endl;
        break;
      }
    }
  }
}

int main(int argc, char const *argv[]) {
  // test();
  vector<string> list;
  ifstream inFile;
  inFile.open("/home/samtitle/Desktop/adventofcode/SamAdventCodeChallenge/Day_2/input.txt");
  if (!inFile) {
    std::cout << "Error couldn't open file." << std::endl;
  } else {
    string s;
    while (inFile >> s) {
      list.push_back(s);
    }
    inFile.close();
    std::cout << "Finished reading input..." << std::endl;
  }
  // test();
  // std::cout << "My answer to Part 1 is : " << checksum(list) << std::endl;
  // test2();
  part2(list);
  return 0;
}
