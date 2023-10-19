long OverflowIsNeeded(){  //Returns the time to a point and decides whether to raise the flag after launch
long Now = RT.GetAbs(); 
long Time1 = T1.GetAbs(); 
long Time2 = T2.GetAbs(); 
int A;
if (Now > Time1) Time1 += 86400;
if (Now > Time2) Time2 += 86400;
if (Time1 > Time2) A = Time2 - Now;
if (Time2 > Time1) A = Time1 - Now;
if (A >= 1800 && A <=1810 && OverflowNeededFlag == 0){OverflowNeededFlag = 1; TRMin.Reset();};
if (OverflowNeededFlag == 0 && ChInTimeFlag == 1 && A <= 1800) {OverflowNeededFlag = 1; ChInTimeFlag = 0; TRMin.Reset();} else {ChInTimeFlag = 0;};
//Serial.println(Now);
return A;
}

void BrlMGMT(){  //Basic light control algorithm
   BrlIndMode = 0;
   if (OverflowNeededFlag){
     TRMin.TimeOut(1850, 1);
     BrlIndMode = 2;
     if (TRMin.GetNowPos() >= 1700 && TRMin.GetNowPos() <= 1750){for (int i = 0; i < 4; i++){EnotherBrl[i] = GetTargetBrl (i);};};
     if (TRMin.GetNowPos() >= 1810){
       BrlIndMode = 0;
       if (AwakeFlag == 1){AwakeFlag = 0;};
       TRMin.Reset();
       OverflowNeededFlag = 0;
       };
  };
  
   if (ChMenu.Count() == 1 && ChEncFlag) BrlIndMode = 1;

if (BrlIndMode == 0){ //Basic mode
     ReadBrlEEPROM ();
     if (AwakeFlag == 1){AwakeFlag = 0;};
     if (GetPosition () == 0) {
       for (int i = 0; i < 4; i++){NOWBRL[i] = Brl[i].Count();};
       };
     if (GetPosition () == 1) {
       for (int i = 0; i < 4; i++){NOWBRL[i] = Brl[i+4].Count();};
       };
       WriteNowBrl();
       StartBrl();
};

if (BrlIndMode == 1){  //If you change brl for now
     int A = WorkTimeSet.Count() * 4;
     int B = CurStrip.Count() + A;

     int OAEM[] = {0, 0, 0, 0};
     OAEM[CurStrip.Count()] = Brl[B].Count();
     for (int i = 0; i < 4; i++){NOWBRL[i] = OAEM[i];};
     StartBrl();
};

if (BrlIndMode == 2){  //If it si overflow between the light periods
       for (int i = 0; i < 3; i++){
       long A = long(GetTargetBrl(i) - NOWWBRL[i]);
       long E = long(A*TRMin.GetNowPos());
       long F = long(E / 1800);
       if (TRMin.GetNowPos() >= 1795) {NOWBRL[i] = EnotherBrl[i];} else{
         NOWBRL[i] = NOWWBRL[i] + F;
       };
       
       //Serial.print (NOWBRL[i]); Serial.print ("|"); 
       //Serial.print (GetTargetBrl (i)); Serial.print ("///");

     };
     if (TRMin.GetNowPos() >= 900 && TRMin.GetNowPos() <= 1790) {NOWBRL[3] = GetTargetBrl(3);};
     if (TRMin.GetNowPos() > 1790) {NOWBRL[3] = EnotherBrl[3];};
     //Serial.println (" ");
     //Serial.println (TRMin.GetNowPos());

     StartBrl();
};
//Serial.println("AA");
}


long GetTargetBrl(long A){   // Returns the target brightness based on the current mode
   ReadBrlEEPROM ();
   TimeInd();
   long Ret = 0;
   bool P = GetPosition();
   //Serial.println("43");
   if (AwakeFlag == 1){
     if (OverflowIsNeeded() < 1800 && P == 0) {Ret = Brl[A+4].Count();};
     if (OverflowIsNeeded() > 1800 && P == 0) {Ret = Brl[A].Count();};
     if (OverflowIsNeeded() < 1800 && P == 1) {Ret = Brl[A].Count();};
     if (OverflowIsNeeded() > 1800 && P == 1) {Ret = Brl[A+4].Count();};
     //Serial.println("RE");
   }; 
   if (AwakeFlag == 0) {
     
     if (P == 0) {Ret = Brl[A+4].Count();/*Serial.println("!");*/};
     if (P == 1) {Ret = Brl[A].Count();/*Serial.println("!!!");*/};
   };

   //Serial.print("("); Serial.print(AwakeFlag); Serial.print(")");
   return Ret;
}

void StartBrl(){                                                          // Starts the PWM
  if (NOWBRL[0] > 0) PWM_set(10, NOWBRL[0]); else digitalWrite(10, 0);
  if (NOWBRL[1] > 0) PWM_set(9, NOWBRL[1]); else digitalWrite(9, 0);
  if (NOWBRL[2] > 0) PWM_set(3, NOWBRL[2]); else digitalWrite(3, 0);
  digitalWrite(5, NOWBRL[3]);
}

long OprNaib (long T1, long T2){   // Returns the bigger of two values
  long Naib; 
  if (T1 > T2) Naib = T1; else Naib = T2; 
  return Naib; 
} 

long OprNaim (long T1, long T2){  // Returns the smaller of two values (I don’t know why, but let it be)
  long Naim; 
  if (T1 < T2) Naim = T1; else Naim = T2; 
  return Naim; 
} 

bool GetPosition (){                                                    // Returns position
long Now = RT.GetAbs(); 
long Time1 = T1.GetAbs(); 
long Time2 = T2.GetAbs(); 
bool Pos = 0; 
if (Time1 == OprNaib (Time1, Time2)){ 
if (Now <= Time1 && Now >= Time2) Pos = 1; 
if (Now > Time1 | Now < Time2) Pos = 0; 
}; 
if (Time2 == OprNaib (Time1, Time2)){ 
if (Now <= Time1 | Now >= Time2) Pos = 1; 
if (Now > Time1 && Now < Time2) Pos = 0; 
}; 
//Serial.print("!");Serial.print(Pos);Serial.print("!");
return Pos; 


} 

void WriteNowBrl(){                                     ///This is necessary, yes, this is what the algorithm is based on
  for (int i = 0; i < 4; i++){
    NOWWBRL[i] = NOWBRL[i] ;
  };
}







