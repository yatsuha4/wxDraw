﻿#pragma once

#include "wxdraw/object/Object.hpp"

#define WXDRAW_DECLARE_NODE(Type)                       \
  struct Type {                                         \
    constexpr static const char* TYPE = #Type;          \
    static NodePtr Create(const NodePtr& parent);       \
  }

namespace wxdraw::node {
/**
   ノード
*/
class Node
  : public Object
{
  using super = Object;

 public:
  WXDRAW_DECLARE_NODE(Ellipse);
  WXDRAW_DECLARE_NODE(Export);
  WXDRAW_DECLARE_NODE(Group);
  WXDRAW_DECLARE_NODE(Layer);
  WXDRAW_DECLARE_NODE(Project);
  WXDRAW_DECLARE_NODE(Proxy);
  WXDRAW_DECLARE_NODE(Rectangle);
  WXDRAW_DECLARE_NODE(Root);
  WXDRAW_DECLARE_NODE(Text);
  WXDRAW_DECLARE_NODE(View);

 private:
  std::weak_ptr<Node> parent_;
  std::vector<ComponentBasePtr> components_;
  bool show_;
  wxString comment_;
  std::map<std::type_index, ErrorPtr> errors_;
  wxRecursionGuardFlag updating_;
  wxRecursionGuardFlag rendering_;

 public:
  Node(const wxString& type, const NodePtr& parent);
  Node(const Node& src, const NodePtr& parent);
  ~Node();

  WXDRAW_IS_ACCESSOR(Show, show_);

  WXDRAW_GETTER(Components, components_);
  LayoutComponentPtr getLayout() const;
  ContainerComponentPtr getContainer() const;
  void appendComponent(const ComponentBasePtr& component);
  void removeComponent(const ComponentBasePtr& component);

  template<class T>
  bool canAppendComponent() const {
    return getComponent<T>() == nullptr;
  }

  NodePtr getParent() const;
  void resetParent(const NodePtr& parent);
  static bool IsParent(const NodePtr& child, const NodePtr& parent);

  static std::tuple<NodePtr, size_t> GetParentPos(const NodePtr& node);

  PropertyPtr generateProperty() override;

  void update();
  void render(Renderer& renderer, const Transform& parent);

  static NodePtr Clone(const Node& src, const NodePtr& parent);

  /**
     新規ノードを生成する
  */
  template<class... ComponentTypes>
  static NodePtr Create(const char* type, const NodePtr& parent) {
    auto node = super::Create<Node>(type, parent);
    CreateComponent<ComponentTypes...>(node);
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
  static std::shared_ptr<T> GetParentComponent(const NodePtr& node) {
    if(node) {
      if(auto component = node->getComponent<T>()) {
        return component;
      }
      return GetParentComponent<T>(node->getParent());
    }
    return nullptr;
  }

  WXDRAW_GETTER(Errors, errors_);

  template<class T>
  void setError(const T& error) {
    errors_[typeid(T)] = std::make_shared<T>(error);
  }

  template<class T>
  void resetError() {
    errors_.erase(typeid(T));
  }

  WXDRAW_IS_GETTER(Rendering, rendering_);

 private:
  /**
     コンポーネントを追加する
  */
  template<class T1, class T2, class... Rest>
  static void CreateComponent(const NodePtr& node) {
    CreateComponent<T1>(node);
    CreateComponent<T2, Rest...>(node);
  }

  /**
     コンポーネントを追加する
  */
  template<class T>
  static std::shared_ptr<T> CreateComponent(const NodePtr& node) {
    auto component = T::template Create<T>(node);
    node->appendComponent(component);
    return component;
  }
};
}
