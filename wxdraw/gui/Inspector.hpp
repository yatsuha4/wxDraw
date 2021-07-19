#pragma once

#include "wxdraw/command/ChangePropertyCommand.hpp"
#include "wxdraw/component/PaletteComponent.hpp"
#include "wxdraw/gui/MainFrame.hpp"
#include "wxdraw/property/Member.hpp"

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
  PropertyPtr property_;

 public:
  Inspector(wxWindow* parent, MainFrame* mainFrame);
  ~Inspector() override = default;

  void show(const PropertyPtr& property);
  void clear();

 private:
  void showProperty(const Property& property);
  wxPGChoices createPenChoices() const;
  wxPGChoices createBrushChoices() const;
  wxPGChoices createColorChoices() const;
  wxPGChoices createColorBaseChoices() const;

  template<class T>
  void createPaletteItemChoices(wxPGChoices& choices, 
                                const std::vector<std::shared_ptr<T>>& items) const {
    for(auto& item : items) {
      choices.Add(item->getName(), item->getBitmap());
    }
  }

  void onChanged(wxPropertyGridEvent& event);

  template<class PropertyType, class MemberType>
  PropertyType* append(const std::shared_ptr<MemberType>& member) {
    return append<PropertyType>(member, member->getValue());
  }

  template<class MemberType>
  wxEnumProperty* appendPaletteChoices(const std::shared_ptr<MemberType>& member, 
                                       wxPGChoices choices) {
    return appendChoices(member, choices, 
                         getPaletteComponent()->getIndex(member->getValue()));
  }

  template<class MemberType>
  wxEnumProperty* appendChoices(const std::shared_ptr<MemberType>& member, 
                                wxPGChoices choices, 
                                size_t index) {
    return append<wxEnumProperty>(member, choices, static_cast<int>(index));
  }

  template<class PropertyType, class... Args>
  PropertyType* append(const MemberBasePtr& member, Args&&... args) {
    auto property = new PropertyType(member->getLabel(), member->getUniqueName(), args...);
    append(property, member);
    return property;
  }

  void append(wxPGProperty* property, const MemberBasePtr& member);

  void onRightClick(wxPropertyGridEvent& event);

  template<class T>
  bool doChange(const wxPropertyGridEvent& event) {
    auto member = static_cast<MemberBase*>(event.GetProperty()->GetClientData());
    if(auto m = dynamic_cast<Member<T>*>(member)) {
      T value;
      if(getValue(event, value)) {
        mainFrame_->submitCommand<ChangePropertyCommand<T>>(m->getValue(), value);
      }
      return true;
    }
    return false;
  }

  template<class T1, class T2, class... Rest>
  bool doChange(const wxPropertyGridEvent& event) {
    return doChange<T1>(event) || doChange<T2, Rest...>(event);
  }

  template<class T>
  bool getValue(const wxPropertyGridEvent& event, T& value) const {
    return wxAny(event.GetValue()).GetAs(&value);
  }

  bool getValue(const wxPropertyGridEvent& event, BrushPtr& value) const {
    return getValuePalette(event, value);
  }

  bool getValue(const wxPropertyGridEvent& event, ColorBasePtr& value) const {
    return getValuePalette(event, value);
  }

  bool getValue(const wxPropertyGridEvent& event, ColorPtr& value) const {
    return getValuePalette(event, value);
  }

  bool getValue(const wxPropertyGridEvent& event, PenPtr& value) const {
    return getValuePalette(event, value);
  }

  template<class T>
  bool getValuePalette(const wxPropertyGridEvent& event, 
                       std::shared_ptr<T>& value) const {
    if(auto palette = getPaletteComponent()) {
      value = palette->getItem<T>(event.GetValue().GetLong());
      return true;
    }
    return false;
  }

  const PaletteComponentPtr& getPaletteComponent() const;
};
}
