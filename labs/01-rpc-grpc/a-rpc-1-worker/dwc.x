typedef string String<>;

struct DwcRequest {
  String strings<>;
};

struct WordCount {
  string key<>;
  int value;
};

struct DwcResponse {
  WordCount words_count<>;    
};

program dwc {
  version VER {
    DwcResponse count(DwcRequest) = 1;
  } = 100;
} = 55555555;