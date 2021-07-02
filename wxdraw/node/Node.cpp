#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::node {
/**
   コンストラクタ
*/
Node::Node(const std::string& id)
  : property_(std::make_shared<Property>(id)), 
    show_(true), 
    pos_(0.0, 0.0), 
    scale_(1.0, 1.0), 
    rotate_(0.0), 
    matrix_(1.0)
{
  property_->
    appendMember("Show", show_);
}
/**
   親ノードを取得する
   @return 親ノード
*/
NodePtr Node::getParent() const {
  return parent_.lock();
}
/**
   子供を挿入する
   @param child 挿入する子供
   @param parent 親ノード
   @param index 挿入位置
*/
void Node::InsertChild(const NodePtr& child, const NodePtr& parent, size_t index) {
  child->parent_ = parent;
  parent->children_.insert(parent->children_.begin() + index, child);
}
/**
   子供を削除する
   @param child 削除する子供
*/
void Node::removeChild(const NodePtr& child) {
  child->parent_.reset();
  children_.erase(std::remove(children_.begin(), children_.end(), child));
}
/**
   更新
*/
void Node::update() {
  onUpdate();
}
/**
   描画する
   @param renderer レンダラー
*/
void Node::render(Renderer& renderer) {
  auto matrix = renderer.pushMatrix(matrix_);
  if(show_) {
    onRender(renderer);
  }
  for(auto& child : children_) {
    child->render(renderer);
  }
  renderer.setMatrix(matrix);
}
/**
 */
void Node::onUpdate() {
  glm::dmat3 m;
  m = glm::scale(m, scale_);
  m = glm::rotate(m, rotate_);
  m = glm::translate(m, pos_);
  matrix_ = m;
}
}
