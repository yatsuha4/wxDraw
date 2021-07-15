#include "wxdraw/component/BrushComponent.hpp"
#include "wxdraw/component/ContainerComponent.hpp"
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
NodePtr XmlImporter::parseNode(const wxXmlNode& xml) {
  NodePtr node = std::make_shared<Node>(xml.GetName().ToStdString());
  parseProperty(*node, xml);
  for(auto iter = xml.GetChildren(); iter; iter = iter->GetNext()) {
    if(auto component = parseComponent(*node, *iter)) {
      if(auto container = std::dynamic_pointer_cast<ContainerComponent>(component)) {
        for(auto child = iter->GetChildren(); child; child = child->GetNext()) {
          Node::Append(parseNode(*child), node);
        }
      }
    }
    else {
      wxLogWarning("syntax error, '%s'(line:%d)", iter->GetName(), iter->GetLineNumber());
    }
  }
  return node;
}
/**
 */
ComponentBasePtr XmlImporter::parseComponent(Node& node, const wxXmlNode& xml) {
  return parseComponent<BrushComponent, 
                        ContainerComponent, 
                        EllipseComponent, 
                        GridComponent, 
                        LayerComponent, 
                        LayoutComponent, 
                        RectangleComponent>(node, xml);
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
