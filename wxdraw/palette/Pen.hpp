#pragma once

#include "wxdraw/palette/PenBase.hpp"

namespace wxdraw::palette {
/**
   ペン
*/
class Pen
  : public PenBase
{
  using super = PenBase;

 public:
  static const char* TYPE;

 private:
  double width_;

  static int Serial;

 public:
  Pen();
  Pen(const Pen& src) = default;
  ~Pen() override = default;

  WXDRAW_GETTER(Width, width_);

  void onCreate(const PaletteComponentPtr& palette) override;
  PropertyPtr createProperty() override;
};
}
