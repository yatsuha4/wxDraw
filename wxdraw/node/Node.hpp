#pragma once

namespace wxdraw::node {
/**
   ノード基底クラス
*/
class Node {
 private:
  std::string name_;
  wxRect rect_;
  std::weak_ptr<Node> parent_;
  std::vector<NodePtr> children_;
  PropertyPtr property_;
  bool show_;
  glm::dvec2 pos_;
  glm::dvec2 scale_;
  double rotate_;
  glm::dmat3 matrix_;
  wxTreeListItem item_;

 public:
  Node(const std::string& id);
  virtual ~Node() = default;

  WXDRAW_GETTER(Name, name_);
  WXDRAW_GETTER(Rect, rect_);
  WXDRAW_GETTER(Children, children_);
  WXDRAW_GETTER(Property, property_);

  NodePtr getParent() const;
  static void InsertChild(const NodePtr& child, const NodePtr& parent, size_t index);
  void removeChild(const NodePtr& child);

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

 protected:
  WXDRAW_SETTER(Rect, rect_);

  virtual void onUpdate();
  virtual void onRender(Renderer& renderer) {}
};
}
