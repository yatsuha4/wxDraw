#pragma once

namespace wxdraw::gui {
/**
   パレット
*/
class Palette
  : public wxWindow
{
  using super = wxWindow;

 private:
  MainFrame* mainFrame_;
  PenList* penList_;
  BrushList* brushList_;
  GradientList* gradientList_;
  ColorList* colorList_;

 public:
  Palette(wxWindow* parent, MainFrame* mainFrame);
  ~Palette() override = default;
};
}
