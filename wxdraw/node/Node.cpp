#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
/**
   コピーコンストラクタ
*/
Node::Node(const Node& src)
  : super(src), 
    label_(src.label_), 
    show_(src.show_), 
    container_(src.container_)
{
  setup();
  for(auto& component : src.components_) {
    appendComponent(component->clone(*this));
  }
}
/**
   親ノードを取得する
   @return 親ノード
*/
NodePtr Node::getParent() const {
  return parent_.lock();
}
/**
   ノードを追加する
   @param node 挿入するノード
   @param parent 親ノード
*/
void Node::Append(const NodePtr& node, const NodePtr& parent) {
  Insert(node, parent, parent->getChildren().size());
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
    component->beginUpdate();
  }
  for(auto& component : components_) {
    component->update();
  }
  for(auto& child : children_) {
    child->update();
  }
  for(auto& component : components_) {
    component->endUpdate();
  }
}
/**
   描画する
   @param renderer レンダラー
*/
void Node::render(Renderer& renderer) {
  if(show_) {
    onBeginRender(renderer);
    for(auto& component : components_) {
      component->beginRender(renderer);
    }
    for(auto& component : components_) {
      component->render(renderer);
    }
    for(auto& child : children_) {
      child->render(renderer);
    }
    onEndRender(renderer);
    for(auto& component : components_) {
      component->endRender(renderer);
    }
  }
}
/**
 */
bool Node::canAppend(const std::type_info& type) const {
  return container_;
}
/**
   複製を生成する
   @param src 複製元
   @return 生成した複製
*/
NodePtr Node::Clone(const NodePtr& src) {
  auto dst = src->clone();
  for(auto& child : src->getChildren()) {
    Append(Clone(child), dst);
  }
  return dst;
}
/**
   コンストラクタ
   @param name 名前
*/
Node::Node(const std::string& name)
  : super(name), 
    label_(name), 
    show_(true), 
    container_(false)
{
  setup();
  appendComponent<LayoutComponent>();
}
/**
   複製を生成する
   @return 生成した複製
*/
NodePtr Node::clone() const {
  return std::make_shared<Node>(*this);
}
/**
 */
void Node::setup() {
  appendMember("Label", label_);
  appendMember("Show", show_);
  appendMember("Container", container_);
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
