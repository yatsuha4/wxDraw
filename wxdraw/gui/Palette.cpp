#include "wxdraw/gui/GradientList.hpp"
#include "wxdraw/gui/GradientStopList.hpp"
#include "wxdraw/gui/Palette.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
*/
Palette::Palette(wxWindow* parent, MainFrame* mainFrame)
  : super(parent, wxID_ANY), 
    mainFrame_(mainFrame)
{
  SetSizer(new wxGridSizer(0));
  appendList<PaletteList<Font>, 
             PaletteList<Pen>, 
             PaletteList<Brush>, 
             GradientList, 
             GradientStopList, 
             PaletteList<Color>>();
  Fit();
  setPaletteComponent(nullptr);
}
/**
 */
void Palette::setPaletteComponent(const PaletteComponentPtr& component) {
  paletteComponent_ = component;
  Enable(component != nullptr);
  for(auto& list : lists_) {
    list->refresh();
  }
}
/**
 */
void Palette::setGradient(const GradientPtr& gradient) {
  for(auto& list : lists_) {
    list->setGradient(gradient);
  }
}
/**
 */
void Palette::update() {
  for(auto& list : lists_) {
    list->update();
  }
}
}
