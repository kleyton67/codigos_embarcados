#include <WiFi.h>

// Quais libs são utilizadas aqui?
// -- https://github.com/Syafiqlim/ESP32_MySQL


// Debug Level from 0 to 4
#define _ESP32_MYSQL_LOGLEVEL_      1

#include <ESP32_MySQL.h>

// Replace with your own network credentials
const char* ssid = "casa_local";
const char* password = "Tit@ns0primid0s";

//Configurações MySQL
char user[]         = "esp";              // MySQL user login username
char pass_db[]     = "esp";          // MySQL user login password

IPAddress server(10, 28, 33, 100);

uint16_t server_port = 3313;    // MySQL server port (default : 3306)

char default_database[] = "esp";           //default DB
char default_table[]    = "esp_message";          //default table

char default_column[] = "message";   //default column

String default_value    = "Eu passei por aqui";    //default value (make sure datatype same with column of DB table, like you can use String for VARCHAR)

// Sample query
String INSERT_SQL = String("INSERT INTO ") + default_database + "." + default_table 
                 + " (" + default_column + ")" + " VALUES ('" + default_value + "')";

ESP32_MySQL_Connection conn((Client *)&client);

ESP32_MySQL_Query *query_mem;


void runInsert()
{
  // Initiate the query class instance
  ESP32_MySQL_Query query_mem = ESP32_MySQL_Query(&conn);

  if (conn.connected())
  {
    ESP32_MYSQL_DISPLAY(INSERT_SQL);
    
    // Execute the query
    if ( !query_mem.execute(INSERT_SQL.c_str()) )
    {
      ESP32_MYSQL_DISPLAY("Insert error");
    }
    else
    {
      ESP32_MYSQL_DISPLAY("Data Inserted.");
    }
  }
  else
  {
    ESP32_MYSQL_DISPLAY("Disconnected from Server. Can't insert.");
  }
}

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initWiFi();
  ESP32_MySQL_Query query_mem = ESP32_MySQL_Query(&conn);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Hi");
  if (conn.connectNonBlocking(server, server_port, user, pass_db) != RESULT_FAIL)
  {
    delay(500);
    runInsert();
    conn.close();                     // close the connection
  } 
  else 
  {
    Serial.println("\nMySQL Connection Failed.");
  }
}
