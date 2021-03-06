#pragma once
#include "Bounds.h"
#include "auxiliary/Exception.h"
#include "symbol/SymbolComponent.h"
#include <string>

namespace or2l
{
class Index : public SymbolComponent
{
  public:
    Index() : SymbolComponent("", SymbolType::INDEX)
    {
    }
    Index(const base_types::RegexString &_name, const size_t _plb, const size_t _pub)
        : SymbolComponent(_name, SymbolType::INDEX), lb(_plb), ub(_pub)
    {
        if (ub < lb)
        {
            throw Exception(ExceptionType::ERR_INDEX_BOUNDS);
        }
    }
    ~Index() override = default;

    inline bool operator==(const Index &_B) const
    {
        return this->lb == _B.lb && this->ub == _B.ub && this->name_ == _B.name_;
    }

    explicit operator base_types::Bounds() const
    {
        return base_types::Bounds{lb, ub};
    }

    [[nodiscard]] inline size_t GetUB() const
    {
        return ub;
    }
    [[nodiscard]] inline size_t GetLB() const
    {
        return lb;
    }
    [[nodiscard]] inline size_t GetSize() const
    {
        return ub - lb;
    }

  private:
    size_t lb = 0;
    size_t ub = 0;
};
} // namespace or2l
