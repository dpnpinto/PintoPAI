#!/bin/bash
figlet PintoPAI
echo "-----------------------------------------"
echo "# Pinto Personal Artificial Inteligence #"
echo "-----------------------------------------"
echo
while true; do
	read -rep ">>> " pergunta
	resposta=$(ollama run llama3.1 "$pergunta")
	echo "--------------------------------------"
	echo "$resposta"
	echo "--------------------------------------"
	echo "$resposta" | festival --tts
done
