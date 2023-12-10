#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int getNumAndMoveCnt(const std::string &str, int &cnt) {
  int res = 0;
  while(cnt < str.length() && str[cnt] >= '0' && str[cnt] <= '9') {
    res *= 10;
    res += str[cnt] - '0';
    ++cnt;
  }
  return res;
}

std::vector<int> getNumbers(const std::string &str) {
  bool negative = false;
  int num = 0;
  std::vector<int> res;
  for(int i = 0; i < str.size(); ++i) {
    if(str[i] == ' ') {
      negative = false;
    }
    else if(str[i] == '-') {
      negative = true;
    } else {
      num = getNumAndMoveCnt(str, i);
      res.push_back(negative ? -num : num);
      negative = false;
    }
  }
  return res;
}

int getNextNumber(const std::vector<int> &nums) {
  std::vector<int> diffs;
  for(int i = 1; i < nums.size(); ++i) {
    diffs.push_back(nums[i] - nums[i-1]);
  }
  for(int i = 1; i < diffs.size(); ++i) {
    if(diffs[i] != 0) {
      int x = getNextNumber(diffs);
      return nums[nums.size()-1] + x;
    }
  }
  return nums[nums.size()-1];
}

int getPreviousNumber(const std::vector<int> &nums) {
  std::vector<int> diffs;
  for(int i = 1; i < nums.size(); ++i) {
    diffs.push_back(nums[i] - nums[i-1]);
  }
  for(int i = 1; i < diffs.size(); ++i) {
    if(diffs[i] != 0) {
      int x = getPreviousNumber(diffs);
      return nums[0] - x;
    }
  }
  return nums[0];
}

int main(void)
{
  std::ifstream in;
  in.open("task.txt");
  std::string line;
  std::vector<std::vector<int>> histories;
  while(!in.eof()) {
    getline(in, line);
    histories.push_back(getNumbers(line));
  }
  histories.pop_back();
  
  // for(int i = 0; i < histories.size(); ++i) {
  //   std::cout << "Hist " << i+1 << ' ';
  //   for(int j = 0; j < histories[i].size(); ++j) {
  //     std::cout << histories[i][j] << ' ';
  //   }
  //   std::cout << '\n';
  // }

  int sum = 0;
  for(int i = 0; i < histories.size(); ++i) {
    int s = getNextNumber(histories[i]);
    sum += s;
  }

  std::cout << "First part result " << sum << std::endl;
  sum = 0;
  for(int i = 0; i < histories.size(); ++i) {
    int s = getPreviousNumber(histories[i]);
    sum += s;
  }

  std::cout << "Second part result " << sum << std::endl;
  return 0;
}
