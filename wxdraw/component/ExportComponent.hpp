#pragma once

#include "wxdraw/component/Component.hpp"

namespace wxdraw::component {
/**
   出力設定コンポーネント
*/
class ExportComponent
  : public Component<ExportComponent>
{
   using super = Component<ExportComponent>;

 public:
  static const char* TYPE;

 private:
  wxFileName fileName_;
  glm::ivec2 size_;
  glm::dvec2 scale_;
  glm::dvec2 alignment_;

 public:
  ExportComponent(const NodePtr& node);
  ExportComponent(const ExportComponent& src, const NodePtr& node);
  ~ExportComponent() override = default;

  WXDRAW_ACCESSOR(FileName, fileName_);

  PropertyPtr createProperty() override;

  bool save();

 private:
  void setup();
};
}
