#include "wxdraw/component/ExportComponent.hpp"
#include "wxdraw/file/ImageExporter.hpp"

namespace wxdraw::component {
const char* ExportComponent::TYPE = "Export";
/**
   コンストラクタ
*/
ExportComponent::ExportComponent(Node& node)
  : super(TYPE, node), 
    size_(256), 
    scale_(1.0), 
    alignment_(0.5)
{
  setup();
}
/**
   コピーコンストラクタ
*/
ExportComponent::ExportComponent(const ExportComponent& src, Node& node)
  : super(src, node), 
    fileName_(src.fileName_), 
    size_(src.size_), 
    scale_(src.scale_), 
    alignment_(src.alignment_)
{
  setup();
}
/**
 */
bool ExportComponent::save(const NodePtr& node, const wxString& fileName) {
  ImageExporter exporter(node, size_, scale_, alignment_);
  return exporter.save(fileName);
}
/**
 */
void ExportComponent::setup() {
  appendMember("FileName", fileName_);
  appendMember("Size", size_);
  appendMember("Scale", scale_);
  appendMember("Alignment", alignment_);
}
}
