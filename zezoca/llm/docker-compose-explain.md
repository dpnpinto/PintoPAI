# Docker Compose YAML Breakdown: llama.cpp Server

This document provides a line-by-line explanation of the provided Docker Compose configuration for running a `llama.cpp` server with a Qwen3-Coder model using Nvidia GPUs.

```yaml
services:
  llama-server:
    image: ghcr.io/ggml-org/llama.cpp:server-cuda
    container_name: llama-cpp-cuda
    restart: unless-stopped
    ports:
      - "8080:8080"
    volumes:
      - ./models:/models
    command: >
      --model /models/Qwen3-Coder-30B-A3B-Instruct-Q5_K_M.gguf
      --host 0.0.0.0
      --port 8080
      --ctx-size 4096
      --batch-size 4096
      --ubatch-size 4096
      --threads 4
      --n-gpu-layers -1
      --cache-type-k q8_0
      --cache-type-v q8_0
      --flash-attn on
      --no-mmap
    deploy:
      resources:
        reservations:
          devices:
            - driver: nvidia
              count: all
              capabilities: [gpu]
```

## Explanation of Each Line

### Service Definition
*   **`services:`** 
    The root element that defines the different containers (services) that make up your application.
*   **`llama-server:`** 
    The logical name of this specific service. You can use this name to reference the service in other parts of the Docker Compose file or via command-line tools.

### Container Configuration
*   **`image: ghcr.io/ggml-org/llama.cpp:server-cuda`** 
    Specifies the Docker image to use. Here, it pulls the official `llama.cpp` server image built with CUDA (NVIDIA GPU) support from the GitHub Container Registry.
*   **`container_name: llama-cpp-cuda`** 
    Assigns a custom, readable name to the running container instead of letting Docker auto-generate a random name.
*   **`restart: unless-stopped`** 
    Sets the restart policy. The container will automatically restart if it crashes or if the host machine reboots, unless it was explicitly stopped by the user.

### Networking & Storage
*   **`ports:`** 
    Begins the section for port mappings.
*   **`- "8080:8080"`** 
    Maps port `8080` on your host machine to port `8080` inside the container, allowing you to access the server from outside the container.
*   **`volumes:`** 
    Begins the section for mapping storage volumes.
*   **`- ./models:/models`** 
    Mounts the `./models` directory from your host machine (relative to where the `docker-compose.yml` is located) into the `/models` directory inside the container. This is how you provide the model files to the container.

### Server Command & Parameters
*   **`command: >`** 
    Overrides the default command of the Docker image. The `>` allows you to write a multi-line string in YAML for better readability, which is joined into a single string with spaces when executed.
*   **`--model /models/Qwen3-Coder-30B-A3B-Instruct-Q5_K_M.gguf`** 
    Tells the server which model file to load. The path matches the container's internal volume mount.
*   **`--host 0.0.0.0`** 
    Binds the server to all network interfaces, making it accessible from outside the container's local loopback network.
*   **`--port 8080`** 
    Sets the port the application listens on internally.
*   **`--ctx-size 4096`** 
    Sets the maximum context window size to 4096 tokens (how much text the model can "remember" at once).
*   **`--batch-size 4096`** 
    Sets the physical batch size for processing prompts.
*   **`--ubatch-size 4096`** 
    Sets the logical (micro) batch size. Often matches the physical batch size for optimal throughput.
*   **`--threads 4`** 
    Allocates 4 CPU threads for processing. Even when heavily using the GPU, some CPU threads are needed for prompt processing and orchestration.
*   **`--n-gpu-layers -1`** 
    Instructs the server to offload as many model layers as possible (in this case, *all* of them) to the GPU to maximize speed and minimize RAM usage.
*   **`--cache-type-k q8_0`** 
    Quantizes the Key (K) cache in the attention mechanism to 8-bit precision, significantly reducing VRAM usage during long context generation without much loss in quality.
*   **`--cache-type-v q8_0`** 
    Quantizes the Value (V) cache in the attention mechanism to 8-bit precision.
*   **`--flash-attn on`** 
    Enables Flash Attention, a highly optimized algorithm that speeds up generation and drastically reduces memory usage for large context windows.
*   **`--no-mmap`** 
    Disables memory mapping for the model file. Since `n-gpu-layers` is set to `-1` (loading everything into VRAM), turning off mmap avoids allocating unnecessary system RAM, preventing duplicate memory usage and potential OS swapping.

### GPU Acceleration Settings
*   **`deploy:`** 
    Begins the deployment configuration section, used to specify hardware resource allocation.
*   **`resources:`** 
    Defines the resource constraints and reservations.
*   **`reservations:`** 
    Specifies resources that the host must guarantee are available for this container.
*   **`devices:`** 
    Lists specific hardware devices to map to the container.
*   **`- driver: nvidia`** 
    Tells Docker to use the NVIDIA Container Toolkit to bridge the GPU.
*   **`count: all`** 
    Exposes all available NVIDIA GPUs on the host to this container.
*   **`capabilities: [gpu]`** 
    Explicitly grants the container the capabilities required to access and utilize the GPU compute resources.
