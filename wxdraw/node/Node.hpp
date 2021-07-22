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
  struct Ellipse {
    static const char* TYPE;
    static NodePtr Create(const NodePtr& parent);
  };

  struct Layer {
    static const char* TYPE;
    static NodePtr Create(const NodePtr& parent);
  };

  struct Project {
    static const char* TYPE;
    static NodePtr Create(const NodePtr& parent);
  };

  struct Rectangle {
    static const char* TYPE;
    static NodePtr Create(const NodePtr& parent);
  };

  struct Root {
    static const char* TYPE;
  };

  struct Text {
    static const char* TYPE;
    static NodePtr Create(const NodePtr& parent);
  };

 private:
  std::weak_ptr<Node> parent_;
  std::vector<ComponentBasePtr> components_;
  bool show_;
  wxString comment_;
  wxTreeListItem item_;

 public:
  Node(const wxString& type, const NodePtr& parent);
  Node(const Node& src);
  ~Node();

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

  static NodePtr CreateRoot();
  static NodePtr Clone(const NodePtr& src);

  /**
     新規ノードを生成する
  */
  template<class... ComponentTypes>
  static NodePtr Create(const char* type, const NodePtr& parent) {
    auto node = super::Create<Node>(type, parent);
    CreateComponent<LayoutComponent, ComponentTypes...>(node);
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
  static std::shared_ptr<T> CreateComponent(const NodePtr& node) {
    auto component = T::template Create<T>(node);
    node->appendComponent(component);
    return component;
  }

 private:
  /**
     コンポーネントを追加する
  */
  template<class T1, class T2, class... Rest>
  static void CreateComponent(const NodePtr& node) {
    CreateComponent<T1>(node);
    CreateComponent<T2, Rest...>(node);
  }
};
}
