#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <numeric>

typedef unsigned long long int ulli;

int main(void)
{
  std::ifstream in;
  in.open("task.txt");
  std::string line;
  std::string instructions;
  std::map<std::string, std::pair<std::string, std::string>> network;
  getline(in, instructions);
  getline(in, line);
  while(!in.eof()) {
    getline(in, line);
    if(line.length() > 0)
      network[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};
  }

  // for(auto it = network.begin(); it != network.end(); ++it) {
  //   std::cout << "Node " << it->first << ", l " << it->second.first << ", r " << it->second.second << std::endl;
  // }

  std::string currentNode = "AAA";
  int instructionCnt = 0;
  unsigned long long int stepCnt = 0;
  // while(currentNode != "ZZZ") {
  //   ++stepCnt;
  //   if(instructions[instructionCnt] == 'R') {
  //     currentNode = network[currentNode].second;
  //   } else {
  //     currentNode = network[currentNode].first;
  //   }
  //   ++instructionCnt;
  //   instructionCnt %= instructions.length();
  // }

  std::cout << "First part result " << stepCnt << std::endl;

  std::vector<std::string> currentNodes;
  std::vector<int> steps;
  for(auto it = network.begin(); it != network.end(); ++it) {
    if(it->first[2] == 'A')
      currentNodes.push_back(it->first);
  }
  std::cout << "Nodes ending with A " << currentNodes.size() << std::endl;
  stepCnt = 0;
  instructionCnt = 0;
  for(int i = 0; i < currentNodes.size(); ++i) {
    currentNode = currentNodes[i];
    stepCnt = 0;
    instructionCnt = 0;
    while(currentNode[2] != 'Z') {
      ++stepCnt;
      if(instructions[instructionCnt] == 'R') {
        currentNode = network[currentNode].second;
      } else {
        currentNode = network[currentNode].first;
      }
      ++instructionCnt;
      instructionCnt %= instructions.length();
    }
    std::cout << stepCnt << std::endl;
    steps.push_back(stepCnt);
  }

  stepCnt = steps[0];
  for(int i = 1; i < steps.size(); ++i) {
    stepCnt = std::lcm(stepCnt, steps[i]);
  }

  std::cout << "Second part result " << stepCnt << std::endl;

  return 0;
}

