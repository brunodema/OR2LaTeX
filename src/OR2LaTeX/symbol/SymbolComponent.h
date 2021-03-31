#pragma once
#include "RegexString.h"
#include <memory>

namespace or2l
{
enum class SymbolType
{
    INDEX,
    VARIABLE,
    CONSTANT,
    CONSTRAINT
};

class Symbol
{
  public:
    Symbol(const base_types::RegexString &_str, const SymbolType &_type) : name_(_str), type(_type)
    {
    }
    virtual ~Symbol() = default;

    inline bool operator<(const Symbol &_symbol) const
    {
        return this->name_ < _symbol.name_;
    }

    // virtual std::unique_ptr<SymbolComponent> operator()();
    [[nodiscard]] virtual inline base_types::RegexString GetName() const
    {
        return name_;
    }
    virtual inline void SetName(const base_types::RegexString &_str)
    {
        name_ = _str;
    }
    [[nodiscard]] virtual inline SymbolType GetType() const
    {
        return type;
    }

  protected:
    base_types::RegexString name_;
    SymbolType type;
};
} // namespace or2l
