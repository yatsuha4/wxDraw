#pragma once

namespace wxdraw::node {
/**
   ノード基底クラス
*/
class Node {
 private:
  std::string name_;
  wxRect rect_;
  std::vector<NodePtr> children_;
  PropertyPtr property_;
  bool show_;
  wxRealPoint pos_;
  wxRealPoint scale_;
  wxDouble rotate_;
  wxTreeListItem item_;

 public:
  Node(const std::string& id);
  virtual ~Node() = default;

  WXDRAW_GETTER(Name, name_);
  WXDRAW_GETTER(Rect, rect_);
  WXDRAW_GETTER(Children, children_);
  WXDRAW_GETTER(Property, property_);

  void appendChild(const NodePtr& child);
  void insertChild(size_t index, const NodePtr& child);
  void removeChild(const NodePtr& child);

  virtual void update();
  virtual void render(Renderer& renderer);

  WXDRAW_ACCESSOR(Item, item_);

 protected:
  WXDRAW_SETTER(Rect, rect_);

  virtual void onRender(Renderer& renderer) {}
};
}
