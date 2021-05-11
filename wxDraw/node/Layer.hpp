#pragma once

#include "wxDraw/node/Node.hpp"

namespace wxdraw::node {
/**
   レイヤー
*/
class Layer
  : public Node
{
  using super = Node;

 private:
  wxDouble opacity_ = 1.0;

 public:
  Layer() = default;
  ~Layer() override = default;

  WXDRAW_ACCESSOR(Opacity, opacity_);

 protected:
  void draw(wxGraphicsContext& gc) override;
};
}
