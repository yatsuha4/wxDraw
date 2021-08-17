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
  wxFileName fileName_;
  wxXmlDocument document_;
  PaletteComponentPtr palette_;
  std::map<wxString, NodePtr> nodes_;
  std::multimap<wxString, NodePtr&> nodeRefs_;

 public:
  XmlImporter(const wxString& fileName);
  ~XmlImporter() override = default;

  NodePtr load(const NodePtr& parent);

  static bool FromString(const wxString& text, int& value);
  static bool FromString(const wxString& text, double& value);
  static bool FromString(const wxString& text, bool& value);

 private:
  NodePtr generateNode(const wxXmlNode& xml, const NodePtr& parent);
  void parsePalette(const wxXmlNode& xml);
  void parseProperty(const wxXmlNode& xml, const Property& property);

  static ComponentBasePtr GenerateComponent(const NodePtr& node, const wxXmlNode& xml);

  template<class T>
  static ComponentBasePtr GenerateComponent(const NodePtr& node, const wxXmlNode& xml) {
    if(xml.GetName() == T::TYPE) {
      auto component = std::make_shared<T>(node);
      node->appendComponent(component);
      return component;
    }
    return nullptr;
  }

  template<class T1, class T2, class... Rest>
  static ComponentBasePtr GenerateComponent(const NodePtr& node, const wxXmlNode& xml) {
    if(auto component = GenerateComponent<T1>(node, xml)) {
      return component;
    }
    return GenerateComponent<T2, Rest...>(node, xml);
  }

  template<class T>
  bool parseMember(const MemberBasePtr& member, const wxString& value) {
    if(auto m = Member<T>::As(member)) {
      if(!fromString(value, m->getValue())) {
        wxLogWarning("syntax error, '%s' for '%s'", value, member->getName());
      }
      return true;
    }
    return false;
  }

  template<class T1, class T2, class... Rest>
  bool parseMember(const MemberBasePtr& member, const wxString& value) {
    return parseMember<T1>(member, value) ||
      parseMember<T2, Rest...>(member, value);
  }

  bool fromString(const wxString& src, int& dst);
  bool fromString(const wxString& src, double& dst);
  bool fromString(const wxString& src, bool& dst);
  bool fromString(const wxString& src, wxString& dst);
  bool fromString(const wxString& src, wxColour& dst);
  bool fromString(const wxString& src, wxFileName& dst);
  bool fromString(const wxString& src, wxFont& dst);
  bool fromString(const wxString& src, Choice& dst);
  bool fromString(const wxString& src, NodePtr& dst);

  bool fromString(const wxString& src, PenPtr& dst) {
    return fromStringPalette(src, dst);
  }

  bool fromString(const wxString& src, BrushPtr& dst) {
    return fromStringPalette(src, dst);
  }

  bool fromString(const wxString& src, ColorPtr& dst) {
    return fromStringPalette(src, dst);
  }

  bool fromString(const wxString& src, ColorBasePtr& dst) {
    return fromStringPalette(src, dst);
  }

  bool fromString(const wxString& src, FontPtr& dst) {
    return fromStringPalette(src, dst);
  }

  template<class T>
  bool fromStringPalette(const wxString& src, std::shared_ptr<T>& dst) {
    if(palette_) {
      dst = palette_->findItem<T>(src);
      return true;
    }
    return false;
  }

  void entryNode(const NodePtr& node);
  void getNode(const wxString& id, NodePtr& node);

  static void Warning(const wxString& message, const wxXmlNode& xml);
};
}
