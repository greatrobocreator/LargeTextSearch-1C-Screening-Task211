#pragma once

#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>
#include <map>
#include <memory>

#include "../NodesManager.h"

class SuffixAutomaton {
 public:
  SuffixAutomaton(const std::string &s,
                  std::shared_ptr<NodesManager> nodes_manager =
                  std::make_shared<RAMNodesManager>());
  SuffixAutomaton(std::ifstream &input_file,
                  std::shared_ptr<NodesManager> nodes_manager =
                  std::make_shared<RAMNodesManager>());

  SuffixAutomaton &operator+=(char c);
  SuffixAutomaton &operator+=(const std::string &s);
  SuffixAutomaton &operator+=(std::ifstream &file);

  int FindFirstOccurrence(const std::string &pattern) const;

  ~SuffixAutomaton() = default;

 private:

  std::size_t last_;

  std::shared_ptr<NodesManager> nodes_manager_;
};
