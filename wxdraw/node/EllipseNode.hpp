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
  static const char* TYPE;

 public:
  EllipseNode();
  EllipseNode(const EllipseNode& src);
  ~EllipseNode() override = default;

 protected:
  NodePtr clone() const override;
};
}
