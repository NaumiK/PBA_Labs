#ifndef LAB6_MLL_H
#define LAB6_MLL_H

#include <iostream>
#include <string>

struct Node {
    Node *next = nullptr;
    std::string NSF_, job_, place_;
};

std::istream &operator>>(std::istream &in, Node &n);
std::ostream &operator<<(std::ostream &out, const Node &n);
bool operator==(const Node &a, const Node &b);

class MLL {
    Node *first_ = nullptr, *last_ = nullptr;

public:
    const Node *begin() const;
    const Node *end()   const;
    const Node *last()  const;

public:
    bool empty() const;
    void r_f();
    void clean();
    void push_back(Node *node);
    ~MLL();
};

std::istream &operator>>(std::istream &in, MLL &mll);
std::ostream &operator<<(std::ostream &out, MLL &mll);
void MLL_print(const MLL &mll, std::ostream &out = std::cout, std::ostream &eout = std::cerr, std::ostream &qout = std::cout);
void MLL_printT(const MLL &mll, std::ostream &out = std::cout, std::ostream &eout = std::cerr, std::ostream &qout = std::cout);
uint64_t MLL_cnt_coincidences(const MLL &mll, std::string &s, uint64_t type);

#endif//LAB6_MLL_H
