//===--- EecsBoolDefineCheck.cpp - clang-tidy------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "EecsBoolDefineCheck.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/MacroArgs.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

namespace {
class BoolDefinePPCallbacks : public PPCallbacks {
public:
  BoolDefinePPCallbacks(ClangTidyCheck &Check, Preprocessor &PP)
      : Check(Check), PP(PP) {}

  void MacroDefined(const Token &MacroNameTok, const MacroDirective *MD) override;

private:
  ClangTidyCheck &Check;
  Preprocessor &PP;
};
}

void BoolDefinePPCallbacks::MacroDefined(const Token &MacroNameTok, const MacroDirective *MD) {
  const MacroInfo *MI = MD->getMacroInfo();
  const auto name = MacroNameTok.getIdentifierInfo()->getName();
  if (name == "TRUE" || name == "FALSE") {
    Check.diag(MI->getDefinitionLoc(), "Do not define TRUE or FALSE macros: %0") << MacroNameTok.getIdentifierInfo();
  }
}

void EecsBoolDefineCheck::registerPPCallbacks(
    CompilerInstance &Compiler) {
  Compiler.getPreprocessor().addPPCallbacks(
      ::llvm::make_unique<BoolDefinePPCallbacks>(
          *this, Compiler.getPreprocessor()));
}

} // namespace misc
} // namespace tidy
} // namespace clang
