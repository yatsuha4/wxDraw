#pragma once

#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
/**
   コンポーネント基底クラス
*/
class ComponentBase
  : public Property
{
  using super = Property;

 private:
  Node& node_;

 public:
  ComponentBase(const std::string& name, Node& node);
  ComponentBase(const ComponentBase& src, Node& node);
  virtual ~ComponentBase() = default;

  Node& getNode() const {
    return node_;
  }

  void beginUpdate();
  void update();
  void endUpdate();

  void beginRender(Renderer& renderer);
  void render(Renderer& renderer);
  void endRender(Renderer& renderer);

  virtual ComponentBasePtr clone(Node& node) const = 0;

 protected:
  virtual void onBeginUpdate() {}
  virtual void onUpdate() {}
  virtual void onEndUpdate() {}

  virtual void onBeginRender(Renderer& renderer) {}
  virtual void onRender(Renderer& renderer) {}
  virtual void onEndRender(Renderer& renderer) {}
};
}
