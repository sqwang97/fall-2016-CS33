long switch_prob(long x, long n) {
    long result = x;
    switch(n) {
        case 60:
        case 62:
            result *= 8;
            break;
        case 63:
            result >>= 3;
            break;
        case 64:
            result <<= 4;
            result -= x;
            x = result;
        case 65:
            x *= x;
        default:
            result = x + 75;
            break;
    }
    return result;
}
