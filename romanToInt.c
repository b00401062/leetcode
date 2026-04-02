static const int values[] = {
    1000,
    900,
    500,
    400,
    100,
    90,
    50,
    40,
    10,
    9,
    5,
    4,
    1
};

static const char* symbols[] = {
    "M",
    "CM",
    "D",
    "CD",
    "C",
    "XC",
    "L",
    "XL",
    "X",
    "IX",
    "V",
    "IV",
    "I"
};

int romanToInt(char* s) {
    int total = 0;
    int i = 0;
    while (s[i] != '\0') {
        for (int j = 0; j < 13; j++) {
            int len = strlen(symbols[j]);
            if (strncmp(s + i, symbols[j], len) == 0) {
                total += values[j];
                i += len;
                break;
            }
        }
    }
    return total;
}
