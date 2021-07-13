#pragma once

#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
/**
 */
class RectangleNode
  : public Node
{
  using super = Node;

 public:
  static const char* TYPE;

 public:
  RectangleNode();
  RectangleNode(const RectangleNode& src);
  ~RectangleNode() override = default;

 protected:
  NodePtr clone() const override;

 private:
  void setup();
};
}
