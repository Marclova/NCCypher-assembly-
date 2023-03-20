//indici dei registri usati (1,18,19,20,21,26,27,30,31)

void setup() {
    pinMode(2, INPUT);
  }

void loop() {
  while (digitalRead(2)==LOW) {}
  asm(/*<assegnazione valore R27>*/
      "MOV R18, R27 \n" //R18=valore da criptare R27=valore generico che dovrebbe variare ad ogni ciclo in quanto rappresentante le singole lettere di una stringa
      
      "INC R30 \n" //R30=base1 criptaggio
      "INC R31 \n" //R31=base2 criptaggio
      "LDI R27, 0X05 \n"
      "CPSE R30, R27 \n" //azzeramento modulo 5
        "MOV R30, R1 \n" //avviene se R30 == 5
      "LDI R27, 0X07 \n"
      "CPSE R31, R27 \n" //azzeramento modulo 7
        "MOV R31, R1 \n" //avviene se R31 == 7
      "MOV R19, R30 \n" //R19=valore usato per rendere la criptatura più complessa
      "ADD R19, R31 \n"
      "SBRC R19, 0 \n"  //R19(MOD 2) == 0?
        "JMP NO \n"
        "JMP SI \n"
      "NO:"
          "SBRC R20, 0 \n" //R20(MOD 2) == 0? (R20= valore di R19 nel ciclo precedente)
            "JMP NO_1 \n"
            "JMP SI_1 \n"
          "NO_1:"
              "INC R21 \n" //R21= valore da sommare a R18 per esguire il criptaggio/decriptaggio
              "INC R21 \n"
              "JMP END \n"
          "SI_1:"
              "LDI R21, 0x02 \n"
              "JMP END \n"
      "SI:"
          "SBRC R20, 0 \n" //R20(MOD 2) == 0?
            "JMP NO_2 \n"
            "JMP SI_2 \n"
          "NO_2:"
              "LDI R21, 0x01 \n"
              "JMP END \n"
          "SI_2:"
              "INC R21 \n"
      "END:"
      "MOV R20, R19 \n"
      
      "LDI R27, 0X07 \n"
      "CPSE R21, R27 \n"
        "JMP SKIP_1 \n"
        "LDI R21, 1 \n"
        "JMP SETTED \n"
      "SKIP_1:"
      "LDI R27, 0X0A \n"
      "CPSE R21, R27 \n"
        "JMP SETTED \n"
        "LDI R21, 0x04 \n"
      "SETTED:"  //contenimento di R20 per rendere la criptatura più efficacie
      
      "LDI R27, 0X01 \n"
      "CPSE R26, R27 \n" //R26==0 -> criptaggio  R26==1 -> decriptaggio
        "JMP CRIPTAGGIO \n"
      "DECRIPTAGGIO:"
        "SUB R18, R21 \n"
        "JMP FIN \n"
      "CRIPTAGGIO:"
        "ADD R18, R21 \n"
      "FIN:"
      /*<invio del valore di R18>*/
      );
      delay(1000);
}
