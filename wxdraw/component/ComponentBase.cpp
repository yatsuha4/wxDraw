#include "wxdraw/component/ComponentBase.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
   @param node ノード
   @param name 名前
*/
ComponentBase::ComponentBase(const std::string& name, Node& node)
  : super(name), 
    node_(node)
{
}
/**
   コピーコンストラクタ
*/
ComponentBase::ComponentBase(const ComponentBase& src, Node& node)
  : super(src), 
    node_(node)
{
}
/**
   更新を開始する
*/
void ComponentBase::beginUpdate() {
  onBeginUpdate();
}
/**
   更新する
*/
void ComponentBase::update() {
  onUpdate();
}
/**
   更新を終了する
*/
void ComponentBase::endUpdate() {
  onEndUpdate();
}
/**
   描画を開始する
   @param renderer レンダラー
*/
void ComponentBase::beginRender(Renderer& renderer) {
  onBeginRender(renderer);
}
/**
   描画する
   @param renderer レンダラー
*/
void ComponentBase::render(Renderer& renderer) {
  onRender(renderer);
}
/**
   描画を終了する
   @param renderer レンダラー
*/
void ComponentBase::endRender(Renderer& renderer) {
  onEndRender(renderer);
}
}
