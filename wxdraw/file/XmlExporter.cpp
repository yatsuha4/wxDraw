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
  document_.SetRoot(parse(node));
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
  auto xml = parse(*node);
  for(auto& component : node->getComponents()) {
    xml->AddChild(parse(*component));
  }
  for(auto& child : node->getChildren()) {
    xml->AddChild(parse(child));
  }
  return xml;
}
/**
 */
wxXmlNode* XmlExporter::parse(const Property& property) {
  auto xml = new wxXmlNode(wxXML_ELEMENT_NODE, property.getName());
  for(auto& member : property.getMembers()) {
    xml->AddAttribute(member->getName(), member->toString());
  }
  return xml;
}
}
