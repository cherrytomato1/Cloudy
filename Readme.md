# 부재중 반려견 돌봄이 Cloudy
- 부재중 반려견 돌봄이 Cloudy
- 19.9.10 ~ 20.10.21
- 교내 2020 창의적 종합설계 경진대회 은상
- 2020학년도 정보통신공학과 졸업작품전시회 우수상 
- 2020 한이음 ICT멘토링 입선

## 팀구성
- 팀장  : 김민기 ( 총괄, 객체인식/추적, 앱-파이-아두이노 통신 서버, 앱 기능 )

  팀원  : 김효권 ( 센서/모터 동작, 주행 기능, 장애물 회피 )
  
  팀원  : 김길연 ( 하드웨어 제작, 앱 UI, 카메라 스트리밍 서버)
  
  팀원  : 변규린 ( 프로젝트 일정관리, 하드웨어 제작, 센서/모터 동작 )
  
## 프로젝트 개요

- 반려견을 키우는 1인 가구가 증가함으로 홀로 남겨진 반려견을 모니터링 하는 IOT 기기의 필요성 증가
- 기존 반려동물 감시 기기와 다르게 객체인식 기능을 접목하여 조작 없이 반려견을 추적할 수 있도록 제작
- 설문조사 및 시장조사를 통해 필요성 확인

## 시연 영상
--https://www.youtube.com/watch?v=ObmEl-eeEP8

## 개발
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EC%99%84%EC%84%B1.PNG" />
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EC%96%B4%ED%94%8C.bmp" />

### 하드웨어
- 라즈베리파이 4
- 아두이노 메가
- USB IP 카메라
- Intel Neural Computing Stick 2
- 초음파 센서
- 모터, 모터쉴드, 리튬 배터리, 외관 프레임
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EB%B6%80%ED%92%88%EA%B5%AC%EC%84%B1.PNG" />

### 개발환경
 - 라즈베리파이 - python
 - 안드로이드 - Kotlin
 - 아두이노 - C/C++
 
### 프로그램 구성 및 사용 라이브러리

- Socket 서버를 통한 Pi - Android 통신
- Aduino - Pi 시리얼 통신
- Aduino에서 센서 및 모터제어
- Android에서 Web View 통해 실시간 영상 확인
- 초음파 센서로 장애물 회피기동
- pi 내 리눅스 가상환경 구성

- mjpge streamer package - 실시간 영상 송출 서버
- OpenCV 4.1.2
- OpenVino for raspbian - NCS toolkit
- MobileNet SSD - caffe 모델 객체인식 알고리즘

### 동작 흐름, 구성도
- 동작흐름도
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EB%8F%99%EC%9E%91%20%EA%B5%AC%EC%84%B1.PNG" />

- 기능블록도
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EB%B8%94%EB%A1%9D%EB%8F%84.png" />

- 어플리케이션 순서도
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EC%88%9C%EC%84%9C%EB%8F%84%20%EC%96%B4%ED%94%8C%EB%A6%AC%EC%BC%80%EC%9D%B4%EC%85%98.bmp" />

- Pi, Aduino 순서도
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%ED%8C%8C%EC%9D%B4%20%EC%95%84%EB%91%90%EC%9D%B4%EB%85%B8%20%EC%88%9C%EC%84%9C%EB%8F%84.bmp" />

### 동작 과정
- 객체인식
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EC%96%B4%ED%94%8C.bmp" />
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EC%A2%8C%ED%91%9C.bmp" />


반려견을 인식하면 인식된 객체의 좌표와 박스 사이즈를 시리얼로 아두이노에게 전송, 아두이노는 박스크기로 거리를 조정하고 좌표로 움직여야할 방향으로 회전 및 기동

- 장애물 회피
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EC%B4%88%EC%9D%8C%ED%8C%8C.png" />


초음파 센서의 배치 각도를 조정하여 기동방향의 장애물을 탐지하고 초음파 센서의 수신시간 차이로 거리를 측정하여 회피기동

- 모터 및 바퀴
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EC%98%B4%EB%8B%88%ED%9C%A0.bmp" />


옴니휠을 사용하여 제약 없이 기동

- 어플리케이션
<img src="https://raw.githubusercontent.com/cherrytomato1/Cloudy/master/images/%EC%96%B4%ED%94%8C.bmp" />


어플리케이션의 버튼으로 수동제어, 자동제어를 설정하며 수동제어 시 화살표 버튼으로 기기 기동 


<details>
<summary> </summary>
<div markdown="1">
## 수상
  
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%EC%83%81%EC%9E%A5.PNG" />
<img src="https://github.com/cherrytomato1/Cloudy/blob/38f6191ccb15026a9ea78c3358a17b6b6099d850/%E1%84%8C%E1%85%A9%E1%86%AF%E1%84%8B%E1%85%A5%E1%86%B8%E1%84%8C%E1%85%A1%E1%86%A8%E1%84%91%E1%85%AE%E1%86%B7%E1%84%8C%E1%85%A5%E1%86%AB%E1%84%89%E1%85%B5%E1%84%92%E1%85%AC%20%E1%84%89%E1%85%A1%E1%86%BC%E1%84%8C%E1%85%A1%E1%86%BC-1.jpg" />
<img src="https://github.com/cherrytomato1/Cloudy/blob/master/images/%E1%84%92%E1%85%A1%E1%86%AB%E1%84%8B%E1%85%B5%E1%84%8B%E1%85%B3%E1%86%B7_%E1%84%8B%E1%85%B5%E1%86%B8%E1%84%89%E1%85%A5%E1%86%AB.PNG" />

</div>
</details>

