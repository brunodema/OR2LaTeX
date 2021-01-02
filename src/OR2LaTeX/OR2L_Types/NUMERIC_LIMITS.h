namespace or2l {
static constexpr double kEpsilon = 0.000001;

static constexpr bool IsNumericallyNull(double val) {
  return val < kEpsilon && val > -kEpsilon;
}
}  // namespace or2l
