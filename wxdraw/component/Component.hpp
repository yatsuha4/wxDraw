#pragma once

#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
/**
   コンポーネント基底クラス
*/
class Component
  : public Property
{
  using super = Property;

 private:
  Node& node_;

 public:
  virtual ~Component() = default;

  Node& getNode() const {
    return node_;
  }

  void beginUpdate();
  void update();
  void endUpdate();

  void beginRender(Renderer& renderer);
  void render(Renderer& renderer);
  void endRender(Renderer& renderer);

 protected:
  Component(const std::string& name, Node& node);

  virtual void onBeginUpdate() {}
  virtual void onUpdate() {}
  virtual void onEndUpdate() {}

  virtual void onBeginRender(Renderer& renderer) {}
  virtual void onRender(Renderer& renderer) {}
  virtual void onEndRender(Renderer& renderer) {}
};
}
