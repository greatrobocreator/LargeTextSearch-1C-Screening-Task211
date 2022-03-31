#include <fstream>
#include <utility>
#include "SuffixAutomaton.h"

SuffixAutomaton::SuffixAutomaton(const std::string &s,
                                 std::shared_ptr<NodesManager> nodes_manager) :
    nodes_manager_(std::move(nodes_manager)) {

  nodes_manager_->AddNode(0, -1);
  last_ = 0;
  *this += s;
}

SuffixAutomaton::SuffixAutomaton(std::ifstream &input_file,
                                 std::shared_ptr<NodesManager> nodes_manager) :
    nodes_manager_(std::move(nodes_manager)) {

  nodes_manager_->AddNode(0, -1);
  last_ = 0;
  *this += input_file;
}

SuffixAutomaton &SuffixAutomaton::operator+=(const std::string &s) {
  for (const auto &c : s) {
    *this += c;
  }
  return *this;
}

SuffixAutomaton &SuffixAutomaton::operator+=(std::ifstream &input_file) {
  char c;
  while (input_file.get(c)) {
    *this += c;
  }
  return *this;
}

SuffixAutomaton &SuffixAutomaton::operator+=(char new_char) {

  std::size_t new_node_index =
      nodes_manager_->AddNode(nodes_manager_->GetLen(last_) + 1, -1);

  int p = last_;
  for (; p != -1 && !nodes_manager_->HasEdge(p, new_char);
         p = nodes_manager_->GetLink(p)) {
    nodes_manager_->SetEdge(p, new_char, new_node_index);
  }

  if (p == -1) {
    nodes_manager_->SetLink(new_node_index, 0);
  } else {
    std::size_t q = nodes_manager_->GetEdge(p, new_char);

    if (nodes_manager_->GetLen(q) == nodes_manager_->GetLen(p) + 1) {
      nodes_manager_->SetLink(new_node_index, q);
    } else {
      auto clone_index = nodes_manager_->CopyNode(q);

      nodes_manager_->SetLink(q, clone_index);
      nodes_manager_->SetLink(new_node_index, clone_index);
      nodes_manager_->SetLen(clone_index, nodes_manager_->GetLen(p) + 1);

      for (; p != -1 && nodes_manager_->GetEdge(p, new_char) == q;
             p = nodes_manager_->GetLink(p)) {
        nodes_manager_->SetEdge(p, new_char, clone_index);
      }
    }
  }

  last_ = new_node_index;

  return *this;
}

int SuffixAutomaton::FindFirstOccurrence(const std::string &pattern) const {
  std::size_t v = 0;
  for (const auto &c: pattern) {
    if (!nodes_manager_->HasEdge(v, c)) {
      return -1;
    }
    v = nodes_manager_->GetEdge(v, c);
  }
  return nodes_manager_->GetNode(v).first_occurrence_ + 1 - pattern.size();
}
