#pragma once

namespace wxdraw::gui {
/**
 */
class ColorProperty
  : public wxSystemColourProperty
{
  using super = wxSystemColourProperty;

 private:
  wxPGChoices choices_;
  PaletteComponentPtr palette_;

 public:
  ColorProperty(const wxString& label, 
                const wxString& name, 
                ColorIndex value, 
                ComponentBase& component);
  ~ColorProperty() override = default;

  wxColour GetColour(int index) const override;

 private:
  ColorProperty(const wxString& label, 
                const wxString& name, 
                ColorIndex value, 
                ComponentBase& component, 
                const PaletteComponentPtr& palette);
};
}
