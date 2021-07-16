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
  wxListView* list_;

 public:
  PaletteList(wxWindow* parent, Palette* palette, const wxString& label);
  ~PaletteList() override = default;

  WXDRAW_GETTER(Palette, palette_);

 protected:
  WXDRAW_GETTER(List, list_);

  virtual void onListItemSelected(wxListEvent& event) {}
};
}
