#include "wxdraw/component/ExportComponent.hpp"
#include "wxdraw/file/ImageExporter.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* ExportComponent::TYPE = "Export";
/**
   コンストラクタ
*/
ExportComponent::ExportComponent(const NodePtr& node)
  : super(TYPE, node)
{
}
/**
   コピーコンストラクタ
*/
ExportComponent::ExportComponent(const ExportComponent& src, const NodePtr& node)
  : super(src, node), 
    fileName_(src.fileName_)
{
}
/**
 */
PropertyPtr ExportComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("FileName", fileName_);
  return property;
}
/**
 */
bool ExportComponent::save() {
  ImageExporter exporter(getNode(), fileName_);
  return exporter.save();
}
}
