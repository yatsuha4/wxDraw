#pragma once

namespace wxdraw::gui {
/**
 */
class GradientProperty
  : public wxSystemColourProperty
{
  using super = wxSystemColourProperty;

 private:
  GradientPtr gradient_;
  PaletteComponentPtr palette_;
  wxPGChoices choices_;

 public:
  GradientProperty(const wxString& label, 
                   const wxString& name, 
                   const GradientPtr& gradient, 
                   const PaletteComponentPtr& palette);
  ~GradientProperty() override = default;

  wxColour GetColour(int index) const override;

 private:
  static std::vector<const char*> CreateLabels(const PaletteComponent& palette);
};
}
