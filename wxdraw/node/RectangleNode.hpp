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
  ~RectangleNode() override = default;
};
}
