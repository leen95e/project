#pragma once
#include "ast.h"

// Constant folding: every sub-tree whose value is known at compile time
// is replaced by a single NumberExpr.
std::unique_ptr<Expr> fold(std::unique_ptr<Expr> e);

// Runs fold on every statement of the program.
void optimize(Program& program);