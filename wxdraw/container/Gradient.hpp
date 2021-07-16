#pragma once

namespace wxdraw::container {
/**
   グラデーション
*/
class Gradient
  : public std::vector<GradientColorPtr>
{
 public:
  static const char* TYPE;

 private:
  std::string name_;

 public:
  Gradient() = default;
  ~Gradient() = default;

  WXDRAW_GETTER(Name, name_);

  PropertyPtr createProperty(const PaletteComponentPtr& palette);

  void sort();

  wxColour getColor() const;
  operator wxGraphicsGradientStops();

  wxImage createImage(const wxSize& size);
};
}
