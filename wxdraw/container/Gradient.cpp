#include "wxdraw/container/Gradient.hpp"
#include "wxdraw/gui/Renderer.hpp"

namespace wxdraw::container {
/**
 */
void Gradient::sort() {
  std::stable_sort(begin(), end(), [](const wxGraphicsGradientStop& lhs, 
                                      const wxGraphicsGradientStop& rhs) {
    return lhs.GetPosition() < rhs.GetPosition();
  });
}
/**
 */
wxColour Gradient::getColor() const {
  return empty() ? wxTransparentColour : front().GetColour();
}
/**
 */
Gradient::operator wxGraphicsGradientStops() {
  wxASSERT(size() >= 2);
  sort();
  auto startPos = 
    std::lower_bound(begin(), end(), 0.0f, [](const wxGraphicsGradientStop& iter, 
                                              float value) {
                                              
      return iter.GetPosition() < value;
    });
  if(startPos == end()) {
    startPos = begin();
  }
  auto endPos = 
    std::lower_bound(startPos, end(), 1.0f, [](const wxGraphicsGradientStop& iter, 
                                               float value) {
      return iter.GetPosition() < value;
    });
  if(endPos == end()) {
    --endPos;
  }
  wxGraphicsGradientStops stops(startPos->GetColour(), endPos->GetColour());
  for(auto iter = startPos; iter != endPos; iter++) {
    if(iter->GetPosition() > 0.0f && iter->GetPosition() < 1.0f) {
      stops.Add(*iter);
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
