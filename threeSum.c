typedef struct {
    void** data;
    int size;
    int capacity;
} List;

List listInit() {
    List list;
    list.size = 0;
    list.capacity = 2;
    list.data = malloc(sizeof(void*) * list.capacity);
    return list;
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

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    qsort(nums, numsSize, sizeof(int), cmp);
    List result = listInit();
    for (int i = 0; i < numsSize - 2; i++) {
        if (i > 0 && nums[i] == nums[i - 1]) {
            continue;
        }
        if (nums[i] > 0) {
            break;
        }
        int left = i + 1;
        int right = numsSize - 1;
        int target = -nums[i];
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                int* triplet = malloc(3 * sizeof(int));
                triplet[0] = nums[i];
                triplet[1] = nums[left];
                triplet[2] = nums[right];
                listAdd(&result, triplet);
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
    *returnSize = result.size;
    *returnColumnSizes = malloc(sizeof(int) * result.size);
    for (int i = 0; i < result.size; i++) {
        (*returnColumnSizes)[i] = 3;
    }
    return (int**) result.data;
}
