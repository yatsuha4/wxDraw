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
  NodePtr createNode(const wxXmlNode& xml);
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

  static void Warning(const wxString& message, const wxXmlNode& xml);
};
}
