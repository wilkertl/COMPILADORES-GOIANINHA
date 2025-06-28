#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}=== EXECUTANDO TESTES SEMÂNTICOS ===${NC}"
echo

# Check if compiler exists
if [ ! -f "./goianinha" ]; then
    echo -e "${RED}Erro: Compilador 'goianinha' não encontrado. Execute 'make' primeiro.${NC}"
    exit 1
fi

# Check if test directory exists
if [ ! -d "semantico_testes" ]; then
    echo -e "${RED}Erro: Diretório 'semantico_testes' não encontrado.${NC}"
    exit 1
fi

# Counter for tests
total_tests=0
passed_tests=0
failed_tests=0

echo -e "${YELLOW}Diretório de testes: semantico_testes/${NC}"
echo -e "${YELLOW}Compilador: ./goianinha${NC}"
echo

# Function to run a single test
run_test() {
    local test_file="$1"
    local expected_result="$2"  # "success" or "error"
    local test_name=$(basename "$test_file" .txt)
    
    echo -e "${BLUE}Testando: ${test_name}${NC}"
    echo "Arquivo: $test_file"
    
    # Run the compiler and capture output
    output=$(./goianinha "$test_file" 2>&1)
    exit_code=$?
    
    echo "Saída do compilador:"
    echo "$output"
    
    # Check result based on expected outcome
    if [ "$expected_result" = "success" ]; then
        if [ $exit_code -eq 0 ] && echo "$output" | grep -q "Análise semântica concluída com sucesso"; then
            echo -e "${GREEN}✅ PASSOU - Compilação bem-sucedida como esperado${NC}"
            ((passed_tests++))
        else
            echo -e "${RED}❌ FALHOU - Esperava sucesso, mas houve erro${NC}"
            ((failed_tests++))
        fi
    else
        if [ $exit_code -ne 0 ] || echo "$output" | grep -q "Erro semântico"; then
            echo -e "${GREEN}✅ PASSOU - Erro semântico detectado como esperado${NC}"
            ((passed_tests++))
        else
            echo -e "${RED}❌ FALHOU - Esperava erro semântico, mas compilou com sucesso${NC}"
            ((failed_tests++))
        fi
    fi
    
    ((total_tests++))
    echo
    echo "----------------------------------------"
    echo
}

# Run tests for correct programs (should succeed)
echo -e "${YELLOW}=== TESTES QUE DEVEM PASSAR (SEM ERROS SEMÂNTICOS) ===${NC}"
echo

if [ -f "semantico_testes/expressao1Correto.txt" ]; then
    run_test "semantico_testes/expressao1Correto.txt" "success"
fi

if [ -f "semantico_testes/fatorialCorreto.txt" ]; then
    run_test "semantico_testes/fatorialCorreto.txt" "success"
fi

# Run tests for incorrect programs (should fail with semantic errors)
echo -e "${YELLOW}=== TESTES QUE DEVEM FALHAR (COM ERROS SEMÂNTICOS) ===${NC}"
echo

if [ -f "semantico_testes/fatorialErroLin3NomeDeclaradoNoMesmoEscopo.txt" ]; then
    run_test "semantico_testes/fatorialErroLin3NomeDeclaradoNoMesmoEscopo.txt" "error"
fi

if [ -f "semantico_testes/fatorialErroLin4TipoRetornado.txt" ]; then
    run_test "semantico_testes/fatorialErroLin4TipoRetornado.txt" "error"
fi

if [ -f "semantico_testes/fatorialErroLin5TipoRetornado.txt" ]; then
    run_test "semantico_testes/fatorialErroLin5TipoRetornado.txt" "error"
fi

# Summary
echo -e "${BLUE}=== RESUMO DOS TESTES ===${NC}"
echo -e "Total de testes: ${BLUE}$total_tests${NC}"
echo -e "Testes que passaram: ${GREEN}$passed_tests${NC}"
echo -e "Testes que falharam: ${RED}$failed_tests${NC}"

if [ $failed_tests -eq 0 ]; then
    echo -e "${GREEN}🎉 Todos os testes passaram!${NC}"
    exit 0
else
    echo -e "${RED}⚠️  Alguns testes falharam. Verifique a implementação.${NC}"
    exit 1
fi 