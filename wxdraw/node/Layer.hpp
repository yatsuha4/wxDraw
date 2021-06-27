#pragma once

#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
/**
   レイヤー
*/
class Layer
  : public Node
{
  using super = Node;

 private:
  double opacity_;

 public:
  Layer();
  ~Layer() override = default;

 protected:
  void render(Renderer& renderer) override;
};
}
