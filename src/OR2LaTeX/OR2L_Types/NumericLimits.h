namespace or2l
{
static constexpr double EPSILON = 0.000001;

static constexpr bool IsNumericallyNull(double val)
{
    return val < EPSILON && val > -EPSILON;
}
} // namespace or2l
