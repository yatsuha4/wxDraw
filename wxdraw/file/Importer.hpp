#pragma once

namespace wxdraw::file {
/**
   入力基底クラス
*/
class Importer {
 public:
  virtual ~Importer() = default;

  virtual NodePtr load() = 0;

 protected:
  Importer() = default;
};
}
