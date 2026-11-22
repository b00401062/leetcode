typedef struct {
    char* key;
    int origCount;
    int currCount;
    bool occupied;
} Entry;

typedef struct {
    Entry* entries;
    int capacity;
} Map;

unsigned long hash(char* str, int len) {
    unsigned long h = 14695981039346656037UL;
    for (int i = 0; i < len; i++) {
        h ^= (unsigned char) str[i];
        h *= 1099511628211UL;
    }
    return h;
}

Map mapInit() {
    int capacity = 8192;
    return (Map) {
        .entries = calloc(capacity, sizeof(Entry)),
        .capacity = capacity
    };
}

Entry* mapFind(Map* self, char* word, int wordSize) {
    unsigned long h = hash(word, wordSize);
    int mask = self->capacity - 1;
    int idx = h & mask;
    while (self->entries[idx].occupied) {
        if (strncmp(self->entries[idx].key, word, wordSize) == 0) {
            return &self->entries[idx];
        }
        idx = (idx + 1) & mask;
    }
    return NULL;
}

Entry* mapInsert(Map* self, char* word) {
    unsigned long h = hash(word, strlen(word));
    int mask = self->capacity - 1;
    int idx = h & mask;
    while (self->entries[idx].occupied) {
        if (strcmp(self->entries[idx].key, word) == 0) {
            self->entries[idx].origCount++;
            return &self->entries[idx];
        }
        idx = (idx + 1) & mask;
    }
    self->entries[idx] = (Entry) {word, 1, 0, true};
    return &self->entries[idx];
}

void mapReset(Map* self) {
    for (int i = 0; i < self->capacity; i++) {
        if (self->entries[i].occupied) {
            self->entries[i].currCount = 0;
        }
    }
}

typedef struct {
    int* data;
    int size;
    int capacity;
} List;

List listInit() {
    int capacity = 2;
    return (List) {
        .data = malloc(sizeof(int) * capacity),
        .size = 0,
        .capacity = capacity
    };
}

void listAdd(List* self, int value) {
    if (self->size == self->capacity) {
        self->capacity *= 2;
        self->data = realloc(self->data, sizeof(int) * self->capacity);
    }
    self->data[self->size++] = value;
}

int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    int N = strlen(s);
    int wordSize = strlen(words[0]);
    Map map = mapInit();
    for (int i = 0; i < wordsSize; i++) {
        mapInsert(&map, words[i]);
    }
    List result = listInit();
    for (int offset = 0; offset < wordSize; offset++) {
        mapReset(&map);
        for (int count = 0, start = offset, end = offset; end + wordSize <= N; end += wordSize) {
            Entry* currEntry = mapFind(&map, s + end, wordSize);
            if (currEntry == NULL) {
                start = end + wordSize;
                count = 0;
                mapReset(&map);
                continue;
            }
            while (currEntry->currCount >= currEntry->origCount) {
                Entry* prevEntry = mapFind(&map, s + start, wordSize);
                prevEntry->currCount -= 1;
                start += wordSize;
                count -= 1;
            }
            currEntry->currCount += 1;
            count += 1;
            if (count == wordsSize) {
                listAdd(&result, start);
            }
        }
    }
    free(map.entries);
    *returnSize = result.size;
    return result.data;
}
