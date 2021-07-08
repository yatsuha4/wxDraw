#pragma once

namespace wxdraw::gui {
/**
   インスペクタ
*/
class Inspector
  : public wxPropertyGrid
{
  using super = wxPropertyGrid;

 private:
  MainFrame& mainFrame_;
  NodePtr node_;

 public:
  Inspector(wxWindow* parent, MainFrame& mainFrame);
  ~Inspector() override = default;

  void show(const NodePtr& node);
  void clear();

 private:
  void showProperty(const PropertyPtr& property);
  void append(wxPGProperty* property, const MemberBasePtr& member);
};
}
