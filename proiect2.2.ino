#include <Servo.h>
#include <SoftwareSerial.h>

// Pinii motor 1
#define mpin00 5
#define mpin01 6

// Pinii motor 2
#define mpin10 3
#define mpin11 11

SoftwareSerial bluetooth(12, 13); //rx tx

void setup()
{ // configurarea pinilor motor ca iesire, initial valoare 0
  digitalWrite(mpin00, 0);
  digitalWrite(mpin01, 0);
  digitalWrite(mpin10, 0);
  digitalWrite(mpin11, 0);
  pinMode (mpin00, OUTPUT);
  pinMode (mpin01, OUTPUT);
  pinMode (mpin10, OUTPUT);
  pinMode (mpin11, OUTPUT);

  //start comunicare Bluetooth
  Serial.begin(9600);
  bluetooth.begin(9600);

}

//// FUNCTIILE PENTRU DEPLASARE ////
void moveFront()
{  
  StartMotor(mpin00, mpin01, 0, 79);
  StartMotor(mpin10, mpin11, 0, 79);
  delay(500);

  StartMotor(mpin00, mpin01, 0, 0);
  StartMotor(mpin10, mpin11, 0, 0);
  delay(2000);
}

void moveFrontDreptunghi()
{  
  StartMotor(mpin00, mpin01, 0, 79);
  StartMotor(mpin10, mpin11, 0, 79); 
  delay(700);

  StartMotor(mpin00, mpin01, 0, 0);
  StartMotor(mpin10, mpin11, 0, 0);
  delay(2000);
  
}

void moveFrontTriunghi()
{  
  StartMotor(mpin00, mpin01, 0, 99);
  StartMotor(mpin10, mpin11, 0, 99); 
  delay(700);

  StartMotor(mpin00, mpin01, 0, 0);
  StartMotor(mpin10, mpin11, 0, 0);
  delay(2000);
  
}

void rotation()
{
   StartMotor(mpin00, mpin01, 0, 39);
   StartMotor(mpin10, mpin11, 1, 39);
   delay(925); 
  
   StartMotor(mpin00, mpin01, 0, 0);
   StartMotor(mpin10, mpin11, 0, 0);
   delay(2000);
}

void rotationTriunghi()
{
   StartMotor(mpin00, mpin01, 0, 39);
   StartMotor(mpin10, mpin11, 1, 39);
   delay(725); 
  
   StartMotor(mpin00, mpin01, 0, 0);
   StartMotor(mpin10, mpin11, 0, 0);
   delay(2000);
}


//// REALIZAREA FIGURILOR GEOMETRICE ////
void patrat()
{ 
  moveFront();
  rotation();
  moveFront();
  rotation();
  moveFront();
  rotation();
  moveFront();
}

void dreptunghi()
{ 
  moveFrontDreptunghi();
  rotation();
  moveFront();
  rotation();
  moveFrontDreptunghi();
  rotation();
  moveFront();
}

void triunghi()
{ 
  moveFront();
  rotationTriunghi();
  moveFrontTriunghi();
  rotationTriunghi();
  moveFrontTriunghi();
}


void rotationCerc()
{
   StartMotor(mpin00, mpin01, 0, 79);
   delay(5000); 
  
   StartMotor(mpin00, mpin01, 0, 0);
   delay(2000);
}

void cerc()
{
   rotationCerc();
}

void StartMotor (int m1, int m2, int forward, int speed)
{ 
  
  if (speed == 0)
    // oprire
  {
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
  }
  else
  {
    if (forward)
    {
      digitalWrite(m2, 0);
      analogWrite(m1, speed); // folosire PWM
    }
    else
    {
      digitalWrite(m1, 0);
      analogWrite(m2, speed);
    }
  }
}

//// RECEPTIA COMENZILOR DIN BLUETOOTH ////
String obiect="";

String bluetoothRecieve()
{
  while (bluetooth.available()) 
  {
   obiect=bluetooth.readString();
  }
 
  return obiect;
}


void loop()
{
  String obj = bluetoothRecieve();

  //// INTERPRETARAE COMENZILOR DIN BLUETOOTH ////
  if (obj.startsWith("patrat")==true)
  {  
    Serial.println(obj);
    obj="";
    obiect="";
    patrat();
  }

  if (obj.startsWith("dreptunghi")==true)
  {  
    Serial.println(obj);
    obj="";
    obiect="";
    dreptunghi();
  }

  if (obj.startsWith("cerc")==true)
  {
    Serial.println(obj);
    obiect = "";
    obj="";
    cerc();
  }
  
  if (obj.startsWith("triunghi")==true)
  {
    Serial.println(obj);
    obiect = "";
    obj="";
    triunghi();
  }

}
