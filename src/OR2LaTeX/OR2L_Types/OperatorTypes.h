#pragma once

namespace or2l {
enum class MathExpressionOperatorTypes {
  EQUAL,
  GREATER_EQUAL,
  GREATER,
  LESS_EQUAL,
  LESS
};

enum class ObjectiveExpressionOperatorTypes { MINIMIZE, MAXIMIZE };
}  // namespace or2l