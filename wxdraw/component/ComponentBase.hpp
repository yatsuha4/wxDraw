#pragma once

#include "wxdraw/property/PropertyOwner.hpp"

namespace wxdraw::component {
/**
   コンポーネント基底クラス
*/
class ComponentBase
  : public PropertyOwner
{
  using super = PropertyOwner;

 public:
  enum Priority {
    LAYOUT, 
    DEFAULT, 
    CONTAINER
  };

 private:
  std::string name_;
  std::weak_ptr<Node> node_;
  Priority priority_;

 public:
  ComponentBase(const std::string& name, 
                const NodePtr& node, 
                Priority priority);
  ComponentBase(const ComponentBase& src, 
                const NodePtr& node);
  virtual ~ComponentBase();

  WXDRAW_GETTER(Name, name_);
  NodePtr getNode();
  WXDRAW_GETTER(Priority, priority_);

  virtual void onCreate() {}
  virtual PropertyPtr createProperty();

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
