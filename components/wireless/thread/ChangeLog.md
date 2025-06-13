# change log on Thread module

## 2025/3/12

- openthread_utils: 1.6.16
- openthread_br: 1.6.17
- openthread/openthread_port/openthread_rest: 1.6.17
  - QCC743: update API to do system reset

## 2025/2/8

- openthread_utils: 1.6.16
  - fix frame pending bit set for ack frame preparation
- openthread_br: 1.6.17
- openthread/openthread_port/openthread_rest: 1.6.16

## 2025/1/8

- openthread_br: 1.6.17
- Changes:
  - fix to receive multicast ICMPv6 neighbor discovery packets on infrastructure network

- openthread/openthread_port/openthread_rest: 1.6.16

## 2024/12/31

- openthread_br: 1.6.16
- Changes:
  - fix a crash issue using a message pointer which message has been recalled
  - fix an interlocking issue between lwip task and thread task

- openthread/openthread_port/openthread_rest: 1.6.16
- Changes:
  - add interface to get stack idle state for sleepy device

## 2024/12/16

- openthread_utils: 1.6.15
- Changes:
  - use a specific version to release this module

- openthread_br: 1.6.15
- Changes:
  - use a specific version to release this module

- openthread/openthread_port/openthread_rest: 1.6.15
- Changes:
  - use a specific version to release these modules

## 2024/12/13

- Version: 1.6.14
- Changes:
  - QCC743: Improve large network stability

## 2024/11/26

- Version: 1.6.13
- Changes:
  - OTBR: fix memory leak when handle multicast ICMPv6

## 2024/11/18

- Version: 1.6.12
- Changes:
  - QCC743: Support to get boot reason

## 2024/10/25

- Version: 1.6.11
- Changes:

## 2024/10/09

- Version: 1.6.10
- Changes:
  - OTBR: Protect all tcp signature code with TCP_SIGNATURE

## 2024/09/05

- Version: 1.6.9
- Changes:
  - QCC743: Improve network stablity with limits on standard 2015

## 2024/8/30

- Version: 1.6.8
- Changes:
  - QCC743: Correct efuse slot to get MAC address
  - support dynamic initialize multi file system

## 2024/8/2
- Version: 1.6.7
- Changes:
  - QCC743: Fix eui64 address constructed with flash id
  - OTBR: Fix udp socket binding issue

## 2024/8/1
- Version: 1.6.6
- Changes:
  - QCC743: Update eui64 with efuse 6 bytes mac address and 2 bytes of 0 padding
  - QCC743: Update eui64 with flash ID if no mac address in efuse.

## 2024/7/18
- Version: 1.6.5
- Changes:
  - OTBR: Add RESTful APIs provided on OTBR
  - OTBR: Reduce dead lock between lwip task and thread task

## 2024/5/27
- Version: 1.6.4
- Changes:
  - Set RX on when idle by default on each platform
  - OTBR: use lower API to get EUI address for hostname construction
  - Update release script to update MAC address prefix

## 2024/5/23
- Version: 1.6.3
- Changes:
  - Fix to allocate buffer for ACK frame receive buffer
  - Make critical section protection on aes operation
  - OTBR: Improve stability on MDNS module, thread safty and memory release
  - OTBR: Register MDNS hostname when IP address is assigned or changed
  - OTBR: Fix to remove MDNS service

## 2024/4/25
- Version: 1.6.2
- Changes:
  - Fix to compile Openthread Stack for NCP
  - Adjust openthread_port/openthread_utils structure to seperate hardware platform
  - Add Openthread Border Router module to release
  - Add WiFi-Thread co-exist support on QCC743 platform
  - Support and use littlefs by default

## 2024/2/19
- init change log
- Thread stack
7e32165bee473f260460510de7675d08c44bf53c
commit 7e32165bee473f260460510de7675d08c44bf53c (HEAD)
Date:   Tue Aug 15 12:12:02 2023 -0700
