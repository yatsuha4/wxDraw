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

  template<class PropertyType, class MemberType>
  PropertyType* append(const std::shared_ptr<MemberType>& member) {
    auto property = new PropertyType(member->getLabel(), 
                                     member->getUniqueName(), 
                                     member->getValue());
    append(property, member);
    return property;
  }

  void append(wxPGProperty* property, const MemberBasePtr& member);
};
}
