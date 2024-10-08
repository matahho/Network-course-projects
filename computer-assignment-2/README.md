# Project Title

Implementing Network Simulator for Measuring Different Routing Protocols

## Description

We utilized QT tools to create a Network Simulator system.

### Part one : Event Control

### Part two : Data Generator

### Part three : Router
First we made our router class that has a _id in it that is unique for each router using this code: 
```cpp 
inline static uint routerID = 0;
const uint _id;
```
then for testing we created a QThread for each router and using ``moveToThread`` and ``connect`` assigned it to the router
```cpp 
QThread* thread = new QThread();
routers[i].moveToThread(thread);
QObject::connect(thread, &QThread::started, &routers[i], &Router::start);
```
### Part four : Cluster

### Part five : Packet

## Authors

* Mehdi Seyed Haji Hossein
* Kasra Noorbakhsh
