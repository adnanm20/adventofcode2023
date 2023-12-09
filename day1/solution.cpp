#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string formatLine(std::string str) {
  std::vector<std::string> nums {
                                  "zero",
                                  "one",
                                  "two",
                                  "three",
                                  "four",
                                  "five",
                                  "six",
                                  "seven",
                                  "eight",
                                  "nine"};

  std::string formatted = "";
  bool rep = false;
  for(int i = 0; i < str.length(); ++i) {
    for(int j = 1; j < nums.size(); ++j) {
      if(str.substr(i, nums[j].length()) == nums[j]) {
        formatted += '0' + j;
        rep = true;
      }
    }
    if(!rep)
      formatted += str[i];
    rep = false;
  }

  return formatted;
}

int getFirstLastNum(std::string str) {
  int f = 0, l = 0;
  for(int i = 0; i < str.length(); ++i)
  {
    if(!f && str[i] >= '0' && str[i] <= '9') f = str[i] - '0';
    if(str[i] >= '0' && str[i] <= '9') l = str[i] - '0';
  }
  return f*10 + l;
}

void formatLines(std::vector<std::string> &lines) {
  for(int i = 0; i < lines.size(); ++i) {
    lines[i] = formatLine(lines[i]);
  }
}

int main(void)
{
  std::ifstream in;
  in.open("task.txt");
  std::vector<std::string> lines;
  std::string line;
  while(!in.eof()) {
    getline(in, line);
    lines.push_back(line);
  }

  formatLines(lines);
  

  int sum = 0;
  for(auto l : lines) {
    sum += getFirstLastNum(l);
  }

  std::cout << sum << std::endl;
  in.close();

  return 0;
}
