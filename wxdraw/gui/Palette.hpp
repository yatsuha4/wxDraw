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
  GradientPtr gradient_;
  PaletteComponentPtr paletteComponent_;

 public:
  Palette(wxWindow* parent, MainFrame* mainFrame);
  ~Palette() override = default;

  WXDRAW_GETTER(MainFrame, mainFrame_);

  void setGradient(const GradientPtr& gradient);

  void setPaletteComponent(const PaletteComponentPtr& component);
  WXDRAW_GETTER(PaletteComponent, paletteComponent_);

  void update();
};
}
