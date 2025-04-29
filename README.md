# 🗨️ IRC Server

> A simple implementation of an IRC (Internet Relay Chat) server built from scratch using sockets and C/C++. This project aims to replicate core IRC functionalities as defined in RFC 1459.

---

## 📌 Overview

This IRC server is a lightweight implementation of the IRC protocol, supporting multiple clients, channels, and basic IRC commands. It uses low-level socket programming to handle TCP connections, parses IRC messages, and manages communication between clients and channels in real-time.

The project is designed to reinforce knowledge in:

- Networking and TCP sockets
- I/O multiplexing (using `poll`, `select`, or `epoll`)
- Text-based protocols (RFC 1459)
- String parsing and memory management
- Concurrent client handling

---

## ⚙️ Features

- Multi-client support
- Channels with JOIN / PART
- Nickname and user registration
- Private messaging between users
- Channel messaging and topic setting
- Server password authentication
- Command parsing per RFC 1459:
  - `NICK`, `USER`, `JOIN`, `PART`, `PRIVMSG`, `PING`, `PONG`, `QUIT`, etc.
- Graceful client disconnection
- `poll()`-based I/O multiplexing

---

## 🏗️ Project Structure

```bash
irc-server/
├── src/
│   ├── main.cpp              # Entry point
│   ├── server.cpp/.hpp       # Server socket logic
│   ├── client.cpp/.hpp       # Client state and handlers
│   ├── parser.cpp/.hpp       # IRC message parser
│   └── command_handler.cpp/.hpp  # Handles IRC commands
├── include/
│   └── ...                   # All headers
├── Makefile
└── README.md
🧪 How to Run
1. Build
make

2. Run the Server

./ircserv <port> <password>
port: The TCP port for the server (e.g., 6667)

password: Clients must supply this on connection

3. Connect a Client
You can use any IRC client, like:
# Using netcat for testing
nc localhost 6667

# Or using an IRC client
irc localhost 6667

📋 Example Interaction
NICK Alice
USER alice 0 * :Alice Example
JOIN #42
PRIVMSG #42 :Hello, world!

🛡️ Security Notes
Basic error handling on malformed commands

Server disconnects invalid clients

Password-protected access

📚 References
RFC 1459 - Internet Relay Chat Protocol

Beej's Guide to Network Programming

🧠 Author
👤 Reda Bouissali
42 School - IRC Project
