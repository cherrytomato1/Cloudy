
#define IN1 9

#define IN2 8

#define IN3 10

#define IN4 6

#define ENA 11

#define ENB 3


#define STOP 0

#define FORWARD 1

#define BACK 2

#define LEFT 3

#define RIGHT 4



int data;
int transdata;
int fast = 100;

char buffer[20];
char bufferIndex=0;


void forward() {

  digitalWrite(IN1, HIGH);

  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);

  digitalWrite(IN4, LOW);

}

void back() {

  digitalWrite(IN1, LOW);

  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);

  digitalWrite(IN4, HIGH);

}

void right() {

  digitalWrite(IN1, LOW);

  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);

  digitalWrite(IN4, LOW);

}

void left() {

  digitalWrite(IN1, HIGH);

  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);

  digitalWrite(IN4, HIGH);

}

void stop() {

  digitalWrite(IN1, LOW);

  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);

  digitalWrite(IN4, LOW);

}

void setMotor(int dir, int spd){

  if(dir == 0) {

    setSpeed(spd);

    stop();

  }

  else if(dir == 1) {

    setSpeed(spd);

    forward();

  }

  else if(dir == 2) {

    setSpeed(spd);

    back();

  }

  else if(dir == 3) {

    setSpeed(spd);

    left();

  }

  else if(dir == 4) {

    setSpeed(spd);

    right();

  }

}

void setSpeed(int spd) {

  analogWrite(ENA, spd);

  analogWrite(ENB, spd);

}

void setup() {

  pinMode(IN1, OUTPUT);

  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);

  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);

  pinMode(ENB, OUTPUT);

  Serial.begin(9600);


  delay(1000);

}



//void loop() {

 // if(Serial.available()){
  //  data=Serial.read();
 
   
   // transdata=data-48;
   // Serial.println(transdata);
 
   // setMotor(transdata,fast);

 // }

  //ShowDistance();

//}
void loop(){
  
  while(Serial.available()){
    buffer[bufferIndex]=Serial.read();
    bufferIndex++;
  }
  
   
  int pos=atoi(buffer);
  if(pos>=0){
    if(pos<7)
    Serial.println(pos);
    else{
    int state= pos/10000;
    Serial.println(state);
    
    int boxsize=(pos%10000)/1000;
    Serial.println(boxsize);
    
    int boxpoint=(pos%10000)%1000;
    Serial.println(boxpoint);
    }
    
  }
  
  //Serial.println(data);
 
 delay(100);
  
  for(int a=0; a<21;a++){
    buffer[a]=NULL;
  }
  bufferIndex=0;
}

