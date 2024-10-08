# Project Title

Socket programming

## Description

We utilized QT and Boost library tools to create a distributed live voice call system.

### Part one : Writing the Program
After installing the requirements, we first utilized Qt to access our device's microphone, for which we created the `AudioSource` class(All classes that are introduced have their own constructore and deconstructors). Using :
```cpp 
explicit AudioSource(QObject *parent = nullptr);
```
we set the initial things like the source of input and the format of input taken.

we have :
```cpp 
void audioSourceData(QIODevice *IO, QAudioSource *audioSource);
```
that is a private slot that reads from IO and saves in its buffer and when it is done it triggers audioDataTransmit signal.

this class has :
```cpp 
 qreal audioSourceLevel(const char *data, qint64 length);
```
that is a private method that using 2 for loops, returns the maximum level of our audio input.

we created the `AudioSink` class that is similiar to AudioSource class(their constructors and deconstructors are roughly the same).

we have :
```cpp 
void audioDataReceived(QByteArray newAudioBuffer, qreal newAudioLevel);
```
that is a private slot that sets its own buffer and audio level that are passed to it and when it is done it triggers checkAudioDataReceived signal.

this class has :
```cpp 
void audioSinkData(QIODevice *IO);
```
that is a private method that checks that whether the recived buffer is not empty and after that writes it out on IO.

### Part two : Connection
the `Server` class has a tcp acceptor and a tcp socket that are initilized in its constructore using this line of code :
```cpp
: acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) , socket_(io_context)
```
acceptConnection methods accepts the clients that want to connect to this socket. Here the server sends the audio input that from the previous step we collected to the client.

### Part three : WebRTC
WebRTC stands for Web Real-Time Communications. It is a great protocol for audio/video usecases. As it seems it is easy to use, you are not worried about compatibility with different devices and you can develop a simple live streaming app but if you want to add some widgets that for example Meet or Skype has, you must develop them. Like most of other protocols similar to WebRTC it uses UDP.
We can name three **pros** of WebRTC:
* Simplicity: Developers are not worried about different aspects of the streaming server and so many things are done within it.
* Compatibility: It is supported by various populer web browsers and devices and it can work with almost any OS.
* Security: Messeges are allways encrypted by a security protocol named Secure RTP protocol (SRTP). Only users with access to the secret encryption key can decode the communication streams.

We can name three **cons** of WebRTC:
* Scalability: WebRTC is not always suitable for streaming large events with high network load.
* Future: WebRTC uses free VP8 codec(encoding and decoding algorithms). Some companies prefer to use non free codecs like:H.264 and H.265, which limits their ability to use certain features. This will become a problem for software developers
* Relibility: The quality of WebRTC communication heavily relies on internet bandwidth and the viewer's Internet connection speed.

#### TURN server
TURN stands for Traversal Using Relays around NAT. Existance of firewalls or private IP addresses can make a difficulty for connecting devices that want to communicate. In this case a TURN server can helps the devices to connect and find each other. When the STUN server can't help(like when there exists private Ip addresses) we use TURN server. It is somehow the backup of STUN server and forms a undirect communication. A TURN server acts as a translator for devices sharing data with the WebRTC protocol without using IP. We can see a TURN server as the ansector of File sharing systems.
#### STUN server
STUN stands for Session Traversal Utilities for NAT. It introduces different devices to each other by using each device's public IP address. When a device wants to connect to another device it sends a request to the STUN server and the server replies back the ip address and the port needed for the connection. STUN server helps clients behind firewalls and NAT devices to establish direct communication 

" description of the term NAT: It is used to allow multiple devices to share a single public IP address "

![STUN server](https://github.com/matahho/CN_CA_1/assets/148063514/ef016451-2951-4a8e-bb35-d8dad28af2f4)

#### SIGNALING server
We can say that this server is where the usefull informations are transmitted. This server initializes and introduces different aspects of data for communication. "Signalling servers are at the heart of WebRTC signalling, serving as the glue that holds the entire communication process together.". TURN server and STUN server that we talked about them earlier are 2 different types of Signaling Servers.

![SIGNALING server](https://github.com/matahho/CN_CA_1/assets/148063514/35828bfa-79f9-4b35-8bb8-c3eed319f4dd)

As we can see in the picture above, we have ICE and SDP but what are they?
* ICE: ICE stands for Interactive Connectivity Establishment. Again it is a protocol for problems that we have before(NAT and firewalls). ICE candidates (shown in picture) are potential netwrok addresses for determining the most efficient network path for establishing a direct connection. ICE helps WebRTC traverse NATs and firewalls by allowing devices to find and use the most efficient network path between them. At the end we can say the two previously introduced servers: STUN and TURN, are two types of ICE servers.

* SDP: SDP stands for Session Description Protocol. It is used to set up **multimedia sessions** between devices across the internet. It has some information about the connection like the codec(previously introduced) and transport layer protocol and etc. When two devices attempt to establish a WebRTC connection, they exchange SDP messages to negotiate the details of the media streams they want to send and receive (as shown in picture). At the end we can say that this protocol is a powerful tool for the compability of the WebRTC.


## Authors

* Mehdi Seyed Haji Hossein
* Kasra Noorbakhsh

### Good Resources 
[A youtube video to explain webRTC](https://www.youtube.com/watch?v=WmR9IMUD_CY)
