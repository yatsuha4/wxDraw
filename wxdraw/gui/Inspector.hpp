#pragma once

#include "wxdraw/command/EditCommand.hpp"
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
  class ClientData
    : public wxClientData
  {
   private:
    MemberBasePtr member_;

   public:
    ClientData(const MemberBasePtr& member)
      : member_(member)
    {}
    ~ClientData() override = default;

    WXDRAW_GETTER(Member, member_);
  };

 private:
  MainFrame* mainFrame_;
  PropertyPtr property_;

 public:
  Inspector(wxWindow* parent, MainFrame* mainFrame);
  ~Inspector() override = default;

  void show(PropertyPtr property);
  void update();
  void clear();

 private:
  PaletteComponentPtr getPaletteComponent() const;
  void showProperty(const Property& property);

  template<class T1, class T2, class... Rest>
  wxPGProperty* appendMember(const MemberBasePtr& member) {
    if(auto property = appendMember<T1>(member)) {
      return property;
    }
    return appendMember<T2, Rest...>(member);
  }

  template<class T>
  wxPGProperty* appendMember(const MemberBasePtr& member) {
    if(auto m = Member<T>::As(member)) {
      return appendMember(m);
    }
    return nullptr;
  }

  wxPGProperty* appendMember(const Member<int>::Ptr& member) {
    return append<wxIntProperty>(member);
  }

  wxPGProperty* appendMember(const Member<double>::Ptr& member) {
    return append<wxFloatProperty>(member);
  }

  wxPGProperty* appendMember(const Member<bool>::Ptr& member) {
    return append<wxBoolProperty>(member);
  }

  wxPGProperty* appendMember(const Member<wxString>::Ptr& member) {
    return append<wxStringProperty>(member);
  }

  wxPGProperty* appendMember(const Member<wxColour>::Ptr& member) {
    return append<wxColourProperty>(member);
  }

  wxPGProperty* appendMember(const Member<wxFileName>::Ptr& member) {
    return append<wxFileProperty>(member, member->getValue().GetFullPath());
  }

  wxPGProperty* appendMember(const Member<wxFont>::Ptr& member) {
    return append<wxFontProperty>(member);
  }

  wxPGProperty* appendMember(const Member<Choice>::Ptr& member);

  wxPGProperty* appendMember(const Member<PenPtr>::Ptr& member) {
    return appendPaletteChoices(member, createPaletteItemChoices<Pen>());
  }

  wxPGProperty* appendMember(const Member<BrushPtr>::Ptr& member) {
    return appendPaletteChoices(member, createPaletteItemChoices<Brush>());
  }

  wxPGProperty* appendMember(const Member<ColorPtr>::Ptr& member) {
    return appendPaletteChoices(member, createPaletteItemChoices<Color>());
  }

  wxPGProperty* appendMember(const Member<ColorBasePtr>::Ptr& member) {
    return appendPaletteChoices(member, createColorBaseChoices());
  }

  wxPGProperty* appendMember(const Member<FontPtr>::Ptr& member) {
    return appendPaletteChoices(member, createPaletteItemChoices<Font>());
  }

  wxPGProperty* appendMember(const Member<NodePtr>::Ptr& member);

  template<class PropertyType, class T>
  wxPGProperty* append(const std::shared_ptr<Member<T>>& member) {
    return append<PropertyType>(member, member->getValue());
  }

  template<class T>
  wxPGProperty* appendPaletteChoices(const std::shared_ptr<Member<T>>& member, 
                                     wxPGChoices choices) {
    auto palette = getPaletteComponent();
    return appendChoices(member, choices, 
                         palette ? palette->getIndex(member->getValue()) : 0);
  }

  template<class T>
  wxPGProperty* appendChoices(const std::shared_ptr<Member<T>>& member, 
                              wxPGChoices choices, 
                              size_t index) {
    return append<wxEnumProperty>(member, choices, static_cast<int>(index));
  }

  template<class PropertyType, class... Args>
  wxPGProperty* append(const MemberBasePtr& member, Args&&... args) {
    auto property = new PropertyType(member->getLabel(), member->getUniqueName(), args...);
    append(property, member);
    return property;
  }

  void append(wxPGProperty* property, const MemberBasePtr& member);

  wxPGChoices createColorBaseChoices() const;

  template<class T>
  wxPGChoices createPaletteItemChoices() const {
    wxPGChoices choices;
    if(auto palette = getPaletteComponent()) {
      createPaletteItemChoices(choices, palette->getItems<T>());
    }
    choices.Add("Null");
    return choices;
  }

  template<class T>
  void createPaletteItemChoices(wxPGChoices& choices, 
                                const std::vector<std::shared_ptr<T>>& items) const {
    for(auto& item : items) {
      choices.Add(item->getName(), item->getBitmap());
    }
  }

  void onChanged(wxPropertyGridEvent& event);
  void onRightClick(wxPropertyGridEvent& event);

  template<class T>
  bool doChange(const wxPropertyGridEvent& event) {
    if(auto data = static_cast<ClientData*>(event.GetProperty()->GetClientObject())) {
      if(auto member = Member<T>::As(data->getMember())) {
        T value;
        if(getValue(event, value)) {
          mainFrame_->submitCommand<EditCommand<T>>(member, value);
        }
        return true;
      }
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

  bool getValue(const wxPropertyGridEvent& event, Choice& choice) const;

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

  bool getValue(const wxPropertyGridEvent& event, FontPtr& value) const {
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

  void update(wxPGProperty* property);

  template<class T1, class T2, class... Rest>
  bool update(wxPGProperty* property, const MemberBasePtr& member) {
    return update<T1>(property, member) ||
      update<T2, Rest...>(property, member);
  }

  template<class T>
  bool update(wxPGProperty* property, const MemberBasePtr& member) {
    if(auto m = Member<T>::As(member)) {
      updateMember(property, m->getValue());
      return true;
    }
    return false;
  }

  template<class T>
  void updateMember(wxPGProperty* property, const T& value) {
    property->SetValue(value);
  }

  void updateMember(wxPGProperty* property, const wxColour& value) {}

  void updateMember(wxPGProperty* property, const wxFileName& value) {
    property->SetValue(value.GetFullPath());
  }

  void updateMember(wxPGProperty* property, const wxFont& value) {}
  void updateMember(wxPGProperty* property, const Choice& value) {}
  void updateMember(wxPGProperty* property, const PenPtr& value) {}
  void updateMember(wxPGProperty* property, const BrushPtr& value) {}
  void updateMember(wxPGProperty* property, const ColorPtr& value) {}
  void updateMember(wxPGProperty* property, const ColorBasePtr& value) {}
  void updateMember(wxPGProperty* property, const FontPtr& value) {}
  void updateMember(wxPGProperty* property, const NodePtr& value);
};
}
