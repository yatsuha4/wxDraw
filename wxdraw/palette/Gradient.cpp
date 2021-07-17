#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Gradient::TYPE = "Gradient";
int Gradient::Serial = 0;
/**
 */
void Gradient::sort() {
  std::stable_sort(stops_.begin(), stops_.end(), 
                   [](const auto& lhs, const auto& rhs) {
                     return *lhs < *rhs;
                   });
}
/**
 */
wxColour Gradient::getColor() const {
  return stops_.empty() ? wxTransparentColour : stops_.front()->getColor()->getColor();
}
/**
 */
Gradient::operator wxGraphicsGradientStops() {
  wxASSERT(stops_.size() >= 2);
  sort();
  auto startPos = 
    std::lower_bound(stops_.begin(), stops_.end(), 0.0, 
                     [](const auto& iter, double value) {
                       return iter->getPos() < value;
                     });
  if(startPos == stops_.end()) {
    startPos = stops_.begin();
  }
  auto endPos = 
    std::lower_bound(startPos, stops_.end(), 1.0, 
                     [](const auto& iter, double value) {
                       return iter->getPos() < value;
                     });
  if(endPos == stops_.end()) {
    --endPos;
  }
  wxGraphicsGradientStops stops((*startPos)->getColor()->getColor(), 
                                (*endPos)->getColor()->getColor());
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
  if(stops_.size() < 2) {
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
void Gradient::onCreate(const PaletteComponentPtr& palette) {
  name_ = wxString::Format("%s_%d", TYPE, ++Serial);
  auto stop = std::make_shared<GradientStop>();
  stop->onCreate(palette);
  stops_.push_back(stop);
}
/**
   プロパティを生成する
*/
PropertyPtr Gradient::createProperty(const PaletteComponentPtr& palette) {
  auto property = super::createProperty(TYPE, palette);
  property->appendMember("Name", name_);
  return property;
}
}
