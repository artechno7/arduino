const int buttonSaya = 2;     // mengubah ‘buttonSaya’ menjadi variabel pin 2
const int ledSaya =  3;      // mengubah ‘ledSaya’ menjadi variabel pin 3
int buttonStatusSaya = 0;         // mengubah ‘buttonStatusSaya’ menjadi variable 0
 
void setup() 
{
   pinMode(ledSaya, OUTPUT); // mengubah ‘ledSaya’ menjadi pin OUTPUT
   pinMode(buttonSaya, INPUT); //mengubah ‘buttonSaya’ menjadi pin INPUT
}
 
void loop() 
{
   // untuk membaca variabel 'buttonSaya' yang akan dipindahkan ke variabel ‘buttonStatusSaya’
 
   buttonStatusSaya = digitalRead(buttonSaya); 
   // jika ‘buttonStatusSaya’ saya mendapatkan variabel nilai 1 atau HIGH atau ditekan ‘buttonSaya’-nya.
   if (buttonStatusSaya == HIGH)  
   {
      digitalWrite(ledSaya, HIGH); //maka ‘ledSaya’ menyala
   } 
   else 
   {
      digitalWrite(ledSaya, LOW); //apabila tidak ada, maka ‘ledSaya’ mati
   }
}
