typedef struct {
    char* data;
    int size;
    int numLeft;
    int numRight;
} Stack;

Stack* stackNew(int n) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->size = 0;
    stack->numLeft = 0;
    stack->numRight = 0;
    stack->data = (char*) malloc((2 * n + 1) * sizeof(char));
    stack->data[2 * n] = '\0';
    return stack;
}

void stackPush(Stack* stack, char c) {
    stack->data[stack->size++] = c;
    if (c == '(') {
        stack->numLeft++;
    } else if (c == ')') {
        stack->numRight++;
    }
}

char stackPop(Stack* stack) {
    if (stack->size == 0) {
        return '\0';
    }
    char c = stack->data[--stack->size];
    if (c == '(') {
        stack->numLeft--;
    } else if (c == ')') {
        stack->numRight--;
    }
    return c;
}

typedef struct {
    char** data;
    int size;
    int capacity;
} List;

List* listNew() {
    List* list = (List*) malloc(sizeof(List));
    list->size = 0;
    list->capacity = 2;
    list->data = (char**) malloc(list->capacity * sizeof(char*));
    return list;
}

void listAdd(List* list, Stack stack) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = (char**) realloc(list->data, list->capacity * sizeof(char*));
    }
    list->data[list->size] = malloc((stack.size + 1) * sizeof(char));
    snprintf(list->data[list->size], stack.size + 1, "%s", stack.data);
    list->size++;
}

char** generateParenthesis(int n, int* returnSize) {
    Stack* stack = stackNew(n);
    List* result = listNew();
    do {
        while (stack->numLeft < n) {
            stackPush(stack, '(');
        }
        while (stack->numRight < n) {
            stackPush(stack, ')');
        }
        listAdd(result, *stack);
        while (stack->numLeft == stack->numRight && stack->size > 0) {
            while (stackPop(stack) != '(');
        }
        stackPush(stack, ')');
    } while (stack->numLeft != 0);
    *returnSize = result->size;
    return result->data;
}
