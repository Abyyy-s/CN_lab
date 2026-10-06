# Network Programming Lab — Complete Programs & Algorithms

All 54 C socket programs are compiled and verified.
Each `.c` file contains:
1. Complete C source code.
2. Exactly **50 blank line spaces** after the code.
3. The **Algorithm** written as a C comment block (`/* ... */`), including:
   - Respective Algorithm (TCP Server, TCP Client, UDP Server, or UDP Client).
   - Experiment-Specific Step-by-Step Logic.
   - Companion Algorithm for lab record reference.

---

## Directory Structure

```
A_lab/
├── compile_all.sh                 <- Compiles all 54 programs
├── q1_matrix/                     <- Identify Matrix Type (Upper/Lower/Diagonal)
│   ├── tcp/  server.c, client.c   (Port 12345)
│   └── udp/  server.c, client.c   (Port 12346)
├── q1_matrix_addition/            <- Matrix Addition
│   ├── tcp/  server.c, client.c   (Port 12347)
│   └── udp/  server.c, client.c   (Port 12348)
├── q1_matrix_multiply/            <- Matrix Multiplication
│   ├── tcp/  server.c, client.c   (Port 12349)
│   └── udp/  server.c, client.c   (Port 12350)
├── q2_multichat/                  <- Multi-user Chat
│   ├── tcp/  server.c, client.c   (Port 8888  - select() based)
│   └── udp/  server.c, client.c   (Port 8889  - dynamic registration)
├── q3_datetime/                   <- Concurrent Date & Time Server
│   ├── tcp/  server.c, client.c   (Port 9001  - concurrent fork())
│   └── udp/  server.c, client.c   (Port 9002)
├── q4_abbreviation/               <- Abbreviation Expander (Slang to Formal)
│   └── udp/  server.c, client.c   (Port 9003)
├── q5_fibonacci/                  <- Fibonacci Series
│   ├── tcp/  server.c, client.c   (Port 5001)
│   └── udp/  server.c, client.c   (Port 5002)
├── q6_palindrome/                 <- Palindrome Check
│   ├── tcp/  server.c, client.c   (Port 5003)
│   └── udp/  server.c, client.c   (Port 5004)
├── q7_prime/                      <- Prime or Composite Check
│   ├── tcp/  server.c, client.c   (Port 5005)
│   └── udp/  server.c, client.c   (Port 5006)
├── q8_oddeven/                    <- Odd or Even Check
│   ├── tcp/  server.c, client.c   (Port 5007)
│   └── udp/  server.c, client.c   (Port 5008)
├── q9_average/                    <- Average of Three Numbers
│   ├── tcp/  server.c, client.c   (Port 5009)
│   └── udp/  server.c, client.c   (Port 5010)
├── q10_sumnumbers/                <- Sum of N Numbers
│   ├── tcp/  server.c, client.c   (Port 5011)
│   └── udp/  server.c, client.c   (Port 5012)
├── q11_stringreverse/             <- String Reverse
│   ├── tcp/  server.c, client.c   (Port 5013)
│   └── udp/  server.c, client.c   (Port 5014)
└── q12_factorial/                 <- Factorial of a Number
    ├── tcp/  server.c, client.c   (Port 5015)
    └── udp/  server.c, client.c   (Port 5016)
```

---

## General Algorithms

### TCP Server
1. Start.
2. Create a socket using socket().
3. Assign IP address and port number using bind().
4. Wait for client connection using listen().
5. Accept the client connection using accept().
6. Receive data from the client using recv()/read().
7. Process the received data.
8. Send the result back using send()/write().
9. Close the client socket.
10. Close the server socket.
11. Stop.

### TCP Client
1. Start.
2. Create a socket using socket().
3. Specify the server IP address and port number.
4. Establish connection using connect().
5. Read/input the required data.
6. Send data to the server using send()/write().
7. Receive the result using recv()/read().
8. Display the result.
9. Close the socket.
10. Stop.

### UDP Server
1. Start.
2. Create a socket using socket().
3. Assign IP address and port number using bind().
4. Receive data from the client using recvfrom().
5. Process the received data.
6. Send the result back using sendto().
7. Close the socket.
8. Stop.

### UDP Client
1. Start.
2. Create a socket using socket().
3. Specify the server IP address and port number.
4. Read/input the required data.
5. Send data to the server using sendto().
6. Receive the result using recvfrom().
7. Display the result.
8. Close the socket.
9. Stop.
