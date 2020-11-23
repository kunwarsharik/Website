#include <Servo.h>
Servo bm;
Servo gm;
Servo udm;
int flagw=0;
int flaglr=0;
int in =2;// echo
int out=3;//trigger
int initialize=0;
int o =0;
int ud_down=0;
int flagud=0;
int ud_up=0;
int break_flag=0;
int g=0;// green side m h
int b =0;// b side m h
int g_prev=0;
int b_prev=0;
int flagdis=0;
long dur;
long dis;
long tocm;
long sec;
int flaglr_prev=0;
void setup() {
  Serial.begin(9600);
  bm.attach(9);
  gm.attach(10);
  udm.attach(5);
  pinMode(in, INPUT);
  pinMode(out, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, INPUT);//niche ka mark
  pinMode(7, INPUT);//upar ka mark
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  gm.write(99);
  bm.write(88);
}

void loop() {
  o=digitalRead(8);
  digitalWrite(4,HIGH);
  Serial.print(digitalRead(7));
    if (o==1){
      while(1){
      if (initialize==0){
        while(1){
          
          for (int i=0;i<=50;i++){
            ud_up=digitalRead(7);
            if (ud_up==1){
              while(ud_up==1){
              ud_up=digitalRead(7);
              initialize=1;
              gm.write(99);
              bm.write(88);
              udm.write(110);
              delay(2000);
              udm.write(123);
              Serial.println("ab break kra niche krne ka");
              //break;// while loop breaked
              }
              if (initialize==1){
          break;//while loop break
          } }
            else{
              udm.write(138);
              delay(1000);
              gm.write(99);
              bm.write(88);
              Serial.println("inside up");
                }
            }//for end
        if (initialize==1){
          Serial.println("initialize ho chuka h");
          break;//while loop break
          }
        }
        
      }//init wala if end

      else {//initialize==1 ki trah h
        g = digitalRead(12);
        b = digitalRead(13);
        flagw=digitalRead(11);
        
        digitalWrite(out,LOW);
        delayMicroseconds(2);
        udm.write(123);
        digitalWrite(out,HIGH);
        delayMicroseconds(10);
        digitalWrite(out,LOW);
        dur=pulseIn(in,HIGH);
        tocm=dur / 29 / 2;
        if((tocm>15)&&(tocm<50)){
        digitalWrite(4,LOW);
        }
        else{
        digitalWrite(4,HIGH);
        }
        Serial.print(g);
        Serial.print(b);
        Serial.print(flagw);
        Serial.println("-");
        
        if(g==1){
            flaglr=1;
            gm.write(99);
          }
        if(b==1){
          flaglr=0;
          bm.write(88);
        }
        
        if (((g==1)&&(g_prev==0))||((b==1)&&(b_prev==0))){
          ud_up = digitalRead(7);
          ud_down=digitalRead(6);
          if(ud_down==1){
            Serial.println("upar ka command mil gya");
            flagud=1;
            }
          if(ud_up==1){
            flagud=0;
            initialize=0;
//            break_flag=1;
            gm.write(99);
            bm.write(88);
            udm.write(123);
            digitalWrite(4,HIGH);
            break;//break the while jo upar ke else se bahar ka h
            }
          if(flagud==1){
            gm.write(99);
            bm.write(88);
            udm.write(138);
            delay(2500);
            Serial.println("upar ka command");
            digitalWrite(4,HIGH);
            }
          
          if(flagud==0){
            gm.write(99);
            bm.write(88);
            udm.write(100);
            delay(3000);
            Serial.println("niche ka command");
            digitalWrite(4,HIGH);
            
            }
          udm.write(123);
        }
      if (flaglr==0){
        if (flagw==0){
          //toward green motor
           gm.write(150);
           delay(350);
           bm.write(0);
           delay(400);
           digitalWrite(out,LOW);
           delayMicroseconds(2);
           udm.write(123);
           digitalWrite(out,HIGH);
           delayMicroseconds(10);
           digitalWrite(out,LOW);
           dur=pulseIn(in,HIGH);
           tocm=dur / 29 / 2;
           if((tocm>15)&&(tocm<50)){
           digitalWrite(4,LOW);
           }
           else{
           digitalWrite(4,HIGH);
           }
        }
        if (flagw==1){
            for (int i=0;i<3;i++){
              gm.write(150);
              bm.write(88);
              delay(300);
              
              digitalWrite(out,LOW);
              delayMicroseconds(2);
              udm.write(123);
              digitalWrite(out,HIGH);
              delayMicroseconds(10);
              digitalWrite(out,LOW);
              dur=pulseIn(in,HIGH);
              tocm=dur / 29 / 2;
              if((tocm>15)&&(tocm<50)){
              digitalWrite(4,LOW);
              }
              else{
              digitalWrite(4,HIGH);
              }
            
            }
          }
      }// flaglr==0 k liye
      
      if (flaglr==1){
        if (flagw==0){
        //toward brown motor
         gm.write(58);// wese 63,140 use kr re thee.
         delay(350);
         bm.write(179);
         delay(400);
         digitalWrite(out,LOW);
         delayMicroseconds(2);
         udm.write(123);
         digitalWrite(out,HIGH);
         delayMicroseconds(10);
         digitalWrite(out,LOW);
         dur=pulseIn(in,HIGH);
         tocm=dur / 29 / 2;
         if((tocm>15)&&(tocm<50)){
           digitalWrite(4,LOW);
           }
         else{
           digitalWrite(4,HIGH);
           }
        }
    
        if(flagw==1){
          for (int i=0;i<3;i++){
            bm.write(179);
            gm.write(99);
            delay(300);

            digitalWrite(out,LOW);
            delayMicroseconds(2);
            udm.write(123);
            digitalWrite(out,HIGH);
            delayMicroseconds(10);
            digitalWrite(out,LOW);
            dur=pulseIn(in,HIGH);
            tocm=dur / 29 / 2;
            
            if((tocm>15)&&(tocm<50)){
              digitalWrite(4,LOW);
              }
            else{
              digitalWrite(4,HIGH);
              }
          }
        }
      }

      g_prev=g;
      b_prev=b;
        
        }
      }

  }
  else{
      gm.write(99);
      bm.write(88);
      udm.write(123);
      Serial.println("bahar ka else se break");
      delay(1000);
  }
  
}
