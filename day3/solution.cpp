#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int getNumberAt(int x, int y, std::vector<std::string> &schem) {
  if(x < 0 || y < 0 || x > schem.size() || y > schem[0].size())
    return 0;
  if(!(schem[y][x] >= '0' && schem[y][x] <= '9')) {
    return 0;
  }
  int res = 0;
  while(x >= 0 && schem[y][x] >= '0' && schem[y][x] <= '9') {
    --x;
  }
  ++x;
  while(x < schem[0].length() && schem[y][x] >= '0' && schem[y][x] <= '9') {
    res *= 10;
    res += schem[y][x] - '0';
    schem[y][x] = '.';
    ++x;
  }

  return res;
}

int main(void) {
  std::ifstream in;
  in.open("task.txt");
  std::vector<std::string> schematic;
  std::string line;
  while(!in.eof()) {
    getline(in, line);
    schematic.push_back(line);
  }
  std::vector<std::string> schematic2 = schematic;

  int sum = 0;
  for(int i = 0; i < schematic.size(); ++i) {
    for(int j = 0; j < schematic[i].length(); ++j) {
      if(schematic[i][j] != '.' && !(schematic[i][j] >= '0' && schematic[i][j] <= '9')) {
        sum += getNumberAt(j-1, i-1, schematic); //also removes number from map
        sum += getNumberAt(j-0, i-1, schematic);
        sum += getNumberAt(j+1, i-1, schematic);
        sum += getNumberAt(j-1, i-0, schematic);
        sum += getNumberAt(j+1, i-0, schematic);
        sum += getNumberAt(j-1, i+1, schematic);
        sum += getNumberAt(j-0, i+1, schematic);
        sum += getNumberAt(j+1, i+1, schematic);
      }
    }
  }
  std::cout << "Part one sum " << sum << std::endl;

  schematic = schematic2;
  sum = 0;
  for(int i = 0; i < schematic.size(); ++i) {
    for(int j = 0; j < schematic[i].length(); ++j) {
      int f = 1, s = 0;
      int gotTwo = 0;
      if(schematic[i][j] == '*') {
        s = getNumberAt(j-1, i-1, schematic); //also removes number from map
        if(s) {++gotTwo;f *= s;}
        s = getNumberAt(j-0, i-1, schematic);
        if(s) {++gotTwo;f *= s;}
        s = getNumberAt(j+1, i-1, schematic);
        if(s) {++gotTwo;f *= s;}
        s = getNumberAt(j-1, i-0, schematic);
        if(s) {++gotTwo;f *= s;}
        s = getNumberAt(j+1, i-0, schematic);
        if(s) {++gotTwo;f *= s;}
        s = getNumberAt(j-1, i+1, schematic);
        if(s) {++gotTwo;f *= s;}
        s = getNumberAt(j-0, i+1, schematic);
        if(s) {++gotTwo;f *= s;}
        s = getNumberAt(j+1, i+1, schematic);
        if(s) {++gotTwo;f *= s;}
      }
      if(gotTwo == 2)
        sum += f;
    }
  }
  std::cout << "Part two sum " << sum << std::endl;

  in.close();

  return 0;
}
