#!/bin/bash
figlet PintoPAI
echo "-----------------------------------------"
echo "# Pinto Personal Artificial Inteligence #"
echo "-----------------------------------------"
echo
sudo systemctl start ollama.service
while true; do
	read -r -p ">>> " pergunta
#	echo ollama run llama3.1 $pergunta | festival --tts
	resposta=$(ollama run llama3.1 $pergunta)
	echo $resposta
	echo $resposta | festival --tts
done
sudo systemctl stop ollama.service
