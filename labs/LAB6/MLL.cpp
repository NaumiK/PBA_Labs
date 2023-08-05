#include "MLL.h"
#include "MExc.h"
#include <iomanip>

std::istream &operator>>(std::istream &in, Node &n) {
    try {
        std::getline(in, n.NSF_, '$');
        std::getline(in, n.job_, '$');
        std::getline(in, n.place_, '$');
    }
    catch (std::exception &err) {}
    return in;
}

bool operator==(const Node &a, const Node &b) {
    return a.NSF_ == b.NSF_ && a.job_ == b.job_ && a.place_ == b.place_;
}

std::ostream &operator<<(std::ostream &out, Node &n) {
    out << "{"
        << "\"Full name\": " << "\"" << n.NSF_ << "\"" << ", "
        << "\"Job\": " << "\"" << n.job_ << "\"" << ", "
        << "\"Place\": " << "\"" << n.place_ << "\"" << "}";
    return out;
}

bool MLL::empty() {
    return first_ == nullptr;
}

void MLL::r_f() {
    if (empty()) return;
    Node *p = first_;
    first_ = p->next;
    delete p;
}

void MLL::clean() {
    while (!empty()) r_f();
}

void MLL::print(std::ostream &out, std::ostream &eout, std::ostream &qout) {
    for (Node *p = first_; p != nullptr; p = p->next)
        out << *p << ", ";
}

void MLL::printT(std::ostream &out, std::ostream &eout, std::ostream &qout) {
    out << std::setw(32) << std::left << "Full name"
        << std::setw(32) << std::left << "Job"
        << std::setw(32) << std::left << "Place" << '\n';
    for (Node *p = first_; p != nullptr; p = p->next)
        out << std::left << std::setw(32) << p->NSF_
            << std::left << std::setw(32) << p->job_
            << std::left << std::setw(32) << p->place_ << '\n';
    out << std::endl;
}

void MLL::push_back(Node *node) {
    if (empty()) {
        first_ = node;
        last_ = node;
        return;
    }
    last_->next = node;
    last_ = node;
}

uint64_t MLL::cnt(std::string &s, uint64_t type) {
    uint64_t res = 0;
    if (type > 2) throw MExc::NotThatType();
    for (Node *p = first_; p != nullptr; p = p->next) {
        std::string *ss[] = {&p->NSF_, &p->job_, &p->place_};
        if (s == *ss[type]) ++res;
    }
    return res;
}

MLL::~MLL() {
    clean();
}

std::istream &operator>>(std::istream &in, MLL &mll) {
    Node *n = new Node;
    in >> *n;
    mll.push_back(n);
    return in;
}

std::ostream &operator<<(std::ostream &out, MLL &mll) {
    for (const Node *p = mll.first_; p != nullptr; p = p->next)
        out << p->NSF_ << "$" << p->job_ << "$" << p->place_ << (p != mll.last_ ? "$" : "");
    return out;
}
