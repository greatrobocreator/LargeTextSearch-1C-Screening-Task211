#include "NodesManager.h"

/** RAM Nodes Manager **/

std::size_t RAMNodesManager::AddNode(std::size_t len, int link) {
  nodes_.emplace_back(len, link, len - 1);
  return nodes_.size() - 1;
}

std::size_t RAMNodesManager::AddNode(const Node &node) {
  nodes_.emplace_back(node);
  return nodes_.size() - 1;
}

const NodesManager::Node &RAMNodesManager::GetNode(std::size_t index) const {
  return nodes_[index];
}

std::size_t RAMNodesManager::CopyNode(std::size_t index) {
  return AddNode(GetNode(index));
}

std::size_t RAMNodesManager::GetLen(std::size_t index) const {
  return GetNode(index).len_;
}

void RAMNodesManager::SetLen(std::size_t index, std::size_t len) {
  nodes_[index].len_ = len;
}

int RAMNodesManager::GetLink(std::size_t index) const {
  return GetNode(index).link_;
}

void RAMNodesManager::SetLink(std::size_t index, int link) {
  nodes_[index].link_ = link;
}

std::size_t RAMNodesManager::GetEdge(std::size_t index, char c) const {
  return GetNode(index).GetEdge(c);
}

void RAMNodesManager::SetEdge(std::size_t index, char c, std::size_t to) {
  nodes_[index].SetEdge(c, to);
}

bool RAMNodesManager::HasEdge(std::size_t index, char c) const {
  return GetNode(index).HasEdge(c);
}

/** File Nodes Manager **/

FileNodesManager::FileNodesManager() : nodes_file_("tmp_nodes_file",
                                                   std::ios_base::binary) {}

std::size_t FileNodesManager::AddNode(std::size_t len, int link) {
  nodes_file_.seekg(0, std::ios_base::end);
  return 0;
}

void FileNodesManager::WriteNode(const Node &node) {
  nodes_file_ << node.len_ << node.link_ << node.first_occurrence_;
  std::size_t i = 0;
  for (const auto &x: node.edges_) {
    nodes_file_ << x.first << ":" << x.second;
    ++i;
  }
  for (; i < alphabet_size; ++i) {
    nodes_file_ << "a:0";
  }
}
const NodesManager::Node &FileNodesManager::GetNode(std::size_t index) const {
  return *(new Node());
}

std::size_t FileNodesManager::AddNode(const NodesManager::Node &node) {
  return 0;
}

std::size_t FileNodesManager::CopyNode(std::size_t index) {
  return 0;
}

std::size_t FileNodesManager::GetLen(std::size_t index) const {
  return 0;
}

void FileNodesManager::SetLen(std::size_t index, std::size_t len) {

}
int FileNodesManager::GetLink(std::size_t index) const {
  return 0;
}
void FileNodesManager::SetLink(std::size_t index, int link) {

}
std::size_t FileNodesManager::GetEdge(std::size_t index, char c) const {
  return 0;
}
void FileNodesManager::SetEdge(std::size_t index, char c, std::size_t to) {

}
bool FileNodesManager::HasEdge(std::size_t index, char c) const {
  return false;
};

