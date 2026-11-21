int divide(int dividend, int divisor) {
    bool negative = (dividend < 0) ^ (divisor < 0);
    long ldividend = labs((long) dividend);
    long ldivisor = labs((long) divisor);
    long quotient = 0;
    while (ldividend >= ldivisor) {
        int exp = 0;
        while (ldividend >= (ldivisor << (exp + 1))) {
            exp++;
        }
        quotient += 1L << exp;
        ldividend -= ldivisor << exp;
    }
    if (quotient > INT_MAX) return INT_MAX;
    return negative ? -quotient : quotient;
}
