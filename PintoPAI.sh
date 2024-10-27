#!/bin/bash
figlet PintoPAI
echo "-----------------------------------------"
echo "# Pinto Personal Artificial Inteligence #"
echo "-----------------------------------------"
echo
while true; do
	read -r -p ">>> " pergunta
#	echo ollama run llama3.1 $pergunta | festival --tts
	resposta=$(ollama run llama3.1 $pergunta)
	echo $resposta
	echo $resposta | festival --tts
done
