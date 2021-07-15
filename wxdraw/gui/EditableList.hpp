#pragma once

namespace wxdraw::gui {
/**
   編集可能リスト
*/
class EditableList
  : public wxWindow
{
  using super = wxWindow;

 private:
  wxListCtrl* listCtrl_;

 public:
  EditableList(wxWindow* parent);
  ~EditableList() override = default;
};
}
