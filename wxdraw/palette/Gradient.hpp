#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
   グラデーション
*/
class Gradient
  : public PaletteItem
{
  using super = PaletteItem;

 public:
  static const char* TYPE;

 private:
  wxString name_;
  std::vector<ColorPtr> colors_;

  static int Serial;

 public:
  Gradient() = default;
  Gradient(const Gradient& src) = default;
  ~Gradient() = default;

  WXDRAW_GETTER(Name, name_);
  WXDRAW_ACCESSOR(Colors, colors_);

  void sort();

  wxColour getColor() const;
  operator wxGraphicsGradientStops();

  void createImage(wxImage& image);

  void onCreate() override;
  PropertyPtr createProperty(const PaletteComponentPtr& palette) override;
};
}
