#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

int getNumAndMoveCnt(const std::string &str, int &cnt) {
  int res = 0;
  while(cnt < str.length() && str[cnt] >= '0' && str[cnt] <= '9') {
    res *= 10;
    res += str[cnt] - '0';
    ++cnt;
  }
  return res;
}

int getCardValue(const char c) {
  if(c >= '0' && c <= '9') return c - '0';
  else {
    switch (c) {
      case 'A':
        return 15;
        break;
      case 'K':
        return 14;
        break;
      case 'Q':
        return 13;
        break;
      case 'J':
        return 1; //12 for first part
        break;
      case 'T':
        return 11;
        break;
    }
  }
  return 0;
}

int evalHand(const std::string &hand) {
  // std::cout << "Evaluating " << hand << std::endl;
  std::map<char, int> cardCnt;
  for(int i = 0; i < hand.length(); ++i) {
    ++cardCnt[hand[i]];
  }
  auto itJ = cardCnt.find('J');
  if(itJ != cardCnt.end()) {
    int m = -1;
    char cM = '0';
    for(auto f = cardCnt.begin(); f != cardCnt.end(); ++f) {
      if(f->first != 'J' && f->second > m) {
        m = f->second;
        cM = f->first;
      }
    }
    // std::cout << "Max card " << cM << std::endl;
    cardCnt[cM] += itJ->second;
    cardCnt.erase(itJ);
  }
  // for(auto it = cardCnt.begin(); it != cardCnt.end(); ++it) {
  //   std::cout << "card " << it->first << ", cnt " << it->second << std::endl;
  // }
  switch (cardCnt.size()) {
    case 1:
      return 6;
    case 2:
      for(auto it = cardCnt.begin(); it != cardCnt.end(); ++it) {
        if(it->second == 4) return 5;
      }
      return 4;
    case 3:
      for(auto it = cardCnt.begin(); it != cardCnt.end(); ++it) {
        if(it->second == 3) return 3;
      }
      return 2;
    case 4:
      return 1;
    case 5:
      return 0;
  }
  return 0;
}

struct HandBid {
  std::string hand;
  int bid;
  int value;
  HandBid(std::string str) {
    hand = str.substr(0, 5);
    int i = 6;
    bid = getNumAndMoveCnt(str, i);
    value = evalHand(hand);
  }
};

bool cardCompare(const HandBid &x, const HandBid &y) {
  std::string l = x.hand;
  std::string r = y.hand;
  for(int i = 0; i < l.size(); ++i) {
    int a = getCardValue(l[i]);
    int b = getCardValue(r[i]);
    if(a < b) return false;
    else if(a > b) return true;
  }
  return false;
}

int main(void)
{
  std::ifstream in;
  in.open("task.txt");
  std::vector<HandBid> hands;
  std::string line;
  while(!in.eof()) {
    getline(in, line);
    hands.push_back(HandBid(line));
  }

  hands.pop_back();
  // for(int i = 0; i < hands.size(); ++i) {
  //   std::cout << "Hand: " << i+1
  //             << ", cards: " << hands[i].hand
  //             << ", bid: " << hands[i].bid
  //             << ", hand val: " << hands[i].value << '\n';
  // }
  // std::cout << std::endl;

  std::sort(hands.begin(), hands.end(), cardCompare);

  // for(int i = 0; i < hands.size(); ++i) {
  //   std::cout << "Hand: " << i+1
  //             << ", cards: " << hands[i].hand
  //             << ", bid: " << hands[i].bid
  //             << ", hand val: " << hands[i].value << '\n';
  // }
  // std::cout << std::endl;

  std::stable_sort(hands.begin(), hands.end(), [](HandBid l, HandBid r){return l.value > r.value;});

  // for(int i = 0; i < hands.size(); ++i) {
  //   std::cout << "Hand: " << i+1
  //             << ", cards: " << hands[i].hand
  //             << ", bid: " << hands[i].bid
  //             << ", hand val: " << hands[i].value << '\n';
  // }

  int res = 0;
  for(int i = 0; i < hands.size(); ++i) {
    res += (hands.size() - i) * hands[i].bid;
  }
  std::cout << "Result " << res << std::endl;
  return 0;
}
