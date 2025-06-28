#include "mips_code_generator.h"
#include <iostream>
#include <iomanip>

// ============================================================================
// Implementação do RegisterManager
// ============================================================================

RegisterManager::RegisterManager() {
    tempRegisters = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};
    for (int i = 0; i < tempRegisters.size(); i++) {
        availableRegs.push(i);
        regInUse[i] = false;
    }
}

std::string RegisterManager::allocateRegister() {
    if (availableRegs.empty()) {
        throw std::runtime_error("Nenhum registrador temporário disponível");
    }
    int regIndex = availableRegs.top();
    availableRegs.pop();
    regInUse[regIndex] = true;
    return tempRegisters[regIndex];
}

void RegisterManager::freeRegister(const std::string& reg) {
    for (int i = 0; i < tempRegisters.size(); i++) {
        if (tempRegisters[i] == reg && regInUse[i]) {
            regInUse[i] = false;
            availableRegs.push(i);
            return;
        }
    }
}

bool RegisterManager::isRegisterAvailable(const std::string& reg) {
    for (int i = 0; i < tempRegisters.size(); i++) {
        if (tempRegisters[i] == reg) {
            return !regInUse[i];
        }
    }
    return false;
}

void RegisterManager::freeAllRegisters() {
    while (!availableRegs.empty()) {
        availableRegs.pop();
    }
    for (int i = 0; i < tempRegisters.size(); i++) {
        availableRegs.push(i);
        regInUse[i] = false;
    }
}

std::string RegisterManager::getRegisterName(int index) {
    if (index >= 0 && index < tempRegisters.size()) {
        return tempRegisters[index];
    }
    return "";
}

// ============================================================================
// Implementação do MIPSCodeGenerator
// ============================================================================

MIPSCodeGenerator::MIPSCodeGenerator(PilhaTabelaSimbolos& symTable) 
    : symbolTable(symTable), currentStackOffset(0), labelCounter(0), stringCounter(0) {
    currentFunction = "";
}

// Métodos auxiliares para emissão de código
void MIPSCodeGenerator::emitInstruction(const std::string& op, const std::string& arg1, 
                                       const std::string& arg2, const std::string& arg3) {
    currentCode << "    " << op;
    if (!arg1.empty()) {
        currentCode << " " << arg1;
        if (!arg2.empty()) {
            currentCode << ", " << arg2;
            if (!arg3.empty()) {
                currentCode << ", " << arg3;
            }
        }
    }
    currentCode << std::endl;
}

void MIPSCodeGenerator::emitLabel(const std::string& label) {
    currentCode << label << ":" << std::endl;
}

void MIPSCodeGenerator::emitComment(const std::string& comment) {
    currentCode << "    # " << comment << std::endl;
}

void MIPSCodeGenerator::emitDataDirective(const std::string& label, const std::string& directive, 
                                         const std::string& value) {
    dataSection << label << ": " << directive << " " << value << std::endl;
}

std::string MIPSCodeGenerator::generateLabel(const std::string& prefix) {
    return prefix + "_" + std::to_string(labelCounter++);
}

std::string MIPSCodeGenerator::generateStringLabel() {
    return "str_" + std::to_string(stringCounter++);
}

// Métodos de conversão de tipos
int MIPSCodeGenerator::getTypeSize(SymbolType type) {
    switch (type) {
        case SymbolType::INT_TYPE: return 4;
        case SymbolType::CHAR_TYPE: return 1;
        default: return 4;
    }
}

std::string MIPSCodeGenerator::getLoadInstruction(SymbolType type) {
    switch (type) {
        case SymbolType::INT_TYPE: return "lw";
        case SymbolType::CHAR_TYPE: return "lb";
        default: return "lw";
    }
}

std::string MIPSCodeGenerator::getStoreInstruction(SymbolType type) {
    switch (type) {
        case SymbolType::INT_TYPE: return "sw";
        case SymbolType::CHAR_TYPE: return "sb";
        default: return "sw";
    }
}

// Métodos para gerenciamento de memória
void MIPSCodeGenerator::allocateLocalVariable(const std::string& name, SymbolType type) {
    int size = getTypeSize(type);
    currentStackOffset -= size;
    MIPSVariable var(name, type, false, currentStackOffset, size);
    localVariables[name] = var;
}

void MIPSCodeGenerator::allocateGlobalVariable(const std::string& name, SymbolType type) {
    int size = getTypeSize(type);
    MIPSVariable var(name, type, true, 0, size);
    globalVariables[name] = var;
    std::string directive = (type == SymbolType::INT_TYPE) ? ".word" : ".byte";
    emitDataDirective(name, directive, "0");
}

MIPSVariable* MIPSCodeGenerator::findVariable(const std::string& name) {
    auto localIt = localVariables.find(name);
    if (localIt != localVariables.end()) {
        return &localIt->second;
    }
    auto globalIt = globalVariables.find(name);
    if (globalIt != globalVariables.end()) {
        return &globalIt->second;
    }
    return nullptr;
}

std::string MIPSCodeGenerator::loadVariable(const std::string& varName) {
    MIPSVariable* var = findVariable(varName);
    if (!var) {
        throw std::runtime_error("Variável não encontrada: " + varName);
    }
    std::string reg = regManager.allocateRegister();
    std::string loadInstr = getLoadInstruction(var->type);
    if (var->isGlobal) {
        emitInstruction(loadInstr, reg, var->name);
    } else {
        emitInstruction(loadInstr, reg, std::to_string(var->offset) + "($sp)");
    }
    return reg;
}

void MIPSCodeGenerator::storeVariable(const std::string& varName, const std::string& reg) {
    MIPSVariable* var = findVariable(varName);
    if (!var) {
        throw std::runtime_error("Variável não encontrada: " + varName);
    }
    std::string storeInstr = getStoreInstruction(var->type);
    if (var->isGlobal) {
        emitInstruction(storeInstr, reg, var->name);
    } else {
        emitInstruction(storeInstr, reg, std::to_string(var->offset) + "($sp)");
    }
}

// Métodos para syscalls do SPIM
void MIPSCodeGenerator::generateSyscall(int syscallNumber) {
    emitInstruction("li", "$v0", std::to_string(syscallNumber));
    emitInstruction("syscall");
}

void MIPSCodeGenerator::generateReadInt() {
    generateSyscall(5);
}

void MIPSCodeGenerator::generateReadChar() {
    generateSyscall(12);
}

void MIPSCodeGenerator::generateWriteInt(const std::string& reg) {
    emitInstruction("move", "$a0", reg);
    generateSyscall(1);
}

void MIPSCodeGenerator::generateWriteChar(const std::string& reg) {
    emitInstruction("move", "$a0", reg);
    generateSyscall(11);
}

void MIPSCodeGenerator::generateWriteString(const std::string& stringLabel) {
    emitInstruction("la", "$a0", stringLabel);
    generateSyscall(4);
}

void MIPSCodeGenerator::generateWriteNewline() {
    std::string newlineLabel = generateStringLabel();
    emitDataDirective(newlineLabel, ".asciiz", "\"\\n\"");
    generateWriteString(newlineLabel);
}

void MIPSCodeGenerator::generateExit() {
    generateSyscall(10);
} // Métodos de geração de expressões
std::string MIPSCodeGenerator::generateExpression(std::shared_ptr<ASTNode> node) {
    if (!node) {
        throw std::runtime_error("Nó de expressão nulo");
    }
    
    switch (node->nodeType) {
        case NodeType::BINARY_OP_NODE:
            return generateBinaryOp(std::static_pointer_cast<BinaryOpNode>(node));
        case NodeType::UNARY_OP_NODE:
            return generateUnaryOp(std::static_pointer_cast<UnaryOpNode>(node));
        case NodeType::FUNC_CALL_NODE:
            return generateFuncCall(std::static_pointer_cast<FuncCallNode>(node));
        case NodeType::ID_NODE:
            return generateId(std::static_pointer_cast<IdNode>(node));
        case NodeType::INT_LITERAL_NODE:
            return generateIntLiteral(std::static_pointer_cast<IntLiteralNode>(node));
        case NodeType::CHAR_LITERAL_NODE:
            return generateCharLiteral(std::static_pointer_cast<CharLiteralNode>(node));
        default:
            throw std::runtime_error("Tipo de expressão não suportado");
    }
}

std::string MIPSCodeGenerator::generateBinaryOp(std::shared_ptr<BinaryOpNode> node) {
    BinaryOperator op = node->operator_;
    std::string leftReg = generateExpression(node->left);
    std::string rightReg = generateExpression(node->right);
    std::string resultReg;
    
    if (op == BinaryOperator::ADD || op == BinaryOperator::SUBTRACT || 
        op == BinaryOperator::MULTIPLY || op == BinaryOperator::DIVIDE) {
        resultReg = generateArithmeticOp(op, leftReg, rightReg);
    } else if (op == BinaryOperator::EQUAL || op == BinaryOperator::NOT_EQUAL ||
               op == BinaryOperator::LESS || op == BinaryOperator::GREATER ||
               op == BinaryOperator::LESS_EQUAL || op == BinaryOperator::GREATER_EQUAL) {
        resultReg = generateRelationalOp(op, leftReg, rightReg);
    } else if (op == BinaryOperator::AND || op == BinaryOperator::OR) {
        resultReg = generateLogicalOp(op, leftReg, rightReg);
    } else {
        throw std::runtime_error("Operador binário não suportado");
    }
    
    regManager.freeRegister(leftReg);
    regManager.freeRegister(rightReg);
    return resultReg;
}

std::string MIPSCodeGenerator::generateArithmeticOp(BinaryOperator op, const std::string& leftReg, 
                                                   const std::string& rightReg) {
    std::string resultReg = regManager.allocateRegister();
    
    switch (op) {
        case BinaryOperator::ADD:
            emitInstruction("add", resultReg, leftReg, rightReg);
            break;
        case BinaryOperator::SUBTRACT:
            emitInstruction("sub", resultReg, leftReg, rightReg);
            break;
        case BinaryOperator::MULTIPLY:
            emitInstruction("mul", resultReg, leftReg, rightReg);
            break;
        case BinaryOperator::DIVIDE:
            emitInstruction("div", leftReg, rightReg);
            emitInstruction("mflo", resultReg);
            break;
        default:
            throw std::runtime_error("Operador aritmético não suportado");
    }
    return resultReg;
}

std::string MIPSCodeGenerator::generateRelationalOp(BinaryOperator op, const std::string& leftReg, 
                                                   const std::string& rightReg) {
    std::string resultReg = regManager.allocateRegister();
    
    switch (op) {
        case BinaryOperator::LESS:
            emitInstruction("slt", resultReg, leftReg, rightReg);
            break;
        case BinaryOperator::GREATER:
            emitInstruction("slt", resultReg, rightReg, leftReg);
            break;
        case BinaryOperator::LESS_EQUAL:
            emitInstruction("slt", resultReg, rightReg, leftReg);
            emitInstruction("xori", resultReg, resultReg, "1");
            break;
        case BinaryOperator::GREATER_EQUAL:
            emitInstruction("slt", resultReg, leftReg, rightReg);
            emitInstruction("xori", resultReg, resultReg, "1");
            break;
        case BinaryOperator::EQUAL:
            emitInstruction("sub", resultReg, leftReg, rightReg);
            emitInstruction("sltiu", resultReg, resultReg, "1");
            break;
        case BinaryOperator::NOT_EQUAL:
            emitInstruction("sub", resultReg, leftReg, rightReg);
            emitInstruction("sltu", resultReg, "$zero", resultReg);
            break;
        default:
            throw std::runtime_error("Operador relacional não suportado");
    }
    return resultReg;
}

std::string MIPSCodeGenerator::generateLogicalOp(BinaryOperator op, const std::string& leftReg, 
                                                const std::string& rightReg) {
    std::string resultReg = regManager.allocateRegister();
    
    switch (op) {
        case BinaryOperator::AND:
            emitInstruction("and", resultReg, leftReg, rightReg);
            break;
        case BinaryOperator::OR:
            emitInstruction("or", resultReg, leftReg, rightReg);
            break;
        default:
            throw std::runtime_error("Operador lógico não suportado");
    }
    return resultReg;
}

std::string MIPSCodeGenerator::generateUnaryOp(std::shared_ptr<UnaryOpNode> node) {
    std::string operandReg = generateExpression(node->operand);
    std::string resultReg = regManager.allocateRegister();
    
    switch (node->operator_) {
        case UnaryOperator::MINUS:
            emitInstruction("neg", resultReg, operandReg);
            break;
        case UnaryOperator::NOT:
            emitInstruction("xori", resultReg, operandReg, "1");
            break;
        default:
            throw std::runtime_error("Operador unário não suportado");
    }
    
    regManager.freeRegister(operandReg);
    return resultReg;
}

std::string MIPSCodeGenerator::generateId(std::shared_ptr<IdNode> node) {
    return loadVariable(node->identifier);
}

std::string MIPSCodeGenerator::generateIntLiteral(std::shared_ptr<IntLiteralNode> node) {
    std::string reg = regManager.allocateRegister();
    emitInstruction("li", reg, std::to_string(node->value));
    return reg;
}

std::string MIPSCodeGenerator::generateCharLiteral(std::shared_ptr<CharLiteralNode> node) {
    std::string reg = regManager.allocateRegister();
    emitInstruction("li", reg, std::to_string((int)node->value));
    return reg;
}

std::string MIPSCodeGenerator::generateFuncCall(std::shared_ptr<FuncCallNode> node) {
    emitComment("Chamada de função: " + node->functionName);
    saveRegisters();
    
    for (size_t i = 0; i < node->arguments.size() && i < 4; i++) {
        std::string argReg = generateExpression(node->arguments[i]);
        emitInstruction("move", "$a" + std::to_string(i), argReg);
        regManager.freeRegister(argReg);
    }
    
    emitInstruction("jal", node->functionName);
    restoreRegisters();
    
    std::string resultReg = regManager.allocateRegister();
    emitInstruction("move", resultReg, "$v0");
    return resultReg;
}

// Métodos de geração de comandos
void MIPSCodeGenerator::generateStatement(std::shared_ptr<ASTNode> node) {
    if (!node) return;
    
    switch (node->nodeType) {
        case NodeType::ASSIGN_STMT_NODE:
            generateAssignStmt(std::static_pointer_cast<AssignStmtNode>(node));
            break;
        case NodeType::RETURN_STMT_NODE:
            generateReturnStmt(std::static_pointer_cast<ReturnStmtNode>(node));
            break;
        case NodeType::READ_STMT_NODE:
            generateReadStmt(std::static_pointer_cast<ReadStmtNode>(node));
            break;
        case NodeType::WRITE_STMT_NODE:
            generateWriteStmt(std::static_pointer_cast<WriteStmtNode>(node));
            break;
        case NodeType::WRITE_STRING_STMT_NODE:
            generateWriteStringStmt(std::static_pointer_cast<WriteStringStmtNode>(node));
            break;
        case NodeType::NEWLINE_STMT_NODE:
            generateNewlineStmt(std::static_pointer_cast<NewlineStmtNode>(node));
            break;
        case NodeType::IF_STMT_NODE:
        case NodeType::IF_ELSE_STMT_NODE:
            generateIfStmt(std::static_pointer_cast<IfStmtNode>(node));
            break;
        case NodeType::WHILE_STMT_NODE:
            generateWhileStmt(std::static_pointer_cast<WhileStmtNode>(node));
            break;
        case NodeType::BLOCK_NODE:
            generateBlock(std::static_pointer_cast<BlockNode>(node));
            break;
        case NodeType::EMPTY_STMT_NODE:
            break;
        default:
            throw std::runtime_error("Tipo de comando não suportado");
    }
}

void MIPSCodeGenerator::generateAssignStmt(std::shared_ptr<AssignStmtNode> node) {
    emitComment("Atribuição: " + node->identifier);
    std::string exprReg = generateExpression(node->expression);
    storeVariable(node->identifier, exprReg);
    regManager.freeRegister(exprReg);
}

void MIPSCodeGenerator::generateReturnStmt(std::shared_ptr<ReturnStmtNode> node) {
    emitComment("Return");
    if (node->expression) {
        std::string exprReg = generateExpression(node->expression);
        emitInstruction("move", "$v0", exprReg);
        regManager.freeRegister(exprReg);
    }
    emitInstruction("jr", "$ra");
}

void MIPSCodeGenerator::generateReadStmt(std::shared_ptr<ReadStmtNode> node) {
    emitComment("Leia: " + node->identifier);
    MIPSVariable* var = findVariable(node->identifier);
    if (!var) {
        throw std::runtime_error("Variável não encontrada: " + node->identifier);
    }
    
    if (var->type == SymbolType::INT_TYPE) {
        generateReadInt();
    } else if (var->type == SymbolType::CHAR_TYPE) {
        generateReadChar();
    }
    storeVariable(node->identifier, "$v0");
}

void MIPSCodeGenerator::generateWriteStmt(std::shared_ptr<WriteStmtNode> node) {
    emitComment("Escreva expressão");
    std::string exprReg = generateExpression(node->expression);
    
    if (node->expression->symbolType == SymbolType::INT_TYPE) {
        generateWriteInt(exprReg);
    } else if (node->expression->symbolType == SymbolType::CHAR_TYPE) {
        generateWriteChar(exprReg);
    }
    regManager.freeRegister(exprReg);
}

void MIPSCodeGenerator::generateWriteStringStmt(std::shared_ptr<WriteStringStmtNode> node) {
    emitComment("Escreva string");
    std::string stringLabel = generateStringLabel();
    emitDataDirective(stringLabel, ".asciiz", "\"" + node->stringLiteral + "\"");
    generateWriteString(stringLabel);
}

void MIPSCodeGenerator::generateNewlineStmt(std::shared_ptr<NewlineStmtNode> node) {
    emitComment("Nova linha");
    generateWriteNewline();
}

void MIPSCodeGenerator::generateIfStmt(std::shared_ptr<IfStmtNode> node) {
    emitComment("Comando if");
    std::string condReg = generateExpression(node->condition);
    std::string elseLabel = generateLabel("else");
    std::string endLabel = generateLabel("end_if");
    
    emitInstruction("beq", condReg, "$zero", node->elseStmt ? elseLabel : endLabel);
    regManager.freeRegister(condReg);
    
    generateStatement(node->thenStmt);
    
    if (node->elseStmt) {
        emitInstruction("j", endLabel);
        emitLabel(elseLabel);
        generateStatement(node->elseStmt);
    }
    emitLabel(endLabel);
}

void MIPSCodeGenerator::generateWhileStmt(std::shared_ptr<WhileStmtNode> node) {
    emitComment("Comando while");
    std::string loopLabel = generateLabel("while_loop");
    std::string endLabel = generateLabel("end_while");
    
    emitLabel(loopLabel);
    std::string condReg = generateExpression(node->condition);
    emitInstruction("beq", condReg, "$zero", endLabel);
    regManager.freeRegister(condReg);
    
    generateStatement(node->body);
    emitInstruction("j", loopLabel);
    emitLabel(endLabel);
} // Métodos de geração de declarações
void MIPSCodeGenerator::generateVarDecl(std::shared_ptr<VarDeclNode> node, bool isGlobal) {
    for (const std::string& identifier : node->identifiers) {
        if (isGlobal) {
            allocateGlobalVariable(identifier, node->varType);
        } else {
            allocateLocalVariable(identifier, node->varType);
        }
    }
}

void MIPSCodeGenerator::generateFuncDecl(std::shared_ptr<FuncDeclNode> node) {
    emitComment("Função: " + node->functionName);
    emitLabel(node->functionName);
    
    enterFunction(node->functionName);
    
    // Processa parâmetros
    if (node->parameters) {
        auto paramList = std::static_pointer_cast<ParamListNode>(node->parameters);
        for (size_t i = 0; i < paramList->parameters.size(); i++) {
            auto param = std::static_pointer_cast<ParamNode>(paramList->parameters[i]);
            allocateLocalVariable(param->paramName, param->paramType);
            
            // Move parâmetro do registrador de argumento para a pilha
            if (i < 4) {
                std::string argReg = "$a" + std::to_string(i);
                storeVariable(param->paramName, argReg);
            }
        }
    }
    
    // Gera corpo da função
    generateBlock(std::static_pointer_cast<BlockNode>(node->body), true);
    
    // Se não houver return explícito, adiciona um
    if (node->returnType == SymbolType::VOID_TYPE) {
        emitInstruction("jr", "$ra");
    }
    
    exitFunction();
}

void MIPSCodeGenerator::generateBlock(std::shared_ptr<BlockNode> node, bool isFunctionBlock) {
    if (!isFunctionBlock) {
        enterScope();
    }
    
    // Gera declarações de variáveis locais
    for (auto varDecl : node->localVars) {
        generateVarDecl(std::static_pointer_cast<VarDeclNode>(varDecl), false);
    }
    
    // Gera comandos
    for (auto stmt : node->statements) {
        generateStatement(stmt);
    }
    
    if (!isFunctionBlock) {
        exitScope();
    }
}

void MIPSCodeGenerator::generateProgram(std::shared_ptr<ProgramNode> node) {
    generateProgramHeader();
    
    // Gera declarações globais
    for (auto decl : node->declarations) {
        if (decl->nodeType == NodeType::VAR_DECL_NODE) {
            generateVarDecl(std::static_pointer_cast<VarDeclNode>(decl), true);
        } else if (decl->nodeType == NodeType::FUNC_DECL_NODE) {
            // Funções são processadas na seção .text
            textSection << currentCode.str();
            currentCode.str("");
            currentCode.clear();
            
            generateFuncDecl(std::static_pointer_cast<FuncDeclNode>(decl));
            
            textSection << currentCode.str();
            currentCode.str("");
            currentCode.clear();
        }
    }
    
    // Gera função main
    generateMainFunction();
    generateBlock(std::static_pointer_cast<BlockNode>(node->mainBlock));
    generateProgramFooter();
    
    textSection << currentCode.str();
}

// Métodos para gerenciamento de pilha e contexto
void MIPSCodeGenerator::enterFunction(const std::string& funcName) {
    currentFunction = funcName;
    localVarStack.push(localVariables);
    stackOffsetStack.push(currentStackOffset);
    localVariables.clear();
    currentStackOffset = 0;
}

void MIPSCodeGenerator::exitFunction() {
    if (!localVarStack.empty()) {
        localVariables = localVarStack.top();
        localVarStack.pop();
    }
    if (!stackOffsetStack.empty()) {
        currentStackOffset = stackOffsetStack.top();
        stackOffsetStack.pop();
    }
    currentFunction = "";
}

void MIPSCodeGenerator::enterScope() {
    // Para blocos dentro de funções
}

void MIPSCodeGenerator::exitScope() {
    // Restaura o estado das variáveis locais
}

void MIPSCodeGenerator::saveRegisters() {
    emitComment("Salvando registradores");
    emitInstruction("addi", "$sp", "$sp", "-40");  // 10 registradores * 4 bytes
    
    for (int i = 0; i < 10; i++) {
        std::string reg = "$t" + std::to_string(i);
        std::string offset = std::to_string(i * 4);
        emitInstruction("sw", reg, offset + "($sp)");
    }
}

void MIPSCodeGenerator::restoreRegisters() {
    emitComment("Restaurando registradores");
    
    for (int i = 0; i < 10; i++) {
        std::string reg = "$t" + std::to_string(i);
        std::string offset = std::to_string(i * 4);
        emitInstruction("lw", reg, offset + "($sp)");
    }
    
    emitInstruction("addi", "$sp", "$sp", "40");
}

// Métodos para inicialização do programa
void MIPSCodeGenerator::generateProgramHeader() {
    dataSection << ".data" << std::endl;
    textSection << ".text" << std::endl;
    textSection << ".globl main" << std::endl;
}

void MIPSCodeGenerator::generateMainFunction() {
    currentCode << std::endl;
    emitLabel("main");
    emitComment("Início do programa principal");
}

void MIPSCodeGenerator::generateProgramFooter() {
    emitComment("Fim do programa");
    generateExit();
}

// Método principal de geração
std::string MIPSCodeGenerator::generate(std::shared_ptr<ASTNode> root) {
    if (!root || root->nodeType != NodeType::PROGRAM_NODE) {
        throw std::runtime_error("Nó raiz deve ser um ProgramNode");
    }
    
    auto programNode = std::static_pointer_cast<ProgramNode>(root);
    generateProgram(programNode);
    
    return getCompleteCode();
}

// Métodos para obter o código gerado
std::string MIPSCodeGenerator::getDataSection() const {
    return dataSection.str();
}

std::string MIPSCodeGenerator::getTextSection() const {
    return textSection.str();
}

std::string MIPSCodeGenerator::getCompleteCode() const {
    std::stringstream complete;
    complete << dataSection.str() << std::endl;
    complete << textSection.str() << std::endl;
    return complete.str();
}

// Métodos de debug
void MIPSCodeGenerator::printVariables() const {
    std::cout << "=== Variáveis Globais ===" << std::endl;
    for (const auto& pair : globalVariables) {
        const MIPSVariable& var = pair.second;
        std::cout << var.name << " (" << (var.type == SymbolType::INT_TYPE ? "int" : "char") 
                  << ", " << var.size << " bytes)" << std::endl;
    }
    
    std::cout << "=== Variáveis Locais ===" << std::endl;
    for (const auto& pair : localVariables) {
        const MIPSVariable& var = pair.second;
        std::cout << var.name << " (" << (var.type == SymbolType::INT_TYPE ? "int" : "char") 
                  << ", offset: " << var.offset << ", " << var.size << " bytes)" << std::endl;
    }
}

void MIPSCodeGenerator::printFunctions() const {
    std::cout << "=== Funções ===" << std::endl;
    for (const auto& pair : functions) {
        const FunctionInfo& func = pair.second;
        std::cout << func.name << " -> " << (func.returnType == SymbolType::INT_TYPE ? "int" : 
                     func.returnType == SymbolType::CHAR_TYPE ? "char" : "void") << std::endl;
        std::cout << "  Parâmetros: ";
        for (const auto& param : func.parameters) {
            std::cout << param.first << "(" << (param.second == SymbolType::INT_TYPE ? "int" : "char") << ") ";
        }
        std::cout << std::endl;
    }
} 