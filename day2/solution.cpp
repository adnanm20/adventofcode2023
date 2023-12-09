#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Set {
  int redCount = 0,
      blueCount = 0,
      greenCount = 0;
};

int getNumAndMoveCnt(const std::string &str, int &cnt) {
  int res = 0;
  while(cnt < str.length() && str[cnt] >= '0' && str[cnt] <= '9') {
    res *= 10;
    res += str[cnt] - '0';
    ++cnt;
  }
  return res;
}

std::string getColorAndMoveCnt(const std::string &str, int &cnt) {
  std::string res = "";
  while(cnt < str.length() && str[cnt] >= 'a' && str[cnt] <= 'z') {
    res += str[cnt];
    ++cnt;
  }
  --cnt;
  return res;
}

struct Game {
  int id = 0;
  std::vector<Set> sets;
  Game(std::string strgame) {
    int startSets = 0;
    for(int i = 5; i < strgame.length(); ++i) {
      if(strgame[i] == ':') {
        startSets = i;
        break;
      }
      if(strgame[i] >= '0' && strgame[i] <= '9') {
        id *= 10;
        id += strgame[i] - '0';
      }
    }
    Set currSet;
    int num = 0;
    std::string clr;
    for(int setCnt = startSets+2; setCnt < strgame.length(); ++setCnt) {
      if(strgame[setCnt] >= '0' && strgame[setCnt] <= '9') {
        num = getNumAndMoveCnt(strgame, setCnt);
      } else if (strgame[setCnt] == ' ') {}
      else if (strgame[setCnt] == ',') {}
      else if (strgame[setCnt] == ';') {
        sets.push_back(currSet);
        currSet.blueCount = 0;
        currSet.redCount = 0;
        currSet.greenCount = 0;
      }
      else {
        clr = getColorAndMoveCnt(strgame, setCnt);
        if(clr == "red") currSet.redCount = num;
        else if(clr == "green") currSet.greenCount = num;
        else if(clr == "blue") currSet.blueCount = num;
        if(setCnt == strgame.length() - 1)
          sets.push_back(currSet);
      }
    }
 }
};

std::vector<Game> getImpossible(std::vector<Game> &games) {
  std::vector<Game> res;
  bool flag = false;
  for(int i = 0; i < games.size(); ++i) {
    flag = true;
    for(int j = 0; j < games[i].sets.size(); ++j) {
      if(games[i].sets[j].redCount > 12
        || games[i].sets[j].greenCount > 13
        || games[i].sets[j].blueCount > 14) {
        flag = false;
        break;
      }
    }
    if(flag) {
      res.push_back(games[i]);
    }
  }
  return res;
}

Set getMinPossible(Game &game) {
  Set res;
  for(int i = 0; i < game.sets.size(); ++i) {
    if(res.redCount < game.sets[i].redCount)
      res.redCount = game.sets[i].redCount;
    if(res.greenCount < game.sets[i].greenCount)
      res.greenCount = game.sets[i].greenCount;
    if(res.blueCount < game.sets[i].blueCount)
      res.blueCount = game.sets[i].blueCount;
  }
  return res;
}

int main(void)
{
  std::ifstream in;
  in.open("task.txt");
  std::vector<Game> games;
  std::string game;
  while(!in.eof()) {
    getline(in, game);
    games.push_back(Game(game));
  }

  // for(int i = 0; i < games.size(); ++i) {
  //   std::cout << "gID " << games[i].id << ": ";
  //   for(int j  = 0; j < games[i].sets.size(); ++j) {
  //     std::cout << " R: " << games[i].sets[j].redCount
  //               << " G: " << games[i].sets[j].greenCount
  //               << " B: " << games[i].sets[j].blueCount << ';';
  //   }
  //   std::cout << '\n';
  // }
 
  std::vector<Game> possible = getImpossible(games);
  // for(int i = 0; i < possible.size(); ++i) {
  //   std::cout << "gID " << possible[i].id << ": ";
  //   for(int j  = 0; j < possible[i].sets.size(); ++j) {
  //     std::cout << " R: " << possible[i].sets[j].redCount
  //               << " G: " << possible[i].sets[j].greenCount
  //               << " B: " << possible[i].sets[j].blueCount << ';';
  //   }
  //   std::cout << '\n';
  // }
 
  int sum = 0;
  for(int i = 0; i < possible.size(); ++i) {
    sum += possible[i].id;
  }
  std::cout << "Sum: " << sum << std::endl;

  int powerSum = 0;
  for(int i = 0; i < games.size(); ++i) {
    Set x = getMinPossible(games[i]);
    powerSum += x.redCount * x.greenCount * x.blueCount;
  }
  std::cout << "powerSum: " << powerSum << std::endl;
  return 0;
}

