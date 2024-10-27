#!/bin/bash
# Yes I like robotic voice in my Ollama, Like War Games from 1983
# To run this you have to install Ollama, festival and figlet for the lertes ;)
# by dpnpinto.github.io/
# As the others projects, desclaymer, use at your own risk :)
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
