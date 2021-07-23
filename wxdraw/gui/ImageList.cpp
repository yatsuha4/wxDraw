#include "wxdraw/gui/ImageList.hpp"

namespace wxdraw::gui {
/**
   コンストラクタ
   @param size サイズ
*/
ImageList::ImageList(const wxSize& size)
  : super(size.GetWidth(), size.GetHeight())
{}
/**
   イメージを追加する
   @param id アートID
   @param client クライアント
*/
void ImageList::append(const wxArtID& id, const wxArtClient& client) {
  Add(wxArtProvider::GetBitmap(id, client, GetSize()));
}
}
