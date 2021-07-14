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
  Component(const std::string& name, const NodePtr& node)
    : super(name, node)
  {}
  Component(const Component& src, const NodePtr& node)
    : super(src, node)
  {}
  ~Component() override = default;

  ComponentBasePtr clone(const NodePtr& node) const override {
    return std::make_shared<T>(static_cast<const T&>(*this), node);
  }
};
}
