//===--- EecsTypedefTCheck.cpp - clang-tidy--------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "EecsTypedefTCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void EecsTypedefTCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(typedefDecl().bind("x"), this);
}

void EecsTypedefTCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<TypedefDecl>("x");
  const SourceLocation loc = MatchedDecl->getBeginLoc();

  if (loc.isInvalid() || loc.isMacroID()) {
    return;
  }

  if (MatchedDecl->getName().endswith("_t") || MatchedDecl->isHidden()) {
    return;
  }
  diag(MatchedDecl->getLocation(), "typedefs must end in `_t` (%0)") << MatchedDecl;
}

} // namespace misc
} // namespace tidy
} // namespace clang
