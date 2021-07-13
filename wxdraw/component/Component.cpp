#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
   @param node ノード
   @param name 名前
*/
Component::Component(const std::string& name, Node& node)
  : super(name), 
    node_(node)
{
}
/**
   コピーコンストラクタ
*/
Component::Component(const Component& src, Node& node)
  : super(src), 
    node_(node)
{
}
/**
   更新を開始する
*/
void Component::beginUpdate() {
  onBeginUpdate();
}
/**
   更新する
*/
void Component::update() {
  onUpdate();
}
/**
   更新を終了する
*/
void Component::endUpdate() {
  onEndUpdate();
}
/**
   描画を開始する
   @param renderer レンダラー
*/
void Component::beginRender(Renderer& renderer) {
  onBeginRender(renderer);
}
/**
   描画する
   @param renderer レンダラー
*/
void Component::render(Renderer& renderer) {
  onRender(renderer);
}
/**
   描画を終了する
   @param renderer レンダラー
*/
void Component::endRender(Renderer& renderer) {
  onEndRender(renderer);
}
/**
 */
ComponentPtr Component::clone(Node& node) const {
  return std::make_shared<Component>(*this, node);
}
}
