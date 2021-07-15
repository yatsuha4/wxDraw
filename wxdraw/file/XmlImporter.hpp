#pragma once

#include "wxdraw/file/Importer.hpp"
#include "wxdraw/node/Node.hpp"

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

 public:
  XmlImporter(const wxString& fileName);
  ~XmlImporter() override = default;

  NodePtr load() override;

  static bool FromString(const wxString& text, int& value);
  static bool FromString(const wxString& text, double& value);
  static bool FromString(const wxString& text, bool& value);

 private:
  NodePtr parseNode(const wxXmlNode& xml);
  ComponentBasePtr parseComponent(Node& node, const wxXmlNode& xml);
  void parseProperty(Property& property, const wxXmlNode& xml);

  template<class T>
  static NodePtr CreateNode(const wxString& type) {
    return (type == T::TYPE) ? std::make_shared<T>() : nullptr;
  }

  template<class T1, class T2, class... Rest>
  static NodePtr CreateNode(const wxString& type) {
    if(auto node = CreateNode<T1>(type)) {
      return node;
    }
    return CreateNode<T2, Rest...>(type);
  }

  template<class T>
  ComponentBasePtr parseComponent(Node& node, const wxXmlNode& xml) {
    if(xml.GetName() == T::TYPE) {
      if(auto component = node.getComponent<T>()) {
        parseProperty(*component, xml);
        return component;
      }
    }
    return nullptr;
  }

  template<class T1, class T2, class... Rest>
  ComponentBasePtr parseComponent(Node& node, const wxXmlNode& xml) {
    if(auto component = parseComponent<T1>(node, xml)) {
      return component;
    }
    return parseComponent<T2, Rest...>(node, xml);
  }
};
}
