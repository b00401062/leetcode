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

char* intToRoman(int num) {
    char* result = (char*) calloc(20, sizeof(char));
    int i = 0;
    while (num > 0) {
        while (num >= romanNumerals[i].value) {
            strcat(result, romanNumerals[i].symbol);
            num -= romanNumerals[i].value;
        }
        i++;
    }
    return result;
}
