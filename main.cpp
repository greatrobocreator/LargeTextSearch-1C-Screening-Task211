#include <iostream>
#include <fstream>
#include <sstream>
#include "Automaton/SuffixAutomaton.h"

int main() {

  std::ifstream input_file("../Texts/book-war-and-peace.txt");
  //std::ifstream input_file("../Texts/Human_genome.fa");

  SuffixAutomaton
      suffix_automaton(input_file, std::make_shared<FileNodesManager>());

  std::cout << "Automaton ready!" << std::endl;

  /*std::string pattern =
      "CCCAAAACAGACAGGTCTTACGTTAACCTTCACCTTAAAAAGGATATTGCCTTTTTTCCTTCTGCTTCAC";*/
  std::string pattern = "sex";
  std::cout << suffix_automaton.FindFirstOccurrence(pattern) << std::endl;

  //std::cout << buffer.str().substr(274780 - 10, 20) << std::endl;

  return 0;
}
