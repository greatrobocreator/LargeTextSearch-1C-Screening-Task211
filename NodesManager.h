#pragma once

#include <string>
#include <vector>
#include <map>
#include <fstream>

class NodesManager {

 protected:
  class Node;

 public:

  virtual std::size_t AddNode(std::size_t len = 0, int link = -1) = 0;
  virtual std::size_t AddNode(const Node &node) = 0;
  virtual const Node &GetNode(std::size_t index) const = 0;
  virtual std::size_t CopyNode(std::size_t index) = 0;

  virtual std::size_t GetLen(std::size_t index) const = 0;
  virtual void SetLen(std::size_t index, std::size_t len) = 0;

  virtual int GetLink(std::size_t index) const = 0;
  virtual void SetLink(std::size_t index, int link) = 0;

  virtual std::size_t GetEdge(std::size_t index, char c) const = 0;
  virtual void SetEdge(std::size_t index, char c, std::size_t to) = 0;
  virtual bool HasEdge(std::size_t index, char c) const = 0;

  virtual ~NodesManager() {};
 protected:

  struct Node {
    Node(std::size_t len = 0, int link = -1, std::size_t first_occurrence = -1)
        : len_(len), link_(link), first_occurrence_(first_occurrence) {};

    Node(const Node &node) = default;

    void SetEdge(char c, std::size_t to) { edges_[c] = to; }

    bool HasEdge(char c) const { return edges_.count(c) > 0; }
    std::size_t GetEdge(char c) const { return edges_.at(c); }

    virtual ~Node() {};

    std::map<char, std::size_t> edges_;
    size_t len_;
    int link_;
    std::size_t first_occurrence_;
  };

};

class RAMNodesManager : public NodesManager {
 public:
  RAMNodesManager() = default;

  std::size_t AddNode(std::size_t len, int link) override;
  std::size_t AddNode(const Node &node) override;
  const Node &GetNode(std::size_t index) const override;
  std::size_t CopyNode(std::size_t index) override;

  std::size_t GetLen(std::size_t index) const override;
  void SetLen(std::size_t index, std::size_t len) override;

  int GetLink(std::size_t index) const override;
  void SetLink(std::size_t index, int link) override;

  std::size_t GetEdge(std::size_t index, char c) const override;
  void SetEdge(std::size_t index, char c, std::size_t to) override;
  bool HasEdge(std::size_t index, char c) const override;

 private:
  std::vector<Node> nodes_;
};

class FileNodesManager : public NodesManager {
 public:
  FileNodesManager();

  std::size_t AddNode(std::size_t len, int link) override;
  std::size_t AddNode(const Node &node) override;
  const Node &GetNode(std::size_t index) const override;
  std::size_t CopyNode(std::size_t index) override;

  std::size_t GetLen(std::size_t index) const override;
  void SetLen(std::size_t index, std::size_t len) override;

  int GetLink(std::size_t index) const override;
  void SetLink(std::size_t index, int link) override;

  std::size_t GetEdge(std::size_t index, char c) const override;
  void SetEdge(std::size_t index, char c, std::size_t to) override;
  bool HasEdge(std::size_t index, char c) const override;

 private:

  void WriteNode(const Node &node);

  std::fstream nodes_file_;

  static const std::size_t alphabet_size = 40;
};
