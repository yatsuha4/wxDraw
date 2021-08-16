#include "wxdraw/component/LayoutComponent.hpp"
#include "wxdraw/container/Transform.hpp"
#include "wxdraw/file/ImageExporter.hpp"
#include "wxdraw/gui/Renderer.hpp"
#include "wxdraw/node/Node.hpp"

namespace wxdraw::file {
/**
   コンストラクタ
*/
ImageExporter::ImageExporter(const NodePtr& node, const wxFileName& fileName)
  : super(node), 
    fileName_(fileName)
{
}
/**
 */
bool ImageExporter::save() {
  auto size = glm::ceil(getNode()->getLayout()->getSize());
  wxImage image(size.x, size.y);
  image.InitAlpha();
  for(int x = 0; x < image.GetWidth(); x++) {
    for(int y = 0; y < image.GetHeight(); y++) {
      image.SetAlpha(x, y, 0);
    }
  }
  {
    Transform transform;
    transform.matrix = glm::scale(glm::translate(glm::dmat3(1.0), size * 0.5), 
                                  glm::dvec2(1.0, -1.0));
    transform.rect.pos = size * -0.5;
    transform.rect.size = size;
    Renderer renderer(image);
    getNode()->render(renderer, transform);
  }
  return image.SaveFile(fileName_.GetFullPath());
}
}
