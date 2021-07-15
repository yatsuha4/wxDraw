#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/component/ExportComponent.hpp"
#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/component/ProjectComponent.hpp"
#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::node {
const char* Node::TYPE_ELLIPSE = "Ellipse";
const char* Node::TYPE_LAYER = "Layer";
const char* Node::TYPE_PROJECT = "Project";
const char* Node::TYPE_RECTANGLE = "Rectangle";
const char* Node::TYPE_ROOT = "Root";
/**
   コンストラクタ
   @param name 名前
*/
Node::Node(const std::string& name)
  : super(name), 
    label_(name), 
    show_(true)
{
  setup();
}
/**
   コピーコンストラクタ
*/
Node::Node(const Node& src)
  : super(src), 
    label_(src.label_), 
    show_(src.show_), 
    comment_(src.comment_)
{
  setup();
}
/**
   コンテナコンポーネントを取得する
*/
ContainerComponentPtr Node::getContainer() const {
  return getComponent<ContainerComponent>();
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
  wxASSERT(!node->getParent());
  auto container = parent->getContainer();
  wxASSERT(container);
  container->appendChild(node);
  node->parent_ = parent;
}
/**
   ノードを挿入する
   @param node 挿入するノード
   @param parent 親ノード
   @param index 挿入位置
*/
void Node::Insert(const NodePtr& node, const NodePtr& parent, size_t index) {
  wxASSERT(!node->getParent());
  auto container = parent->getContainer();
  wxASSERT(container);
  container->insertChild(node, index);
  node->parent_ = parent;
}
/**
   ノードを削除する
   @param node 削除するノード
*/
void Node::Remove(const NodePtr& node) {
  auto parent = node->getParent();
  wxASSERT(parent);
  auto container = parent->getContainer();
  wxASSERT(container);
  container->removeChild(node);
  node->parent_.reset();
}
/**
   更新
*/
void Node::update() {
  for(auto& component : components_) {
    component->beginUpdate();
  }
  for(auto& component : components_) {
    component->update();
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
    for(auto& component : components_) {
      component->beginRender(renderer);
    }
    for(auto& component : components_) {
      component->render(renderer);
    }
    for(auto& component : components_) {
      component->endRender(renderer);
    }
  }
}
/**
 */
NodePtr Node::CreateEllipse() {
  return Create<EllipseComponent>(TYPE_ELLIPSE);
}
NodePtr Node::CreateLayer() {
  return Create<LayerComponent, 
                ContainerComponent, 
                GridComponent>(TYPE_LAYER);
}
NodePtr Node::CreateProject() {
  return Create<ProjectComponent, 
                ContainerComponent, 
                GridComponent, 
                PaletteComponent, 
                BrushComponent>(TYPE_PROJECT);
}
NodePtr Node::CreateRectangle() {
  return Create<RectangleComponent>(TYPE_RECTANGLE);
}
NodePtr Node::CreateRoot() {
  return Create<ContainerComponent>(TYPE_ROOT);
}
/**
   複製を生成する
   @param src 複製元
   @return 生成した複製
*/
NodePtr Node::Clone(const NodePtr& src) {
  auto dst = std::make_shared<Node>(*src);
  for(auto& component : src->getComponents()) {
    dst->appendComponent(component->clone(dst));
    if(auto container = std::dynamic_pointer_cast<ContainerComponent>(component)) {
      for(auto& child : container->getChildren()) {
        Append(Clone(child), dst);
      }
    }
  }
  return dst;
}
/**
 */
void Node::setup() {
  appendMember("Label", label_);
  appendMember("Show", show_);
  appendMember("Comment", comment_);
}
/**
   コンポーネントを追加する
   @param component 追加するコンポーネント
*/
void Node::appendComponent(const ComponentBasePtr& component) {
  auto pos = std::upper_bound(components_.begin(), 
                              components_.end(), 
                              component->getPriority(), 
                              [](ComponentBase::Priority priority, 
                                 const ComponentBasePtr& iter) {
                                return priority < iter->getPriority();
                              });
  components_.insert(pos, component);
}
/**
   コンポーネントを削除する
   @param component 削除するコンポーネント
*/
void Node::removeComponent(const ComponentBasePtr& component) {
  components_.erase(std::remove(components_.begin(), components_.end(), component));
}
}
