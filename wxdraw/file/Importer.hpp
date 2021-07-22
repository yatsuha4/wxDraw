#pragma once

namespace wxdraw::file {
/**
   入力基底クラス
*/
class Importer {
 public:
  virtual ~Importer() = default;

 protected:
  Importer() = default;
};
}
