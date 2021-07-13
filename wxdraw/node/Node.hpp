#pragma once

#include "wxdraw/property/Property.hpp"

namespace wxdraw::node {
/**
   ノード基底クラス
*/
class Node
  : public Property
{
  using super = Property;

 private:
  std::weak_ptr<Node> parent_;
  std::vector<NodePtr> children_;
  std::vector<ComponentBasePtr> components_;
  std::string label_;
  bool show_;
  bool container_;
  wxTreeListItem item_;

 public:
  Node(const Node& src);
  virtual ~Node() = default;

  WXDRAW_ACCESSOR(Label, label_);
  WXDRAW_ACCESSOR(Container, container_);
  WXDRAW_GETTER(Children, children_);
  WXDRAW_GETTER(Components, components_);

  NodePtr getParent() const;
  static void Append(const NodePtr& node, const NodePtr& parent);
  static void Insert(const NodePtr& node, const NodePtr& parent, size_t index);
  static void Remove(const NodePtr& node);

  /**
     コンポーネントを追加する
     @return 追加したコンポーネント
  */
  template<class T>
  std::shared_ptr<T> appendComponent() {
    auto component = std::make_shared<T>(*this);
    appendComponent(component);
    return component;
  }

  virtual void update();
  virtual void render(Renderer& renderer);

  WXDRAW_ACCESSOR(Item, item_);

  template<class T>
  static std::shared_ptr<T> GetParent(NodePtr node) {
    while(node) {
      if(auto t = std::dynamic_pointer_cast<T>(node)) {
        return t;
      }
      node = node->getParent();
    }
    return nullptr;
  }

  template<class T>
  bool canAppend() const {
    return canAppend(typeid(T));
  }

  virtual bool canAppend(const std::type_info& type) const;

  template<class T>
  std::shared_ptr<T> getComponent() const {
    for(auto& iter : components_) {
      if(auto component = std::dynamic_pointer_cast<T>(iter)) {
        return component;
      }
    }
    return nullptr;
  }

  static NodePtr Clone(const NodePtr& src);

 protected:
  Node(const std::string& name);

  virtual void onUpdate() {}
  virtual void onBeginRender(Renderer& renderer) {}
  virtual void onEndRender(Renderer& renderer) {}

  virtual NodePtr clone() const;

 private:
  void setup();

  void appendComponent(const ComponentBasePtr& component);
  void removeComponent(const ComponentBasePtr& component);
};
}
