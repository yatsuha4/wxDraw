#include "wxdraw/gui/BrushList.hpp"
#include "wxdraw/gui/ColorList.hpp"
#include "wxdraw/gui/GradientList.hpp"
#include "wxdraw/gui/Palette.hpp"
#include "wxdraw/gui/PenList.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
*/
Palette::Palette(wxWindow* parent, MainFrame* mainFrame)
  : super(parent, wxID_ANY), 
    mainFrame_(mainFrame), 
    penList_(new PenList(this, this)), 
    brushList_(new BrushList(this, this)), 
    gradientList_(new GradientList(this, this)), 
    colorList_(new ColorList(this, this))
{
  auto sizer = new wxGridSizer(4);
  sizer->Add(penList_, wxSizerFlags().Expand().Proportion(1));
  sizer->Add(brushList_, wxSizerFlags().Expand().Proportion(1));
  sizer->Add(gradientList_, wxSizerFlags().Expand().Proportion(1));
  sizer->Add(colorList_, wxSizerFlags().Expand().Proportion(1));
  SetSizerAndFit(sizer);
  setPaletteComponent(nullptr);
}
/**
 */
void Palette::setGradient(const GradientPtr& gradient) {
  colorList_->setGradient(gradient);
}
/**
 */
void Palette::setPaletteComponent(const PaletteComponentPtr& component) {
  paletteComponent_ = component;
  Enable(component != nullptr);
}
/**
 */
void Palette::update() {
  colorList_->update();
}
}
