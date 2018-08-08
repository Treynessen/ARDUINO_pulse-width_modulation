void setup() {
  pinMode(7, INPUT_PULLUP); // Включить/выключить светодиод
  pinMode(8, INPUT_PULLUP); // Повысить яркость
  pinMode(12, INPUT_PULLUP); // Понизить яркость
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

bool low_signal_LED_BUTTON = true; 
bool LED_ON = true; 
byte count_low_signal_LED_BUTTON = 0;
const byte LED_NUM = 5;
const byte SIGNAL_PIN_NUMS[LED_NUM] = {5, 6, 9, 10, 11};
byte LED_COUNT = 0;
byte bright = 255;
long time_for_bright = 0;

void LED_CONTROL(){
  if (LED_COUNT == LED_NUM && LED_ON) LED_COUNT = LED_ON = 0;
  else if (LED_COUNT == LED_NUM && !LED_ON) {
    LED_COUNT = 0;
    LED_ON = true;
  }
  if(LED_ON) analogWrite(SIGNAL_PIN_NUMS[LED_COUNT++], bright);
  else digitalWrite(SIGNAL_PIN_NUMS[LED_COUNT++], LOW);
}

void loop() {
  // Включение/выключение светодиодов
  if (!low_signal_LED_BUTTON && digitalRead(7) && count_low_signal_LED_BUTTON++ >= 100) low_signal_LED_BUTTON = true; 
  if (low_signal_LED_BUTTON && !digitalRead(7)) {
    LED_CONTROL();
    low_signal_LED_BUTTON = false;
    count_low_signal_LED_BUTTON = 0; 
  } 
  // Регулировка яркости
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
