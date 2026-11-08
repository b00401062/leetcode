typedef struct {
    char* data;
    int top;
    int capacity;
} Stack;

Stack* stack_init() {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    stack->capacity = 100;
    stack->top = -1;
    stack->data = (char*) malloc(stack->capacity * sizeof(char));
    return stack;
}

void stack_push(Stack* stack, char c) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->data = (char*) realloc(stack->data, stack->capacity * sizeof(char));
    }
    stack->data[++stack->top] = c;
}

char stack_pop(Stack* stack) {
    if (stack->top == -1) {
        return '\0';
    }
    return stack->data[stack->top--];
}

void stack_free(Stack* stack) {
    free(stack->data);
    free(stack);
}

bool isValid(char* s) {
    Stack* stack = stack_init();
    for (char c = *s; c != '\0'; c = *(++s)) {
        switch (c) {
            case '(':
            case '{':
            case '[':
                stack_push(stack, c);
                break;
            case ')':
                if (stack_pop(stack) != '(') {
                    stack_free(stack);
                    return false;
                }
                break;
            case '}':
                if (stack_pop(stack) != '{') {
                    stack_free(stack);
                    return false;
                }
                break;
            case ']':
                if (stack_pop(stack) != '[') {
                    stack_free(stack);
                    return false;
                }
                break;
        }
    }
    bool isValid = stack->top == -1;
    stack_free(stack);
    return isValid;
}
