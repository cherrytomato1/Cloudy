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
int i;
// 시리얼 통신 변수 선언
char data;
char input_data;
int value; 
long recv_data;
int turn_dir;
String strr;

int ctrl;     //controll, ㅈㅔ어정보
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

int serial_data() {
  if(Serial.available()) {
    data = Serial.read();
    input_data = data - 48;
  }
  return input_data;
}

void control_bot() {
  setMotor(serial_data(), 0, 0);
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
void cloudy_bot() {
  value = abs(10);
  while(Serial.available())
  {
     buffer[bufferIndex++]=Serial.read();
    
              
     if(bufferIndex==5)
     {
       recv_data = atoi(buffer);
       bufferIndex=0;
     }
  }
   ctrl = recv_data/10000;
   boxSize = (recv_data%10000) / 1000;
   pos = (recv_data%1000)%1000;
   Serial.print(ctrl);
   Serial.write(9);
   Serial.print(boxSize);
   Serial.write(9);
   Serial.print(pos);
   Serial.println();

  turn_dir = rotation_dir(pos);
  if(abs(pos) <= value) {
    Advoid_Obstacles();
  }
  else {
    if(turn_dir == LEFT_TURN) {
      trun_left(fast);
    }
    else if(turn_dir == RIGHT_TURN) {
      turn_right(fast);
    }
    //setMotor(turn_dir, fast, 0);
  }
}  
 
void setSpeed(int right_spd, int left_spd, int back_spd) {  // pwm제어를 통한 속도 조절
  analogWrite(RIGHT_PWM, right_spd);
  analogWrite(LEFT_PWM, left_spd);
  analogWrite(BACK_PWM, back_spd);
}

void duration(int dur) {
  if(duration > 0) {
    delay(dur);
  }
}

void stop() {
  digitalWrite(RIGHT_A, LOW);
  digitalWrite(RIGHT_B, LOW);
  digitalWrite(LEFT_A, LOW);
  digitalWrite(LEFT_B, LOW);
  digitalWrite(BACK_A, LOW);
  digitalWrite(BACK_B, LOW);
}
void left_turn() {
  digitalWrite(RIGHT_A, HIGH);
  digitalWrite(RIGHT_B, LOW);
  digitalWrite(LEFT_A, HIGH);
  digitalWrite(LEFT_B, LOW);
  digitalWrite(BACK_A, LOW);
  digitalWrite(BACK_B, HIGH);
}
void right_turn() {
  digitalWrite(RIGHT_A, LOW);
  digitalWrite(RIGHT_B, HIGH);
  digitalWrite(LEFT_A, LOW);
  digitalWrite(LEFT_B, HIGH);
  digitalWrite(BACK_A, HIGH);
  digitalWrite(BACK_B, LOW);
}
void forward() {
  digitalWrite(RIGHT_A, HIGH);
  digitalWrite(RIGHT_B, LOW);
  digitalWrite(LEFT_A, LOW);
  digitalWrite(LEFT_B, HIGH);
  digitalWrite(BACK_A, LOW);
  digitalWrite(BACK_B, LOW);
}
void right() {
  digitalWrite(BACK_A, LOW);
  digitalWrite(BACK_B, HIGH);
  digitalWrite(RIGHT_A, LOW);
  digitalWrite(RIGHT_B, HIGH);
  digitalWrite(LEFT_A, LOW);
  digitalWrite(LEFT_B, HIGH);
}

void left() {
  digitalWrite(BACK_A, HIGH);
  digitalWrite(BACK_B, LOW);
  digitalWrite(RIGHT_A, HIGH);
  digitalWrite(RIGHT_B, LOW);
  digitalWrite(LEFT_A, HIGH);
  digitalWrite(LEFT_B, LOW);
}

void back() {
  digitalWrite(RIGHT_A, LOW);
  digitalWrite(RIGHT_B, HIGH);
  digitalWrite(LEFT_A, HIGH);
  digitalWrite(LEFT_B, LOW);
  digitalWrite(BACK_A, LOW);
  digitalWrite(BACK_B, LOW);
}

void setRightMotorDir(int speed) {
  int dir;
  
  if(speed<0)
    dir=1;
  else
    dir=0;
  if(dir == 0) {
    digitalWrite(RIGHT_A, HIGH);
    digitalWrite(RIGHT_B, LOW);
  }
  else {
    digitalWrite(RIGHT_A, LOW);
    digitalWrite(RIGHT_B, HIGH); 
  }
  analogWrite(RIGHT_PWM, speed);
}
void setLeftMotorDir(int speed) {
  int dir;
  
  if(speed<0)
    dir=1;a
  else
    dir=0;
  if(dir == 0) {
    digitalWrite(LEFT_A, HIGH);
    digitalWrite(LEFT_B, LOW);
  }
  else 
    digitalWrite(LEFT_A, LOW);
    digitalWrite(LEFT_B, HIGH); 
  }
  analogWrite(LEFT_PWM, speed);
}
void setBackMotorDir(int speed) {
  int dir;
  
  if(speed<0)
    dir=1;
  else
    dir=0;
    
  if(dir == 0) {
    digitalWrite(BACK_A, HIGH);
    digitalWrite(BACK_B, LOW);
  }
  else {
    digitalWrite(BACK_A, LOW);
    digitalWrite(BACK_B, HIGH); 
  }
  
  analogWrite(BACK_PWM, speed);
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


void trun_left(int spd) {
  ctrlMotor(R_WHEEL, spd);
  ctrlMotor(L_WHEEL, spd);
  ctrlMotor(B_WHEEL, -spd);
}
void trun_right(int spd) {
  ctrlMotor(R_WHEEL, -spd);
  ctrlMotor(L_WHEEL, -spd);
  ctrlMotor(B_WHEEL, spd);
}
void move_up(int spd) {
  ctrlMotor(R_WHEEL, spd);
  ctrlMotor(L_WHEEL, -spd);, 
  ctrlMotor(B_WHEEL, 0);
}
void move_down(int spd) {
  ctrlMotor(R_WHEEL, -spd);
  ctrlMotor(L_WHEEL, spd);
  ctrlMotor(B_WHEEL, 0);
}
void move_right(int spd, int num) {
  ctrlMotor(R_WHEEL, -spd);
  ctrlMotor(L_WHEEL, -spd+num);
  ctrlMotor(B_WHEEL, -spd*2);
}
void move_left(int spd, int num) {
  ctrlMotor(R_WHEEL, spd+num);
  ctrlMotor(L_WHEEL, spd);
  ctrlMotor(B_WHEEL, spd*2);
}
void move_stop() {
  ctrlMotor(R_WHEEL, 0);
  ctrlMotor(L_WHEEL, 0);
  ctrlMotor(B_WHEEL, 0);
}

void setMotor(int dir, int spd, int dur) {  // 모터 제어
   if(dir == 0) { // dir에 따라 방향 제어
    setSpeed(spd, spd, spd);  // 속도 조절
    move_stop();
    duration(dur);  // delay()
  }
   else if(dir == 1) {
    setSpeed(spd, spd, spd);
    forward();
    duration(dur);
  }
   else if(dir == 2) {
    setSpeed(spd, spd, spd*2);  //
    right();
    duration(dur);
  }
   else if(dir == 3) {
    setSpeed(spd, spd, spd*2);
    left();
    duration(dur);
  }
  else if(dir == 4) {
    setSpeed(spd, spd, spd);
    back();
    duration(dur);
  }
  else if(dir == 5) {
    setSpeed(spd, spd, spd);
    left_turn();
    duration(dur);
  }
  else if(dir == 6) {
    setSpeed(spd, spd, spd);
    right_turn();
    duration(dur);
  }
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

void Advoid_Check() { // 정면에 장애물 없이 왼쪽 오른쪽에 장애물 있을때
  if(distance_L <= SIDE_DETECTION_DISTANCE && distance_R <= SIDE_DETECTION_DISTANCE && distance_F <= DETECTION_DISTANCE) {
    Serial.println("U-turn");
  }
  else if(distance_L <= SIDE_DETECTION_DISTANCE) {
    move_right(fast);
    delay(1500);
    front_check = 0;
    Serial.println("RIGHT");
  }
  else if(distance_R <= SIDE_DETECTION_DISTANCE) {
    move_left(fast);
    delay(1500);
    front_check = 0;
    Serial.println("LEFT");
  }
  else {
    move_up(fast);
    delay(1500);
    Serial.println("FORWARD");
  }
} 

void Advoid_Obstacles() { // 장애물 회피
  if(distance_F <= DETECTION_DISTANCE) {  // 정면 장애물 감지
    stop();
    Serial.println("STOP");
    front_check += 1;
    //Serial.println(front_check);
    if(front_check >= FRONT_STAY_TIME) {  
      if(distance_L <= SIDE_DETECTION_DISTANCE && distance_R <= SIDE_DETECTION_DISTANCE) { // 정면에 장애물이 있고 양쪽에도 장애물이 있을때
        Serial.println("U-TURN2");
        trun_right(fast);
        delay(1500);
      }
      else if(distance_R <= DETECTION_DISTANCE) {   // 정면에 장애물 있고 오른쪽에도 장애물이 있을때
        Serial.println("LEFT2");
        move_left(fast);
        delay(1500);
        front_check = 0;
      }
      else if(distance_L <= DETECTION_DISTANCE) {   // 정면에 장애물 있고 왼쪽에도 장애물이 있을때
        Serial.println("RIGHT2");
        move_right(fast);
        delay(1500);
        front_check = 0;
      }
      else {                                        // 정면에만 장애물 있으면 왼쪽으로
        Serial.println("LEFT3");
        move_left(fast);
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
void test() {
    /*up(100);
    delay(3000);
    down(100);
    delay(3000);*/
    rig(100);
    delay(3000);
    lef(100);
    delay(3000);
    stop();
}
void loop() {
  cur_time = millis();
  if(cur_time - pre_time >= mtime) { // 50ms 마다 초음파 측정
    Read_distance();
    //cloudy_bot();
    Advoid_Obstacles();
    //test();
    pre_time = cur_time;
    ShowDistance();   
  }
}
  
  /*setMotor(FORWARD, fast, 0);
  delay(delayy);
  setMotor(BACK, fast, 0);
  delay(delayy);
  setMotor(RIGHT, 0, 0);
  delay(delayy);
  setMotor(LEFT, 0, 0);
  delay(delayy);*/
  
