
void ScreenSaver(){
oled.setCursor (0,0);
oled.print("V 2.0");

oled.setCursor (40,0);
PrintTime (CurH, CurM, CurS, 1);

   if (BrlIndMode == 0) {oled.setCursor (25,1); oled.print("Mode: Static       ");};
   if (BrlIndMode == 2) {oled.setCursor (25,1); oled.print("Mode: Dynamic       ");};

oled.setCursor (0,2);
oled.print("Cur.|");
oled.setCursor (0,3);
oled.print("Brt.|");
oled.setCursor (30,2);
oled.print("WW:");
oled.setCursor (30,3);
oled.print("WC:");
oled.setCursor (48,2);
oled.print(NOWBRL[0]);
if (NOWBRL[0] < 10) oled.print("  ");
if (NOWBRL[0] < 100) oled.print(" ");
oled.setCursor (48,3);
oled.print(NOWBRL[1]);
if (NOWBRL[1] < 10) oled.print("  ");
if (NOWBRL[1] < 100) oled.print(" ");

oled.setCursor (80,2);
oled.print("RB:");
oled.setCursor (80,3);
oled.print("B :");
oled.setCursor (98,2);
oled.print(NOWBRL[2]);
if (NOWBRL[0] < 10) oled.print("  ");
if (NOWBRL[0] < 100) oled.print(" ");
oled.setCursor (98,3);
oled.print(NOWBRL[3]);
if (NOWBRL[1] < 10) oled.print("  ");
if (NOWBRL[1] < 100) oled.print(" ");
}

