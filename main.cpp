#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <chrono>
#include "Automaton/SuffixAutomaton.h"

using std::chrono::duration;
using std::chrono::duration_cast;

int main() {
  std::ifstream input_file("../Texts/WarAndPeace.txt");
  //std::ifstream input_file("../Texts/Human_genome.fa");

  auto begin = std::chrono::high_resolution_clock::now();
  SuffixAutomaton suffix_automaton(input_file);
  auto end = std::chrono::high_resolution_clock::now();

  input_file.close();

  std::cout.precision(4);
  std::cout << "Reading file and building suffix automaton done in "
            << std::fixed
            << duration_cast<std::chrono::seconds>(end - begin).count()
            << std::setprecision(5)
            << " seconds" << std::endl;

  std::string pattern;

  while (std::getline(std::cin, pattern)) {
    begin = std::chrono::high_resolution_clock::now();

    auto first_occurrence =
        suffix_automaton.FindFirstOccurrence(pattern);

    for (size_t i = 0; i < 999; ++i) {
      first_occurrence =
          suffix_automaton.FindFirstOccurrence(pattern);
    }

    end = std::chrono::high_resolution_clock::now();

    if (first_occurrence != -1) {
      std::cout << "Found occurrence at " << first_occurrence
                << " in "
                << duration_cast<std::chrono::nanoseconds>(end - begin).count()
                    / 1000
                << " nanoseconds" << std::endl;
    } else {
      std::cout << "There is no patter in text. Done in "
                << duration_cast<std::chrono::nanoseconds>(end - begin).count()
                    / 1000
                << " nanoseconds" << std::endl;
    }
  }

  return 0;
}