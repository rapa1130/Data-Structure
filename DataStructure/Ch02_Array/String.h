class String{
public:
    String();
    String(const char* arr);
    int Length() const;
    char& operator[](int index);
    char operator[](int index)const;
    bool operator==(const String& right);
    bool operator!=(const String& right);
    int Find(const String& pos);
    int kmp(String pat);
    void fail_func();
    void Print_Fail();
    void push_back(const char& val);
private:
    int* f;
    char* str;
    int capacity;
    int size;
};