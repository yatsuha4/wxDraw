#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/EllipseComponent.hpp"
#include "wxdraw/component/GridComponent.hpp"
#include "wxdraw/component/LayerComponent.hpp"
#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/component/RectangleComponent.hpp"
#include "wxdraw/file/XmlImporter.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
*/
XmlImporter::XmlImporter(const wxString& fileName)
  : super(), 
    document_(fileName)
{
}
/**
 */
NodePtr XmlImporter::load() {
  if(document_.IsOk()) {
    return parseNode(*document_.GetRoot());
  }
  return nullptr;
}
/**
 */
NodePtr XmlImporter::parseNode(const wxXmlNode& xml) {
  NodePtr node = std::make_shared<Node>(xml.GetName().ToStdString());
  parseProperty(*node, xml);
  for(auto iter = xml.GetChildren(); iter; iter = iter->GetNext()) {
    if(iter->GetName() == "Components") {
      parseComponents(*node, *iter);
    }
    else if(auto child = parseNode(*iter)) {
      Node::Insert(child, node, node->getChildren().size());
    }
  }
  return node;
}
/**
 */
bool XmlImporter::FromString(const wxString& text, int& value) {
  long v;
  if(wxNumberFormatter::FromString(text, &v)) {
    value = static_cast<int>(v);
    return true;
  }
  return false;
}
/**
 */
bool XmlImporter::FromString(const wxString& text, double& value) {
  return wxNumberFormatter::FromString(text, &value);
}
/**
 */
bool XmlImporter::FromString(const wxString& text, bool& value) {
  long v;
  if(wxNumberFormatter::FromString(text, &v)) {
    value = static_cast<bool>(v);
    return true;
  }
  return false;
}
/**
 */
void XmlImporter::parseComponents(Node& node, const wxXmlNode& xml) {
  for(auto iter = xml.GetChildren(); iter; iter = iter->GetNext()) {
    if(!parseComponent<BrushComponent, 
                       EllipseComponent, 
                       GridComponent, 
                       LayerComponent, 
                       LayoutComponent, 
                       RectangleComponent>(node, *iter)) {
      wxLogWarning("syntax error, %s:%d", iter->GetName(), iter->GetLineNumber());
    }
  }
}
/**
   メンバーに値を書き込む
   @param property プロパティ
   @param xml XMLノード
*/
void XmlImporter::parseProperty(Property& property, const wxXmlNode& xml) {
  for(auto& member : property.getMembers()) {
    wxString text;
    if(xml.GetAttribute(member->getName(), &text)) {
      if(auto m = Member<int>::As(member)) {
        FromString(text, m->getValue());
      }
      else if(auto m = Member<double>::As(member)) {
        FromString(text, m->getValue());
      }
      else if(auto m = Member<bool>::As(member)) {
        FromString(text, m->getValue());
      }
      else if(auto m = Member<wxString>::As(member)) {
        m->getValue() = text;
      }
      else if(auto m =  Member<wxColour>::As(member)) {
        m->getValue() = wxColour(text);
      }
    }
  }
}
}
