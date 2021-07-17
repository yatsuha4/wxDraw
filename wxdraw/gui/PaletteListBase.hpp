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

  virtual void update() {}

 protected:
  WXDRAW_GETTER(List, list_);
  WXDRAW_GETTER(ImageList, imageList_);

  const PaletteComponentPtr& getPaletteComponent() const;

  virtual PaletteItemPtr getItem(size_t index) const;

  template<class T>
  static std::shared_ptr<T>
  GetItem(size_t index, const std::vector<std::shared_ptr<T>>& items) {
    return (index < items.size()) ? items.at(index) : nullptr;
  }

  virtual void appendItem(size_t index) {}
  virtual void removeItem(size_t index) {}

  void onListItemSelected(wxListEvent& event);
  void onTool(wxCommandEvent& event);
};
}
