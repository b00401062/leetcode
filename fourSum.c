typedef struct {
    void** data;
    int size;
    int capacity;
} List;

List listInit() {
    return (List) {
        .data = malloc(sizeof(void*) * 4),
        .size = 0,
        .capacity = 4
    };
}

void listAdd(List* list, void* value) {
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->data = realloc(list->data, sizeof(void*) * list->capacity);
    }
    list->data[list->size++] = value;
}

void listFree(List* list) {
    free(list->data);
}

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), cmp);
    List result = listInit();
    for (int i = 0; i < numsSize - 3; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        for (int j = i + 1; j < numsSize - 2; j++) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;
            int left = j + 1;
            int right = numsSize - 1;
            while (left < right) {
                long sum = (long) nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target) {
                    int* quadruplet = malloc(sizeof(int) * 4);
                    memcpy(quadruplet, (int[]){nums[i], nums[j], nums[left], nums[right]}, sizeof(int) * 4);
                    listAdd(&result, quadruplet);
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1]) {
                        left++;
                    }
                    while (left < right && nums[right] == nums[right + 1]) {
                        right--;
                    }
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
    }
    returnSize[0] = result.size;
    *returnColumnSizes = malloc(sizeof(int) * result.size);
    for (int i = 0; i < result.size; i++) {
        (*returnColumnSizes)[i] = 4;
    }
    return (int**) result.data;
}
