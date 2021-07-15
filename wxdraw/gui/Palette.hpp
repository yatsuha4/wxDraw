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
  GradientList* gradientList_;

 public:
  Palette(wxWindow* parent, MainFrame* mainFrame);
  ~Palette() override = default;
};
}
