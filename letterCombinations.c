const char* mapping[] = {
    "",     // 0
    "",     // 1
    "abc",  // 2
    "def",  // 3
    "ghi",  // 4
    "jkl",  // 5
    "mno",  // 6
    "pqrs", // 7
    "tuv",  // 8
    "wxyz"  // 9
};

char** letterCombinations(char* digits, int* returnSize) {
    if (strlen(digits) == 0) {
        *returnSize = 1;
        return (static char*[]) {""};
    }
    char** recursiveResult = letterCombinations(digits + 1, returnSize);
    char** result = malloc(sizeof(char*) * (*returnSize) * strlen(mapping[digits[0] - '0']));
    int resultIndex = 0;
    for (char* p = mapping[digits[0] - '0']; *p != '\0'; p++) {
        for (int i = 0; i < *returnSize; i++) {
            char* combination = malloc(strlen(recursiveResult[i]) + 2);
            combination[0] = *p;
            strcpy(combination + 1, recursiveResult[i]);
            result[resultIndex++] = combination;
        }
    }
    *returnSize *= strlen(mapping[digits[0] - '0']);
    return result;
}
