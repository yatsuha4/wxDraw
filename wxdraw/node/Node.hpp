#pragma once

namespace wxdraw::node {
/**
   ノード基底クラス
*/
class Node {
 private:
  wxRect rect_;
  std::vector<NodePtr> children_;
  PropertyPtr property_;
  bool show_;
  wxRealPoint pos_;
  wxRealPoint scale_;
  wxDouble rotate_;

 public:
  Node(const std::string& id);
  virtual ~Node() = default;

  WXDRAW_GETTER(Rect, rect_);
  WXDRAW_GETTER(Children, children_);

  void appendChild(NodePtr child);
  void removeChild(NodePtr child);

  virtual void update();
  virtual void render(Renderer& renderer);

 protected:
  WXDRAW_SETTER(Rect, rect_);

  virtual void onRender(Renderer& renderer) {}
};
}
