
//#include <NewPing.h>                // SE DEFINE AL SENSOR ULTRASONICO 
#include <Servo.h>                  // SE DEFINE AL SERVOMOTOR. 

const int TRIG_PIN = 2;   //Pin digital 2 para el Trigger del sensor
const int ECHO_PIN = 10;      //Pin digital 3 para el Echo del sensor

//#define TRIG_PIN A0                 // SE DEFINE EL SENSOR ULTRASONICO, TRIG VA AL PIN A0 DEL ARDUINO UNO.#define ECHO_PIN A1                 // SE DEFINE EL SENSOR ULTRASONICO, ECHO VA AL PIN A1 ARDUINO UNO.
//#define MAX_DISTANCE 200            
//NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 
Servo myservo;   

boolean goesForward = false;         
int distance = 100;               
int speedSet = 0;               
                                  
const int motorPin1  = 8;          //MOTOR 1 IZQUIERDA
const int motorPin2  = 9;          
const int motorPin3  = 5;          //MOTOR 2 DERECHA
const int motorPin4  = 6;
const int Enable = 11;  

void setup() {

  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT); //pin como salida
  pinMode(ECHO_PIN, INPUT);  //pin como entrada
  digitalWrite(TRIG_PIN, LOW);//Inicializamos el pin con 0
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(Enable, OUTPUT);
  
  
  myservo.attach(3);              // PIN PWM DEL SERVO VA AL PIN 3 DEL ARDUINO UNO.
  myservo.write(115);              // VELOCIDAD DEL SERVO.
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  digitalWrite(Enable, LOW);
}

void loop() {
  
  int cm = ping(TRIG_PIN, ECHO_PIN);
  Serial.print("DistanciA: ");
  Serial.println(cm);
  Serial.print("cm");
  Serial.println();
 
 int distanceR = 0;
 int distanceL = 0;
 delay(40);

  long t;
  long d;
  long DistanciaReal;
  long DistanciaDeseada = 10;
  long Error;

  Error = DistanciaDeseada - cm;
  Serial.print("Error: ");
  Serial.print(Error);
  Serial.println();
  
  while(Error>0) { // 0%
    analogWrite(motorPin2, 0);
    cm = ping(TRIG_PIN, ECHO_PIN);
    Error = DistanciaDeseada - cm;
    delay(100);
  };
  while(Error<=0) {
    // moveStop();
   int errorAbs = abs(Error);
   int K = 5;
   int Velocidad = K * errorAbs;
   int salida = map(Velocidad, 0, 100, 0, 255);
   if(salida>255) salida=255;
  //  Serial.print("Velocidad: ");
  //   Serial.print(Velocidad);//Enviamos serialmente el valor de la distancia
  //   Serial.println();
    Serial.print("Salida: ");
    Serial.print(salida);      //Enviamos serialmente el valor de la distancia
    Serial.println();
    // Serial.println();

    analogWrite(motorPin2, salida);
    //analogWrite(motorPin3, salida);
    cm = ping(TRIG_PIN, ECHO_PIN);
    Error = DistanciaDeseada - cm;

    delay(100);
  };

  delay(1000);
// if(distance<=15)                //SE ACTIVA EL SENSOR ULTRASONICO CUANDO DETECTA OBSTACULOS A MENOS DE 15CM.
// {
//  moveStop();                   
//  delay(200);                   
//  moveBackward();              //EL CARRITO SE DETIENE Y SE VA HACIA ATRAS POR 800 MILISEGUNDOS.
//  delay(800);                      
  
//  moveStop();
//  delay(200);
//  distanceR = lookRight();       
//  delay(200);
//  distanceL = lookLeft();         
//  delay(200);

//  if(distanceR>=distanceL)
//  {
//    turnRight();           
//    moveStop();
//  }
  
//      else
      
//  {
//    turnLeft();            
//    moveStop();
//  }
  
// }else   
                        
// {
//  moveForward();         
// }
// distance = readPing();
// } 
}
int lookRight()          
{
    myservo.write(50);    
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115);        
    return distance;
}

int lookLeft()
{
    myservo.write(170); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(115); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  // int cm = sonar.ping_cm();
 // if(cm==0)
  {
  //  cm = 250;
  }
 // return cm;
  
}

void moveStop() {
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 0);
  } 
  
void moveForward() {        //CARRITO AVANZA


    //analogWrite(motorPin1, 180);       
    analogWrite(motorPin2, 255);
    //analogWrite(motorPin3, 180);     
    //analogWrite(motorPin4, 0);  
  
}

void moveBackward() {        //HACIA ATRAS
    
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 180);       
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);      
  
}  

void turnRight() {     //GIRA A LA DERECHA Y AVANZA
  
    analogWrite(motorPin1, 180);     
    analogWrite(motorPin2, 0);
    analogWrite(motorPin3, 0);
    analogWrite(motorPin4, 180);   
    delay(300);
    moveForward();      
  
} 
 
void turnLeft() {           //GIRA A LA IZQUIERDA Y AVANZA
    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 255);   
    analogWrite(motorPin3, 255);    
    analogWrite(motorPin4, 0);     
    delay(300);
    moveForward();
}  

int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;
  
  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  
  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  
  distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
  return distanceCm;
}
