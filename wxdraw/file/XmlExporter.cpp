#include "wxdraw/component/Component.hpp"
#include "wxdraw/file/XmlExporter.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
*/
XmlExporter::XmlExporter(const NodePtr& node)
  : super(node)
{
}
/**
   出力
*/
bool XmlExporter::save(wxOutputStream& output) {
  return document_.Save(output);
}
/**
 */
wxXmlNode* XmlExporter::parse(const NodePtr& node) {
  auto xml = new wxXmlNode(wxXML_ELEMENT_NODE, "Node");
  parse(*xml, *node->getProperty());
  for(auto& component : node->getComponents()) {
    xml->AddChild(parse(component));
  }
  for(auto& child : node->getChildren()) {
    xml->AddChild(parse(child));
  }
  return xml;
}
/**
 */
wxXmlNode* XmlExporter::parse(const ComponentPtr& component) {
  auto xml = new wxXmlNode(wxXML_ELEMENT_NODE, "Component");
  parse(*xml, *component->getProperty());
  return xml;
}
/**
 */
void XmlExporter::parse(wxXmlNode& xml, const Property& property) {
}
}
