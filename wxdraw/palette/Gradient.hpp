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

  static int Serial;

 public:
  Gradient() = default;
  Gradient(const Gradient& src) = default;
  ~Gradient() = default;

  WXDRAW_ACCESSOR(Stops, stops_);

  void sort();

  operator wxGraphicsGradientStops();

  void update() override;
  void onCreate(const PaletteComponentPtr& palette) override;
  PropertyPtr createProperty() override;
};
}
