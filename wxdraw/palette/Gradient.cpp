#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/palette/Color.hpp"
#include "wxdraw/palette/Gradient.hpp"
#include "wxdraw/palette/GradientStop.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::palette {
const char* Gradient::TYPE = "Gradient";
/**
   コンストラクタ
*/
Gradient::Gradient(const PaletteComponentPtr& palette)
  : super(TYPE, palette), 
    radius_(0.0)
{
}
/**
   コピーコンストラクタ
 */
Gradient::Gradient(const Gradient& src)
  : super(src), 
    gradientType_(src.gradientType_), 
    radius_(src.radius_)
{
  std::transform(src.stops_.begin(), src.stops_.end(), std::back_inserter(stops_), 
                 [](const auto& stop) {
                 return std::make_shared<GradientStop>(*stop);
                 });
}
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
  wxGraphicsGradientStops stops((*startPos)->getWxColor(), (*endPos)->getWxColor());
  for(auto iter = startPos; iter != endPos; iter++) {
    if((*iter)->getPos() > 0.0 && (*iter)->getPos() < 1.0) {
      stops.Add(**iter);
    }
  }
  return stops;
}
/**
 */
void Gradient::update() {
  if(stops_.empty()) {
    setBitmap(GetNullBitmap());
  }
  else {
    wxImage image(BITMAP_SIZE);
    {
      Renderer renderer(image);
      auto& context = renderer.getContext();
      if(stops_.size() < 2) {
        context.SetBrush(wxBrush(stops_.front()->getWxColor()));
      }
      else {
        context.SetBrush(context.CreateLinearGradientBrush(0.0, 0.0, 
                                                           image.GetWidth(), 
                                                           image.GetHeight(), *this));
      }
      context.DrawRectangle(0.0, 0.0, image.GetWidth(), image.GetHeight());
    }
    setBitmap(image);
  }
  super::update();
}
/**
 */
void Gradient::onCreate() {
  super::onCreate();
  if(stops_.empty()) {
    for(int i = 0; i < 2; i++) {
      auto stop = Create<GradientStop>(getPalette());
      stop->setPos(i);
      stops_.push_back(stop);
    }
  }
}
/**
   プロパティを生成する
*/
PropertyPtr Gradient::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("Name", getName());
  property->appendChoice("GradientType", gradientType_);
  property->appendMember("Radius", radius_);
  return property;
}
}
