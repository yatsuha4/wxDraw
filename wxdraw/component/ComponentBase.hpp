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
  std::weak_ptr<Node> node_;

 public:
  ComponentBase(const std::string& name, const NodePtr& node);
  ComponentBase(const ComponentBase& src, const NodePtr& node);
  virtual ~ComponentBase() = default;

  NodePtr getNode();

  void beginUpdate();
  void update();
  void endUpdate();

  void beginRender(Renderer& renderer);
  void render(Renderer& renderer);
  void endRender(Renderer& renderer);

  virtual ComponentBasePtr clone(const NodePtr& node) const = 0;

 protected:
  virtual void onBeginUpdate() {}
  virtual void onUpdate() {}
  virtual void onEndUpdate() {}

  virtual void onBeginRender(Renderer& renderer) {}
  virtual void onRender(Renderer& renderer) {}
  virtual void onEndRender(Renderer& renderer) {}
};
}
