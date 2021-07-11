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
  RectangleNode();
  ~RectangleNode() override = default;
};
}
