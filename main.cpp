#include <iostream>
#include <fstream>
#include <sstream>
#include "Automaton/SuffixAutomaton.h"

int main() {

  std::ifstream input_file("../Texts/book-war-and-peace.txt");

  std::stringstream buffer;
  buffer << input_file.rdbuf();

  /*SuffixAutomaton suffix_automaton(input_file);

  std::cout << suffix_automaton.FindFirstOccurrence("sex") << std::endl;*/

  std::cout << buffer.str().substr(274780 - 10, 20) << std::endl;

  return 0;
}
