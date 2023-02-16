// Copyright 2023 Leo Peckham

#include "src/parser/phrase.h"
#include "src/operators/operators.h"


std::vector<std::set<Token>> ORDER_OF_OPERATIONS = {
    {Token::PRINT},
    {Token::TIMES, Token::SLASH},
    {Token::PLUS, Token::MINUS},
};




void subtree(std::list<Node*>::iterator begin,
    std::list<Node*>::iterator end,
    std::list<Node*>* nodes) {
    using enum Token;

    // parens -> tree
    std::stack<std::list<Node*>::iterator> prio;
    for (auto i = std::next(begin); i != end; ++i) {
        if ((*i)->token == BEGIN_PRIORITY) {
            prio.push(i);
        } else if ((*i)->token == END_PRIORITY) {
            auto begin_prio = prio.top();
            auto end_prio = i;
            // we do this weird ++i --i dance to keep the iterator valid
            ++i;
            subtree(begin_prio, end_prio, nodes);
            delete (*begin_prio); delete(*end_prio);
            nodes->erase(begin_prio); nodes->erase(end_prio);
            prio.pop();
            --i;
        }
    }

    // L to R, groups pull in left nodes
    for (auto operations : ORDER_OF_OPERATIONS) {
        for (auto i = std::next(begin); i != end; ++i) {
            if (operations.contains((*i)->token)) {
                auto j = i;
                while ((*j)->token != LITERAL && (*j)->right == nullptr) {
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
                    && ((*std::prev(i))->token == LITERAL
                        || (*std::prev(i))->right != nullptr)) {
                    (*i)->left = *std::prev(i);
                    nodes->erase(std::prev(i));
                }
            }
        }
    }
}

Literal subevaluate(Node* head) {
    using enum Token;
    if (head == nullptr) {
        return Null();
    }

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


Node* Phrase::tree() {
    std::list<Node*> local_nodes;
    for (auto node : nodes) {
        local_nodes.push_back(new Node{node->token, node->value});
    }
    local_nodes.push_front(new Node{ Token::BEGIN_PHRASE, Null() });
    local_nodes.push_back(new Node{ Token::END_PHRASE, Null() });
    subtree(local_nodes.begin(), --local_nodes.end(), &local_nodes);
    delete(local_nodes.front()); delete(local_nodes.back());
    local_nodes.pop_front(); local_nodes.pop_back();
    return local_nodes.front();
}


Literal Phrase::evaluate(bool terminating) {
    Node* head = tree();
    Literal ret = subevaluate(head);
    return ret;
}
