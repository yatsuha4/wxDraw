#include "wxdraw/component/ComponentBase.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::component {
/**
   コンストラクタ
   @param name 名前
   @param node ノード
   @param priority 優先順位
*/
ComponentBase::ComponentBase(const std::string& name, 
                             const NodePtr& node, 
                             Priority priority)
  : super(name), 
    node_(node), 
    priority_(priority)
{
}
/**
   コピーコンストラクタ
*/
ComponentBase::ComponentBase(const ComponentBase& src, const NodePtr& node)
  : super(src), 
    node_(node), 
    priority_(src.priority_)
{
}
/**
 */
NodePtr ComponentBase::getNode() {
  return node_.lock();
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
/**
 */
wxColour ComponentBase::getColor(ColorIndex index) {
  if(auto palette = getNode()->getParentComponent<PaletteComponent>()) {
    auto& colors = palette->getColors();
    if(index < colors.size()) {
      return colors.at(index).color;
    }
  }
  return *wxRED;
}
}
