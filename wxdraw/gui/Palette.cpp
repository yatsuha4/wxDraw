#include "wxdraw/gui/GradientList.hpp"
#include "wxdraw/gui/Palette.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
*/
Palette::Palette(wxWindow* parent, MainFrame* mainFrame)
  : super(parent, wxID_ANY), 
    mainFrame_(mainFrame), 
    gradientList_(new GradientList(this))
{
  auto sizer = new wxBoxSizer(wxHORIZONTAL);
  sizer->Add(gradientList_, wxSizerFlags().Expand().Proportion(1));
  SetSizerAndFit(sizer);
}
}
