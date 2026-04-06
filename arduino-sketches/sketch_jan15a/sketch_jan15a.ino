// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 9 as an output.
  pinMode(9, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  ZapalDiodeNa(9, 1);
  delay(5000);              // wait for 500 milliseconds
}

void ZapalDiodeNa(int dioda, int sekund){
  ZapalDiode(dioda);
  delay(sekund * 1000);
  ZgasDiode(dioda);
}

void ZapalDiode(int numer){
  digitalWrite(numer, HIGH);
}

void ZgasDiode(int numer){
  digitalWrite(numer, LOW);
}