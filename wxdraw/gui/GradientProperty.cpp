#include "wxdraw/gui/GradientProperty.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
*/
GradientProperty::GradientProperty(const wxString& label, 
                                   const wxString& name, 
                                   const GradientPtr& gradient, 
                                   const PaletteComponentPtr& palette)
  : super(label, name, CreateLabels(*palette).data(), nullptr, &choices_, 
          wxColourPropertyValue()), 
    gradient_(gradient), 
    palette_(palette)
{
  //Init();
}
/**
 */
wxColour GradientProperty::GetColour(int index) const {
  return wxTransparentColour;
}
/**
 */
std::vector<const char*> GradientProperty::CreateLabels(const PaletteComponent& palette) {
  std::vector<const char*> labels;
  return labels;
}
}
