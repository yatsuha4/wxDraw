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
  MainFrame* mainFrame_;
  NodePtr node_;

 public:
  Inspector(wxWindow* parent, MainFrame* mainFrame);
  ~Inspector() override = default;

  void show(const NodePtr& node);
  void clear();

 private:
  void showProperty(Property& property);

  template<class PropertyType, class MemberType>
  PropertyType* append(const std::shared_ptr<MemberType>& member) {
    return append<PropertyType>(member, 
                                member->getLabel(), 
                                member->getUniqueName(), 
                                member->getValue());
  }

  template<class PropertyType, class... Args>
  PropertyType* append(const MemberBasePtr& member, Args... args) {
    auto property = new PropertyType(args...);
    append(property, member);
    return property;
  }

  void append(wxPGProperty* property, const MemberBasePtr& member);

  void onChanged(wxPropertyGridEvent& event);
};
}
