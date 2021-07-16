#pragma once

namespace wxdraw::container {
/**
   グラデーションの要素
*/
class GradientColor {
 public:
  static const char* TYPE;

 private:
  wxColour color_;
  double pos_;

 public:
  GradientColor();
  GradientColor(const GradientColor& src) = default;
  ~GradientColor() = default;

  WXDRAW_ACCESSOR(Color, color_);
  WXDRAW_ACCESSOR(Pos, pos_);

  PropertyPtr createProperty();

  operator wxGraphicsGradientStop() const;
};
}
