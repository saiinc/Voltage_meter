//Пример для подключения дисплея по шине I2C
//
//Тип подключения дисплея: 1 - по шине I2C, 2 - десятиконтактное. Обязательно указывать ДО подключения библиотеки
//Если этого не сделать, при компиляции возникнет ошибка: "LCD type connect has not been declared"
#define _LCD_TYPE 1
#include <LCD_1602_RUS_ALL.h>

#define piezoPin 46

#define pot A2
#define led 9
#define tone_INTERVAL 1000
#define lcd_display_INTERVAL 500 // Частота обновления экрана дисплея в мс
unsigned long lcd_timing = 0;
unsigned long tone_timing = 0;
uint16_t voltage;
uint8_t tone_status = 0;

LCD_1602_RUS <LiquidCrystal_I2C> lcd(0x27, 16, 2);

void setup()
{
  pinMode(led, OUTPUT);
  // пин с потенциометром - вход
  pinMode(pot, INPUT);
  
  lcd.init(); // Инициализация LCD
  // Печать сообщения на LCD
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HAПPЯЖEHИE");  
}

void loop()
{
  voltage = map(analogRead(pot), 0, 1023, 0, 50);
  // Вывод информации на дисплей
   if (millis() - lcd_timing > lcd_display_INTERVAL)
   {
      lcd_timing = millis();
      lcd.setCursor(12, 0);
      lcd.print(String(voltage)+"B  ");
      if (voltage < 20)
      {
        lcd.setCursor(0, 0);
        lcd.print("HAПPЯЖEHИE");
        lcd.setCursor(0, 1);        
        lcd.print("CЛИШKOM HИЗKOE!");
        tone_status = 1;
        
      }
      else if (voltage > 30)
      {
        lcd.setCursor(0, 0);
        lcd.print("HAПPЯЖEHИE");
        lcd.setCursor(0, 1);
        lcd.print("CЛИШKOM BЫCOKOE!");
        tone_status = 2;
      }
      else
      {
        lcd.setCursor(0, 1);
        lcd.print("                ");
        tone_status = 0;
      }      
   }
   if (tone_status != 0)
   {
    digitalWrite(led, HIGH);
   }
   else
   {
    digitalWrite(led, LOW);
   }
   if (millis() - tone_timing > tone_INTERVAL && tone_status == 1)
   {
     tone_timing = millis();
     tone(piezoPin, 400, 300); // Звук прекратится через 500 мс, о программа останавливаться не будет!  
   }
   else if (millis() - tone_timing > tone_INTERVAL && tone_status == 2)
        {
          tone_timing = millis();
          tone(piezoPin, 1000, 300); // Звук прекратится через 500 мс, о программа останавливаться не будет!
        }
}
