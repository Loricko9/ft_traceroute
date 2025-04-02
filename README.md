# Ft_traceroute

[![en](https://img.shields.io/badge/Language-en-red)](README.md)

$$\color{darkgreen}{{\Huge \mathbf {125/100 ✅}}}$$

## The goal

Reproduce the simple `traceroute` command with udp socket

We just have to handle `--help` option

**This program need to use raw socket to receive ICMP Packet so you must have root right !**

## Execution

This project contain a `Makefile`.
It compile each file in `src/` directory and it produce a executable
The executable must be executed as follow :
````sh
sudo ./ft_traceroute [options] addresses [packetlen]
````

$\color{red}{\large {\mathbf {⚠⚠\ You\ need\ to\ have\ root\ right\ to\ run\ the\ program\ ⚠⚠}}}$

You can put either ip addresses (`172.217.20.163`) or DNS addresses (`google.fr`).
You can also put flag in bonuses in any order in the command, see `--help` for more detail.

## Bonuses

The program also handle this flags :
| Flag | Description |
| ---- | ----- |
| -p | Port number where send udp packet |
| -m | Maximal number of ttl autorized |
| -f | First ttl at the start |
| -n | Skip the DNS resolution for each packet |

