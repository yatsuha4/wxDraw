#pragma once

namespace wxdraw::node {
/**
   コンポーネント基底クラス
*/
class Component {
 public:
  virtual ~Component() = default;

  virtual void onUpdate(Node& node) {}
  virtual void onRender(Node& node, Renderer& renderer) {}

 protected:
  Component() = default;
};
}
