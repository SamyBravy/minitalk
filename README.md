# 📡 Minitalk

![Language](https://img.shields.io/badge/Language-C-blue)

## 📝 Overview

**Minitalk** is a small data exchange program using UNIX signals. It consists of a client and a server that communicate using only `SIGUSR1` and `SIGUSR2`.

This project explores:
-   **Inter-Process Communication (IPC)** using signals.
-   **Signal Handling** in C.
-   **Bitwise Operations** to transmit data.

## 🚀 Features

-   **Server**: Prints its PID and waits for signals.
-   **Client**: Takes the server's PID and a string, sending the string char by char (bit by bit).
-   **Reliability**: Handles multiple clients and ensures message integrity.
-   Unicode support (UTF-8).
-   Server acknowledgement (ping-pong signals).

## 🛠️ Installation & Usage

### Compilation
Use the `Makefile` to compile the project:

```bash
make        # Compiles the project
```

### Running

1.  **Start the Server**:
    ```bash
    ./server
    ```
    The server will print its PID (e.g., `12345`).

2.  **Run the Client**:
    ```bash
    ./client <PID> "Hello, Minitalk!"
    ```
    Replace `<PID>` with the server's PID.

## 📂 Project Structure

-   `srcs/`: Source code (client and server).
-   `my_lib/`: Custom library (Libft, ft_printf).

## ⚠️ Requirements

-   GCC compiler
-   Make
-   UNIX environment (Linux/macOS)
