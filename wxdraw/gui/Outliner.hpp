#pragma once

namespace wxdraw::gui {
/**
   アウトライナ
*/
class Outliner
  : public wxTreeListCtrl
{
  using super = wxTreeListCtrl;

 private:
  MainFrame& mainFrame_;

 public:
  Outliner(wxWindow* parent, MainFrame& mainFrame);
  ~Outliner() override = default;
};
}
