// Copyright 2023 Leo Peckham

#include "src/parser/phrase.h"
#include "src/operators/operators.h"


std::vector<std::set<Token>> ORDER_OF_OPERATIONS = {
    {Token::TIMES, Token::SLASH},
    {Token::PLUS, Token::MINUS},
};


void create_tree(std::list<Node*>::iterator begin, std::list<Node*>::iterator end,
    // This function looks messy because of all of the pointers,
    // but it really isn't that bad. Maybe refactor to use less
    // pointers, or use unique_ptr in the future but! good for now

    std::list<Node*>* nodes) {
    using enum Token;

    // Parentheses
    int open_count = 0;
    // Keep track of what section the parentheses contain
    std::list<Node*>::iterator prio_begin;
    std::list<Node*>::iterator prio_end;
    for (std::list<Node*>::iterator node = begin; node != end; ++node) {
        if ((*node)->token == BEGIN_PRIORITY) {
            if (open_count == 0) {
                prio_begin = node;
            }
            ++open_count;
        } else if ((*node)->token == END_PRIORITY) {
            if (open_count == 1) {
                prio_end = node;
                // Evaluate what's in the parenthese, updating nodes
                create_tree(std::next(prio_begin), prio_end, nodes);
                // Delete parentheses, and free nodes since not in tree
                delete (*prio_begin); nodes->erase(prio_begin);
                delete (*prio_end); nodes->erase(prio_end);
                break;
            }
            --open_count;
        }
    }

    // Non-parentheses
    for (std::set<Token> operations : ORDER_OF_OPERATIONS) {
        for (std::list<Node*>::iterator node = begin; node != end; ++node) {
            if (operations.find((*node)->token) != operations.end()) {
                auto prev = std::prev(node);
                auto next = std::next(node);
                (*node)->left = *prev; (*node)->right = *next;
                nodes->erase(next);
                nodes->erase(prev);
            }
        }
    }
}


Node* Phrase::tree() {
    using enum Token;
    std::list<Node*> nodes;

    for (Token token : tokens) {
        nodes.push_back(new Node{ token });
    }

    create_tree(nodes.begin(), nodes.end(), &nodes);

    return nodes.front();
}


Literal Phrase::evaluate(bool terminating) {
    using enum Token;
    using enum Type;

    Literal left = Null();

    while (tokens.size() > 0) {
        Token current_token = tokens.front();
        tokens.pop_front();
        switch (current_token) {
        case BEGIN_PRIORITY:
            left = evaluate();
            break;
        case END_PRIORITY:
            goto end;
        case PLUS:
            left = OPERATOR_PLUS(left, evaluate(true));
            break;
        case MINUS:
            left = OPERATOR_MINUS(left, evaluate(true));
            break;
        case TIMES:
            left = OPERATOR_TIMES(left, evaluate(true));
            break;
        case SLASH:
            left = OPERATOR_SLASH(left, evaluate(true));
            break;
        case LITERAL:
            left = literals.front();
            literals.pop_front();
            if (terminating) {
                goto end;
            }
            else {
                break;
            }
        }
    }
end:
    // do some conversions down under certain circumstances
    if (std::holds_alternative<SN_real>(left)) {
        auto f = std::get<SN_real>(left);
        if (f == std::floor(f)) {
            left = static_cast<SN_int>(f);
        }
    }
    if (std::holds_alternative<Rational>(left)) {
        if (std::get<Rational>(left).denominator() == 1) {
            left = SN_int(std::get<Rational>(left));
        }
    }
    return left;
}
