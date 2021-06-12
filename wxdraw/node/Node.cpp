#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::node {
/**
 */
Node::Node(const std::string& id)
  : property_(std::make_shared<Property>(id)), 
    show_(true), 
    pos_(0.0, 0.0), 
    scale_(1.0, 1.0), 
    rotate_(0.0)
{
  property_->
    appendMember("Show", show_);
}

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
 */
void Node::update() {
}
/**
   描画する
   @param _renderer レンダラー
*/
void Node::render(Renderer& _renderer) {
  Renderer renderer(_renderer);
  auto& context = renderer.getContext();
  auto matrix = context.GetTransform();
  context.Translate(pos_.x, pos_.y);
  context.Scale(scale_.x, scale_.y);
  context.Rotate(rotate_);
  if(show_) {
    onRender(renderer);
  }
  for(auto& child : children_) {
    child->render(renderer);
  }
  context.SetTransform(matrix);
}
}
