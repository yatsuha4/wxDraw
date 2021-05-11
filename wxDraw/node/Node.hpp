#pragma once

namespace wxdraw::node {
/**
   ノード基底クラス
*/
class Node {
 private:
  wxRect rect_;
  std::vector<NodePtr> children_;

 public:
  Node() = default;
  virtual ~Node() = default;

  WXDRAW_GETTER(Rect, rect_);
  WXDRAW_GETTER(Children, children_);

  void appendChild(NodePtr child);
  void removeChild(NodePtr child);

  virtual void draw(wxGraphicsContext& gc);

 protected:
  WXDRAW_SETTER(Rect, rect_);

  virtual void onDraw(wxGraphicsContext& gc) {}
};
}
