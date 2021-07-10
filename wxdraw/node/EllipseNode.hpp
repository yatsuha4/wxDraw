#pragma once

#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
/**
 */
class EllipseNode
  : public Node
{
  using super = Node;

 public:
  EllipseNode();
  ~EllipseNode() override = default;
};
}
