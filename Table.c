#define TABLE_CAPACITY 100003

#define hash(key) (((key) % TABLE_CAPACITY + TABLE_CAPACITY) % TABLE_CAPACITY)

typedef struct {
    int key;
    void* value;
} TableEntry;

typedef struct {
    TableEntry** entries;
    int capacity;
} Table;

Table tableInit() {
    Table table;
    table.capacity = TABLE_CAPACITY;
    table.entries = calloc(table.capacity, sizeof(TableEntry*));
    return table;
}

void tablePut(Table* table, int key, void* value) {
    int index = hash(key);
    while (table->entries[index] != NULL) {
        index = (index + 1) % table->capacity;
    }
    table->entries[index] = malloc(sizeof(TableEntry));
    table->entries[index]->key = key;
    table->entries[index]->value = value;
}

void* tableGet(Table* table, int key) {
    int index = hash(key);
    while (table->entries[index] != NULL) {
        if (table->entries[index]->key == key) {
            return table->entries[index]->value;
        }
        index = (index + 1) % table->capacity;
    }
    return NULL;
}

void tableFree(Table* table) {
    for (int i = 0; i < table->capacity; i++) {
        if (table->entries[i] != NULL) {
            free(table->entries[i]);
        }
    }
    free(table->entries);
}
