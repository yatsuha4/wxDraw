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
  void parseComponents(Node& node, const wxXmlNode& xml);
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
  bool parseComponent(Node& node, const wxXmlNode& xml) {
    if(xml.GetName() == T::TYPE) {
      parseProperty(*node.getComponent<T>(), xml);
      return true;
    }
    return false;
  }

  template<class T1, class T2, class... Rest>
  bool parseComponent(Node& node, const wxXmlNode& xml) {
    return parseComponent<T1>(node, xml) ||
      parseComponent<T2, Rest...>(node, xml);
  }
};
}
