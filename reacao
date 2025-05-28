int led_Pin[5] = {13,12,11,10,9};
int btn_Pin[6] = {22,23,24,25,26,27};
int btn_random;
int btnP1;
int btnP2;
int timer;

void setup()

{

  pinMode(led_Pin[0],OUTPUT);
  pinMode(led_Pin[1],OUTPUT);
  
  for(int i = 0;i < 6;i++){
  pinMode(btn_Pin[i],INPUT_PULLUP);
  }
  
  randomSeed(analogRead(A0));
    
  Serial.begin(9600);
  
  
}

void aperte()
{
  	timer = millis();
    btn_random = random(0,3);
    Serial.println(btn_random+1);
  
  	while(true){ 
    	btnP1 = digitalRead(btn_Pin[btn_random]);
  		btnP2 = digitalRead(btn_Pin[btn_random + 3]);
      
    	if(btnP1 == LOW){
        Serial.println("P1 ganhou");
        break;
      }

    	if(btnP2 == LOW){
        Serial.println("P2 ganhou");
        break;

    	}
    }
  
}

void loop(){
  aperte();
  delay(1000);
}
