int l_wheel=2;
int l_back=10;
int r_back=4;
int r_wheel=13;
int o_r=5; 


int o_l=6;
//int s_r=11;
int led=11;
int s_l=10;
int m_1,m_2,m_3;
int c_1,c_2,c_3;
int t_1,t_2,t_3;
bool GoBack=true;
// sonic2 for left
// sonic3 for right
  String DifferentWays[] = {
    "null",
    "top",
    "right",
    "left",
    "prev"
  };
int start=0;
int trig_1=3;
int echo_1=5;
int BestWay=0;

bool fix_or_not=true;
bool whoami=true;
bool if_run_r=true;
bool if_run_l=true;

int value1,value2,value3;
int x_value1,x_value2,x_value3;

int trig_2=6;
int echo_2=7;

int trig_3=11;
int echo_3=8;

bool isRight=true;
bool isLeft=true;

bool rightconfirm=false;
bool leftconfirm=true;
int randNumber;
int LastTurn=0;

void setup(){
  Serial.begin(9600);
  pinMode(r_wheel,OUTPUT);
  pinMode(l_wheel,OUTPUT);
  pinMode(l_back,OUTPUT);
  //pinMode(led,OUTPUT);
  pinMode(echo_1,INPUT);
  pinMode(trig_1,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(echo_2,INPUT);
  pinMode(trig_2,OUTPUT);
  pinMode(echo_3,INPUT);
  pinMode(trig_3,OUTPUT);
  randomSeed(analogRead(0));
  digitalWrite(9,250);
  digitalWrite(10,250);
  
 digitalWrite(r_wheel,HIGH);
 
  //digitalWrite(r_back,HIGH);
    //digitalWrite(l_wheel,HIGH);
  delay(3000);
  
}

int validate_turn(){
  x_value1=sonic1();
  x_value3=sonic2();
  x_value2=sonic3();
  //Serial.println(x_value1);
  if(x_value2 >=33 && x_value3 >=33 && x_value1 >= 33){
    fix_or_not=false;
    digitalWrite(l_wheel,LOW);
    digitalWrite(r_wheel,LOW);
    if(sonic3() >=33 && sonic2() >=33 && sonic1() >= 33){
      randNumber=random(1,4);
      maze_solve(1,1,1,3);
      return 0;
    }

    
  }if(x_value2 >=30 && x_value3 >=33 && x_value1 < 33 ){
        fix_or_not=false;

        digitalWrite(l_wheel,LOW);
        digitalWrite(r_wheel,LOW);
    if(sonic3() >=33 && sonic2() >=33 && sonic1() <33 ){
    randNumber=random(2,4);
    maze_solve(0,1,1,3);
    return 0;
    }

    
  }if(x_value2 >=33 && x_value3 <33 && x_value1 < 33){
          fix_or_not=false;

        digitalWrite(l_wheel,LOW);
        digitalWrite(r_wheel,LOW);
        

    if(sonic3() >=33 && sonic2() <33 && sonic1() <33){
      maze_solve(0,1,0,3);
      return 0;
    }

  
  }if(x_value2 <33 && x_value3 >=33 && x_value1 < 33){
          fix_or_not=false;

        digitalWrite(l_wheel,LOW);
        digitalWrite(r_wheel,LOW);

    if(sonic3() <30 && sonic2() >=40 && sonic1() <30){
        maze_solve(0,0,1,2);
        return 0;
    }

    
  }if(x_value2 >=33 && x_value3 < 33 && x_value1 >= 33){
          fix_or_not=false;
        digitalWrite(l_wheel,LOW);
        digitalWrite(r_wheel,LOW);

    if(sonic3() >=33 && sonic2() < 33 && sonic1() >= 33){
      
      randNumber=random(1,4);
      if(randNumber == 2){randNumber=3;}
      maze_solve(1,1,0,3);
      return 0;
    }

    
  }if(x_value2 <33 && x_value3 >=33 && x_value1 >= 33){
        fix_or_not=false;

        digitalWrite(l_wheel,LOW);
        digitalWrite(r_wheel,LOW);

    if(sonic3() <33 && sonic2() >=33 && sonic1() >= 33){
      randNumber=random(1,3);
      maze_solve(1,0,1,2);
      return 0;
    }
    
    }
  
  
 }
void loop(){

  Serial.println(sonic1());
    path_fix();
  if(if_run_r == true){
  digitalWrite(r_wheel,HIGH);
  }
  if(if_run_l == true){
  digitalWrite(l_wheel,HIGH);
  }
  validate_turn();
  path_fix();


}
int full_returnx(){
    digitalWrite(r_wheel,LOW);
    digitalWrite(l_wheel,HIGH);
    digitalWrite(r_back,HIGH);
    delay(200);
    while(true){
      //Serial.println(sonic1());
      if(sonic1() >= 30){
        delay(1);
        if(sonic1() >= 30){
        digitalWrite(l_wheel,LOW);
        digitalWrite(l_back,LOW);
                  break;
          }
        }
      }
      delay(200);

    return 0;
}


int path_fix(){
  
  Serial.println("fixx");
  value1=sonic1();
  value3=sonic2();
  value2=sonic3();
  //Serial.println(value2);
  if(sonic1() <= 11 && value3 <= 20 && value2 <=20 ){
    stop();
    digitalWrite(r_wheel,HIGH);
    digitalWrite(l_wheel,HIGH);
    return 0;
  }
  if(value3 > value2+3 && value3 >= 0  && value2 >= 0){
        digitalWrite(l_wheel,LOW);
        digitalWrite(r_wheel,HIGH);
        delay(50);
        digitalWrite(r_wheel,HIGH);
        digitalWrite(l_wheel,HIGH);
        if_run_r=true;
        if_run_l=true;
        
        if_run_l=false;
        return 0;
  }if(value2 > value3+3 && value3 >= 0  && value2 >= 0){
    digitalWrite(r_wheel,LOW);
    digitalWrite(l_wheel,HIGH);
      delay(50);
      digitalWrite(r_wheel,HIGH);
      digitalWrite(l_wheel,HIGH);
      if_run_r=true;
      if_run_l=true;
      return 0;
    }if(value2 = value3+3 || value3 == value2-3 || value2 == value3){
      digitalWrite(r_wheel,HIGH);
      digitalWrite(l_wheel,HIGH);
      return 0;
      }
      //validate_turn();
     return 0;

}


int maze_solve(int top,int left,int right,int rand_value){
  //Serial.println("TOP :"+String(top)+" Left : "+String(left)+" Right :"+String(right));
  //Serial.println(modifiedJsonString);
  Serial.println("");
  switch(rand_value){
    case 1:
      //serializeJson(doc, modifiedJsonString);
      //Serial.println(modifiedJsonString);
      //readJson(way_count,1);
      Serial.println("Go Forward");
      digitalWrite(r_wheel,HIGH);
      digitalWrite(l_wheel,HIGH);
      
      break;
    
  case 2:
  digitalWrite(9,150);
  digitalWrite(10,150);

  AllOff();
  Serial.println("LEFT");
      if(start == 0){
        start++;
        BestWay=3;
        }
      else{
        start++;
        }
      
      LastTurn=2;
      //serializeJson(doc, modifiedJsonString);
      //Serial.println(modifiedJsonString);
      //fix_or_not=true;
      //digitalWrite(led,HIGH);
      digitalWrite(l_wheel,HIGH);
      digitalWrite(r_wheel,HIGH);
      if(sonic1() <= 20){
      for(int right=0;right<=200;right++){
        delay(10);
        if(sonic1() <= 10 && sonic1() <= 30){
          //digitalWrite(led,LOW);
          break;
          
        }else{
          delay(10);
          }
        }
      }else{
        delay(400);
       }
      digitalWrite(l_wheel,LOW);
      digitalWrite(r_wheel,LOW);
      delay(400);
      digitalWrite(l_wheel,HIGH);
      digitalWrite(l_wheel,10);
      digitalWrite(r_wheel,HIGH);
      //digitalWrite(r_back,HIGH);
      //delay(650);
      
      //int son_val=sonic1();
        for(int right=0;right<=200;right++){
        delay(30);
        if(sonic1() >= 35){
          delay(100);
          //digitalWrite(led,HIGH);
          break;
          
        }else{
          delay(70);
          }
        }
      //if(son_val >= 45 && son_val*-1 < 0 ){
      //Serial.println("Sonic : "+String(sonic1()));
      delay(10);
      //if(sonic1()-45 >= 0){
       delay(20);
       //if(sonic1()-45 >= 0){
       digitalWrite(l_wheel,HIGH);
       //digitalWrite(r_back,LOW);
        path_fix();
        delay(100);
        digitalWrite(l_wheel,LOW);
        digitalWrite(r_wheel,LOW);
        //Serial.println("Sonic0.2 : "+String(sonic1()));
        //digitalWrite(led,LOW);
        fix_or_not=true;
        ////break;
        //freadJson(way_count,3);
        break;
          digitalWrite(9,80);
         digitalWrite(9,80);

    
    case 3:
              digitalWrite(9,150);
              digitalWrite(10,150);
      AllOff();
      if(start == 0){
        start++;
        BestWay=3;
        }else{
          start++;}
      
    LastTurn=1;
    //serializeJson(doc, modifiedJsonString);
    //Serial.println(modifiedJsonString);

    //fix_or_not=true;
    //Serial.println(44444);
    //digitalWrite(led,HIGH);
    digitalWrite(l_wheel,HIGH);
    digitalWrite(r_wheel,HIGH);
    if(sonic1() <= 20){

    for(int right=0;right<=200;right++){
        delay(25);
        if(sonic1() <= 10){
         // digitalWrite(led,LOW);
          break;
          
        }else{
          delay(25);
          }
        }
    }else{
      delay(200);
      }
    digitalWrite(l_wheel,LOW);
    digitalWrite(r_wheel,LOW);
    delay(300);
    digitalWrite(r_wheel,HIGH);
    digitalWrite(l_wheel,HIGH);
    //digitalWrite(9,150);
    //digitalWrite(r_back,HIGH);
    //delay(580);
    
    //int son_val=sonic1();
    //if(son_val >= 45 && son_val*-1 < 0 ){
    for(int right=0;right<=200;right++){
        delay(70);
        if(sonic1() >= 50){
          delay(50);
          //digitalWrite(led,HIGH);
          break;
          
        }else{
          delay(70);
          }
        }
    //Serial.println("Sonic : "+String(sonic1()));
    delay(10);
    //if(sonic1()-45 >= 0){
     delay(20);
     //if(sonic1()-45 >= 0){
     digitalWrite(r_wheel,HIGH);
     digitalWrite(l_wheel,HIGH);
     //digitalWrite(r_back,LOW);
      path_fix();
      delay(100);
      digitalWrite(l_wheel,LOW);
      digitalWrite(r_wheel,LOW);
      //Serial.println("Sonic0.2 : "+String(sonic1()));
      //digitalWrite(led,LOW);
      //fix_or_not=true;
      //break;
      //readJson(way_count,2);
      break;
   
    
   
  
              digitalWrite(9,80);
              digitalWrite(10,80);
  //delay(2000);  
  return 0;  
}
}




int sonic1(){
  m_1=10;
  digitalWrite(trig_1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_1,LOW);
  t_1=pulseIn(echo_1,HIGH);
  c_1=(t_1*0.034)/2;
  for(int x=0;x<=10;x++){
    m_1+=c_1;
  }
  //Serial.println(m_1/10);
    if(m_1/10 < -340){
         return 250;
    }else{
      return m_1/10;
      }
}



int sonic2(){
  m_2=10;
  digitalWrite(trig_2,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_2,LOW);
  t_2=pulseIn(echo_2,HIGH);
  c_2=(t_2*0.034)/2;
  for(int x=0;x<=10;x++){
    delay(1);
    m_2+=c_2;
  }
  if(m_2/10 < -340){
    return 230;
  }else{
  return m_2/10;
  }
}



int sonic3(){
  m_3=10;
  digitalWrite(trig_3,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_3,LOW);
  t_3=pulseIn(echo_3,HIGH);
  c_3=(t_3*0.034)/2;
  for(int x=0;x<=10;x++){
    m_3+=c_3;
    delay(1);
  }
  if(m_3/10 < -340){
    return 230;
  }else{
  return m_3/10;
  }
}


int stop(){
  AllOff();
  delay(100);
  full_return();
  return 0;
}


int AllOff(){
  digitalWrite(r_wheel,LOW);
  digitalWrite(l_wheel,LOW);
  digitalWrite(l_back,LOW);
  digitalWrite(r_back,LOW);

}

int full_return(){
  Serial.println(889988);
  AllOff();
  digitalWrite(l_wheel,HIGH);
  digitalWrite(r_back,HIGH);
  delay(300);
  while(true){
    delay(50);
    if(sonic1() >= 35 && sonic2() <= 25 && sonic3() <= 25 ){
      if(sonic2()+7 >= sonic3() || sonic3()+7>= sonic3()){
      AllOff();
      }
    }
    delay(30);
  return 0;
  }
}