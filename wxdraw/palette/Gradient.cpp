#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Gradient::TYPE = "Gradient";
int Gradient::Serial = 0;
/**
 */
void Gradient::sort() {
  std::stable_sort(colors_.begin(), colors_.end(), 
                   [](const ColorPtr& lhs, const ColorPtr& rhs) {
                     return *lhs < *rhs;
                   });
}
/**
 */
wxColour Gradient::getColor() const {
  return colors_.empty() ? wxTransparentColour : colors_.front()->getColor();
}
/**
 */
Gradient::operator wxGraphicsGradientStops() {
  wxASSERT(colors_.size() >= 2);
  sort();
  auto startPos = 
    std::lower_bound(colors_.begin(), colors_.end(), 0.0, 
                     [](const ColorPtr& iter, double value) {
                       return iter->getPos() < value;
                     });
  if(startPos == colors_.end()) {
    startPos = colors_.begin();
  }
  auto endPos = 
    std::lower_bound(startPos, colors_.end(), 1.0, 
                     [](const ColorPtr& iter, double value) {
                       return iter->getPos() < value;
                     });
  if(endPos == colors_.end()) {
    --endPos;
  }
  wxGraphicsGradientStops stops((*startPos)->getColor(), (*endPos)->getColor());
  for(auto iter = startPos; iter != endPos; iter++) {
    if((*iter)->getPos() > 0.0 && (*iter)->getPos() < 1.0) {
      stops.Add(**iter);
    }
  }
  return stops;
}
/**
 */
void Gradient::createImage(wxImage& image) {
  Renderer renderer(image, glm::dmat3(1.0));
  auto& context = renderer.getContext();
  if(colors_.size() < 2) {
    context.SetBrush(wxBrush(getColor()));
  }
  else {
    context.SetBrush(context.CreateLinearGradientBrush(0.0, 0.0, 
                                                       image.GetWidth(), 
                                                       image.GetHeight(), *this));
  }
  context.DrawRectangle(0.0, 0.0, image.GetWidth(), image.GetHeight());
}
/**
 */
void Gradient::onCreate() {
  name_ = wxString::Format("%s_%d", TYPE, ++Serial);
}
/**
   プロパティを生成する
*/
PropertyPtr Gradient::createProperty(const PaletteComponentPtr& palette) {
  auto property = super::createProperty(TYPE, palette);
  return property;
}
}
