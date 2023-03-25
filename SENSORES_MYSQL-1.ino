#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

const int trigPin = 12;  //D4
const int echoPin = 14;  //D3

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

WiFiClient client;
MySQL_Connection conn((Client *)&client);
IPAddress server_addr(52, 165, 234, 7);  // MySQL server IP
char user[] = "";                  // MySQL user
char password[] = "";              // MySQL password

/////////////////
//Acelerometro///
/////////////////
char insertAcelerometro[]="INSERT INTO NASA_V.S_ACELEROMETRO (x, y, z, num_caidas, id_paciente) VALUES(%s, %s, %s, %s, 1)";
char query_1[128];

// Variables temporales
char c_x[16], c_y[16], c_z[16], c_contCaidas[16];// c_id_persona[16]
String dat;

// Variables para determinar medidas
int contCaidas;
float _x;
float _y;
float _z;
Adafruit_MPU6050 mpu;
#define D4 2

///////////////
//Ultrasonico//
///////////////
long duration;
float distanceCm;
float distanceInch;
int cantChoques;
char insertUltrasonico[]="INSERT INTO NASA_V.S_ULTRASONICA (distancia, num_choques, id_paciente) VALUES(%s,%s, 1)";
char query_2[128];

// Variables temporales
char c_distancia[16], c_num_choques[16];// c_id_persona[16]
String dat2;

float _distancia;
int _choques;

////////////////////////////////////////////////////////////////
// Sección de inicialización
////////////////////////////////////////////////////////////////

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  /////
    while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");
  
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  
  Serial.println("MPU6050 Found!");
  /////
  
 wifiConnect();
  Serial.println("Conectando a la DB");

  while(conn.connect(server_addr, 3306, user, password) != true){
    delay(200);
    Serial.print(".");
  };

  Serial.println("Conectado al servidor SQL");
  pinMode(D4, OUTPUT);
  
  Serial.println("");
  delay(10);
}

////////////////////////////////////////////////////////////////
// Fin de sección de inicialización
////////////////////////////////////////////////////////////////

void wifiConnect() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  //Conexión a la red WiFi
    Serial.print("Conectado a WiFi --> ");
    Serial.print(WIFI_SSID); Serial.println(" ...");

    int teller = 0;
    while (WiFi.status() != WL_CONNECTED) {  //Esperar a establecer conexión WiFi
        delay(1000);
        Serial.println(++teller); Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("WiFi conectado!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}  //End wifiConnect()

///////////////////////////////////////////////////////////////
// LOOP
///////////////////////////////////////////////////////////////


void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);

  if(a.acceleration.z > -7.00){
    Serial.println("");
    Serial.print(" Se cayó la persona ");
    Serial.println("");
    contCaidas = contCaidas + 1;
    Serial.print("Veces que ha caido: ");
    Serial.print(contCaidas);
    Serial.println("");
    digitalWrite(D4,LOW);
    delay(1000);
    };

  digitalWrite(D4,HIGH);
  Serial.print(" Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  _x = a.acceleration.x;
  _y = a.acceleration.y;
  _z = a.acceleration.z;

// char c_x[16], c_y[16], c_z[16], c_contCaidas[16], c_id_persona[16];
// String dat;

  dat = String(_x);
  dat.toCharArray(c_x, 16);

  dat = String(_y);
  dat.toCharArray(c_y, 16);

  dat = String(_z);
  dat.toCharArray(c_z, 16);

  dat = String(contCaidas);
  dat.toCharArray(c_contCaidas, 16);
  
  sprintf(query_1, insertAcelerometro, c_x, c_y, c_z, c_contCaidas);
  Serial.println("Registandro datos");
  Serial.println(query_1);

  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    cur_mem->execute(query_1);
    delete cur_mem;

  

////////////////////////////////////////////////////////////////

// Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;

  if(distanceCm >= 803){
    Serial.println("La persona choco ");
    cantChoques = cantChoques + 1;
  } else if (distanceCm < 25) {
    Serial.println("La persona está a punto de chocar");
    }
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  Serial.print("Distance (inch): ");
  Serial.println(distanceInch);
  Serial.print("Cantidad de choques: ");
  Serial.println(cantChoques);
  delay(1000);


  
  _distancia = distanceCm;
  _choques = cantChoques;

  dat2 = String(_distancia);
  dat2.toCharArray(c_distancia, 16);

  dat2 = String(_choques);
  dat2.toCharArray(c_num_choques, 16);
  
  sprintf(query_2, insertUltrasonico, c_distancia,  c_num_choques);
  Serial.println("Registandro datos");
  Serial.println(query_2);

  MySQL_Cursor *cur_mem2 = new MySQL_Cursor(&conn);
    cur_mem2->execute(query_2);
    delete cur_mem2;

    if(WiFi.status() != WL_CONNECTED) {
        wifiConnect();
    }
  Serial.println("");
  delay(5000);
}
