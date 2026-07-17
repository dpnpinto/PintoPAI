# My Local LLM Setup: llama.cpp, Docker and Arch Linux - The Zezoca
I use [local LLMs](https://huggingface.co) for various tasks, especially integrated with Vim. These days, I prefer [llama.cpp](https://llama-cpp.com) because it is open-source, written in C++, 
and serves as the core for many other tools. In this repository, I will share my configurations and document my workflow, which 
relies primarily on [Docker](https://www.docker.com) running on [Arch Linux](https://archlinux.org) (yes Zezoca in Arch Linux is nice and's stable as a rock :D).

## [Youtube Video](https://youtu.be/tPE8WkHRAcs?si=OaUuqnnhe4Dw3bSk) 

Every time you update the drivers dont forget to update NVIDIA CDI - nvidia-container-toolkit

Example:

WARNING: updating nvidia-utils version (580.159.04 -> 580.173.02) in /etc/cdi/nvidia.yaml using plain string substitution.
 -> If you meet problems, run the following command to regenerate the CDI file:
    nvidia-ctk cdi generate --output="/etc/cdi/nvidia.yaml"
