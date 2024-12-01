#!/bin/bash
figlet PintoPAI
echo "-----------------------------------------"
echo "# Pinto Personal Artificial Inteligence #"
echo "-----------------------------------------"
echo
while true; do
	read -rep ">>> " pergunta
	echo "--------------------------------------"
#	echo ollama run llama3.1 $pergunta | festival --tts        
	resposta=$(ollama run llama3.1 $pergunta)
	echo "--------------------------------------"
	echo $resposta
	echo "--------------------------------------"
	echo $resposta | festival --tts
done
