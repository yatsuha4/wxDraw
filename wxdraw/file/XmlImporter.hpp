#pragma once

#include "wxdraw/file/Importer.hpp"
#include "wxdraw/node/Node.hpp"
#include "wxdraw/property/Member.hpp"

namespace wxdraw::file {
/**
   XML入力
*/
class XmlImporter
  : public Importer
{
  using super = Importer;

 private:
  wxXmlDocument document_;
  PaletteComponentPtr palette_;

 public:
  XmlImporter(const wxString& fileName);
  ~XmlImporter() override = default;

  NodePtr load(const NodePtr& parent);

  static bool FromString(const wxString& text, int& value);
  static bool FromString(const wxString& text, double& value);
  static bool FromString(const wxString& text, bool& value);

 private:
  NodePtr createNode(const wxXmlNode& xml, const NodePtr& parent);
  void parsePalette(const wxXmlNode& xml);
  void parseProperty(const wxXmlNode& xml, const Property& property);

  static ComponentBasePtr CreateComponent(const NodePtr& node, const wxXmlNode& xml);

  template<class T>
  static ComponentBasePtr CreateComponent(const NodePtr& node, const wxXmlNode& xml) {
    if(xml.GetName() == T::TYPE) {
      return Node::AppendComponent<T>(node);
    }
    return nullptr;
  }

  template<class T1, class T2, class... Rest>
  static ComponentBasePtr CreateComponent(const NodePtr& node, const wxXmlNode& xml) {
    if(auto component = CreateComponent<T1>(node, xml)) {
      return component;
    }
    return CreateComponent<T2, Rest...>(node, xml);
  }

  template<class T>
  bool parseMember(const MemberBasePtr& member, const wxString& value) const {
    if(auto m = Member<T>::As(member)) {
      if(!fromString(value, m->getValue())) {
        wxLogWarning("syntax error, '%s' for '%s'", value, member->getName());
      }
      return true;
    }
    return false;
  }

  template<class T1, class T2, class... Rest>
  bool parseMember(const MemberBasePtr& member, const wxString& value) const {
    return parseMember<T1>(member, value) ||
      parseMember<T2, Rest...>(member, value);
  }

  bool fromString(const wxString& src, int& dst) const;
  bool fromString(const wxString& src, double& dst) const;
  bool fromString(const wxString& src, bool& dst) const;
  bool fromString(const wxString& src, wxString& dst) const;
  bool fromString(const wxString& src, wxColour& dst) const;
  bool fromString(const wxString& src, wxFileName& dst) const;
  bool fromString(const wxString& src, wxFont& dst) const;
  bool fromString(const wxString& src, Choice& dst) const;

  bool fromString(const wxString& src, PenPtr& dst) const {
    return fromStringPalette(src, dst);
  }

  bool fromString(const wxString& src, BrushPtr& dst) const {
    return fromStringPalette(src, dst);
  }

  bool fromString(const wxString& src, ColorPtr& dst) const {
    return fromStringPalette(src, dst);
  }

  bool fromString(const wxString& src, ColorBasePtr& dst) const {
    return fromStringPalette(src, dst);
  }

  bool fromString(const wxString& src, FontPtr& dst) const {
    return fromStringPalette(src, dst);
  }

  template<class T>
  bool fromStringPalette(const wxString& src, std::shared_ptr<T>& dst) const {
    if(palette_) {
      dst = palette_->findItem<T>(src);
      return true;
    }
    return false;
  }

  static void Warning(const wxString& message, const wxXmlNode& xml);
};
}
