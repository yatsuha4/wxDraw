#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/component/Component.hpp"
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
  for(auto& component : components_) {
    component->update();
  }
}
/**
   描画する
   @param renderer レンダラー
*/
void Node::render(Renderer& renderer) {
  auto matrix = renderer.pushMatrix(matrix_);
  if(show_) {
    onBeginRender(renderer);
    for(auto& component : components_) {
      component->beginRender(renderer);
    }
    for(auto& child : children_) {
      child->render(renderer);
    }
    onEndRender(renderer);
    for(auto& component : components_) {
      component->endRender(renderer);
    }
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
  property_->appendMember("Name", name_);
  property_->appendMember("Show", show_);
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
/**
   コンポーネントを追加する
   @param component 追加するコンポーネント
*/
void Node::appendComponent(const ComponentPtr& component) {
  components_.push_back(component);
}
/**
   コンポーネントを削除する
   @param component 削除するコンポーネント
*/
void Node::removeComponent(const ComponentPtr& component) {
  components_.erase(std::remove(components_.begin(), components_.end(), component));
}
}
