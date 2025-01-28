struct Sentence{
  wchar_t* sent;
  int size;
};

struct Text{
  struct Sentence** lines;
  int max_amount;
  int real_amount;
};

struct My_date{
  int year;
  int month;
  int day;
  wchar_t src[11];
};
