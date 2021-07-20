#pragma once

#include "wxdraw/object/Object.hpp"

namespace wxdraw::palette {
/**
   パレット要素基底クラス
*/
class PaletteItem
  : public Object
{
  using super = Object;

 public:
  static const wxSize BITMAP_SIZE;

 private:
  PaletteComponentPtr palette_;
  wxBitmap bitmap_;

  static wxBitmap NullBitmap;

 public:
  PaletteItem(const std::string& type, const PaletteComponentPtr& palette);
  PaletteItem(const PaletteItem& src) = default;
  ~PaletteItem() override = default;

  WXDRAW_GETTER(Palette, palette_);
  WXDRAW_ACCESSOR(Bitmap, bitmap_);

  virtual void update();

  static const wxBitmap& GetNullBitmap();

  template<class T, class... Args>
  static std::shared_ptr<T> New(const PaletteComponentPtr& palette, Args... args) {
    auto item = super::New<T>(palette, args...);
    item->update();
    return item;
  }
};
}
