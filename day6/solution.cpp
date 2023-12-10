#include <iostream>
#include <fstream>
#include <vector>
#include <string>

unsigned long long int getNumAndMoveCnt(const std::string &str, int &cnt) {
  unsigned long long int res = 0;
  while(cnt < str.length() && str[cnt] >= '0' && str[cnt] <= '9') {
    res *= 10;
    res += str[cnt] - '0';
    ++cnt;
  }
  return res;
}

std::vector<int> getNums(const std::string &str, int start) {
  std::vector<int> res;
  while(start < str.length()) {
    if(str[start] == ' ') {}
    else {
      res.push_back(getNumAndMoveCnt(str, start));
    }
    ++start;
  }
  return res;
}

std::vector<unsigned long long int> getNums2(const std::string &str, int start) {
  std::vector<unsigned long long int> res;
  std::string s = "";
  while(start < str.length()) {
    if(str[start] == ' ') {}
    else {
      s += str[start];
    }
    ++start;
  }
  int i = 0;
  res.push_back(getNumAndMoveCnt(s, i));
  return res;
}

int main(void)
{
  std::ifstream in;
  in.open("task.txt");
  std::string line;
  getline(in, line);
  std::vector<unsigned long long int> times = getNums2(line, 11);
  getline(in, line);
  std::vector<unsigned long long int> distances = getNums2(line, 11);

  for(int i = 0; i < times.size(); ++i) {
    std::cout << times[i] << ' ';
  }
  std::cout << std::endl;
  for(int i = 0; i < distances.size(); ++i) {
    std::cout << distances[i] << ' ';
  }
  std::cout << std::endl;
  
  unsigned long long int res = 1;
  for(int rCnt = 0; rCnt < times.size(); ++rCnt) {
    unsigned long long int counter = 0;
    std::cout << "Race " << rCnt+1 << std::endl;
    for(int i = times[rCnt]/2; i > 0; --i) {
      if(i * (times[rCnt] - i) > distances[rCnt]) {
        // std::cout << "Btn hold for " << i  << " wins" << std::endl;
        ++counter;
      }
    }
    counter *= 2;
    counter -= (times[rCnt]%2==0);
    // std::cout << "counter " << counter << std::endl;
    res *= counter;
  }
  std::cout << "First part result " << res << std::endl;
  return 0;
}

// Time:      7  15   30
//      4294967295
// 204171312101780
// Distance:  9  40  200
