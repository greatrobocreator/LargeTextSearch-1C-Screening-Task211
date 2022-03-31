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

NodesManager::Node RAMNodesManager::GetNode(std::size_t index) {
  return nodes_[index];
}

std::size_t RAMNodesManager::CopyNode(std::size_t index) {
  return AddNode(GetNode(index));
}

std::size_t RAMNodesManager::GetLen(std::size_t index) {
  return GetNode(index).len_;
}

void RAMNodesManager::SetLen(std::size_t index, std::size_t len) {
  nodes_[index].len_ = len;
}

int RAMNodesManager::GetLink(std::size_t index) {
  return GetNode(index).link_;
}

void RAMNodesManager::SetLink(std::size_t index, int link) {
  nodes_[index].link_ = link;
}

std::size_t RAMNodesManager::GetEdge(std::size_t index, char c) {
  return GetNode(index).GetEdge(c);
}

void RAMNodesManager::SetEdge(std::size_t index, char c, std::size_t to) {
  nodes_[index].SetEdge(c, to);
}

bool RAMNodesManager::HasEdge(std::size_t index, char c) {
  return GetNode(index).HasEdge(c);
}

/** File Nodes Manager **/

FileNodesManager::FileNodesManager() :

    size_(0) {
  std::string filename("tmp_nodes_file.tmp");
  nodes_file_.open(filename,
                   std::fstream::binary | std::fstream::in
                       | std::fstream::out);
  nodes_file_.flush();
}

std::size_t FileNodesManager::AddNode(std::size_t len, int link) {
  nodes_file_.seekp(0, std::ios_base::end);
  WriteNode(Node(len, link));
  return size_++;
}

void FileNodesManager::WriteNode(const Node &node) {
  nodes_file_ << node.len_ << node.link_ << node.first_occurrence_;
  std::size_t i = 0;
  for (const auto &x: node.edges_) {
    nodes_file_ << x.first << ":" << x.second;
    ++i;
  }
  for (; i < alphabet_size; ++i) {
    nodes_file_ << "a:" << static_cast<std::size_t>(-1);
  }
  nodes_file_.flush();
}

void FileNodesManager::WriteNodeToIndex(std::size_t index, const Node &node) {
  nodes_file_.seekp(index * node_size);
  WriteNode(Node(node));
}

NodesManager::Node FileNodesManager::ReadNode() {
  Node node;
  nodes_file_.read(reinterpret_cast<char *>(&node.len_), sizeof(node.len_));
  nodes_file_.read(reinterpret_cast<char *>(&node.link_), sizeof(node.link_));
  nodes_file_.read(reinterpret_cast<char *>(&node.first_occurrence_),
                   sizeof(node.first_occurrence_));

  for (std::size_t i = 0; i < alphabet_size; ++i) {
    char c1, c2;
    nodes_file_.get(c1);
    nodes_file_.get(c2);

    std::size_t to;
    nodes_file_.read(reinterpret_cast<char *>(&to), sizeof(to));

    if (c1 == 'a' && to == static_cast<std::size_t>(-1)) {
      break;
    }

    node.edges_[c1] = to;
  }
  return node;
}

NodesManager::Node FileNodesManager::GetNode(std::size_t index) {
  nodes_file_.seekg(index * node_size);
  return ReadNode();
}

std::size_t FileNodesManager::AddNode(const NodesManager::Node &node) {
  nodes_file_.seekp(0, std::ios_base::end);
  WriteNode(Node(node));
  return size_++;
}

std::size_t FileNodesManager::CopyNode(std::size_t index) {
  return AddNode(GetNode(index));
}

std::size_t FileNodesManager::GetLen(std::size_t index) {
  return GetNode(index).len_;
}

void FileNodesManager::SetLen(std::size_t index, std::size_t len) {
  Node node = GetNode(index);
  node.len_ = len;
  WriteNodeToIndex(index, Node(node));
}

int FileNodesManager::GetLink(std::size_t index) {
  return GetNode(index).link_;
}

void FileNodesManager::SetLink(std::size_t index, int link) {
  Node node = GetNode(index);
  node.link_ = link;
  WriteNodeToIndex(index, node);
}

std::size_t FileNodesManager::GetEdge(std::size_t index, char c) {
  return GetNode(index).GetEdge(c);
}

void FileNodesManager::SetEdge(std::size_t index, char c, std::size_t to) {
  Node node = GetNode(index);
  node.SetEdge(c, to);
  WriteNodeToIndex(index, node);
}

bool FileNodesManager::HasEdge(std::size_t index, char c) {
  return GetNode(index).HasEdge(c);
}
