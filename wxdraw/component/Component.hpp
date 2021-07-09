﻿#pragma once

namespace wxdraw::component {
/**
   コンポーネント基底クラス
*/
class Component {
 private:
  Node& node_;
  PropertyPtr property_;
  bool active_;

 public:
  virtual ~Component() = default;

  Node& getNode() const {
    return node_;
  }

  WXDRAW_GETTER(Property, property_);

  void update();
  void beginRender(Renderer& renderer);
  void render(Renderer& renderer);
  void endRender(Renderer& renderer);

 protected:
  Component(Node& node);

  virtual void onUpdate() {}
  virtual void onBeginRender(Renderer& renderer) {}
  virtual void onRender(Renderer& renderer) {}
  virtual void onEndRender(Renderer& renderer) {}
};
}
