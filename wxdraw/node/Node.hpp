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

 public:
  static const char* TYPE_ELLIPSE;
  static const char* TYPE_LAYER;
  static const char* TYPE_PROJECT;
  static const char* TYPE_RECTANGLE;

 private:
  std::weak_ptr<Node> parent_;
  std::vector<NodePtr> children_;
  std::vector<ComponentBasePtr> components_;
  wxString label_;
  bool show_;
  bool container_;
  wxString comment_;
  wxTreeListItem item_;

 public:
  Node(const std::string& name);
  Node(const Node& src);
  virtual ~Node() = default;

  WXDRAW_ACCESSOR(Label, label_);
  WXDRAW_IS_ACCESSOR(Container, container_);
  WXDRAW_GETTER(Children, children_);
  WXDRAW_GETTER(Components, components_);

  NodePtr getParent() const;
  static void Append(const NodePtr& node, const NodePtr& parent);
  static void Insert(const NodePtr& node, const NodePtr& parent, size_t index);
  static void Remove(const NodePtr& node);

  virtual void update();
  virtual void render(Renderer& renderer);

  WXDRAW_ACCESSOR(Item, item_);

  static NodePtr CreateEllipse();
  static NodePtr CreateLayer();
  static NodePtr CreateProject();
  static NodePtr CreateRectangle();

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
  virtual void onUpdate() {}
  virtual void onBeginRender(Renderer& renderer) {}
  virtual void onEndRender(Renderer& renderer) {}

  virtual NodePtr clone() const;

 private:
  void setup();

  void appendComponent(const ComponentBasePtr& component);
  void removeComponent(const ComponentBasePtr& component);

  /**
     ノードを生成する
  */
  template<class... ComponentTypes>
  static NodePtr Create(const std::string& name, bool container = false) {
    auto node = std::make_shared<Node>(name);
    node->setContainer(container);
    AppendComponent<LayoutComponent, ComponentTypes...>(node);
    return node;
  }

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
