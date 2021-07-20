#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
const wxSize PaletteItem::BITMAP_SIZE(16, 16);
wxBitmap PaletteItem::NullBitmap;
/**
 */
PaletteItem::PaletteItem(const wxString& type, 
                         const PaletteComponentPtr& palette)
  : super(type), 
    palette_(palette), 
    bitmap_(GetNullBitmap())
{
}
/**
 */
void PaletteItem::update() {
  wxMemoryDC dc(bitmap_);
  dc.SetPen(*wxBLACK_PEN);
  dc.SetBrush(*wxTRANSPARENT_BRUSH);
  dc.DrawRectangle(bitmap_.GetSize());
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
