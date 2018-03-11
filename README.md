# GChat
my own implementation of command line TCP chat using C socket

## principle

![principle](http://img.blog.csdn.net/20180124144804402) 

## environment

gcc-7.1.0 + macOS 10.12.6

## usage

Support one on one chat. Multi-chat not yet supported.

To chat, launch server first:

```shell
./server
```

then launch client:

```shell
./client
```

## recompile

```shell
gcc gyTCPserver.c -o server
gcc gyTCPclient.c -o client
```

## todo

- [x] translate comments into English🤣
