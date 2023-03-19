#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

WiFiClient Client;

int buttonRight = 16; // D0
int buttonRight_C = 0; 

int buttonCenter = 12; //D5
int buttonCenter_C = 0; 

int buttonLeft = 2; // D4
int buttonLeft_C = 0; 

  int Menu = 0;
  int selectMenu = 0;
  int redscore = 0;
  int bluescore = 0;
  int selectTeam = 0;
  int selectedTeam = 0;
  int socreComplete = 0;
  int quarter = 1;
  int ballTime = 0;
  int endSport = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("System Start");
  Serial.println(Menu); 
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  
  pinMode(buttonRight, INPUT);
  pinMode(buttonCenter, INPUT);
  pinMode(buttonLeft, INPUT);

  //lcd.setCursor(0, 0); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 0 บรรทัดที่ 0
  //lcd.print("ArduinoAll TEST"); //พิมพ์ข้อความ
  //lcd.setCursor(2, 1); // กำหนดตำแหน่งเคอร์เซอร์ที่ แถวที่ 2 บรรทัดที่ 1
  //lcd.print("arduinoall.com"); //พิมพ์ข้อความ "arduinoall.com"
  //lcd.display();        //เปิดหน้าจอ
  //lcd.backlight();      //เปิดไฟ backlight 
  //lcd.clear();          //ล้างหน้าจอ
  //lcd.setCursor(0, 0);  //ตั่งค่าcursor
  //lcd.print("num = ");    //แสดงข้อข้อความ

  WiFiManager wm;
  wm.autoConnect("AutoConnectAP");
  Serial.println("Connected");

}
void loop()
{
  buttonRight_C = digitalRead(buttonRight);
  buttonCenter_C = digitalRead(buttonCenter);
  buttonLeft_C = digitalRead(buttonLeft);
  
  if (buttonRight_C == HIGH) 
  {
    Serial.println("Right Press");
    if(selectMenu == 0){Menu = Menu + 1;}

    if(selectMenu == 1 && selectedTeam == 0){selectTeam = selectTeam + 1;}

    if(selectedTeam == 1 && selectTeam == 1){bluescore = bluescore + 1;}

    if(selectedTeam == 1 && selectTeam == 0){redscore = redscore + 1;}

    if(selectedTeam == 1 && selectTeam == 2){quarter = quarter + 1;}

    if(selectedTeam == 1 && selectTeam == 2){ballTime = ballTime + 1;}  

    delay(200);
  }

  if (buttonLeft_C == HIGH) 
  {

    Serial.println("Left Press");

    if(selectMenu == 0){Menu = Menu - 1;}

    if(selectMenu == 1 && selectedTeam == 0){selectTeam = selectTeam - 1;}
    
    if(selectedTeam == 1 && selectTeam == 1){bluescore = bluescore - 1;}

    if(selectedTeam == 1 && selectTeam == 0){redscore = redscore - 1;}

    if(selectedTeam == 1 && selectTeam == 2){quarter = quarter - 1;}
    
    if(selectedTeam == 1 && selectTeam == 2){ballTime = ballTime - 1;}  
    
    delay(200);
  }

  if (buttonCenter_C == HIGH) 
  {
    Serial.println("Center Press");
    
    UpToDatabase();

    if(selectMenu == 0)
    {
      selectMenu = 1;
    }
    else if(selectMenu == 1)
    {
      selectedTeam = 1;
    }
    
    if (selectedTeam == 1 && socreComplete == 1)
    {
      selectedTeam = 0;
      selectTeam = 0;
      socreComplete = 0;
    }


    if (selectedTeam == 1 && selectTeam == 3)
    {
      endSport = 1;
      UpToDatabase();
      
      Menu = 0;
      selectMenu = 0;
      redscore = 0;
      bluescore = 0;
      selectTeam = 0;
      selectedTeam = 0;
      socreComplete = 0;
      quarter = 1;
      ballTime = 0;
      endSport = 0;
      Serial.println("ClearData");
    }

    delay(200);
  }

  if(Menu == 0 && selectMenu == 0)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("1:Basketball");
    delay(200);
  }

  if(Menu == 1 && selectMenu == 0)
  {
    lcd.clear(); 
    lcd.setCursor(0, 0);  
    lcd.print("2:Football");
    delay(200);
  }

//Sport Limit
  if(Menu == -1 || Menu == 2)
  {
    if(Menu == -1){Menu = 0;}
    if(Menu == 2){Menu = 1;}
  }

//Select Limit
  if(selectTeam == -1 || selectTeam == 4)
  {
    if(selectTeam == -1){selectTeam = 0;}
    if(selectTeam == 4){selectTeam = 3;}
  }

//Quter Limit
  if(quarter <= 0 || quarter >= 5)
  {
    if(quarter <= 0){quarter = 1;}
    if(quarter >= 5){quarter = 4;}
  }

//Score Limit
  if(redscore == -1 || bluescore == -1)
  {
    if(redscore == -1){redscore = 0;}
    if(bluescore == -1){bluescore = 0;}
  }  

//Ball Limit
  if(ballTime == -1 || ballTime == 2)
  {
    if(ballTime == -1){ballTime = 0;}
    if(ballTime == 2){ballTime = 1;}
  }  


//BASKETBALL
  if(selectMenu == 1 && Menu == 0)
  {
    if(selectedTeam == 0 && selectTeam == 0)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      lcd.print("BASKETBALL   Q:" + String(quarter));
      lcd.setCursor(0, 1);  
      lcd.print(">RED:" + String(redscore) + " | BLUE:" + String(bluescore));
      delay(200);
    }
    if(selectedTeam == 0 && selectTeam == 1)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      lcd.print("BASKETBALL   Q:" + String(quarter));
      lcd.setCursor(0, 1);  
      lcd.print("RED:" + String(redscore) + " |>BLUE:" + String(bluescore));
      delay(200);
    }

    if(selectedTeam == 0 && selectTeam == 2)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      lcd.print("BASKETBALL   Q:" + String(quarter));
      lcd.setCursor(0, 1);  
      lcd.print(">Quarter : " + String(quarter));
      delay(200);
    }
    
    if(selectedTeam == 0 && selectTeam == 3)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      lcd.print("BASKETBALL   Q:" + String(quarter));
      lcd.setCursor(0, 1);  
      lcd.print(">EXIT?");
      delay(200);
    }

    if(selectedTeam == 1 && selectTeam == 0)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      lcd.print("BASKETBALL   Q:" + String(quarter));
      lcd.setCursor(0, 1);  
      lcd.print("RED |  -" + String(redscore) + "+");
      delay(200);
      socreComplete = 1;
    }

    if(selectedTeam == 1 && selectTeam == 1)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      lcd.print("BASKETBALL   Q:" + String(quarter));
      lcd.setCursor(0, 1);  
      lcd.print("BLUE |  -" + String(bluescore) + "+");
      delay(200);
      socreComplete = 1;
    }

    if(selectedTeam == 1 && selectTeam == 2)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      lcd.print("BASKETBALL   Q:" + String(quarter));
      lcd.setCursor(0, 1);  
      lcd.print(" Quarter |  -" + String(quarter) + "+");
      delay(200);
      socreComplete = 1;
    }
  }


//FOOTBALL
 if(selectMenu == 1 && Menu == 1)
  {
    if(selectedTeam == 0 && selectTeam == 0)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      if(ballTime == 0){lcd.print("FOOTBALL     F-h");}
      else{lcd.print("FOOTBALL     S-h");}
      lcd.setCursor(0, 1);  
      lcd.print(">RED:" + String(redscore) + " | BLUE:" + String(bluescore));
      delay(200);
    }
    if(selectedTeam == 0 && selectTeam == 1)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      if(ballTime == 0){lcd.print("FOOTBALL     F-h");}
      else{lcd.print("FOOTBALL     S-h");}
      lcd.setCursor(0, 1);  
      lcd.print("RED:" + String(redscore) + " |>BLUE:" + String(bluescore));
      delay(200);
    }

    if(selectedTeam == 0 && selectTeam == 2)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      if(ballTime == 0){lcd.print("FOOTBALL     F-h");}
      else{lcd.print("FOOTBALL     S-h");}
      lcd.setCursor(0, 1);  
      if(ballTime == 0){lcd.print(">Frist-haft");}
      else{lcd.print(">Second-half");}
      delay(200);
    }
    
    if(selectedTeam == 0 && selectTeam == 3)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      if(ballTime == 0){lcd.print("FOOTBALL     F-h");}
      else{lcd.print("FOOTBALL     S-h");}
      lcd.setCursor(0, 1);  
      lcd.print(">EXIT?");
      delay(200);
    }

    if(selectedTeam == 1 && selectTeam == 0)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      if(ballTime == 0){lcd.print("FOOTBALL     F-h");}
      else{lcd.print("FOOTBALL     S-h");}
      lcd.setCursor(0, 1);  
      lcd.print("RED |  -" + String(redscore) + "+");
      delay(200);
      socreComplete = 1;
    }

    if(selectedTeam == 1 && selectTeam == 1)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      if(ballTime == 0){lcd.print("FOOTBALL     F-h");}
      else{lcd.print("FOOTBALL     S-h");}
      lcd.setCursor(0, 1);  
      lcd.print("BLUE |  -" + String(bluescore) + "+");
      delay(200);
      socreComplete = 1;
    }

    if(selectedTeam == 1 && selectTeam == 2)
    {
      lcd.clear(); 
      lcd.setCursor(0, 0);  
      if(ballTime == 0){lcd.print("FOOTBALL     F-h");}
      else{lcd.print("FOOTBALL     S-h");}
      lcd.setCursor(0, 1);
      if(ballTime == 0){lcd.print("Frist-haft >>");}
      else{lcd.print("<< Second-half");}
      delay(200);
      socreComplete = 1;
    }
  }
}

void UpToDatabase()
{
  HTTPClient http;
  http.begin(Client,"http://192.168.235.247/ScoreboardProject/addScore.php");
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpCode = http.POST("sport=" +  String(Menu) + 
                           "&redscore=" + String(redscore) +
                           "&bluescore=" + String(bluescore) + 
                           "&ballTime=" + String(ballTime) + 
                           "&quarter=" + String(quarter) + 
                           "&endSport=" + String(endSport));
                                                      
  //http://192.168.235.247/ScoreboardProject/addScore.php?sport=%22Sport%22&redscore=0&bluescore=0&ballTime=0&quarter=1&endSport=0
  //http://localhost/ScoreboardProject/addScore.php?sport=%22Sport%22&redscore=0&bluescore=0&ballTime=0&quarter=1&endSport=0

  Serial.println("sport=" +  String(Menu) + 
                  "&redscore=" + String(redscore) +
                  "&bluescore=" + String(bluescore) + 
                  "&ballTime=" + String(ballTime) + 
                  "&quarter=" + String(quarter) + 
                  "&endSport=" + String(endSport));
  
  if (httpCode > 0) {
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    //Can't Connect
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
} 