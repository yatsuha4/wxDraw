#pragma once

namespace wxdraw::container {
/**
   ペン
*/
class Pen {
 public:
  static const char* TYPE;

 private:
  GradientPtr gradient_;
  double width_;

 public:
  Pen();
  Pen(const Pen& src) = default;
  ~Pen() = default;

  WXDRAW_GETTER(Gradient, gradient_);
  WXDRAW_GETTER(Width, width_);

  PropertyPtr createProperty(const PaletteComponentPtr& palette) const;
};
}
