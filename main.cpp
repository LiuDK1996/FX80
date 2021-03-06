#include <Arduino.h>
#include <NFC.h>
uint8_t aaa[] = "0000000000C90400032a8a";


void connectGSM(String cmd,char *res)
{
    while(1)
    {
        Serial.println(cmd);
        Serial1.println(cmd);
        delay(500);
        while(Serial.available()>0)
        {
            if(Serial.find(res))
            {
                delay(1000);
                return;
            }
        }
        delay(1000);
    }
}
void initGSM()
{
    connectGSM("AT","OK");//AT测试
    connectGSM("ATE1","OK");//开显示
    connectGSM("AT+CPIN?","READY");//是否插卡

}

void initGPRS()
{
    connectGSM("AT+CIPSHUT","OK");
    connectGSM("AT+CGATT=1","OK");
    connectGSM("AT+CSTT=\"CMNET\"","OK");
    connectGSM("AT+CIICR","OK");
    delay(1000);
    Serial1.println("AT+CIFSR");
    delay(1000);
    connectGSM("AT+CIPSTART=\"TCP\",\"122.114.122.174\",\"34176\"","OK");
}


void sendinit()
{
    Serial.print("AT+CSTT=\"CMNET\"\r\n");
    delay(500);
    Serial.print("AT+CIICR\r\n");
    delay(500);
    Serial.print("AT+CIFSR\r\n");
    delay(500);
    Serial.print("AT+CIPSTART=\"TCP\",\"122.114.122.174\",\"34176\"\r\n");
    delay(500);
    //Serial.print("");
    Serial.print("AT+CIPSEND\r\n");
    delay(500);
    Serial.write(aaa,22);
    Serial.println("");
    delay(500);
    Serial.write("1A\r\n");
    delay(500);

    Serial3.print("AT+CSTT=\"CMNET\"\r\n");
    delay(5000);
    Serial3.print("AT+CIICR\r\n");
    delay(5000);
    Serial3.print("AT+CIFSR\r\n");
    delay(5000);
    Serial3.print("AT+CIPSTART=\"TCP\",\"122.114.122.174\",\"34176\"\r\n");
 
    
   
   
}
void setup() 
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    Serial1.begin(9600);//SIM800C
    Serial2.begin(115200);//NFC
    Serial3.begin(9600);
    //delay(5000);
    //sendinit();
    //delay(500);
    
}


void loop()
{
   /*
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    NFC_loop();
    */
   initGSM();
   delay(1000);
   initGPRS();
}