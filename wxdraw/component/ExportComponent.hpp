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

 public:
  ExportComponent(const NodePtr& node);
  ExportComponent(const ExportComponent& src, const NodePtr& node);
  ~ExportComponent() override = default;

  WXDRAW_ACCESSOR(FileName, fileName_);

  PropertyPtr generateProperty() override;

  bool save();

 private:
  void setup();
};
}
