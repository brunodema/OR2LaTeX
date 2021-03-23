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
    Index(const base_types::RegexString &name, const size_t plb, const size_t pub)
        : SymbolComponent(name, SymbolType::INDEX), lb(plb), ub(pub)
    {
        if (ub < lb)
        {
            throw Exception(ExceptionType::ERR_INDEX_BOUNDS);
        }
    }
    ~Index() override = default;

    inline bool operator==(const Index &B) const
    {
        return this->lb == B.lb && this->ub == B.ub && this->name_ == B.name_;
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

template <> struct std::hash<or2l::Index>
{
    std::size_t operator()(const or2l::Index &k) const
    {
        // changed it to be based on their names, which makes sense when thinking
        // about the LaTeX implementation
        return std::hash<std::string>()(k.GetName());
    };
};