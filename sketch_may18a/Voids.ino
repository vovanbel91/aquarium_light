void ReadBrlEEPROM (){for (int i = 0; i < 8; i++ ){Brl[i].Define(EEPROM.read(i));};} //Очевидно читает яркость из EEPROM

void WriteBrlEEPROM(){  //Очевидно записывает яркость в EEPROM
  int A[8];
  for (int i = 0; i < 8; i++) {A[i] = Brl[i].Count();};
  for (int i = 0; i < 8; i++) {WriteEEPROM(i, &A[i]);};
  }

void WriteEEPROM(int A, int* B){    //Скармливаем "адрес котоый займем в EEPROM" и "адрес переменной", если значения разные - оно запишет
if (*B != EEPROM.read(A)) {EEPROM.write (A, *B); Serial.println("WOW");};} 

void WriteTimeEEPROM(){ //Очевидно записывает время в EEPROM
  int A[4];
  for (int i = 0; i < 2; i++) {A[i] = T1.ShowVal(i);};
  for (int i = 0; i < 2; i++) {WriteEEPROM(i+8, &A[i]);};
  for (int i = 2; i < 4; i++) {A[i] = T2.ShowVal(i-2);};
  for (int i = 2; i < 4; i++) {WriteEEPROM(i+8, &A[i]);};
}

void ReadTimeEEPROM(){   //Очевидно читает время из EEPROM
T1.Define(EEPROM.read(8), EEPROM.read(9), 0);
T2.Define(EEPROM.read(10), EEPROM.read(11), 0);
}

void MENUMGMT (){  //Запускает менюшки
  if (EncHFlag) {ChMenu.Incr(1); EncHFlag = 0;};
  if (ChMenu.Count() == 0) MENU0();
  if (ChMenu.Count() == 1) MENU1();
}

void OledRefr(){ //Рефрешит дисплей
  if (SecFlag == 1 | IsInter == 1){
 
  if (TR2.TimeOut(1, 20) == 0) {MenuCount = 0; Cl(); oled.setContrast(1); ScreenSaver();}
  else {
  if (ChMenu.Count() == 0) {MenuCount = 1; Cl(); oled.setContrast(255); DISPLMENU0();};
  if (ChMenu.Count() == 1) {MenuCount = 2; Cl(); oled.setContrast(255); DISPLMENU1();};
  SecFlag = 0;
  IsInter = 0;
};
};
}

void Cl(){if (MenuCount != MenuCountM) {oled.clear (); MenuCountM = MenuCount;};}

void SaveValues(bool A){  //Save values function
if (ChFlag){
    OverflowNeededFlag = 0;
    if (A == 0){
    if (ChNavPos1.Count() != 0){
    TR1.Reset();
    };
    } else {
    TR1.Reset();
    };
    ChFlag = 0;
    ChEncFlag = 1;
    ChInTimeFlag = 1;
};
if (TR1.TimeOut(5, 1)){
  if (T1.ShowVal(0) == T2.ShowVal(0) && T1.ShowVal(1) == T2.ShowVal(1)){
    oled.setCursor (0,2);
    oled.print ("      ==DEBIL?==");
    ReadTimeEEPROM();
  } else{
    WriteTimeEEPROM ();
    WriteBrlEEPROM();
    oled.setCursor (0,2);
    oled.print ("      ==Saved==");
    ClearSavedFlafg = 1;
  };
};
    if (ClearSavedFlafg && TR1.TimeOut(5, 1) == 0){
    ClearSavedFlafg = 0;
    ChEncFlag = 0;
    oled.setCursor (0,2);
    oled.print ("                 ");

  };
}


