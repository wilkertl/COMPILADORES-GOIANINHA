#ifndef MIPS_GENERATOR_H
#define MIPS_GENERATOR_H

#include "ast.h"

// Gerador de código MIPS
void generate_mips_code(ASTNode* root, const char* output_file);

#endif 