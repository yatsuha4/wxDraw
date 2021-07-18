#pragma once

#include "wxdraw/palette/PenBase.hpp"

namespace wxdraw::palette {
/**
 */
class Brush
  : public PenBase
{
  using super = PenBase;

 public:
  static const char* TYPE;

 private:
  double direction_;

  static int Serial;

 public:
  Brush();
  Brush(const Brush& src) = default;
  ~Brush() override = default;

  WXDRAW_ACCESSOR(Direction, direction_);

  void onCreate(const PaletteComponentPtr& palette) override;
  PropertyPtr createProperty() override;
};
}
