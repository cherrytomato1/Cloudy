// 오른쪽 바퀴 핀 정의
#define RIGHT_A 30
#define RIGHT_B 28
#define RIGHT_PWM 8
// 왼쪽 바퀴 핀 정의
#define LEFT_A 44
#define LEFT_B 46
#define LEFT_PWM 2
// 뒷 바퀴 핀 정의
#define BACK_A 24
#define BACK_B 26
#define BACK_PWM 9

// 바퀴 정의
#define R_WHEEL 0
#define L_WHEEL 1
#define B_WHEEL 2

#define STOP 0
#define FORWARD 1
#define RIGHT 2
#define LEFT 3
#define BACK 4
#define LEFT_TURN 5
#define RIGHT_TURN 6

// 초음파 측정 최대 거리: PulseIn함수에서 측정거리 over될 시 0을 반환
#define DIST_MAX 100 // DIST_MAX값까지만 측정 그 외에는 물체가 없다고 본다.
#define DIST_MIN 2 // 측정 최소 거리 지정
#define DIST_S (DIST_MAX *58.2) //초음파센서 타임아웃 설정 (최대거리)

#define maxBufRead 5

#define SIDE_DETECTION_DISTANCE 17
#define DETECTION_DISTANCE 15
#define FRONT_STAY_TIME 1

int trig[3] = {34, 36, 42}; // 좌측, 정면, 우측
int echo[3] = {32, 38, 40};
int motorDir[3][2] ={RIGHT_A, RIGHT_B, LEFT_A, LEFT_B, BACK_A, BACK_B};
int motorPwm[3] = {RIGHT_PWM, LEFT_PWM, BACK_PWM};

unsigned long cur_time ;
unsigned long pre_time ;

const long utime = 2500; // timer loop time(us)
const long mtime = 10; // Ultrasensor timer loop time(ms) 원래 

unsigned long  pre_distance_F;
unsigned long  pre_distance_L;
unsigned long  pre_distance_R;

// 필터 적용된 distance
unsigned long  distance_F;
unsigned long  distance_L;
unsigned long  distance_R;

const float alpha = 0.90;
const float beta = (1 - alpha);

int slow = 60;
int fast = 200;
int normal = 150;
int rot_spd = 45;

int i;
// 시리얼 통신 변수 선언
char data;
char input_data;
int value; 
long recv_data;
int turn_dir;

int ctrl;     //control, ㅈㅔ어정보
int pos;      //position, 좌표정보
int boxSize;  //boxSize 

char buffer[20];
char bufferIndex=0;

int intBuffer;

int detection_distance = 15;
int side_detection_distance = 8;
int side_detection_distance2 = 17;
int front_check = 0;
int front_stay_time = 1; // 전방 감지 시간
int uturn_delay = 1500;
int turn_delay = 175; // 65
int delayy = 1500;

// 패트롤모드에 쓰는 변수
int moveDir;
int moveTime;
unsigned long currentMillis;
long previousMillis = 0;

// test 변수
int testarr[5];

void control_mode(int ctrl_data) {
  if(ctrl_data == 0) move_stop();
  else if(ctrl_data == 1) move_up(fast);
  else if(ctrl_data == 2) move_down(fast);
  else if(ctrl_data == 3) move_left(normal,0);
  else if(ctrl_data == 4) move_right(normal,0);
  else if(ctrl_data == 5) turn_left(normal);
  else if(ctrl_data == 6) turn_right(normal);
}

void auto_mode() {
  pos = pos - 500;  
  move_stop();
  if(boxSize == 0) {  // 0 -> 박스사이즈가 없음, 인식 X -> 패트롤 모드
//    patrol_mode();     // 이동방향, 이동시간 정하기
      move_stop();
  }
  //박스사이즈 최소 수정, 속도 조정
  
  else if(boxSize >= 8) { // 박스사이즈가 7 이상 -> 객체 인식함
    
    if(abs(pos) >= 80) // pos가 10보다 작을때 -> 기계앞에 개가 있을때(기계랑 개랑 일직선상에 있을때)  
    {
      turn_dir = rotation_dir(pos);
      rot_spd = 70;
      if(turn_dir == LEFT_TURN) 
        turn_left(rot_spd);
        //move_left_forward(pos/10);
  
      else if(turn_dir == RIGHT_TURN) 
        turn_right(rot_spd);
        //move_left_forward(pos/10);    
      
      // Advoid_Obstacle(pos);
    }   
  }
  else  // 박스사이즈의 크기가 7이하일때, 거리가 멀때
  {
    // 기계를 개 앞으로 움직이는 작업(고개 돌리기)
    turn_dir = rotation_dir(pos);
//    if(abs(pos) >= 150){
//     
//      rot_spd = 85;
//          
//    if(turn_dir == LEFT_TURN) 
//      turn_left(rot_spd);
//      //move_left_forward(pos/10);
//
//    else if(turn_dir == RIGHT_TURN) 
//      turn_right(rot_spd);
//      //move_right_forward(pos/10);    
//    }
//    else 
      turnAndMove(pos/4);
    
  }  
}

// 패트롤 모드(객체 인식 안됐을때)
void patrol_mode() { // 랜덤 방향, 움직이는 시간
  
  currentMillis = millis();
  if(currentMillis - previousMillis >= moveTime) {
    moveDir = random(0, 6);  // 0, 1, 2, 3, 4, 5 (오른쪽(4), 전진(0~3), 왼쪽(5))
    moveTime = random(1111, 3333);
    if(moveDir >= 5) moveTime / 2.5;    // 회전일경우, 회전 시간 줄임
   
    previousMillis = currentMillis;
  }
  if(distance_F <= DETECTION_DISTANCE) {
      if(moveDir % 2 == 0)
        turn_right(normal);
      else
        turn_left(normal);
        
      delay(500);
      
  }
  else {
      move_up(normal); // 전진
//     else if(moveDir == 5) turn_right(normal); // 오른쪽 회전
//     else if(moveDir == 6) turn_left(normal);  // 왼쪽 회전
  }
}

void patrol_mode_test() { // 랜덤 방향, 움직이는 시간
  for(i=1; i<5; i++) testarr[i] = random(0, 6);
  moveTime = random(1111, 5555);
  currentMillis = millis();
    for(i=0; i<5; i++) {
      if(currentMillis - previousMillis >= moveTime) {
        if(distance_F <= DETECTION_DISTANCE) {
          Serial.print(i);
          Serial.print("장애물");
          Serial.println(testarr[i]);
          if(i != 4) testarr[i+1] = 0;
        }
        else {
          if(testarr[i] <= 3) {
            Serial.print(i);
            Serial.print("전진");
            Serial.println(testarr[i]);
          }
          else if(testarr[i] == 4) {
            Serial.print(i);
            Serial.print("오른회전");
            Serial.println(testarr[i]);
          }
          else if(testarr[i] == 5) {
            Serial.print(i);
            Serial.print("왼회전");
            Serial.println(testarr[i]);
          }
        }
        previousMillis = currentMillis;
      }
  }
}
int rotation_dir(int data) {
  int dir;
  if(data < 0) {
    dir = LEFT_TURN; 
  }
  else if(data > 0) {
    dir = RIGHT_TURN;
  }
  return dir;
}

void move_left_forward(int angle) {
  ctrlMotor(0, (fast-angle));
  ctrlMotor(1, -(fast+angle));
}

void move_right_forward(int angle) {
  ctrlMotor(0, normal-angle);
  ctrlMotor(1, -(normal+angle));
}
void turnAndMove(int angle) {
  ctrlMotor(0, normal-angle);
  ctrlMotor(1, -(normal+angle));
}

void cloudy_bot() {
  value = abs(10);
  bufferIndex=0;
  while(Serial.available())
  {
     buffer[bufferIndex++]=Serial.read();  
     if(bufferIndex==5)
     {
       recv_data = atoi(buffer);
       bufferIndex=0;
     }
  }
   ctrl = recv_data/10000;              // 1이면 객체인식, 0 수동조작 앞에 한자리
   boxSize = (recv_data%10000) / 1000;  // 앞에서 두 번째 자리, 크면 클 수록 박스가 크다
   pos = (recv_data%1000);              // 나머지 세 자리
   
  // 수동 조작 모드
  if (ctrl == 0) control_mode(pos);
  
  // 자율 주행(객체인식) 모드  
  else if (ctrl == 1) auto_mode();
}  
 
void ctrlMotor(int wheel, int speed) {  //wheel 바퀴 번호 (0=right, 1=left, 2=back, speed -255~255)
  int dir;                              //회전방향
  
  if(speed<0)
    dir=0;
  else
    dir=1;
    
  digitalWrite(motorDir[wheel][0], dir);
  digitalWrite(motorDir[wheel][1], !dir);
  
  analogWrite(motorPwm[wheel], abs(speed));
}

void turn_left(int spd) {
  ctrlMotor(R_WHEEL, spd);
  ctrlMotor(L_WHEEL, spd);
  ctrlMotor(B_WHEEL, -spd);
}
void turn_right(int spd) {
  ctrlMotor(R_WHEEL, -spd);
  ctrlMotor(L_WHEEL, -spd);
  ctrlMotor(B_WHEEL, spd);
}
void move_up(int spd) {
  ctrlMotor(R_WHEEL, spd);
  ctrlMotor(L_WHEEL, -spd);
  ctrlMotor(B_WHEEL, 0);
}
void move_down(int spd) {
  ctrlMotor(R_WHEEL, -spd);
  ctrlMotor(L_WHEEL, spd);
  ctrlMotor(B_WHEEL, 0);
}
void move_right(int spd, int angle) {
  ctrlMotor(R_WHEEL, -spd);
  ctrlMotor(L_WHEEL, -spd);
  ctrlMotor(B_WHEEL, (-spd)*2-angle);
}
void move_left(int spd, int angle) {
  ctrlMotor(R_WHEEL, spd);
  ctrlMotor(L_WHEEL, spd);
  ctrlMotor(B_WHEEL, (spd)*2+angle);
}
void move_stop() {
  ctrlMotor(R_WHEEL, 0);
  ctrlMotor(L_WHEEL, 0);
  ctrlMotor(B_WHEEL, 0);
}

unsigned long UltraSonic(int TRIG, int ECHO) {

  //trigger 발사
  unsigned long distance;

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  //echo 핀 입력으로 부터 거리를 cm 단위로 계산
  distance = pulseIn(ECHO, HIGH, DIST_S) / 58.2; //최대 측정 사용시 pulseIn(ECHO,HIGH,DIST_S), pulseIn 반환: unsigned long

  if (distance < DIST_MIN) distance = DIST_MAX * 2;

  return distance;
}

void Read_distance() {  // 초음파 측정 함수
  // 이전 측정 값에 비중을 두고, 현재 측정된 값엔 비중을 낮춤.
  distance_F = UltraSonic(trig[1], echo[1]);
  distance_F = round((alpha * distance_F) + ( beta * pre_distance_F));
  if (distance_F < DIST_MIN) distance_F = DIST_MAX * 2; // 최소 측정 거리 이하이면 물체가 측정거리 밖에 있다고 본다.
  pre_distance_F = distance_F;

  distance_L = UltraSonic(trig[0], echo[0]);
  distance_L = round((alpha * distance_L ) + (beta * pre_distance_L));
  if (distance_L < DIST_MIN) distance_L = DIST_MAX * 2;
  pre_distance_L = distance_L;

  distance_R = UltraSonic(trig[2], echo[2]);
  distance_R = round((alpha * distance_R ) + (beta * pre_distance_R));
  if (distance_R < DIST_MIN) distance_R = DIST_MAX * 2;
  pre_distance_R = distance_R;
}

void ShowDistance() { // 초음파 값 출력함수
  Serial.print(distance_L);
  Serial.print("cm");
  Serial.write(9); //tab
  Serial.print(distance_F);
  Serial.print("cm");
  Serial.write(9);  
  Serial.print(distance_R);
  Serial.print("cm");
  Serial.println();
}

// 장애물 회피 알고리즘
void Advoid_Obstacle(int pos) {
  if(distance_F <= DETECTION_DISTANCE) { // 정면 초음파센서 15cm 이내 장애물 감지 되었을때
    if(distance_L <= SIDE_DETECTION_DISTANCE && distance_R <= SIDE_DETECTION_DISTANCE) { // 
      turn_right(normal);
      delay(1800);
    }
    else if(distance_L <= DETECTION_DISTANCE) {
      move_right(normal,pos/10);
      delay(1000);
    }
    else if(distance_R <= DETECTION_DISTANCE) {
      move_left(normal,pos/10);
      delay(1000);
    }
    else {
      move_right(1000,pos/10);
      delay(1000);
    } // 발견될떄까지 돌진 개 찾을때까지 돌아다니기 장애물회피하며 
  }
  else {  // 전진
      Serial.println("FORWARD");
      if(pos < 0) 
        move_left_forward(pos/10);
      else if(pos > 0) 
        move_right_forward(pos/10);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(RIGHT_A, OUTPUT);
  pinMode(RIGHT_B, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);
  pinMode(LEFT_A, OUTPUT);
  pinMode(LEFT_B, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(BACK_A, OUTPUT);
  pinMode(BACK_B, OUTPUT);
  pinMode(BACK_PWM, OUTPUT);
  for(int i=0; i<=2; i++){
      pinMode(trig[i], OUTPUT);
      pinMode(echo[i], INPUT);
  }
  delay(1000);
}

void loop() {
  cur_time = millis();
  if(cur_time - pre_time >= mtime) { // 50ms 마다 초음파 측정
    
    Read_distance();    
    cloudy_bot();
    pre_time = cur_time;
  }
}
