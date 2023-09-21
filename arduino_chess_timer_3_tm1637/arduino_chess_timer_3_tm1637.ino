    #define CLK1 2
    #define DIO1 3
    #define CLK2 4
    #define DIO2 5
    #define CLK3 6
    #define DIO3 7


    #include <GyverTM1637.h>
    GyverTM1637 disp1(CLK1, DIO1);
    GyverTM1637 disp2(CLK2, DIO2);
    GyverTM1637 disp3(CLK3, DIO3);


    enum state  {Timer1, Timer2, Timer3, Pause};
    int current_state = Pause;
    uint32_t time1 = 0;
    uint32_t time2 = 0;
    uint32_t time3 = 0;
    uint32_t myTimer = 0;



    void setup() {
      Serial.begin(9600);
      disp1.clear();        // чистим первый дисплей
      disp1.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
      disp1.displayInt(0000);// вывести ---- на экране
      disp2.clear();        // чистим второй дисплей
      disp2.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
      disp2.displayInt(0000);// вывести ---- на экране
      disp3.clear();        // чистим второй дисплей
      disp3.brightness(7);  // яркость, 0 - 7 (минимум - максимум)
      disp3.displayInt(0000);// вывести ---- на экране
      pinMode(9, INPUT_PULLUP); // старт 1 дисплей
      pinMode(10, INPUT_PULLUP); // старт 2 дисплей
      pinMode(11, INPUT_PULLUP); // старт 3 дисплей
      pinMode(12, INPUT_PULLUP); // пауза
    }


    void loop() {
      // Set Value
      bool buttonstart1 = false; //выставляет по умолчанию 0 для сигнала кнопки
      bool buttonstart2 = false; //выставляет по умолчанию 0 для сигнала кнопки
      bool buttonstart3 = false; //выставляет по умолчанию 0 для сигнала кнопки
      bool buttonpause = false; //выставляет по умолчанию 0 для сигнала кнопки
      bool timeEvent = false; //выставляет по умолчанию 0 для события
      bool pushButton = false; //выставляет по умолчанию 0 для нажатий кнопок

      bool DEBUG = true;


     if (digitalRead(9) == 0) buttonstart1 = true,  pushButton = true;//выставляет 1 при нажатии кнопки
     if (digitalRead(10) == 0) buttonstart2 = true, pushButton = true;
     if (digitalRead(11) == 0) buttonstart3 = true, pushButton = true;
     if (digitalRead(12) == 0) buttonpause = true, pushButton = true;

      // создает событие при нажатии на кнопку

     if (millis() - myTimer >= 1000) {
        myTimer = millis();
        timeEvent = true; //каждую секунду орет в timeEvent
     }

     if      (buttonpause == true) current_state = Pause;//, Serial.println("pause");
     if (current_state == Pause){
      if      (buttonstart1 == true) current_state = Timer1;//, Serial.println("button1");
      else if (buttonstart2 == true) current_state = Timer2;//, Serial.println("button2");
      else if (buttonstart3 == true) current_state = Timer3;//, Serial.println("button3");
     }

     if (current_state == Timer1) {
       if (timeEvent) {
          time1++;
           disp1.displayInt(time1), Serial.println("time1"), Serial.println(time1);  // Вывод на экран1 состояния
       }
     } else if (current_state == Timer2) {
       if (timeEvent) {
          time2++;
           disp2.displayInt(time2), Serial.println("time2"), Serial.println(time2);  // Вывод на экран2 состояния
       }
     } else if (current_state == Timer3) {
       if (timeEvent) {
         time3++;
         disp3.displayInt(time3), Serial.println("time3"), Serial.println(time3);  // Вывод на экран3 состояния
       }
     } else if (current_state == Pause) {
       if (timeEvent) {
         Serial.println("Pause");
       if (buttonpause == true) current_state = Pause;
       }
     }
   }