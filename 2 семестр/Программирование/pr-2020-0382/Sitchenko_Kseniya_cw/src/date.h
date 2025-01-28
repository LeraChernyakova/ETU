int is_date(wchar_t*ptr);

void get_date(wchar_t* ptr, int* year, int* month, int* day);

int cmp(const void * a, const void * b);

void sort_date(wchar_t* ptr);

void display_date(struct Text* text);

wchar_t* settime(struct tm *a);

void h_nh(struct Text* text);
