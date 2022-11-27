typedef string String<>;

struct DwcRequest {
  String strings<>;
};

struct DwcResponse {
  int length;
  int total_words;
};

program dwc {
  version VER {
    DwcResponse count(DwcRequest) = 1;
  } = 100;
} = 55555555;