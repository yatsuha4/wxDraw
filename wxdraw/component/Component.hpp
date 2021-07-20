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
  using super::ComponentBase;

 public:
  ComponentBasePtr clone(const NodePtr& node) const override {
    return std::make_shared<T>(static_cast<const T&>(*this), node);
  }

  /**
     キャスト
     @param component 基底クラス
     @return T型のコンポーネント(もしくはnullptr)
  */
  static std::shared_ptr<T> As(const ComponentBasePtr& component) {
    return std::dynamic_pointer_cast<T>(component);
  }
};
}
