void MENU1(){
  int A = WorkTimeSet.Count() * 4;
  int B = CurStrip.Count() + A;
  if (EncClFlag){CurStrip.Incr(1); EncClFlag = 0;};
  if (Enc2CFlag){WorkTimeSet.Incr(1); Enc2CFlag = 0; CurStrip.Incr(-2);};
   if (EncRHFlag) {Brl[B].Incr(10); EncRHFlag = 0;};
   if (EncLHFlag) {Brl[B].Incr(-10); EncLHFlag = 0;};
   if (EncRFlag) {Brl[B].Incr(1); EncRFlag = 0;};
   if (EncLFlag) {Brl[B].Incr(-1); EncLFlag = 0;};
  
  OledRefr();
}

void DISPLMENU1(){
  int A = WorkTimeSet.Count() * 4;
  int B = CurStrip.Count() + A;

oled.set1X();
oled.setCursor (0,0);
switch (CurStrip.Count()) {
   case 0: oled.print("Strip: WW");break;
   case 1: oled.print("Strip: WC");break;
   case 2: oled.print("Strip: RB");break;
   case 3: oled.print("Strip: B ");break;
};

oled.setCursor (90,0);
switch (WorkTimeSet.Count()) {
   case 0: oled.print("T1=>T2");break;
   case 1: oled.print("T2=>T1");break;
};
      
oled.setCursor (0,3);
   oled.print ("Brl = ");
   oled.print (Brl[B].Count());
   oled.print ("    ");
oled.setCursor (80,3);
   PrintTime (CurH, CurM, CurS, 1);

SaveValues(1);
}



