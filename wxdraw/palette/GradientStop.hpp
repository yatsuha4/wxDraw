#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
 */
class GradientStop
  : public PaletteItem
{
  using super = PaletteItem;

 public:
  static const char* TYPE;

 private:
  ColorPtr color_;
  double pos_;

 public:
  GradientStop();
  GradientStop(const GradientStop& src) = default;
  ~GradientStop() = default;

  bool operator<(const GradientStop& rhs) const;

  WXDRAW_ACCESSOR(Color, color_);
  WXDRAW_ACCESSOR(Pos, pos_);

  operator wxGraphicsGradientStop() const;
  wxColour getWxColor() const;

  void update() override;
  void onCreate(const PaletteComponentPtr& palette) override;
  PropertyPtr createProperty() override;
};
}
