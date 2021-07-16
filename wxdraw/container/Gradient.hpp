#pragma once

namespace wxdraw::container {
/**
   グラデーション
*/
class Gradient
  : public std::vector<GradientColorPtr>
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
