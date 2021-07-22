#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/component/ExportComponent.hpp"
#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/component/PenComponent.hpp"
#include "wxdraw/component/ProjectComponent.hpp"
#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/component/TextComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"
#include "wxdraw/property/PropertyMember.hpp"

namespace wxdraw::node {
const char* Node::Ellipse::TYPE = "Ellipse";
const char* Node::Layer::TYPE = "Layer";
const char* Node::Project::TYPE = "Project";
const char* Node::Rectangle::TYPE = "Rectangle";
const char* Node::Root::TYPE = "Root";
const char* Node::Text::TYPE = "Text";
/**
   コンストラクタ
   @param type 型名
*/
Node::Node(const wxString& type, const NodePtr& parent)
  : super(type), 
    parent_(parent), 
    show_(true)
{
}
/**
   コピーコンストラクタ
*/
Node::Node(const Node& src, const NodePtr& parent)
  : super(src), 
    parent_(parent), 
    show_(src.show_), 
    comment_(src.comment_)
{
}
/**
   デストラクタ
*/
Node::~Node() {
  components_.clear();
}
/**
   コンテナコンポーネントを取得する
*/
ContainerComponentPtr Node::getContainer() const {
  return getComponent<ContainerComponent>();
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
  auto container = parent->getContainer();
  wxASSERT(container);
  container->getChildren().push_back(node);
  node->parent_ = parent;
}
/**
   ノードを挿入する
   @param node 挿入するノード
   @param parent 親ノード
   @param index 挿入位置
*/
void Node::Insert(const NodePtr& node, const NodePtr& parent, size_t index) {
  auto container = parent->getContainer();
  wxASSERT(container);
  container->getChildren().insert(index, node);
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
  container->getChildren().remove(node);
  node->parent_.reset();
}
/**
   プロパティを生成する
*/
PropertyPtr Node::createProperty() {
  auto property = super::createProperty();
  property->appendMember("Name", getName());
  property->appendMember("Show", show_);
  property->appendMember("Comment", comment_);
  for(auto& component : components_) {
    property->appendMember(std::make_shared<PropertyMember>(component->createProperty()));
  }
  return property;
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
NodePtr Node::CreateRoot() {
  return Create<ContainerComponent>(Root::TYPE, nullptr);
}
/**
 */
NodePtr Node::Clone(const Node& src, const NodePtr& parent) {
  auto dst = std::make_shared<Node>(src, parent);
  std::transform(src.components_.begin(), 
                 src.components_.end(), 
                 std::back_inserter(dst->components_), 
                 [&](auto& component) {
                 return component->clone(dst);
                 });
  return dst;
}
/**
 */
NodePtr Node::Ellipse::Create(const NodePtr& parent) {
  return Node::Create<EllipseComponent>(TYPE, parent);
}
/**
 */
NodePtr Node::Layer::Create(const NodePtr& parent) {
  return Node::Create<LayerComponent, 
                      ContainerComponent, 
                      GridComponent>(TYPE, parent);
}
/**
 */
NodePtr Node::Project::Create(const NodePtr& parent) {
  return Node::Create<ProjectComponent, 
                      ContainerComponent, 
                      GridComponent, 
                      PaletteComponent, 
                      PenComponent, 
                      BrushComponent>(TYPE, parent);
}
/**
 */
NodePtr Node::Rectangle::Create(const NodePtr& parent) {
  return Node::Create<RectangleComponent>(TYPE, parent);
}
/**
 */
NodePtr Node::Text::Create(const NodePtr& parent) {
  return Node::Create<TextComponent>(TYPE, parent);
}
}
