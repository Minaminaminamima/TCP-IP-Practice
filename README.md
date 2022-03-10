# TCP-IP-Practice

pcaket : 네트워크 가장 작은 단위


### Network Layer
|layer|프로토콜|
|:-:|-|
|application|HTTP TELNET SSH FTP|
|Transport|TCP UDP|
|Network|IP|
|Datalink|Ethernet|
|Physical|-|

- layer는 순서가 중요하고, layer 내에서도 계층이 존재한다.
- layer 마다 매핑되는 protocol이 존재
- application Layer
  - TELNET : 보안X / SSH : 보안된 버전
  - FTP : 대용량 파일 전송 프로토콜

- TCP+UDP 사용사례 : 게임
  - 다만 보간(interpoliation)을 사용해 보정 필요


### 사설 IP
- unique한 IP
- IPv4의 부족함으로 인해 동적할당으로 사용됌
- 공유기가 사설 IP를 받아 내부에서 나누는거 가능 


### Domain
일반적으로 IP로 다른 네트워크(서버)로 접근하지 않음 
도메인을 통해 접근함
하나의 사이트 운영? IP, Domain, Server가 있어야 함
