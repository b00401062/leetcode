typedef struct {
    char* symbol;
    int value;
} RomanNumeral;

static const RomanNumeral romanNumerals[] = {
    {"M", 1000},
    {"CM", 900},
    {"D", 500},
    {"CD", 400},
    {"C", 100},
    {"XC", 90},
    {"L", 50},
    {"XL", 40},
    {"X", 10},
    {"IX", 9},
    {"V", 5},
    {"IV", 4},
    {"I", 1}
};

int romanToInt(char* s) {
    int total = 0;
    int i = 0;
    while (s[i] != '\0') {
        for (int j = 0; j < 13; j++) {
            int len = strlen(romanNumerals[j].symbol);
            if (strncmp(s + i, romanNumerals[j].symbol, len) == 0) {
                total += romanNumerals[j].value;
                i += len;
                break;
            }
        }
    }
    return total;
}
