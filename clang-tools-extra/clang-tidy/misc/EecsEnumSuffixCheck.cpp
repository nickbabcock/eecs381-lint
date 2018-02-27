//===--- EecsEnumSuffixCheck.cpp - clang-tidy------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "EecsEnumSuffixCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void EecsEnumSuffixCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(enumDecl().bind("x"), this);
}

void EecsEnumSuffixCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<EnumDecl>("x");
  const SourceLocation loc = MatchedDecl->getLocStart();

  if (loc.isInvalid() || loc.isMacroID()) {
    return;
  }

  if (MatchedDecl->getName().endswith("_e") || MatchedDecl->isHidden()) {
    return;
  }
  diag(MatchedDecl->getLocation(), "enum declarations must end in `_e` (%0)") << MatchedDecl;
}

} // namespace misc
} // namespace tidy
} // namespace clang
