#include "wxdraw/component/ExportComponent.hpp"
#include "wxdraw/file/ImageExporter.hpp"
#include "wxdraw/property/Property.hpp"

namespace wxdraw::component {
const char* ExportComponent::TYPE = "Export";
/**
   コンストラクタ
*/
ExportComponent::ExportComponent(const NodePtr& node)
  : super(TYPE, node), 
    size_(256), 
    scale_(1.0), 
    alignment_(0.5)
{
}
/**
   コピーコンストラクタ
*/
ExportComponent::ExportComponent(const ExportComponent& src, const NodePtr& node)
  : super(src, node), 
    fileName_(src.fileName_), 
    size_(src.size_), 
    scale_(src.scale_), 
    alignment_(src.alignment_)
{
}
/**
 */
PropertyPtr ExportComponent::generateProperty() {
  auto property = super::generateProperty();
  property->appendMember("FileName", fileName_);
  property->appendMember("Size", size_);
  property->appendMember("Scale", scale_);
  property->appendMember("Alignment", alignment_);
  return property;
}
/**
 */
bool ExportComponent::save() {
  ImageExporter exporter(getNode(), fileName_, size_, scale_, alignment_);
  return exporter.save();
}
}
