#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::node {
/**
   親ノードを取得する
   @return 親ノード
*/
NodePtr Node::getParent() const {
  return parent_.lock();
}
/**
   ノードを挿入する
   @param node 挿入するノード
   @param parent 親ノード
   @param index 挿入位置
*/
void Node::Insert(const NodePtr& node, const NodePtr& parent, size_t index) {
  wxASSERT(node->getParent() == nullptr);
  wxASSERT(index <= parent->getChildren().size());
  node->parent_ = parent;
  parent->children_.insert(parent->children_.begin() + index, node);
}
/**
   ノードを削除する
   @param node 削除するノード
*/
void Node::Remove(const NodePtr& node) {
  auto parent = node->getParent();
  wxASSERT(parent);
  node->parent_.reset();
  parent->children_.erase(std::remove(parent->children_.begin(), 
                                      parent->children_.end(), node));
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
bool Node::canAppend(const std::type_info& type) const {
  return true;
}
/**
   コンストラクタ
   @param id 識別子
*/
Node::Node(const std::string& id)
  : name_(id), 
    property_(std::make_shared<Property>(id)), 
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
 */
void Node::onUpdate() {
  glm::dmat3 m;
  m = glm::scale(m, scale_);
  m = glm::rotate(m, rotate_);
  m = glm::translate(m, pos_);
  matrix_ = m;
}
}
