#include "wxdraw/gui/Canvas.hpp"
#include "wxdraw/palette/PaletteItem.hpp"

namespace wxdraw::palette {
const wxSize PaletteItem::BITMAP_SIZE(16, 16);
wxBitmap PaletteItem::NullBitmap;
/**
   コンストラクタ
   @param type 型名
   @param palette パレットコンポーネント
*/
PaletteItem::PaletteItem(const wxString& type, 
                         const PaletteComponentPtr& palette)
  : super(type), 
    palette_(palette), 
    bitmap_(GetNullBitmap())
{
}
/**
   コンストラクタ
   @param type 型名
   @param palette パレットコンポーネント
   @param name 名前
*/
PaletteItem::PaletteItem(const wxString& type, 
                         const PaletteComponentPtr& palette, 
                         const wxString& name)
  : PaletteItem(type, palette)
{
  setName(name);
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
