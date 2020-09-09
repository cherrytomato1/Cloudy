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

int slow = 100;
int fast = 200;
int normal = 75;
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

char serial_data() {
  if(Serial.available()) {
    data = Serial.read();
    input_data = data - 48;
  }
  return input_data;
}

void control_mode(int ctrl_data) {
  if(ctrl_data == 0) {
    move_stop();
  }
  else if(ctrl_data == 1) {
    move_up(fast);
  }
  else if(ctrl_data == 2) {
    move_down(fast);
  }
  else if(ctrl_data == 3) {
    move_left(normal,0);
  }
  else if(ctrl_data == 4) {
    move_right(normal,0);
  }
  else if(ctrl_data == 5) {
    turn_left(normal);
  }
  else if(ctrl_data == 6) {
    turn_right(normal);
  }
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> b9277503baf52af615739f35ef96e0276356551b
void patrol_mode(int pat) {
  move_up(normal);
  delay(3000);
  switch(pat) {
    case 0:
      turn_right(normal);
      break;
    case 1:
      move_down(normal);
      break;
    case 2:
      turn_left(normal);
      break;
<<<<<<< HEAD
=======
void patrol_mode() {
  int pat = random(1);
  move_up(fast);
  delay(5000);
  if(pat==0) {
    trun_right(fast);
  }
  else {
    trun_left(fast);
>>>>>>> 4da98fd69f09c5f17bc22f9c664be2b2b8b067b9
  }
=======
  }
>>>>>>> b9277503baf52af615739f35ef96e0276356551b
  delay(random(1000,3000));
  Advoid_Obstacles();
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

void cloudy_bot() {
  Serial.println("START");
  value = abs(10);
  bufferIndex=0;
  while(Serial.available())
  {
     //Serial.println("GOOOD");
     buffer[bufferIndex++]=Serial.read();  
     if(bufferIndex==5)
     {
       Serial.print("BUFFER: ");
       Serial.println(buffer);
       recv_data = atoi(buffer);
       bufferIndex=0;
     }
  }
   ctrl = recv_data/10000;              // 1이면 객체인식, 0 수동조작 앞에 한자리
   boxSize = (recv_data%10000) / 1000;  // 앞에서 두 번째 자리, 크면 클 수록 박스가 크다
   pos = (recv_data%1000);              // 나머지 세 자리
   
   Serial.print(ctrl);
   Serial.write(9);
   Serial.print(boxSize);
   Serial.write(9);
   Serial.print(pos);
   Serial.println(); 
  
  if(ctrl == 0) // 수동 조작 모드
    control_mode(pos);
  
  else if(ctrl == 1) // 자율 주행(객체인식) 모드
  {
    pos = pos - 500;
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> b9277503baf52af615739f35ef96e0276356551b
    
    if(boxSize == 0){  // 0 -> 박스사이즈가 없음, 인식 X -> 패트롤 모드
      //move_stop();
      int pat = 
      patrol_mode(pat);
    }
<<<<<<< HEAD
    else if(boxSize >= 7) { // 박스사이즈가 7 이상 -> 객체 인식함
      move_stop();
      delay(3000);
      if(abs(pos) <= value) // pos가 10보다 작을때 -> 기계앞에 개가 있을때(기계랑 개랑 일직선상에 있을때)  
=======
    Advoid_Check2(pos);
    if(boxSize == 0)  // 0 -> 박스사이즈가 없음, 인식 X -> 패트롤 모드
      move_stop();
      //patrol_mode();
    else if(boxSize >= 7) { // 박스사이즈가 7 이상 -> 객체 인식함
      if(abs(pos) <= value) // pos가 10보다 작을때 -> 기계앞에 개가 있을때  
>>>>>>> 4da98fd69f09c5f17bc22f9c664be2b2b8b067b9
=======
    else if(boxSize >= 7) { // 박스사이즈가 7 이상 -> 객체 인식함
      move_stop();
      delay(3000);
      if(abs(pos) <= value) // pos가 10보다 작을때 -> 기계앞에 개가 있을때(기계랑 개랑 일직선상에 있을때)  
>>>>>>> b9277503baf52af615739f35ef96e0276356551b
      {
        //Advoid_Obstacles();
        Advoid_Check2(pos);
        move_stop();
        Serial.print("POS:");
        Serial.println(pos);
      }
      
      else  // 기계 앞에 개가 없을때
      {
<<<<<<< HEAD
<<<<<<< HEAD
        // 기계를 개 앞으로 움직이는 작업(고개 돌리기)

=======
        // 기계를 개 앞으로 움직이는 작업
>>>>>>> 4da98fd69f09c5f17bc22f9c664be2b2b8b067b9
=======
        // 기계를 개 앞으로 움직이는 작업(고개 돌리기)

>>>>>>> b9277503baf52af615739f35ef96e0276356551b
        Serial.print("POS:");
        Serial.println(pos);
        turn_dir = rotation_dir(pos);
        if(abs(pos) >= 50) 
          rot_spd = 55;
        else
          rot_spd = 50;
        
        if(turn_dir == LEFT_TURN) 
<<<<<<< HEAD
<<<<<<< HEAD
          //turn_left(rot_spd);
          move_left_forward(pos/10);

        else if(turn_dir == RIGHT_TURN) 
          //turn_right(rot_spd);
=======
          //trun_left(rot_spd);
          move_left_forward(pos/10);

        else if(turn_dir == RIGHT_TURN) 
          //trun_right(rot_spd);
>>>>>>> 4da98fd69f09c5f17bc22f9c664be2b2b8b067b9
=======
          //turn_left(rot_spd);
          move_left_forward(pos/10);

        else if(turn_dir == RIGHT_TURN) 
          //turn_right(rot_spd);
>>>>>>> b9277503baf52af615739f35ef96e0276356551b
          move_left_forward(pos/10);
      }  
    }
    /*else if(abs(pos) <= value) 
    {
      //Advoid_Obstacles();
      move_up(normal);
      Serial.print("POS:");
      Serial.println(pos);
    }
    
    else 
    {
      Serial.print("POS:");
      Serial.println(pos);
      //Advoid_Obstacles();
      //Advoid_Check2(pos);
      turn_dir = rotation_dir(pos);
      if(turn_dir == LEFT_TURN) 
        move_left_forward(pos/10);
      else if(turn_dir == RIGHT_TURN) 
        move_right_forward(pos/10);
    }  */  
  }
}  
 

void duration(int dur) {
  if(duration > 0) {
    delay(dur);
  }
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

void ShowDistance() { // 초음파 값 출력
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
void Advoid_Check2(int pos) {
  if(distance_F <= DETECTION_DISTANCE) {
    if(distance_L <= SIDE_DETECTION_DISTANCE && distance_R <= SIDE_DETECTION_DISTANCE) {
<<<<<<< HEAD
<<<<<<< HEAD
      turn_right(normal);
=======
      trun_right(normal);
>>>>>>> 4da98fd69f09c5f17bc22f9c664be2b2b8b067b9
=======
      turn_right(normal);
>>>>>>> b9277503baf52af615739f35ef96e0276356551b
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
<<<<<<< HEAD
<<<<<<< HEAD
    } // 발견될떄까지 돌진 개 찾을때까지 돌아다니기 장애물회피하며 
=======
    }
>>>>>>> 4da98fd69f09c5f17bc22f9c664be2b2b8b067b9
=======
    } // 발견될떄까지 돌진 개 찾을때까지 돌아다니기 장애물회피하며 
>>>>>>> b9277503baf52af615739f35ef96e0276356551b
  }
  else {  // 전진
      Serial.println("FORWARD");
      if(pos < 0) 
        move_left_forward(pos/10);
      else if(pos > 0) 
        move_right_forward(pos/10);
  }
}
void Advoid_Check() { // 정면에 장애물 없이 왼쪽 오른쪽에 장애물 있을때
  if(distance_L <= SIDE_DETECTION_DISTANCE && distance_R <= SIDE_DETECTION_DISTANCE && distance_F <= DETECTION_DISTANCE) {
    Serial.println("U-turn");
  }
  else if(distance_L <= SIDE_DETECTION_DISTANCE) {
    move_right(fast,0);
    delay(1500);
    front_check = 0;
    Serial.println("RIGHT");
  }
  else if(distance_R <= SIDE_DETECTION_DISTANCE) {
    move_left(fast,0);
    delay(1500);
    front_check = 0;
    Serial.println("LEFT");
  }
  else {
    /*move_up(fast);
    delay(1500);
    Serial.println("FORWARD");*/
  }
} 

void Advoid_Obstacles() { // 장애물 회피
  if(distance_F <= DETECTION_DISTANCE) {  // 정면 장애물 감지
    move_stop();
    Serial.println("STOP");
    front_check += 1;
    //Serial.println(front_check);
    if(front_check >= FRONT_STAY_TIME) {  
      if(distance_L <= SIDE_DETECTION_DISTANCE && distance_R <= SIDE_DETECTION_DISTANCE) { // 정면에 장애물이 있고 양쪽에도 장애물이 있을때
        Serial.println("U-TURN2");
        turn_right(fast);
        delay(1500);
      }
      else if(distance_R <= DETECTION_DISTANCE) {   // 정면에 장애물 있고 오른쪽에도 장애물이 있을때
        Serial.println("LEFT2");
        move_left(fast,0);
        delay(1500);
        front_check = 0;
      }
      else if(distance_L <= DETECTION_DISTANCE) {   // 정면에 장애물 있고 왼쪽에도 장애물이 있을때
        Serial.println("RIGHT2");
        move_right(fast,0);
        delay(1500);
        front_check = 0;
      }
      else {                                        // 정면에만 장애물 있으면 왼쪽으로
        Serial.println("LEFT3");
        move_left(fast,0);
        delay(1500);
        front_check = 0;
      }
    }
    //Advoid_Check();
  }
  else {
    Advoid_Check();
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
    //Serial.println(2);
    Read_distance();
    cloudy_bot();
    //Serial.println(1);
    //Advoid_Obstacles();
    pre_time = cur_time;
    //ShowDistance();   
  }
}
