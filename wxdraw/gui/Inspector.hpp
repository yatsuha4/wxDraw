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
  PropertyPtr property_;

 public:
  Inspector(wxWindow* parent, MainFrame& mainFrame);
  ~Inspector() override = default;

  void show(const PropertyPtr& property);
  void clear();

 private:
  void showProperty(const PropertyPtr& property);
  void append(wxPGProperty* property, const MemberBasePtr& member);
};
}
