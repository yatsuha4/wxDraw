#pragma once

#include "wxdraw/property/Property.hpp"

namespace wxdraw::property {
/**
   オプションつきプロパティクラステンプレート
*/
template<class T>
class OptionProperty
  : public Property
{
  using super = Property;

 private:
  T option_;

 public:
  OptionProperty(const std::string& name, const T& option)
    : super(name), 
      option_(option)
  {}
  ~OptionProperty() override = default;

  WXDRAW_GETTER(Option, option_);

  static std::shared_ptr<OptionProperty<T>> As(const PropertyPtr& property) {
    return std::dynamic_pointer_cast<OptionProperty<T>>(property);
  }
};
}
