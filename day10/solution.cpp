#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

void traverse(std::vector<std::string> &lines,
              std::vector<std::vector<int>> &distances,
              unsigned int x, unsigned int y, int dist = 1) {
  if(x < 0 || y < 0 || x >= lines[0].size() || y >= lines.size())
    return;
  if(x == 0 || x == lines[0].size()-1 || y == 0 || y == lines.size()-1) {
  }
  if(distances[y][x] < dist && distances[y][x] != -1) return;
  
  distances[y][x] = dist;
  switch (lines[y][x]) {
    case '|':
      if(y-1 >= 0 && (lines[y-1][x] == '|' || lines[y-1][x] == '7' || lines[y-1][x] == 'F'))
        traverse(lines, distances, x, y-1, dist+1);
      if(y+1 < lines.size() && (lines[y+1][x] == '|' || lines[y+1][x] == 'L' || lines[y+1][x] == 'J'))
        traverse(lines, distances, x, y+1, dist+1);
      break;
    case '-':
      if(x-1 >= 0 && (lines[y][x-1] == '-' || lines[y][x-1] == 'F' || lines[y][x-1] == 'L')) 
        traverse(lines, distances, x-1, y, dist+1);
      if(x+1 < lines[0].size() && (lines[y][x+1] == '-' || lines[y][x+1] == '7' || lines[y][x+1] == 'J'))
        traverse(lines, distances, x+1, y, dist+1);
      break;
    case 'L':
      if(y-1 >= 0 && (lines[y-1][x] == '|' || lines[y-1][x] == '7' || lines[y-1][x] == 'F'))
        traverse(lines, distances, x, y-1, dist+1);
      if(x+1 < lines[0].size() && (lines[y][x+1] == '-' || lines[y][x+1] == '7' || lines[y][x+1] == 'J'))
        traverse(lines, distances, x+1, y, dist+1);
      break;
    case 'J':
      if(y-1 >= 0 && (lines[y-1][x] == '|' || lines[y-1][x] == '7' || lines[y-1][x] == 'F'))
        traverse(lines, distances, x, y-1, dist+1);
      if(x-1 >= 0 && (lines[y][x-1] == '-' || lines[y][x-1] == 'F' || lines[y][x-1] == 'L')) 
        traverse(lines, distances, x-1, y, dist+1);
      break;
    case '7':
      if(x-1 >= 0 && (lines[y][x-1] == '-' || lines[y][x-1] == 'F' || lines[y][x-1] == 'L')) 
        traverse(lines, distances, x-1, y, dist+1);
      if(y+1 < lines.size() && (lines[y+1][x] == '|' || lines[y+1][x] == 'L' || lines[y+1][x] == 'J'))
        traverse(lines, distances, x, y+1, dist+1);
      break;
    case 'F':
      if(x+1 < lines[0].size() && (lines[y][x+1] == '-' || lines[y][x+1] == '7' || lines[y][x+1] == 'J'))
        traverse(lines, distances, x+1, y, dist+1);
      if(y+1 < lines.size() && (lines[y+1][x] == '|' || lines[y+1][x] == 'L' || lines[y+1][x] == 'J'))
        traverse(lines, distances, x, y+1, dist+1);
      break;
    case '.':
    case 'S':
      return;
      break;
  }
  // lines[y][x] = 'B';
}

enum Direction {
  center, north, south, east, west
};

//1 for pos dir(clockwise, right is inside), 0 for negative dir (cc, left inside)
bool setInOut(std::vector<std::string> &lines, int x, int y, Direction moving) {
  static int leftTurn = 0, rightTurn = 0;
  switch (lines[y][x]) {
    case '|':
      if(moving == south) {
        bool ret = setInOut(lines, x, y+1, south); 
        if(ret) {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'O';//left
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'I';//right
        }
        else {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'I';
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'O';
        }
        return ret;
      }
      if(moving == north) {
        bool ret = setInOut(lines, x, y-1, north); 
        if(ret) {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'I';//right
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'O';//left
        }
        else {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'O';
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'I';
        }
        return ret;
      }
      break;
    case '-':
      if(moving == west) {
        bool ret = setInOut(lines, x-1, y, west); 
        if(ret) {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'O';//left
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'I';//right
        }
        else {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'I';
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'O';
        }
        return ret;
      }
      if(moving == east) {
        bool ret = setInOut(lines, x+1, y, east); 
        if(ret) {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'I';//right
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'O';//left
        }
        else {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'O';
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'I';
        }
        return ret;
      }
      break;
    case 'L':
      if(moving == south) {
        ++leftTurn;
        bool ret = setInOut(lines, x+1, y, east); 
        if(ret) {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'I';//right
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'I';//right
        }
        else {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'O';
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'O';
        }
        return ret;
      }
      if(moving == west) {
        ++rightTurn;
        bool ret = setInOut(lines, x, y-1, north); 
        if(ret) {
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'O';
          (y+1 < 0) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'O';
        }
        else {
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'I';
          (y+1 < 0) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'I';
        }
        return ret;
      }
      break;
    case 'J':
      if(moving == south) {
        ++rightTurn;
        bool ret = setInOut(lines, x-1, y, west); 
        if(ret) {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'O';
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'O';
        }
        else {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'I';
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'I';
        }
        return ret;
      }
      if(moving == east) {
        ++leftTurn;
        bool ret = setInOut(lines, x, y-1, north); 
        if(ret) {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'I';
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'I';
        }
        else {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'O';
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'O';
        }
        return ret;
      }
      break;
    case '7':
      if(moving == east) {
        ++rightTurn;
        bool ret = setInOut(lines, x, y+1, south);
        if(ret) {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'O';
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'O';
        }
        else {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'I';
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'I';
        }
        return ret;
      }
      if(moving == north) {
        ++leftTurn;
        bool ret = setInOut(lines, x-1, y, west); 
        if(ret) {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'I';
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'I';
        }
        else {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'O';
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'O';
        }
        return ret;
      }
      break;
    case 'F':
      if(moving == west) {
        ++leftTurn;
        bool ret = setInOut(lines, x, y+1, south); 
        if(ret) {
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'I';
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'I';
        }
        else {
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'O';
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'O';
        }
        return ret;
      }
      if(moving == north) {
        ++rightTurn;
        bool ret = setInOut(lines, x+1, y, east); 
        if(ret) {
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'O';
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'O';
        }
        else {
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'I';
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'I';
        }
        return ret;
      }
      break;
    case 'S':
      if(moving != center) {
        return leftTurn < rightTurn;
      }
      bool ret = false;
      if(y-1 >= 0 && (lines[y-1][x] == '|' || lines[y-1][x] == 'F' || lines[y-1][x] == '7')) {
        ret = setInOut(lines, x, y-1, north);
        if(ret) {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'I';//right
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'O';//left
        }
        else {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'O';
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'I';
        }
        return ret;
      }
      else if (x+1 < lines[0].length() && (lines[y][x+1] == '-' || lines[y][x+1] == 'J' || lines[y][x+1] == '7')) {
        ret = setInOut(lines, x+1, y, east); 
        if(ret) {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'I';//right
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'O';//left
        }
        else {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'O';
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'I';
        }
      }
      else if (y+1 < lines.size() && (lines[y+1][x] == '|' || lines[y+1][x] == 'J' || lines[y+1][x] == 'L')) {
        ret = setInOut(lines, x, y+1, south); 
        if(ret) {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'O';//left
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'I';//right
        }
        else {
          (x+1 >= lines[0].length()) || lines[y][x+1] != '.' ? 0 : lines[y][x+1] = 'I';
          (x-1 < 0) || lines[y][x-1] != '.' ? 0 : lines[y][x-1] = 'O';
        }
      }
      else if (x-1 >= 0 && (lines[y][x-1] == '-' || lines[y][x-1] == 'L' || lines[y][x-1] == 'F')) {
        ret = setInOut(lines, x-1, y, west); 
        if(ret) {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'O';//left
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'I';//right
        }
        else {
          (y+1 >= lines.size()) || lines[y+1][x] != '.' ? 0 : lines[y+1][x] = 'I';
          (y-1 < 0) || lines[y-1][x] != '.' ? 0 : lines[y-1][x] = 'O';
        }
      }
      return ret;
      break;
  }
  return 0;//just to remove warning, function should never reach here
}

void fill(std::vector<std::string> &lines, int x, int y) {
  int i = x;
  for(; i <= lines[0].size(); ++i) {
    if(lines[y][i] != '.') break;
  }
  lines[y][x] = lines[y][i];
}

int main(void)
{
  std::ifstream in;
  in.open("task.txt");
  std::vector<std::string> lines;
  std::string line;
  int startXpos = -1, startYpos = -1;
  int yCnt = -1;
  while(!in.eof()) {
    ++yCnt;
    getline(in, line);
    if(startXpos == -1) {
      for(int i = 0; i < line.length(); ++i) {
        if(line[i] == 'S') {
          startXpos = i;
          startYpos = yCnt;
          break;
        }
      }
    }
    lines.push_back(line);
  }
  lines.pop_back();

  std::vector<std::vector<int>> distances(lines.size(), std::vector<int>(lines[0].size(), -1));


  if(startYpos-1 >= 0 && (lines[startYpos-1][startXpos] == '|' || 
    lines[startYpos-1][startXpos] == 'F' || 
    lines[startYpos-1][startXpos] == '7'))
    traverse(lines, distances, startXpos, startYpos-1);
  if(startYpos+1 < lines.size() && (lines[startYpos+1][startXpos] == '|' || 
    lines[startYpos+1][startXpos] == 'L' || 
    lines[startYpos+1][startXpos] == 'J'))
    traverse(lines, distances, startXpos, startYpos+1);
  if(startXpos-1 >= 0 && (lines[startYpos][startXpos-1] == '-' || 
    lines[startYpos][startXpos-1] == 'F' || 
    lines[startYpos][startXpos-1] == 'L'))
    traverse(lines, distances, startXpos-1, startYpos);
  if(startXpos+1 < lines[0].size() && (lines[startYpos][startXpos+1] == '-' || 
    lines[startYpos][startXpos+1] == '7' || 
    lines[startYpos][startXpos+1] == 'J'))
    traverse(lines, distances, startXpos+1, startYpos);

  int m = -1;
  distances[startYpos][startXpos] = 0;
  for(int i = 0; i < distances.size(); ++i) {
    for(int j = 0; j < distances[0].size(); ++j)
      if(distances[i][j] > m) m = distances[i][j];
  }

  for(int i = 0; i < distances.size(); ++i) {
    for(int j = 0; j < distances[0].size(); ++j) {
      if(distances[i][j] == -1) lines[i][j] = '.';
      // std::cout <<  std::setw(3) << distances[i][j] << ' ';
    }
    // std::cout << '\n';
  }
  std::cout << std::endl;
  setInOut(lines, startXpos, startYpos, center);
  for(int i = 0; i < lines.size(); ++i) {
    for(int j = 0; j < lines[0].size(); ++j) {
      if(lines[i][j] == '.') {
        fill(lines, j, i);
      }
    }
  }
  for(int i = 0; i < lines.size(); ++i) {
    for(int j = 0; j < lines[0].size(); ++j) {
      std::cout << std::setw(0) << lines[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::endl;

  std::cout << "First part result " << m << std::endl;
  int res2 = 0;
  for(int i = 0; i < lines.size(); ++i) {
    for(int j = 0; j < lines[0].size(); ++j) {
      if(lines[i][j] == 'I') {
        ++res2;
      }
    }
  }
  std::cout << "Second part result " << res2 << std::endl;
  return 0;
}

