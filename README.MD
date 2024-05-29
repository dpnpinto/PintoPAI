# Pinto Personal Artificial Inteligence (PintoPAI)
This project is for the instlation of Ollama with container using PodMan
The Instalation is on Arch Linux, because I use it in my worKstation
Later will make a script to install in Rocky Linux and Debian

## Podman instlation


On Linux, control groups constrain resources that are allocated to processes.
There are two versions of cgroups in Linux: cgroup v1 and cgroup v2. cgroup v2 is the new generation of the cgroup API.
ARch Linux uses by default cgroups V1 and V2, for podaman to run not only as root, and we need cgroups V2 for install crun first we will force ARch to use only cgroups V2.
Cgroup v2 offers several improvements over cgroup v1, such as the following:

* Single unified hierarchy design in API
* Safer sub-tree delegation to containers
* Newer features like Pressure Stall Information
* Enhanced resource allocation management and isolation across multiple resources
         ** Unified accounting for different types of memory allocations (network memory, kernel memory, etc)
         ** Accounting for non-immediate resource changes such as page cache write backs

For the instlation if you use GRUB as bootloader you just need to force the use of c group V2 at start of the system.
