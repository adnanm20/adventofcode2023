#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

int getNumAndMoveCnt(const std::string &str, int &cnt) {
  int res = 0;
  while(cnt < str.length() && str[cnt] >= '0' && str[cnt] <= '9') {
    res *= 10;
    res += str[cnt] - '0';
    ++cnt;
  }
  return res;
}

struct Card {
  std::vector<int> winning;
  std::vector<int> ours;
  int cnt = 1;
  Card(std::string str) {
    int cardStart = 0;
    for(int i = 0; i < str.length(); ++i) {
      if(str[i] == ':') {
        cardStart = i + 1;
        break;
      }
    }
    bool flag = false;
    for(int i = cardStart; i < str.length(); ++i) {
      if(str[i] == '|') {
        flag = true;
      } else if (str[i] == ' ') {}
      else {
        int n = getNumAndMoveCnt(str, i);
        if(!flag) {
          winning.push_back(n);
        } else {
          ours.push_back(n);
        }
      }
    }
  }
};

int countIntersecting(const std::vector<int> &first, const std::vector<int> &second) {
  int cnt = 0;
  for(int i = 0; i < first.size(); ++i) {
    for(int j = 0; j < second.size(); ++j) {
      if(first[i] == second[j]) {
        ++cnt;
        break;
      }
    }
  }
  return cnt;
}

int countCards(std::vector<Card> &cards) {
  int res = 0;
  int s = 0;
  for(int i = 0; i < cards.size(); ++i) {
    s = countIntersecting(cards[i].winning, cards[i].ours);
    for(int j = 1; j <= s; ++j) {
      cards[i+j].cnt += cards[i].cnt;
    }
    res += cards[i].cnt;
  }
  return res;
}

int main(void)
{  
  std::ifstream in;
  in.open("task.txt");
  std::vector<Card> cards;
  std::string card;
  while(!in.eof()) {
    getline(in, card);
    cards.push_back(Card(card));
  }

  cards.pop_back();
  // for(int i = 0; i < cards.size(); ++i) {
  //   std::cout << "Card num " << i+1 << "\n Winning: ";
  //   for(int j = 0; j < cards[i].winning.size(); ++j) {
  //     std::cout << cards[i].winning[j] << ' ';
  //   }
  //   std::cout << "\n Ours: ";
  //   for(int j = 0; j < cards[i].ours.size(); ++j) {
  //     std::cout << cards[i].ours[j] << ' ';
  //   }
  //   std::cout << std::endl;
  // }

  int sum = 0;
  for(int i = 0; i < cards.size(); ++i) {
    int s = countIntersecting(cards[i].winning, cards[i].ours);
    sum += pow(2, s-1);
  }
  std::cout << "First part sum " << sum << std::endl;
  
  sum = countCards(cards);
  std::cout << "Second part sum " << sum << std::endl;

  return 0;
}
