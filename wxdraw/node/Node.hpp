#pragma once

#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::node {
/**
   ノード基底クラス
*/
class Node
  : public Property
{
  using super = Property;

 public:
  static const char* TYPE;

 private:
  std::weak_ptr<Node> parent_;
  std::vector<NodePtr> children_;
  std::vector<ComponentBasePtr> components_;
  std::string label_;
  bool show_;
  bool container_;
  wxTreeListItem item_;

 public:
  Node();
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

  virtual void update();
  virtual void render(Renderer& renderer);

  WXDRAW_ACCESSOR(Item, item_);

  template<class T>
  bool canAppend() const {
    return canAppend(typeid(T));
  }

  virtual bool canAppend(const std::type_info& type) const;

  static NodePtr Clone(const NodePtr& src);

  /**
     ノードを生成する
  */
  template<class... ComponentTypes>
  static NodePtr Create() {
    auto node = std::make_shared<Node>();
    AppendComponent<LayoutComponent, ComponentTypes...>(node);
    return node;
  }

  /**
     コンポーネントを取得する
     @return コンポーネント(もしくはnullptr)
  */
  template<class T>
  std::shared_ptr<T> getComponent() const {
    for(auto& iter : components_) {
      if(auto component = std::dynamic_pointer_cast<T>(iter)) {
        return component;
      }
    }
    return nullptr;
  }

  /**
     親ノードのコンポーネントを取得する
     @return コンポーネント(もしくはnullptr)
  */
  template<class T>
  std::shared_ptr<T> getParentComponent() const {
    if(auto component = getComponent<T>()) {
      return component;
    }
    if(auto parent = getParent()) {
      return parent->getParentComponent<T>();
    }
    return nullptr;
  }

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

  /**
     コンポーネントを追加する
  */
  template<class T>
  static void AppendComponent(const NodePtr& node) {
    node->appendComponent(std::make_shared<T>(node));
  }

  /**
     コンポーネントを追加する
  */
  template<class T1, class T2, class... Rest>
  static void AppendComponent(const NodePtr& node) {
    AppendComponent<T1>(node);
    AppendComponent<T2, Rest...>(node);
  }
};
}
