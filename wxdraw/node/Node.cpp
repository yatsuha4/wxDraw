#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
/**
   子供を追加する
   @param child 追加する子供
*/
void Node::appendChild(NodePtr child) {
  children_.push_back(child);
}
/**
   子供を削除する
   @param child 削除する子供
*/
void Node::removeChild(NodePtr child) {
  children_.erase(std::remove(children_.begin(), children_.end(), child));
}
/**
   描画する
   @param gc 描画コンテキスト
*/
void Node::draw(wxGraphicsContext& gc) {
  onDraw(gc);
  for(auto& child : children_) {
    child->draw(gc);
  }
}
}
