# TCP-IP-Practice

### Terminology

- pcaket : 네트워크 가장 작은 단위
- protocol : 통신하기 위한 약속, 규약

</br>



### Network Layer

- layer는 순서가 중요하다
- layer 내에서도 계층이 존재한다.
- layer 마다 매핑되는 protocol이 존재함

|layer|프로토콜|
|:-:|-|
|application|HTTP TELNET SSH FTP|
|Transport|TCP UDP|
|Network|IP|
|Datalink|Ethernet|
|Physical|-|

#### (1) Application layer

- TELNET : 원격 접속 프로토콜. 보안X / SSH : 보안된 버전

- FTP : 대용량 파일 전송 프로토콜
- HTTP : HTML(document) 전달 프로토콜



#### (2) Transport layer

- TCP vs UDP 신뢰 여부의 차이 (세션?)

- TCP+UDP 복합 사용사례 : 게임

  - 다만 UDP를 통해 손실되는 데이터가 있다면 보간(interpoliation)을 사용해 보정 필요

  

#### (3) __Network layer(IP)__

- 사설 IP

  - unique한 IP

  - IPv4의 부족함으로 인해 동적할당으로 사용됌

  - 공유기가 사설 IP를 받아 내부에서 나누는거 가능 

- 도메인

  - 일반적으로 IP로 다른 네트워크(서버)로 접근하지 않고, 도메인을 통해 접근함

- 만약 하나의 웹 사이트를 운영하려면? 

  - IP, Domain, Server가 있어야 함
