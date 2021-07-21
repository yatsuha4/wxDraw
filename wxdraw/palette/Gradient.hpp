#pragma once

#include "wxdraw/palette/ColorBase.hpp"

namespace wxdraw::palette {
/**
   グラデーション
*/
class Gradient
  : public ColorBase
{
  using super = ColorBase;

 public:
  static const char* TYPE;

 private:
  std::vector<GradientStopPtr> stops_;

 public:
  Gradient(const PaletteComponentPtr& palette);
  Gradient(const Gradient& src);
  ~Gradient() = default;

  void onCreate() override;

  WXDRAW_ACCESSOR(Stops, stops_);

  void sort();

  operator wxGraphicsGradientStops();

  void update() override;
  PropertyPtr createProperty() override;
};
}
