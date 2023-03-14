// Copyright 2023 Leo Peckham

#include "src/parser/phrase.h"
#include "src/operators/operators.h"


std::vector<std::set<lexer::TokenID>> ORDER_OF_OPERATIONS = {
    {lexer::TokenID::TIMES, lexer::TokenID::SLASH},
    {lexer::TokenID::PLUS, lexer::TokenID::MINUS},
    {lexer::TokenID::PRINT, lexer::TokenID::DEBUG_PRINT},
};


void subtree(std::list<Node*>::iterator begin,
    std::list<Node*>::iterator end,
    std::list<Node*>* nodes) {
    using enum lexer::TokenID;

    // parens -> tree
    std::stack<std::list<Node*>::iterator> prio;
    for (auto i = std::next(begin); i != end; ++i) {
        if ((*i)->token.id == BEGIN_PRIORITY) {
            prio.push(i);
        } else if ((*i)->token.id == END_PRIORITY) {
            auto begin_prio = prio.top();
            auto end_prio = i;
            // TODO(padril): there's definitely a better way to do that
            // we do this weird ++i --i dance to keep the iterator valid
            ++i;
            subtree(begin_prio, end_prio, nodes);
            delete (*begin_prio); delete(*end_prio);
            nodes->erase(begin_prio); nodes->erase(end_prio);
            prio.pop();
            --i;
        }
    }

    if (nodes->size() <= 3) {
        return;
    }

    // L to R, groups pull in left nodes
    for (auto operations : ORDER_OF_OPERATIONS) {
        for (auto i = std::next(begin); i != end; ++i) {
            if (operations.contains((*i)->token.id)) {
                auto j = i;
                while ((*j)->token.id != LITERAL && (*j)->right == nullptr) {
                    ++j;
                }
                --j;
                while (j != i) {
                    (*j)->right = *std::next(j);
                    nodes->erase(std::next(j));
                    --j;
                }
                (*i)->right = *std::next(i);
                nodes->erase(std::next(i));
                if ((*i)->left == nullptr
                    && ((*std::prev(i))->token.id == LITERAL
                        || (*std::prev(i))->right != nullptr)) {
                    (*i)->left = *std::prev(i);
                    nodes->erase(std::prev(i));
                }
            }
        }
    }
}

Literal subevaluate(Node* head) {
    using enum lexer::TokenID;
    if (head == nullptr) {
        return Null();
    }

    switch (head->token.id) {
    case LITERAL:
        return *head->token.value;
    case PLUS:
        return OPERATOR_PLUS(subevaluate(head->left),
            subevaluate(head->right));
    case MINUS:
        return OPERATOR_MINUS(subevaluate(head->left),
            subevaluate(head->right));
    case TIMES:
        return OPERATOR_TIMES(subevaluate(head->left),
            subevaluate(head->right));
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


Node* Phrase::tree() {
    std::list<Node*> local_nodes;
    for (auto node : nodes) {
        local_nodes.push_back(new Node{node->token});
    }
    local_nodes.push_front(new Node{ {lexer::TokenID::BEGIN_PHRASE, std::nullopt } });
    local_nodes.push_back(new Node{ {lexer::TokenID::END_PHRASE, std::nullopt } });
    subtree(local_nodes.begin(), --local_nodes.end(), &local_nodes);
    delete(local_nodes.front()); delete(local_nodes.back());
    local_nodes.pop_front(); local_nodes.pop_back();
    return local_nodes.size() ? local_nodes.front() : new Node{ { lexer::TokenID::EMPTY, std::nullopt } };
}


Literal Phrase::evaluate(bool terminating) {
    Node* head = tree();
    Literal ret = subevaluate(head);
    return ret;
}
