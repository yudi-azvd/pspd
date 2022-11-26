struct Words {
  char* buffer;
  int length;
};

struct HashTable {
  int capacity;
  int size;
  char *strings;
};

struct gnumbers {
       int g_assets;
       int g_liabilities;
};

struct gnumbers_node {
       gnumbers gn_numbers;
       gnumbers_node *gn_next;
};

program dwc {
  version VER {
    int count(Words) = 1;
  } = 100;
} = 55555555;