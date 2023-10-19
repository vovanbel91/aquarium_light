void MENU0 (){

  if (EncClFlag == 1){ChNavPos1.Incr(1); EncClFlag = 0;};
  if (ChNavPos1.Count() == 0) {
  if (EncRHFlag) {RT.Incr(0); EncRHFlag = 0; ChTimeFlag = 1;};
  if (EncLHFlag) {RT.Decr(0); EncLHFlag = 0; ChTimeFlag = 1;};
  if (EncRFlag) {RT.Incr(1); EncRFlag = 0; ChTimeFlag = 1;};
  if (EncLFlag) {RT.Decr(1); EncLFlag = 0; ChTimeFlag = 1;};
  };
  if (ChNavPos1.Count() == 1) {
  if (EncRHFlag) {T1.Incr(0); EncRHFlag = 0;};
  if (EncLHFlag) {T1.Decr(0); EncLHFlag = 0;};
  if (EncRFlag) {T1.Incr(1); EncRFlag = 0;};
  if (EncLFlag) {T1.Decr(1); EncLFlag = 0;};
  };
  if (ChNavPos1.Count() == 2) {
  if (EncRHFlag) {T2.Incr(0); EncRHFlag = 0;};
  if (EncLHFlag) {T2.Decr(0); EncLHFlag = 0;};
  if (EncRFlag) {T2.Incr(1); EncRFlag = 0;};
  if (EncLFlag) {T2.Decr(1); EncLFlag = 0;};
  };
  TimeInd();
  OledRefr();

};

void DISPLMENU0 (){                                                     //Print display 1 menu
oled.setCursor(0,0);
oled.set2X ();
if (ChNavPos1.Count() == 0){oled.print("|");} else oled.print(" ");
PrintTime (RT.ShowVal(0), RT.ShowVal(1), RT.ShowVal(2), 1);
oled.set1X();
oled.setCursor (0,3);

if (ChNavPos1.Count() == 1){oled.print("|");} else oled.print(" ");
oled.print("T1:");
PrintTime (T1.ShowVal(0), T1.ShowVal(1), T1.ShowVal(2), 0);
oled.print("  ");
if (ChNavPos1.Count() == 2){oled.print("|");} else oled.print(" ");
oled.print("T2:");
PrintTime (T2.ShowVal(0), T2.ShowVal(1), T2.ShowVal(2), 0);
SaveValues(0);
};

void PrintTime (int Hours, int Minutes, int Seconds, bool UseSeconds){ //Print the string "Hours":"Minutes":"Seconds(optional)"
TrueTime (Hours);
oled.print (":");
TrueTime (Minutes);
  if (UseSeconds){
    oled.print (":");
    TrueTime (Seconds);
  };
};

void TrueTime (int A){if (A < 10){oled.print (0); oled.print (A);} else{oled.print (A);};}; //Function of good looking time printing

void TimeInd(){
if (ChTimeFlag == 1){
rtc.adjust(DateTime(2007, 7, 7, RT.ShowVal(0), RT.ShowVal(1), RT.ShowVal(2))); ChTimeFlag = 0;
} else {RT.Define(CurH, CurM, CurS);};
};













