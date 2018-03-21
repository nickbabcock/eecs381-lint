//===--- EecsEnumValueCapsCheck.cpp - clang-tidy---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "EecsEnumValueCapsCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include <algorithm>

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void EecsEnumValueCapsCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(enumConstantDecl().bind("x"), this);
}

void EecsEnumValueCapsCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *MatchedDecl = Result.Nodes.getNodeAs<EnumConstantDecl>("x");
  const SourceLocation loc = MatchedDecl->getLocStart();

  if (loc.isInvalid() || loc.isMacroID()) {
    return;
  }

  const auto name = MatchedDecl->getName();
  const bool isUpper = std::all_of(name.begin(), name.end(), [](char c) {
    return isupper(c);
  });

  if (isUpper || MatchedDecl->isHidden()) {
    return;
  }

  diag(MatchedDecl->getLocation(), "enum values must be uppercased (%0)") << MatchedDecl;
}

} // namespace misc
} // namespace tidy
} // namespace clang
