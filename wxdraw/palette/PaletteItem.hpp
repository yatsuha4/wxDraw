#pragma once

#include "wxdraw/property/PropertyOwner.hpp"

namespace wxdraw::palette {
/**
   パレット要素基底クラス
*/
class PaletteItem
  : public PropertyOwner
{
 public:
  static const wxSize BITMAP_SIZE;

 private:
  wxString name_;
  wxBitmap bitmap_;

  static wxBitmap NullBitmap;

 public:
  PaletteItem();
  PaletteItem(const PaletteItem& src) = default;
  ~PaletteItem() override = default;

  WXDRAW_ACCESSOR(Name, name_);
  WXDRAW_ACCESSOR(Bitmap, bitmap_);

  virtual void update();
  virtual void onCreate(const PaletteComponentPtr& palette) {}
  virtual PropertyPtr createProperty() = 0;

  static const wxBitmap& GetNullBitmap();

  template<class T, class... Args>
  static std::shared_ptr<T> Create(const PaletteComponentPtr& palette, Args... args) {
    auto item = std::make_shared<T>(args...);
    item->onCreate(palette);
    item->update();
    return item;
  }
};
}
