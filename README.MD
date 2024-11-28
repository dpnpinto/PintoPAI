# Pinto Personal Artificial Inteligence (PintoPAI)
This project is for the instalation of Ollama in a container using PodMan
The Instalation is on Arch Linux, because I use it in my WorkStation
Later I will make a script to install in Rocky Linux and maybe Debian.
Why I use Podman ? Because at start docker have a systemd process allways runing (now I have install docker with sockts) and I like my workstation clean from processes that are not runing nothing.  

## Podman instalation


On Linux, control groups constrain resources that are allocated to processes.
There are two versions of cgroups in Linux: cgroup v1 and cgroup v2. cgroup v2 is the new generation of the cgroup API.
Arch Linux uses by default cgroups V1 and V2, for podman to run not only as root, and as we need cgroups V2 to install crun first we will force ARch to use only cgroups V2.

### Cgroup v2 offers several improvements over cgroup v1, such as the following:

* Single unified hierarchy design in API
* Safer sub-tree delegation to containers
* Newer features like Pressure Stall Information
* Enhanced resource allocation management and isolation across multiple resources
  * Unified accounting for different types of memory allocations (network memory, kernel memory, etc)
  * Accounting for non-immediate resource changes such as page cache write backs

For the instalation if you use GRUB as bootloader you just need to force the use only cgroup V2 at start of the system.
At the moment, as described in Arch wiki Arch Linux uses V2 as default, anyway I foce in GRUB to use only V2 with the kernel cgroup_no_v1="all"
For do that you have to edit de defaults for grub in /etc/default/grub, you can edit the file  with vim, and put the kernel parameter in GRUB_CMDLINE_LINUX_DEFAULT
And the just make grub config again with the new parameter with **sudo grub-mkconfig -o /boot/grub/grub.cfg** and the reboot

## Podman Desktop
 
After some options I tried Podman desktop and I like it because is the some interface for Linux, IOS and WIndows. As I will test the AI models in several desktops I use it.
The instalation is very simple and you can get it from https://podman-desktop.io.
You can install it from aur https://aur.archlinux.org/packages/podman-desktop or you can use flatpak https://flathub.org/apps/io.podman_desktop.PodmanDesktop
The podman desktop have a simple extenction in top of the podman desktop caled AI lab https://podman-desktop.io/docs/ai-lab.

## Install Ollama terminal

Refereces at https://ollama.com

curl -fsSL https://ollama.com/install.sh | sh

## Uninstall Ollama

Delete the Ollama binary:

Use the rm command to remove the Ollama binary. For example:
- sudo rm /usr/local/bin/ollama

If the script created a systemd service, disable and remove it:
If the script created a systemd service for Ollama, you should disable and remove it using the following commands:
- sudo systemctl stop ollama
- sudo systemctl disable ollama
- sudo rm /etc/systemd/system/ollama.service
- sudo systemctl daemon-reload

Remove any created user and group (if applicable):
The script might have created a user and group named "ollama." You can remove them using the following commands:

- sudo userdel ollama
- sudo groupdel ollama

## Easy mode for all grapic cards AMD/NVIDIA
You  have a very easy way to test LLM's with a GUI using [LM Studio](https://lmstudio.ai), you can download the binary from here https://lmstudio.ai/download
