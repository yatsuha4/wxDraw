#pragma once

#include "wxdraw/object/Object.hpp"

namespace wxdraw::component {
/**
   コンポーネント基底クラス
*/
class ComponentBase
  : public Object
{
  using super = Object;

 public:
  enum Priority {
    LAYOUT, 
    DEFAULT, 
    CONTAINER
  };

 private:
  std::weak_ptr<Node> node_;
  Priority priority_;

 public:
  ComponentBase(const char* type, 
                const NodePtr& node, 
                Priority priority = Priority::DEFAULT);
  ComponentBase(const ComponentBase& src, 
                const NodePtr& node);
  virtual ~ComponentBase();

  NodePtr getNode();
  WXDRAW_GETTER(Priority, priority_);

  void beginUpdate();
  void update();
  void endUpdate();

  virtual void beginRender(Renderer& renderer, const LayoutComponentPtr& layout) {}
  virtual void render(Renderer& renderer, const LayoutComponentPtr& layout) {}
  virtual void endRender(Renderer& renderer, const LayoutComponentPtr& layout) {}

  virtual ComponentBasePtr clone(const NodePtr& node) const = 0;

 protected:
  virtual void onBeginUpdate() {}
  virtual void onUpdate() {}
  virtual void onEndUpdate() {}
};
}
