#pragma once

namespace wxdraw::gui {
/**
   編集可能リスト
*/
class PaletteListBase
  : public wxWindow
{
  using super = wxWindow;

 protected:
  static const wxSize IMAGE_SIZE;

 private:
  Palette* palette_;
  wxListView* list_;
  std::unique_ptr<wxImageList> imageList_;
  size_t index_;

 public:
  PaletteListBase(wxWindow* parent, Palette* palette);
  ~PaletteListBase() override = default;

  WXDRAW_GETTER(Palette, palette_);

  void update();

 protected:
  WXDRAW_GETTER(List, list_);

  WXDRAW_GETTER(ImageList, imageList_);
  int appendGradientImage(const GradientPtr& gradient);
  int appendColorImage(const wxColour& color);
  int appendImage(const wxBitmap& bitmap);

  const PaletteComponentPtr& getPaletteComponent() const;

  virtual PaletteItemPtr getItem(size_t index) const;
  virtual void appendItem(size_t index) {}
  virtual void removeItem(size_t index) {}
  virtual void onSelectItem(const PaletteItemPtr& item);
  virtual void onUpdate() {}

  void onListItemSelected(wxListEvent& event);
  void onTool(wxCommandEvent& event);
};
}
