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

#define STOP 0
#define FORWARD 1
#define RIGHT 2
#define LEFT 3
#define BACK 4
#define TURN 5

// 초음파 측정 최대 거리: PulseIn함수에서 측정거리 over될 시 0을 반환
#define DIST_MAX 100 // DIST_MAX값까지만 측정 그 외에는 물체가 없다고 본다.
#define DIST_MIN 2 // 측정 최소 거리 지정
#define DIST_S (DIST_MAX *58.2) //초음파센서 타임아웃 설정 (최대거리)

int trig[3] = {34, 36, 42}; // 좌측, 정면, 우측
int echo[3] = {32, 38, 40};

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

int slow = 75;
int fast = 150;

int detection_distance = 15;
int side_detection_distance = 8;
int side_detection_distance2 = 17;
int front_check = 0;
int front_stay_time = 1; // 전방 감지 시간
int uturn_delay = 1500;
int turn_delay = 175; // 65
int delayy = 1500;

void setSpeed(int spd) {
  analogWrite(RIGHT_PWM, spd);
  analogWrite(LEFT_PWM, spd);
  analogWrite(BACK_PWM, spd);
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
void turn() {
  digitalWrite(RIGHT_A, HIGH);
  digitalWrite(RIGHT_B, LOW);
  digitalWrite(LEFT_A, HIGH);
  digitalWrite(LEFT_B, LOW);
  digitalWrite(BACK_A, LOW);
  digitalWrite(BACK_B, HIGH);
 // Serial.println("TURN");
}
void forward() {
  digitalWrite(RIGHT_A, HIGH);
  digitalWrite(RIGHT_B, LOW);
  digitalWrite(LEFT_A, LOW);
  digitalWrite(LEFT_B, HIGH);
  digitalWrite(BACK_A, LOW);
  digitalWrite(BACK_B, LOW);
}
void dir_speed() {
  analogWrite(LEFT_PWM, slow);
  analogWrite(RIGHT_PWM, slow);
  analogWrite(BACK_PWM, fast);
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

void setMotor(int dir, int spd, int dur) {
   if(dir == 0) {
    setSpeed(spd);
    stop();
    duration(dur);
  }
   else if(dir == 1) {
    setSpeed(spd);
    forward();
    duration(dur);
  }
   else if(dir == 2) {
    dir_speed();
    right();
    duration(dur);
  }
   else if(dir == 3) {
    dir_speed();
    left();
    duration(dur);
  }
  else if(dir == 4) {
    setSpeed(spd);
    back();
    duration(dur);
  }
  else if(dir == 5) {
    setSpeed(spd);
    turn();
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

void Read_distance() {
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

void ShowDistance() {
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

void Advoid_Check() {
  if(distance_L <= side_detection_distance && distance_R <= side_detection_distance && distance_F <= detection_distance) {
    Serial.println("U-turn");
  }
  else if(distance_L <= side_detection_distance) {
    setMotor(RIGHT, 0, turn_delay);
    front_check = 0;
    Serial.println("RIGHT");
  }
  else if(distance_R <= side_detection_distance) {
    setMotor(LEFT, 0, turn_delay);
    front_check = 0;
    Serial.println("LEFT");
  }
  else {
    setMotor(FORWARD, fast, 0);
    Serial.println("FORWARD");
  }
} 

void Advoid_Obstacles() {
  if(distance_F <= detection_distance) {
    setMotor(STOP, 0, 0);
    Serial.println("STOP");
    front_check += 1;
    //Serial.println(front_check);
    if(front_check >= front_stay_time) {
      if(distance_L <= side_detection_distance2 && distance_R <= side_detection_distance2) {
        Serial.println("U-TURN2");
        setMotor(TURN, fast, uturn_delay);
      }
      else if(distance_R <= detection_distance) {
        Serial.println("LEFT2");
        setMotor(LEFT, 0, turn_delay);
        front_check = 0;
      }
      else if(distance_L <= detection_distance) {
        Serial.println("RIGHT2");
        setMotor(RIGHT, 0, turn_delay);
        front_check = 0;
      }
      else {
        Serial.println("LEFT3");
        setMotor(LEFT, 0, turn_delay);
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
    Read_distance();
    Advoid_Obstacles();
    pre_time = cur_time;
    //ShowDistance();   
  }
  //setMotor(TURN, fast, 0);
  /*setMotor(FORWARD, fast, 0);
  delay(delayy);
  setMotor(BACK, fast, 0);
  delay(delayy);
  setMotor(RIGHT, 0, 0);
  delay(delayy);
  setMotor(LEFT, 0, 0);
  delay(delayy);*/
  
}
