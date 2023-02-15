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

    auto current_literal = literals.begin();
    Literal value;

    nodes.push_back(new Node{ BEGIN_PRIORITY });
    for (Token token : tokens) {
        if (token == LITERAL) {
            value = *current_literal;
            ++current_literal;
        }
        else {
            value = Literal(Null{});
        }
        nodes.push_back(new Node{ token, value });
    }
    nodes.push_back(new Node{ END_PRIORITY });

    create_tree(&nodes);

    return nodes.front();
}

Literal subevaluate(Node* head) {
    using enum Token;

    switch (head->token) {
    case LITERAL:
        return head->value;
    case PLUS:
        return OPERATOR_PLUS(subevaluate(head->left),
            subevaluate(head->right));
    case MINUS:
        return OPERATOR_MINUS(subevaluate(head->left),
            subevaluate(head->right));
    case TIMES:
        return OPERATOR_TIMES(subevaluate(head->left),
            subevaluate(head->right));
        break;
    case SLASH:
        return OPERATOR_SLASH(subevaluate(head->left),
            subevaluate(head->right));
    case PRINT:
        return OPERATOR_PRINT(subevaluate(head->left),
            subevaluate(head->right));
    case DEBUG_PRINT:
        return OPERATOR_DEBUG_PRINT(subevaluate(head->left),
            subevaluate(head->right));
    }
}

Literal Phrase::evaluate(bool terminating) {
    Node* head = tree();
    return subevaluate(head);
}
