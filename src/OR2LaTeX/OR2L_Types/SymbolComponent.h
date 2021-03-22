#pragma once
#include "RegexString.h"
#include "SymbolType.h"
#include <memory>

namespace or2l
{
class SymbolComponent
{
  public:
    SymbolComponent(const base_types::RegexString &str, const SymbolType &type) : name_(str), type_(type)
    {
    }
    virtual ~SymbolComponent() = default;

    // virtual std::unique_ptr<SymbolComponent> operator()();
    [[nodiscard]] virtual inline base_types::RegexString GetName() const
    {
        return name_;
    }
    virtual inline void SetName(const base_types::RegexString &str)
    {
        name_ = str;
    }
    [[nodiscard]] virtual inline SymbolType GetType() const
    {
        return type_;
    }

  protected:
    base_types::RegexString name_;
    SymbolType type_;
};
} // namespace or2l
