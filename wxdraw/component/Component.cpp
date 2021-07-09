#include "wxdraw/component/Component.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
   @param node ノード
*/
Component::Component(Node& node)
  : node_(node), 
    property_(std::make_shared<Property>("Component")), 
    active_(true)
{
  property_->appendMember("Active", active_);
}
/**
   更新する
*/
void Component::update() {
  if(active_) {
    onUpdate();
  }
}
/**
   描画を開始する
   @param renderer レンダラー
*/
void Component::beginRender(Renderer& renderer) {
  if(active_) {
    onBeginRender(renderer);
  }
}
/**
   描画する
   @param renderer レンダラー
*/
void Component::render(Renderer& renderer) {
  if(active_) {
    onRender(renderer);
  }
}
/**
   描画を終了する
   @param renderer レンダラー
*/
void Component::endRender(Renderer& renderer) {
  if(active_) {
    onEndRender(renderer);
  }
}
}
