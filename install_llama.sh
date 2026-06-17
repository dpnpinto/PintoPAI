
# bash file to install llama.cpp in Arch Linux
# first  install the software to compile the llama.cpp
sudo pacman -S git base-devel cmake
# just to confirm the versions
gcc --version
cmake --version
git --version
# Download llama.cpp from github
git clone https://github.com/ggml-org/llama.cpp.git
cd llama.cpp
mkdir bulld
cd build
.....
