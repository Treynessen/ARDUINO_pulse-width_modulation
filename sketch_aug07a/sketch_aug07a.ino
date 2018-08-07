void setup() {
  Serial.begin(9600);
  pinMode(7, INPUT_PULLUP); // Включить/выключить светодиод
  pinMode(8, INPUT_PULLUP); // Повысить яркость
  pinMode(12, INPUT_PULLUP); // Понизить яркость
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

const byte LED_NUM = 5;
const byte SIGNAL_PIN_NUMS[LED_NUM] = {5, 6, 9, 10, 11};
byte LED_COUNT = 0;
bool LED_ON = true;
byte bright = 255;
long time_for_on_off = 0, time_for_bright = 0;

void LED_CONTROL(){
  if (LED_COUNT == LED_NUM && LED_ON) LED_COUNT = LED_ON = 0;
  else if (LED_COUNT == LED_NUM && !LED_ON) {
    LED_COUNT = 0;
    LED_ON = true;
  }
  if(LED_ON) digitalWrite(SIGNAL_PIN_NUMS[LED_COUNT++], HIGH);
  else digitalWrite(SIGNAL_PIN_NUMS[LED_COUNT++], LOW);
  while(!digitalRead(7));
  time_for_on_off = millis();
}

void loop() {
  if((millis() - time_for_on_off) >= 50 && !digitalRead(7)) LED_CONTROL();
  if((millis() - time_for_bright) >= 50 && !digitalRead(8) && digitalRead(12)){
    if (bright != 255) bright += 5;
    for (byte i = 0 ; i < LED_NUM ; ++i) analogWrite(SIGNAL_PIN_NUMS[i], bright);
    time_for_bright = millis();
  }
  else if((millis() - time_for_bright) >= 50 && !digitalRead(12) && digitalRead(8)){
    if (bright != 0) bright -= 5;
    for (byte i = 0 ; i < LED_NUM ; ++i) analogWrite(SIGNAL_PIN_NUMS[i], bright);
    time_for_bright = millis();
  }
}
