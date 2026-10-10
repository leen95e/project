#include "optimizer.h"

std::unique_ptr<Expr> fold(std::unique_ptr<Expr> e)
{
    auto * b = dynamic_cast<BinaryExpr*>(e.get());
    if (b == nullptr){
        return e;
    }
    b->left = fold(std::move(b->left));
    b->right = fold(std::move(b->right));
    NumberExpr * l = dynamic_cast<NumberExpr*>(b->left.get());
    NumberExpr * r = dynamic_cast<NumberExpr*>(b->right.get());
    if (l && r){
        switch (b->op)
        {
        case '+':
            return std::make_unique<NumberExpr> (l->value + r->value);
        case '-':
            return std::make_unique<NumberExpr> (l->value - r->value);
        case '*':
            return std::make_unique<NumberExpr> (l->value * r->value);
        case '/':
            if (r->value){
                return std::make_unique<NumberExpr> (l->value / r->value);
            }else{
                return e;
            } 
        default:
            break;
        }
    }
    return e;
}

void optimize(Program &program)
{
    for (Assign& as : program){
        as.value = fold(std::move(as.value));
    }
}
