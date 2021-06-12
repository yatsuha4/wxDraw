#pragma once

namespace wxdraw::node {
/**
   円
*/
class Circle
  : public Node
{
  using super = Node;

 public:
  Circle();
  ~Circle() override = default;

 protected:
  void onRender(Renderer& renderer) override;
};
}
