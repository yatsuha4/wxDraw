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

  WXDRAW_GETTER(Color, color_);
  WXDRAW_GETTER(Pos, pos_);

  PropertyPtr createProperty();

  operator wxGraphicsGradientStop() const;
};
}
