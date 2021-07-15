#pragma once

namespace wxdraw::container {
/**
   グラデーションカラー
*/
class Gradient
  : public std::vector<wxGraphicsGradientStop>
{
 public:
  Gradient() = default;
  ~Gradient() = default;

  void sort();

  wxColour getColor() const;
  operator wxGraphicsGradientStops();

  wxImage createImage(const wxSize& size);
};
}
