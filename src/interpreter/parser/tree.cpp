// Copyright 2023 Leo Peckham

#include "src/interpreter/parser/tree.h"


namespace sno {

size_t Tree::size() {
    int count = 1;
    if (left != nullptr) {
        count += left->size();
    }
    if (right != nullptr) {
        count += right->size();
    }
    return count;
}


void subtree(std::list<Tree*>::iterator begin,
             std::list<Tree*>::iterator end,
             std::list<Tree*>* trees) {
    static std::vector<std::set<sno::TokenID>> ORDER_OF_OPERATIONS = {
        {sno::TokenID::TIMES, sno::TokenID::SLASH},
        {sno::TokenID::PLUS, sno::TokenID::MINUS},
        {sno::TokenID::PRINT, sno::TokenID::DEBUG_PRINT},
    };
    using enum sno::TokenID;

    // parens -> tree
    std::stack<std::list<Tree*>::iterator> prio;
    for (auto i = std::next(begin); i != end; ++i) {
        if ((*i)->root->id == BEGIN_PRIORITY) {
            prio.push(i);
        }
        else if ((*i)->root->id == END_PRIORITY) {
            auto begin_prio = prio.top();
            auto end_prio = i;
            // TODO(padril): there's definitely a better way to do that
            // we do this weird ++i --i dance to keep the iterator valid
            ++i;
            subtree(begin_prio, end_prio, trees);
            delete (*begin_prio); delete(*end_prio);
            trees->erase(begin_prio); trees->erase(end_prio);
            prio.pop();
            --i;
        }
    }

    if (trees->size() <= 3) {
        return;
    }

    // L to R, groups pull in left nodes
    for (auto operations : ORDER_OF_OPERATIONS) {
        for (auto i = std::next(begin); i != end; ++i) {
            if (operations.contains((*i)->root->id)) {
                auto j = i;
                ++j;
                while ((*j)->root->id != LITERAL && (*j)->right == nullptr) {
                    ++j;
                }
                --j;
                while (j != i) {
                    (*j)->right = *std::next(j);
                    trees->erase(std::next(j));
                    --j;
                }
                (*i)->right = *std::next(i);
                trees->erase(std::next(i));
                if ((*i)->left == nullptr
                    && ((*std::prev(i))->root->id == LITERAL
                        || (*std::prev(i))->right != nullptr)) {
                    (*i)->left = *std::prev(i);
                    trees->erase(std::prev(i));
                }
            }
        }
    }
}


Literal Tree::evaluate() {
    using enum sno::TokenID;
    Literal lval = left != nullptr ? left->evaluate() : Null();
    Literal rval = right != nullptr ? right->evaluate() : Null();

    switch (root->id) {
    case LITERAL:
        return *root->value;
    case PLUS:
        return OPERATOR_PLUS(lval, rval);
    case MINUS:
        return OPERATOR_MINUS(lval, rval);
    case TIMES:
        return OPERATOR_TIMES(lval, rval);
    case SLASH:
        return OPERATOR_SLASH(lval, rval);
    case PRINT:
        return OPERATOR_PRINT(lval, rval);
    }
}

Tree* create_tree(std::list<Tree*> trees) {
    std::list<Tree*> local_trees;
    for (auto tree : trees) {
        local_trees.push_back(new Tree{ tree->root });
    }
    local_trees.push_front(new Tree{ sno::Token{ sno::TokenID::BEGIN_PHRASE, std::nullopt } });
    local_trees.push_back(new Tree{ sno::Token{ sno::TokenID::END_PHRASE, std::nullopt } });
    subtree(local_trees.begin(), --local_trees.end(), &local_trees);
    delete(local_trees.front()); delete(local_trees.back());
    local_trees.pop_front(); local_trees.pop_back();
    return local_trees.size() ? local_trees.front() : new Tree{ sno::Token{ sno::TokenID::EMPTY, std::nullopt } };
}

std::wostream& operator<<(std::wostream& out, Tree tree)
{
    // TODO: insert return statement here
    return out;
}

}  // namespace sno
