#ifndef LAB6_MLL_H
#define LAB6_MLL_H

#include <iostream>
#include <string>

struct Node {
    Node *next = nullptr;
    std::string NSF_, job_, place_;
    friend std::istream &operator>>(std::istream &in, Node &n);
    friend bool operator==(const Node &a, const Node &b);
    friend std::ostream &operator<<(std::ostream &out, Node &n);
};

class MLL {
    Node *first_ = nullptr, *last_ = nullptr;

public:
    bool empty();
    void r_f();
    void clean();
    void print(std::ostream &out = std::cout, std::ostream &eout = std::cerr, std::ostream &qout = std::cout);
    void printT(std::ostream &out = std::cout, std::ostream &eout = std::cerr, std::ostream &qout = std::cout);
    void push_back(Node *node);
    uint64_t cnt(std::string &s, uint64_t type);
    ~MLL();

    friend std::istream &operator>>(std::istream &in, MLL &mll);
    friend std::ostream &operator<<(std::ostream &out, MLL &mll);
};


#endif//LAB6_MLL_H
