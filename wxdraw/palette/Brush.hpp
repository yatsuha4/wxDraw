#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
 */
class Brush
  : public PaletteItem
{
  using super = PaletteItem;

 public:
  static const char* TYPE;

 private:
  ColorBasePtr color_;

  static int Serial;

 public:
  Brush();
  Brush(const Brush& src) = default;
  ~Brush() override = default;

  WXDRAW_GETTER(Color, color_);

  void onCreate(const PaletteComponentPtr& palette) override;
  void update() override;
  PropertyPtr createProperty() override;
};
}
