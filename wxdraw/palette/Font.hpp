#pragma once

#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
/**
   フォント
*/
class Font
  : public PaletteItem
{
  using super = PaletteItem;

 public:
  static const char* TYPE;

 private:
  wxFont font_;

 public:
  Font(const PaletteComponentPtr& palette);
  Font(const PaletteComponentPtr& palette, 
       const wxString& name, 
       const wxFont& font);
  Font(const Font& src) = default;
  ~Font() override = default;

  WXDRAW_ACCESSOR(Font, font_);

  PropertyPtr generateProperty() override;
};
}
