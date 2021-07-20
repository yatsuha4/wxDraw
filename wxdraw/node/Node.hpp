#pragma once

#include "wxdraw/object/Object.hpp"

namespace wxdraw::node {
/**
   ノード
*/
class Node
  : public Object
{
  using super = Object;

 public:
  static const char* TYPE_ELLIPSE;
  static const char* TYPE_LAYER;
  static const char* TYPE_PROJECT;
  static const char* TYPE_RECTANGLE;
  static const char* TYPE_ROOT;
  static const char* TYPE_TEXT;

 private:
  std::weak_ptr<Node> parent_;
  std::vector<ComponentBasePtr> components_;
  wxString label_;
  bool show_;
  wxString comment_;
  wxTreeListItem item_;

 public:
  Node(const std::string& type);
  Node(const Node& src);
  ~Node();

  WXDRAW_ACCESSOR(Label, label_);

  WXDRAW_GETTER(Components, components_);
  ContainerComponentPtr getContainer() const;
  void appendComponent(const ComponentBasePtr& component);
  void removeComponent(const ComponentBasePtr& component);

  NodePtr getParent() const;
  static void Append(const NodePtr& node, const NodePtr& parent);
  static void Insert(const NodePtr& node, const NodePtr& parent, size_t index);
  static void Remove(const NodePtr& node);

  PropertyPtr createProperty() override;

  void update();
  void render(Renderer& renderer);

  WXDRAW_ACCESSOR(Item, item_);

  static NodePtr NewEllipse();
  static NodePtr NewLayer();
  static NodePtr NewProject();
  static NodePtr NewRectangle();
  static NodePtr NewRoot();
  static NodePtr NewText();

  static NodePtr Clone(const NodePtr& src);

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
  static std::shared_ptr<T> GetParentComponent(const NodePtr& node) {
    if(node) {
      if(auto component = node->getComponent<T>()) {
        return component;
      }
      return GetParentComponent<T>(node->getParent());
    }
    return nullptr;
  }

  /**
     コンポーネントを追加する
  */
  template<class T>
  static std::shared_ptr<T> AppendComponent(const NodePtr& node) {
    auto component = std::make_shared<T>(node);
    node->appendComponent(component);
    return component;
  }

  /**
     新規コンポーネントを追加する
  */
  template<class T>
  static std::shared_ptr<T> NewComponent(const NodePtr& node) {
    auto component = AppendComponent<T>(node);
    component->onNew();
    return component;
  }

 private:
  /**
     新規ノードを生成する
  */
  template<class... ComponentTypes>
  static NodePtr New(const char* type) {
    auto node = super::New<Node>(type);
    NewComponent<LayoutComponent, ComponentTypes...>(node);
    return node;
  }

  /**
     コンポーネントを追加する
  */
  template<class T1, class T2, class... Rest>
  static void NewComponent(const NodePtr& node) {
    NewComponent<T1>(node);
    NewComponent<T2, Rest...>(node);
  }
};
}
