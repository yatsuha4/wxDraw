#pragma once

#include "wxdraw/object/List.hpp"
#include "wxdraw/palette/ColorBase.hpp"
#include "wxdraw/property/Choice.hpp"

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
  Choice::GradientType gradientType_;
  List<GradientStop> stops_;

 public:
  Gradient(const PaletteComponentPtr& palette);
  Gradient(const Gradient& src);
  ~Gradient() = default;

  void onCreate() override;

  WXDRAW_ACCESSOR(GradientType, gradientType_);
  WXDRAW_ACCESSOR(Stops, stops_);

  void sort();

  operator wxGraphicsGradientStops();

  void update() override;
  PropertyPtr createProperty() override;
};
}
