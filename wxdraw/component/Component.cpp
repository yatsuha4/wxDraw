#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
   @param node ノード
   @param name 名前
*/
Component::Component(const std::string& name, Node& node)
  : super(name), 
    node_(node), 
    active_(true)
{
  appendMember("Active", active_);
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
