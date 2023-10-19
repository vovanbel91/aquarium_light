#ifndef Classes_h
#define Classes_h

#include "Arduino.h"

class Timer {

  private:

   int Time;
   int CurSec;
   int Sec;
   bool State;
   bool ReadyFlag;


  public:

   bool TimeOut (int Value, int Duration){
    if (CurSec != Sec && ReadyFlag == 1){Sec = CurSec; Time++; State = false;};
    if (Time >= Value){State = true;};
    if (ReadyFlag == 1 && Time >= Value + Duration){Time = 0; ReadyFlag = 0; State = false;};
    //Serial.println(Time);
    return State;
   };
    void Get(int A) {CurSec = A;};
    void Reset(){ReadyFlag = 1; Time = 0;};
    int GetNowPos(){return Time;};
   
};

class Value {

  public:

  int Count(){return _A;};
  void Define(int G){_A = G;};
  void ValueParam (int A, int MaxValue){
    _A = A;
    _MaxValue = MaxValue;
  };
    void Incr (int IncrVal) {
      _A += IncrVal;
      if (_A >= _MaxValue) _A = 0;
      if (_A < 0) _A = _MaxValue - 1;
      };


  private:

  int _A;
  int _MaxValue;

};

class TimeVal {
  public:
  TimeVal (int Hour, int Minute, int Second){
    _Hour = Hour; _Minute = Minute; _Second = Second; 
    };

    int ShowVal(int Val){
      if (Val == 0) return _Hour;
      if (Val == 1) return _Minute;
      if (Val == 2) return _Second;
    };

    void Incr (int Val){
      if (Val == 0) _Hour++;
      if (_Hour >= 24) _Hour = 0;
      if (Val == 1) _Minute++;
      if (_Minute >= 60) _Minute = 0;
      if (Val == 2) _Second++;
      if (_Second >= 60) _Second = 0;
    };

     void Decr (int Val){
      if (Val == 0) _Hour--;
      if (_Hour < 0) _Hour = 23;
      if (Val == 1) _Minute--;
      if (_Minute < 0) _Minute = 59;
      if (Val == 2) _Second--;
      if (_Second < 0) _Second = 59; 
    };

     void Define (int Hour, int Minute, int Second){
       _Hour = Hour; _Minute = Minute; _Second = Second;
     };

   long GetAbs() {
    long A = _Hour;
    A *= 3600;
    long B = _Minute;
    B *= 60;
    long C = A;
    C += B;
    C += _Second;
    return C;
};

private:

  int _Hour;
  int _Minute;
  int _Second;

};


#endif