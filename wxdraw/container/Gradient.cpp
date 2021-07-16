#include "wxdraw/container/Gradient.hpp"
#include "wxdraw/container/GradientColor.hpp"
#include "wxdraw/gui/Renderer.hpp"

namespace wxdraw::container {
/**
 */
void Gradient::sort() {
  std::stable_sort(begin(), end(), [](const GradientColorPtr& lhs, 
                                      const GradientColorPtr& rhs) {
    return lhs->getPos() < rhs->getPos();
  });
}
/**
 */
wxColour Gradient::getColor() const {
  return empty() ? wxTransparentColour : front()->getColor();
}
/**
 */
Gradient::operator wxGraphicsGradientStops() {
  wxASSERT(size() >= 2);
  sort();
  auto startPos = 
    std::lower_bound(begin(), end(), 0.0, [](const GradientColorPtr& iter, 
                                             double value) {
      return iter->getPos() < value;
    });
  if(startPos == end()) {
    startPos = begin();
  }
  auto endPos = 
    std::lower_bound(startPos, end(), 1.0, [](const GradientColorPtr& iter, 
                                              double value) {
      return iter->getPos() < value;
    });
  if(endPos == end()) {
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
wxImage Gradient::createImage(const wxSize& size) {
  wxImage image(size);
  {
    Renderer renderer(image, glm::dmat3(1.0));
    auto& context = renderer.getContext();
    if(this->size() < 2) {
      context.SetBrush(wxBrush(getColor()));
    }
    else {
      context.SetBrush(context.CreateLinearGradientBrush(0.0, 0.0, size.x, size.y, *this));
    }
    context.DrawRectangle(0.0, 0.0, size.x, size.y);
  }
  return image;
}
}
