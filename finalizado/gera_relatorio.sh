#!/bin/bash

# Verifica se o arquivo de exemplo foi passado como argumento
if [ $# -eq 0 ]; then
    echo "Uso: $0 <caminho_do_arquivo_de_exemplo>"
    exit 1
fi

# Caminho do arquivo de exemplo
exemplo=$1

# Nome do arquivo de relatório
relatorio="relatorio.txt"

# Limpa o conteúdo anterior do relatório
> $relatorio

# Todas as combinações possíveis de opções
opcoes=("" "-a" "-o" "-f" "-a -o" "-a -f" "-o -f")

# Executa o programa com cada combinação de opções
for opcao in "${opcoes[@]}"; do
    echo "Executando: ./comissao $opcao < $exemplo" >> $relatorio
    ./comissao $opcao < $exemplo 2>> $relatorio
    echo -e "\n" >> $relatorio
done

echo "Relatório de erros gerado em $relatorio"
