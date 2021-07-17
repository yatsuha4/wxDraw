#pragma once

namespace wxdraw::property {
/**
 */
class PropertyOwner
  : public std::enable_shared_from_this<PropertyOwner>
{
 public:
  PropertyOwner() = default;
  virtual ~PropertyOwner() = default;

 protected:
  PropertyPtr createProperty(const std::string& type);
};
}
