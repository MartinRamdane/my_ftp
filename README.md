# My FTP

## Description
This project is a FTP server implemented in C. It is compliant with the [RFC 959](https://tools.ietf.org/html/rfc959). It was made during my 2nd year at Epitech. The goal was to learn how to use sockets and how to implement a protocol.

## Usage
```
./myftp port path
```

## Commands

| Command | Description |
| --- | --- |
| USER | Specify user for authentication |
| PASS | Specify password for authentication |
| CWD | Change working directory |
| HELP | List available commands |
| NOOP | Do nothing |
| QUIT | Disconnection |
| PORT | Enable "active" mode for data transfer |
| PASV | Enable "passive" mode for data transfer |
| TYPE | Set type of transfer |
| DELE | Delete file on the server |
| PWD | Print working directory |
| LIST | List files in the current working directory |
| RETR | Download file from server to client |
| STOR | Upload file from client to server |
| CDUP | Change to parent directory |


## Results
This project received the score of 20/20.


## Authors
* **Adam Elaoumari** - [GitHub](https://github.com/AdamLBS)
