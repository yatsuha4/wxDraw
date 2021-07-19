#pragma once

#include "wxdraw/file/Exporter.hpp"
#include "wxdraw/property/Member.hpp"

namespace wxdraw::file {
/**
   XML出力
*/
class XmlExporter
  : public Exporter
{
  using super = Exporter;

 private:
  wxFileName fileName_;
  PaletteComponentPtr palette_;
  wxXmlDocument document_;

 public:
  XmlExporter(const NodePtr& node, const wxFileName& fileName);
  ~XmlExporter() override = default;

  bool save() override;

 private:
  wxXmlNode* createXml(Node& node);
  wxXmlNode* createXml(Node& node, const Property& property);
  wxString getValue(const MemberBasePtr& member);

  template<class T>
  bool getValue(const MemberBasePtr& member, wxString& value) const {
    if(auto m = Member<T>::As(member)) {
      value = toString(m->getValue());
      return true;
    }
    return false;
  }

  template<class T1, class T2, class... Rest>
  bool getValue(const MemberBasePtr& member, wxString& value) const {
    return getValue<T1>(member, value) || getValue<T2, Rest...>(member, value);
  }

  wxString toString(int value) const;
  wxString toString(double value) const;
  wxString toString(bool value) const;
  wxString toString(const wxString& value) const;
  wxString toString(const wxColour& value) const;
  wxString toString(const wxFileName& value) const;
  wxString toString(const PenPtr& value) const;
  wxString toString(const BrushPtr& value) const;
};
}
