#pragma once

#include "wxdraw/component/ComponentBase.hpp"

namespace wxdraw::component {
/**
   コンポーネント基底クラステンプレート
*/
template<class T>
class Component
  : public ComponentBase
{
  using super = ComponentBase;

 public:
  Component(const std::string& name, Node& node)
    : super(name, node)
  {}
  Component(const Component& src, Node& node)
    : super(src, node)
  {}
  ~Component() override = default;

  ComponentBasePtr clone(Node& node) const override {
    return std::make_shared<T>(static_cast<const T&>(*this), node);
  }
};
}
