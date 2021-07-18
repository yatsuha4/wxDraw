#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
   ペン
*/
class Pen
  : public PaletteItem
{
  using super = PaletteItem;

 public:
  static const char* TYPE;

 private:
  ColorBasePtr color_;
  double width_;

  static int Serial;

 public:
  Pen();
  Pen(const Pen& src) = default;
  ~Pen() override = default;

  WXDRAW_GETTER(Color, color_);
  WXDRAW_GETTER(Width, width_);

  void onCreate(const PaletteComponentPtr& palette) override;
  void update() override;
  PropertyPtr createProperty() override;
};
}
