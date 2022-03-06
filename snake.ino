//設定各接腳
int latchPin = 8;
int clockPin = 9;
int dataPin = 10;

int rightPin=2;
int downPin=3;
int upPin=4;
int leftPin=5;
bool rbn=0;
bool rbp=0;
bool dbn=0;
bool dbp=0;
bool ubn=0;
bool ubp=0;
bool lbn=0;
bool lbp=0;

int ntime=0;
int ptime=0;
int pausetime=600;

int dir=1; //1:left 2:up 3:down 4:right
int hx=16;
int hy=4;
byte colDataMatrix[8] = {
   B11111110,
   B11111101,
   B11111011,
   B11110111,
   B11101111,
   B11011111,
   B10111111,
   B01111111
}; //掃描

byte rowDataMatrix[8] = {
   B00000000,
   B00000000,
   B00000000,
   B00000000,
   B00010000,
   B00000000,
   B00000000,
   B00000000
}; //圖案

byte lose[8] = {
   B00000000,
   B10100101,
   B01000010,
   B10100101,
   B00000000,
   B00111100,
   B01000010,
   B10000001
};   
void setup() {
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(rightPin,INPUT_PULLUP);
  pinMode(downPin,INPUT_PULLUP);
  pinMode(upPin,INPUT_PULLUP);
  pinMode(leftPin,INPUT_PULLUP);
  Serial.begin(9600);
  
}
void left(){
    hx=hx<<1;
    if(hx==256) hx=1;
    rowDataMatrix[hy]=hx;
}
void up(){
  int phy;
  phy=hy;
   hy-=1;
   if(hy==-1)hy=7;
   rowDataMatrix[hy]=rowDataMatrix[phy];
   rowDataMatrix[phy]=0;
}
void down(){
  int phy;
  phy=hy;
   hy+=1;
   if(hy==8)hy=0;
    rowDataMatrix[hy]=rowDataMatrix[phy];
   rowDataMatrix[phy]=0;
}
void right(){
    hx=hx>>1;
    if(hx==0) hx=128;
    rowDataMatrix[hy]=hx;
    
}
void updateLed(){
  switch(dir){
    case 1: left();break;
    case 2: up();break;
    case 3: down();break;
    case 4: right();break;
    
    
    
    }
  
  }
void check(){
     rbn = digitalRead(rightPin);
     dbn = digitalRead(downPin);
     ubn = digitalRead(upPin);
     lbn = digitalRead(leftPin);
   if(rbn==0&&rbp==0){
    Serial.println("R");
    dir=4;
    rbp=1;
   }
   else if(rbn==1&&rbp==1)rbp=0;
   if(dbn==0&&dbp==0){
    Serial.println("D");
    dir=3;
    dbp=1;
   }
   else if(dbn==1&&dbp==1)dbp=0;
   if(ubn==0&&ubp==0){
    Serial.println("U");
    dir=2;
    ubp=1;
   }
   else if(ubn==1&&ubp==1)ubp=0;
   if(lbn==0&&lbp==0){
    Serial.println("L");
    dir=1;
    lbp=1;
   }
   else if(lbn==1&&lbp==1)lbp=0;
    ntime=millis();
    if(ntime-ptime>=pausetime){
      updateLed();
      Serial.print("now D:");
      Serial.print(dir);
      Serial.print(" hx: ");
      Serial.print(hx);
      Serial.print(" hy:");
      Serial.print(hy);
      Serial.println(" reflash");
   
      ptime=millis();
     }
 }
void printLed(){
    for(int i = 0; i < 8 ; i++){
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, colDataMatrix[i]);
    shiftOut(dataPin, clockPin, LSBFIRST, rowDataMatrix[i]);
    digitalWrite(latchPin,HIGH);
    delay(1);
  }
 }
void loop() {
  check();
  printLed();

}
