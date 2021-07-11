#pragma once

#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
/**
   レイヤー
*/
class LayerNode
  : public Node
{
  using super = Node;

 public:
  LayerNode();
  ~LayerNode() override = default;
};
}
