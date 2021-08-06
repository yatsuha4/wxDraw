#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/file/ImageExporter.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
*/
ImageExporter::ImageExporter(const NodePtr& node, 
                             const wxFileName& fileName, 
                             const glm::ivec2& size, 
                             const glm::dvec2& scale, 
                             const glm::dvec2& alignment)
  : super(node), 
    fileName_(fileName), 
    size_(size), 
    scale_(scale), 
    alignment_(alignment)
{
}
/**
 */
bool ImageExporter::save() {
  /*
  auto& rect = getNode()->getLayout()->getRect();
  glm::dmat3 m(1.0);
  m = glm::translate(m, (glm::dvec2(size_) - rect.size) * alignment_ - rect.pos * scale_);
  m = glm::scale(m, scale_);
  wxImage image(size_.x, size_.y);
  image.InitAlpha();
  for(int x = 0; x < size_.x; x++) {
    for(int y = 0; y < size_.y; y++) {
      image.SetAlpha(x, y, 0);
    }
  }
  {
    Renderer renderer(image, m);
    //getNode()->render(renderer);
  }
  return image.SaveFile(fileName_.GetFullPath());
  */
  return false;
}
}
