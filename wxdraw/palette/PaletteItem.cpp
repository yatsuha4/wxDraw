#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
const wxSize PaletteItem::BITMAP_SIZE(16, 16);
wxBitmap PaletteItem::NullBitmap;
/**
 */
PaletteItem::PaletteItem()
  : bitmap_(GetNullBitmap())
{
}
/**
 */
const wxBitmap& PaletteItem::GetNullBitmap() {
  if(!NullBitmap.IsOk()) {
    NullBitmap.Create(BITMAP_SIZE);
    wxMemoryDC dc(NullBitmap);
    dc.SetBackground(Canvas::GetBackgroundBrush());
    dc.Clear();
  }
  return NullBitmap;
}
}
