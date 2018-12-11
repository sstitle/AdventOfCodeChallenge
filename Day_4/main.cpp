#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <cstring>

using namespace std;

int FindGuardMostAsleep(vector<tm>& times, vector<string>& actions) {
  cout << "Top of FindGuard " << times.size() << " " << actions.size() << endl;
  for (size_t i = 0; i < times.size(); i++) {
    std::string entry = actions[i];
    // cout << entry << endl;
    int curr_guard;
    int time_acc = 0;
    if (entry[0] == '#') {
      std::string id_string = entry.substr(1, string::npos);
      curr_guard = strtol(id_string.c_str(), &id_string.c_str(), 10);
      cout << "ID: " << id_string << " " << curr_guard << endl;
    } else if (entry[0] == 'a') {
      cout << "sleeps" << endl;
    } else if (entry[0] == 'u') {
      cout << "wakes" << endl;
    }
  }
}

int main(int argc, char const *argv[]) {
  ifstream inFile;
  inFile.open("/home/samtitle/Desktop/adventofcode/SamAdventCodeChallenge/Day_4/input.txt");
  vector<string> lines;
  vector<tm> times;
  vector<string> actions;
  if (!inFile) {
    std::cout << "Error couldn't open file." << std::endl;
  } else {
    string s;
    while (getline(inFile,s)) {
      // std::cout << s << std::endl;
      lines.push_back(s);
    }
    inFile.close();
    sort(lines.begin(),lines.end());
    for (size_t i = 0; i < 5   /*lines.size()*/; i++) {
      // cout << lines[i] << endl;
      char* line = new char[lines[i].size()+1];
      strcpy(line,lines[i].c_str());
      cout << line << endl;

      char buffer[100];
      //Times
      tm time_stamp;
      char* token = strtok(line,"[-]: ");
      time_stamp.tm_year = strtol(token,&token,10);

      token = strtok(NULL,"[-]: ");
      time_stamp.tm_mon = strtol(token,&token,10);

      token = strtok(NULL,"[-]: ");
      time_stamp.tm_mday = strtol(token,&token,10);

      token = strtok(NULL,"[-]: ");
      time_stamp.tm_hour = strtol(token,&token,10);

      token = strtok(NULL,"[-]: ");
      time_stamp.tm_min = strtol(token,&token,10);
      strftime(buffer,100,"%D, %r",&time_stamp);
      cout << "Time: " << buffer << endl;
      times.push_back(time_stamp);

      //Actions
      strcpy(line,lines[i].c_str());
      token = strtok(line,"]");
      token = strtok(NULL,"]");
      char* action = new char[7];
      action = strtok(token, " ");
      action = strtok(NULL, " ");
      std::string entry(action);
      actions.push_back(entry);
      // cout << token << endl;
      // cout << action << endl;
      cout << "Action Keyword : " << entry << endl;
      // cout << "action: " << action[i] << endl;
    }
    /*cout << "Guard #" << */FindGuardMostAsleep(times, actions);// << endl;
  }
  return 0;
}
