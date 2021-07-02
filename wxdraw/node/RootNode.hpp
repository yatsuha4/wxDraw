#pragma once

#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
/**
   ルートノード
*/
class RootNode
  : public Node
{
  using super = Node;

 public:
  RootNode();
  ~RootNode() override = default;
};
}
