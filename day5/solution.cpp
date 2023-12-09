#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct uint3 {
  unsigned int a;
  unsigned int b;
  unsigned int c;
};

unsigned int getNumAndMoveCnt(const std::string &str, int &cnt) {
  unsigned int res = 0;
  while(cnt < str.length() && str[cnt] >= '0' && str[cnt] <= '9') {
    res *= 10;
    res += str[cnt] - '0';
    ++cnt;
  }
  return res;
}

struct Converter {
  std::vector<uint3> mappings;
  void add(std::string str) {
    int i = 0;
    unsigned int x = getNumAndMoveCnt(str, i);
    unsigned int y = getNumAndMoveCnt(str, ++i);
    unsigned int z = getNumAndMoveCnt(str, ++i);
    mappings.push_back(uint3{x, y, z});
  }
  unsigned int convert(unsigned int src) {
    unsigned int res = src;
    for(int i = 0; i < mappings.size(); ++i) {
      if(src >= mappings[i].b && src < (mappings[i].b + mappings[i].c)) {
        res = src + mappings[i].a - mappings[i].b;
      }
    }
    return res;
  }
};
//first part
std::vector<unsigned int> getSeeds(std::string str) {
  std::vector<unsigned int> seeds;
  for(int i = 6; i < str.size(); ++i) {
    if(str[i] == ' ') {}
    else seeds.push_back(getNumAndMoveCnt(str, i));
  }
  return seeds;
}
//second part
std::vector<unsigned int> getSeedsRangeNext(std::string str, int start = 0) {
  std::vector<unsigned int> seeds;
  for(int i = 6; i < str.size(); ++i) {
    if(str[i] == ' ') {}
    else {
      unsigned int n = getNumAndMoveCnt(str, i);
      ++i;
      unsigned int m = getNumAndMoveCnt(str, i);
      if(start > 0) {
        --start;
        continue;
      }
      for(int j = 0; j < m; ++j) {
        seeds.push_back(n+j);
      }
      break;
    }
  }
  return seeds;
}

int main(void)
{
  std::ifstream in;
  std::string line;
  std::string seedsLine;
  in.open("task.txt");
  getline(in, seedsLine);
  int seedCnt = 1;
  std::vector<unsigned int> seeds = getSeedsRangeNext(seedsLine, seedCnt); //change to choose part
  ++seedCnt;
  std::vector<Converter> converters;
  int convCnt = -1;
  for(int i = 0; i < 7; ++i)
    converters.push_back(Converter{});
  while(!in.eof()) {
    getline(in, line);
    if(line.length() == 0) {}
    else if(line[0] >= '0' && line[0] <= '9') {
      converters[convCnt].add(line);
    } else {
      ++convCnt;
    }
  }
  
  // for(int i = 0; i < seeds.size(); ++i) {
  //   std::cout << seeds[i] << ' ';
  // }
  // std::cout << std::endl;
  // for(int i = 0; i < converters.size(); ++i) {
  //   std::cout << "Conv " << i+1 << "\n";
  //   for(int j = 0; j < converters[i].mappings.size(); ++j) {
  //     std::cout << "  " << converters[i].mappings[j].a << ' ' 
  //               << converters[i].mappings[j].b << ' ' 
  //               << converters[i].mappings[j].c << "\n";
  //   }
  // }

  unsigned int minLoc = 4294967295;
  while(seeds.size() > 0) {
    for(int i = 0; i < seeds.size(); ++i) {
      int l = seeds[i];
      for(int j = 0; j < converters.size(); ++j) {
        l = converters[j].convert(l);
      }
      if(minLoc > l) minLoc = l;
    }
    seeds = getSeedsRangeNext(seedsLine, seedCnt);
    ++seedCnt;
  }
  std::cout << "Result " << minLoc << std::endl;

  in.close();
  return 0;
}
