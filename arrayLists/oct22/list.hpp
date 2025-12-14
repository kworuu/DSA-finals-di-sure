class List {
public:
    virtual void add(int num) = 0;
    virtual void addAt(int pos, int num) = 0;
    virtual void remove(int num) = 0;
    virtual int removeAt(int pos) = 0;
    virtual int removeAll(int num) = 0;
    virtual int sumOfAll() = 0;
    virtual void print() = 0;
};
