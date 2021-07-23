#pragma once

namespace wxdraw::gui {
/**
   イメージリスト
*/
class ImageList
  : public wxImageList
{
  using super = wxImageList;

 public:
  ImageList(const wxSize& size);
  ~ImageList() override = default;

  void append(const wxArtID& id, const wxArtClient& client = wxART_OTHER);
};
}
