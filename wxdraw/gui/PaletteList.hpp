#pragma once

namespace wxdraw::gui {
/**
   編集可能リスト
*/
class PaletteList
  : public wxStaticBox
{
  using super = wxStaticBox;

 private:
  Palette* palette_;
  wxListCtrl* listCtrl_;

 public:
  PaletteList(wxWindow* parent, Palette* palette, const wxString& label);
  ~PaletteList() override = default;

  WXDRAW_GETTER(Palette, palette_);
};
}
