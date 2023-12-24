#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

struct Expansion {
  int row = -1;
  int col = -1;
};

struct Position {
  int x = -1;
  int y = -1;
  int distance(const Position& o) {
    return abs(o.x - this->x) + abs(o.y - this->y);
  }
};

std::vector<Expansion> expand(std::vector<std::string> image) {
  std::vector<Expansion> res;
  for(int i = 0; i < image.size(); ++i) {
    bool flag = true;
    for(int j = 0; j < image[0].size(); ++j) {
      if(image[i][j] != '.') {
        flag = false;
        break;
      }
    }
    if(flag) {
      res.push_back({i, -1});
    }
  }

  for(int j = 0; j < image[0].size(); ++j) {
    bool flag = true;
    for(int i = 0; i < image.size(); ++i) {
      if(image[i][j] != '.') {
        flag = false;
        break;
      }
    }
    if(flag) {
      res.push_back({-1, j});
    }
  }

  return res;
}

void getPositions(const std::vector<std::string> &img, std::vector<Position> &pos) {
  for(int i = 0; i < img.size(); ++i) {
    for(int j = 0; j < img[0].size(); ++j) {
      if(img[i][j] == '#') {
        pos.push_back({j, i});
      }
    }
  }
}

int main(void)
{
  int partOneExpansionFactor = 2;
  int partTwoExpansionFactor = 1000000;
  std::ifstream in;
  in.open("task.txt");
  std::string line;
  std::vector<std::string> image;
  while(!in.eof()) {
    getline(in, line);
    image.push_back(line);
  }
  image.pop_back();

  for(int i = 0; i < image.size(); ++i) {
    std::cout << image[i] << '\n';
  }
  std::cout << '\n';
  std::vector<Expansion> expansions = expand(image);

  // for(int i = 0; i < image.size(); ++i) {
  //   auto it = std::find_if(expansions.begin(), expansions.end(), 
  //         [i](Expansion &a){return a.row == i;});
  //   if(it != expansions.end()) {
  //     for(int m = 0; m < partOneExpansionFactor; ++m) {
  //       for(int j = 0; j < image[i].size(); ++j) {
  //         auto it1 = std::find_if(expansions.begin(), expansions.end(), 
  //               [j](Expansion &a){return a.col == j;});
  //         if(it1 != expansions.end()) {
  //           for(int k = 0; k < partOneExpansionFactor; ++k)
  //             std::cout << image[i][j];
  //         } else {
  //           std::cout << image[i][j];
  //         }
  //       }
  //       std::cout << '\n';
  //     }
  //   } else {
  //     for(int j = 0; j < image[i].size(); ++j) {
  //       auto it1 = std::find_if(expansions.begin(), expansions.end(), 
  //             [j](Expansion &a){return a.col == j;});
  //       if(it1 != expansions.end()) {
  //         for(int k = 0; k < partOneExpansionFactor; ++k)
  //           std::cout << image[i][j];
  //       } else {
  //         std::cout << image[i][j];
  //       }
  //     }
  //     std::cout << '\n';
  //   }
  // }

  std::vector<Position> positions;
  getPositions(image, positions);
  int res1 = 0;
  for(int i = 0; i < positions.size()-1; ++i) {
    for(int j = i; j < positions.size(); ++j) {
      res1 += positions[i].distance(positions[j]);
      int br = 0;
      for(int k = 0; k < expansions.size(); ++k) {
        if((expansions[k].col > positions[i].x && expansions[k].col < positions[j].x) ||
            (expansions[k].col > positions[j].x && expansions[k].col < positions[i].x) ||
            (expansions[k].row > positions[i].y && expansions[k].row < positions[j].y) ||
            (expansions[k].row > positions[j].y && expansions[k].row < positions[i].y)) {
          ++br;
        }
      }
      res1 += br * (partOneExpansionFactor-1);
    }
  }

  std::cout << "First part result: " << res1 << std::endl;

  unsigned long long int res2 = 0;
  for(int i = 0; i < positions.size()-1; ++i) {
    for(int j = i; j < positions.size(); ++j) {
      res2 += positions[i].distance(positions[j]);
      unsigned long long int br = 0;
      for(int k = 0; k < expansions.size(); ++k) {
        if((expansions[k].col > positions[i].x && expansions[k].col < positions[j].x) ||
            (expansions[k].col > positions[j].x && expansions[k].col < positions[i].x) ||
            (expansions[k].row > positions[i].y && expansions[k].row < positions[j].y) ||
            (expansions[k].row > positions[j].y && expansions[k].row < positions[i].y)) {
          ++br;
        }
      }
      res2 += br * (partTwoExpansionFactor-1);
    }
  }

  std::cout << "Second part result: " << res2 << std::endl;

  in.close();
  return 0;
}
