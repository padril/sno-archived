// Copyright 2023 Leo Peckham

#include "src/parser/phrase.h"
#include "src/operators/operators.h"


std::vector<std::set<Token>> ORDER_OF_OPERATIONS = {
    {Token::PRINT},
    {Token::TIMES, Token::SLASH},
    {Token::PLUS, Token::MINUS},
};


void create_subtree(std::list<Node*>::iterator begin, std::list<Node*>::iterator end,
    std::list<Node*>* nodes) {
    // Non-parentheses
    for (std::set<Token> operations : ORDER_OF_OPERATIONS) {
        for (std::list<Node*>::iterator node = std::next(begin);
            node != end; ++node) {
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

void create_tree(std::list<Node*>* nodes) {
    // This function looks messy because of all of the pointers,
    // but it really isn't that bad. Maybe refactor to use less
    // pointers, or use unique_ptr in the future but! good for now
    using enum Token;


    auto begin = nodes->begin();
    auto end = nodes->end();

    // Use a stack to figure out parentheses order
    // initialize it with the entire phrase
    std::stack<std::list<Node*>::iterator> stack;
    // Don't increment node here, so that we can choose when, and not
    // invalidate iterators
    for (std::list<Node*>::iterator node = begin; node != end;) {
        if ((*node)->token == BEGIN_PRIORITY) {
            stack.push(node);
            ++node;
        } else if ((*node)->token == END_PRIORITY) {
            auto subbegin = stack.top();
            auto subend = node;
            ++node;
            create_subtree(subbegin, subend, nodes);
            delete(*subbegin); delete(*subend);
            nodes->erase(subbegin); nodes->erase(subend);
            stack.pop();
        }
        else {
            ++node;
        }
    }
}


Node* Phrase::tree() {
    using enum Token;
    std::list<Node*> nodes;

    nodes.push_back(new Node{ BEGIN_PRIORITY });
    for (Token token : tokens) {
        nodes.push_back(new Node{ token });
    }
    nodes.push_back(new Node{ END_PRIORITY });

    create_tree(&nodes);

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
