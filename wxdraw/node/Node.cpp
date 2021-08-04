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
#include "wxdraw/component/ProxyComponent.hpp"
#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/component/TextComponent.hpp"
#include "wxdraw/component/ViewComponent.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Error.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Property.hpp"
#include "wxdraw/property/PropertyMember.hpp"

namespace wxdraw::node {
/**
   コンストラクタ
   @param type 型名
*/
Node::Node(const wxString& type, const NodePtr& parent)
  : super(type), 
    parent_(parent), 
    show_(true), 
    rendering_(false)
{
}
/**
   コピーコンストラクタ
*/
Node::Node(const Node& src, const NodePtr& parent)
  : super(src), 
    parent_(parent), 
    show_(src.show_), 
    comment_(src.comment_), 
    rendering_(false)
{
}
/**
   デストラクタ
*/
Node::~Node() {
  components_.clear();
}
/**
   レイアウトコンポーネントを取得する
*/
LayoutComponentPtr Node::getLayout() const {
  return getComponent<LayoutComponent>();
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
   プロパティを生成する
*/
PropertyPtr Node::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Name", getName());
  property->appendMember("Show", show_);
  property->appendMember("Comment", comment_);
  for(auto& component : components_) {
    property->appendMember(std::make_shared<PropertyMember>(component->generateProperty()));
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
    auto layout = getLayout();
    if(layout) {
      renderer.setMatrix(layout->getMatrix());
    }
    render(renderer, layout);
  }
}
/**
   描画する
   @param renderer レンダラー
   @param layout レイアウトコンポーネント
*/
void Node::render(Renderer& renderer, const LayoutComponentPtr& layout) {
  if(rendering_) {
    throw Error::RecursionRendering("recursion rendering");
  }
  rendering_ = true;
  for(auto& component : components_) {
    component->beginRender(renderer, layout);
  }
  for(auto& component : components_) {
    component->render(renderer, layout);
  }
  for(auto& component : components_) {
    component->endRender(renderer, layout);
  }
  rendering_ = false;
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
   楕円ノードを新規作成する
   @param parent 親ノード
*/
NodePtr Node::Ellipse::Create(const NodePtr& parent) {
  return Node::Create<LayoutComponent, 
                      EllipseComponent>(TYPE, parent);
}
/**
   グループノードを新規作成する
   @param parent 親ノード
*/
NodePtr Node::Group::Create(const NodePtr& parent) {
  return Node::Create<LayoutComponent, 
                      ContainerComponent>(TYPE, parent);
}
/**
   レイヤーノードを新規作成する
   @param parent 親ノード
*/
NodePtr Node::Layer::Create(const NodePtr& parent) {
  return Node::Create<LayoutComponent, 
                      LayerComponent, 
                      ContainerComponent, 
                      GridComponent>(TYPE, parent);
}
/**
   プロジェクトノードを新規作成する
   @param parent 親ノード
*/
NodePtr Node::Project::Create(const NodePtr& parent) {
  return Node::Create<LayoutComponent, 
                      ProjectComponent, 
                      ContainerComponent, 
                      PaletteComponent, 
                      PenComponent, 
                      BrushComponent, 
                      GridComponent, 
                      ViewComponent>(TYPE, parent);
}
/**
   プロキシノードを新規生成する
   @param parent 親ノード
*/
NodePtr Node::Proxy::Create(const NodePtr& parent) {
  return Node::Create<LayoutComponent, 
                      ProxyComponent>(TYPE, parent);
}
/**
   矩形ノードを新規作成する
   @param parent 親ノード
*/
NodePtr Node::Rectangle::Create(const NodePtr& parent) {
  return Node::Create<LayoutComponent, 
                      RectangleComponent>(TYPE, parent);
}
/**
   ルートノードを新規作成する
   @param parent 親ノード
*/
NodePtr Node::Root::Create(const NodePtr& parent) {
  return Node::Create<ContainerComponent>(TYPE, parent);
}
/**
   テキストノードを新規作成する
   @param parent 親ノード
*/
NodePtr Node::Text::Create(const NodePtr& parent) {
  return Node::Create<LayoutComponent, 
                      TextComponent>(TYPE, parent);
}
/**
   ビューノードを新規作成する
   @param parent 親ノード
*/
NodePtr Node::View::Create(const NodePtr& parent) {
  return Node::Create<LayoutComponent, 
                      ViewComponent, 
                      ContainerComponent>(TYPE, parent);
}
}
