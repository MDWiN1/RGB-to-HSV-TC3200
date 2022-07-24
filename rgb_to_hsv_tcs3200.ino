//Nama : Muhamad Dwi Novianto
//NIM  : D40010068
//Program Tugas Akhir

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

int pinBuzzer = 12;
float redval=0;
float greenval=0;
float blueval=0;
float H, S, V;
float red,green,blue,r,g,b;

void setup() {
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Tugas Akhir ");
  delay(2000);
  lcd.clear();
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(pinBuzzer, OUTPUT);
  pinMode(sensorOut, INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  red = pulseIn(sensorOut, LOW);
  r = map(red, 32,162,255,0);
//  Serial.print("R = ");
//  Serial.print(r );
  delay(200);
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  green = pulseIn(sensorOut, LOW);
  g = map(green, 31,198,255,0);
//  Serial.print(" G = ");
//  Serial.print(g );
  delay(200);
 
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  blue = pulseIn(sensorOut, LOW);
  b = map(blue, 31,181,255,0);
//  Serial.print(" B = ");
//  Serial.print(b);
  delay(200);
  redval = constrain(r, 0, 255);
  greenval = constrain(g, 0, 255);
  blueval = constrain(b, 0, 255);
  Serial.print(" R = ");
  Serial.print(redval);
  Serial.print(" G = ");
  Serial.print(greenval);
  Serial.print(" B = ");
  Serial.println(blueval);
  HSV();
  warna();
}
void HSV(){
  if (redval > blueval && redval > greenval ) {
    float cmin = min(greenval,blueval);
//    Serial.print("cmin : ");
//    Serial.print(cmin);
//    delay(200);
    H = 60*(0 + (greenval-blueval)/(redval-cmin));
    if (H < 0){
      H = H +360;
      Serial.print(" H : ");
      Serial.print(H);
    }
    else {
      Serial.print(" H : ");
      Serial.print(H);
    }
    delay(200);
    S = ((redval-cmin)/redval)*100;
    Serial.print(" S : ");
    Serial.print(S);
    Serial.print("% ");
    delay(200);
    V = (redval/255)*100;
    Serial.print(" V : ");
    Serial.print(V);
    Serial.println("% ");
    delay(200);
  }
  else if (greenval > redval && greenval > blueval) {
    float cmin = min(redval,blueval);
//    Serial.print("cmin : ");
//    Serial.print(cmin);
//    delay(200);
    H = 60*(2 + (blueval-redval)/(greenval-cmin));
    Serial.print(" H : ");
    Serial.print(H);
    delay(200);
    S = ((greenval-cmin)/greenval)*100;
    Serial.print(" S : ");
    Serial.print(S);
    Serial.print("% ");
    delay(200);
    V = (greenval/255)*100;
    Serial.print(" V : ");
    Serial.print(V);
    Serial.println("% ");
    delay(200);
  }
  else if (blueval > redval && blueval > greenval) {
    float cmin = min(redval,greenval);
//    Serial.print("cmin : ");
//    Serial.print(cmin);
//    delay(200);
    H = 60*(4 + (redval-greenval)/(blueval-cmin));
    Serial.print(" H : ");
    Serial.print(H);
    delay(200);
    S = ((blueval-cmin)/blueval)*100;
    Serial.print(" S : ");
    Serial.print(S);
    Serial.print("% ");
    delay(200);
    V = (blueval/255)*100;
    Serial.print(" V : ");
    Serial.print(V);
    Serial.println("% ");
    delay(200);
  }
}

void warna(){
  if( H >= 85 && H <= 160 ) {
    Serial.println(" -  GREEN detected!");
    tone(pinBuzzer, 500);
    delay(500);
    noTone(pinBuzzer);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Warna :");
    lcd.setCursor(5, 1);
    lcd.print("Hijau ");
  }
  else if(H > 40 && H <= 70 ) {
    Serial.println(" - YELLOW detected!");
    tone(pinBuzzer, 500);
    delay(500);
    noTone(pinBuzzer);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Warna :");
    lcd.setCursor(5, 1);
    lcd.print("Kuning  ");
  }
  else if(H >= 15 && H <= 40  ){
    Serial.println(" - ORANGE detected!");
    tone(pinBuzzer, 500);
    delay(500);
    noTone(pinBuzzer);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Warna :");
    lcd.setCursor(5, 1);
    lcd.print("Orange  ");
  }
   else if(H >= 0 && H <= 15 ){
    Serial.println(" - RED detected!");
    tone(pinBuzzer, 500);
    delay(500);
    noTone(pinBuzzer);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Warna :");
    lcd.setCursor(5, 1);
    lcd.print("Merah  ");
  }
   else if(H > 330 && H <= 360 ){
    Serial.println(" - RED detected!");
    tone(pinBuzzer, 500);
    delay(500);
    noTone(pinBuzzer);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Warna :");
    lcd.setCursor(5, 1);
    lcd.print("Merah  ");
  }
  else{
    Serial.println(" - NONE");
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("Warna :");
    lcd.setCursor(3, 1);
    lcd.print("Tidak Ada");
    }
}
