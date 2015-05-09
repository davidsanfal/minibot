#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define MANUAL 0
#define AUTOMATIC 1

class PID {

    /**************************************************************************
     * Clase para la generalizacin de las funciones principales de un PID con:
     *    -Posibilidad de cambios de sintonizacin.
     *    -Anti-WindUp.
     *    -Manual/automatico con reset.
     *    -Cambio en los lmites del sistema.
     **************************************************************************/

  public:

    PID( double kp, double ki, double kd, double outMin, double outMax)
    {
      _kp = kp;
      _ki = ki;
      _kd = kd;
      _outMin = outMin;
      _outMax = outMax;
      _inAuto = true;
    }

    void Initialize() //Funcin para el reset.
    {
      _lastInput = _Input;
      _ITerm = _Output;
      if (_ITerm > _outMax) _ITerm = _outMax;
      else if (_ITerm < _outMin) _ITerm = _outMin;
    }

    float Compute(float Setpoint, float Input) //Funcin para el procesamiento del PID.
    {
      _Setpoint = Setpoint;
      _Input = Input;
      if (!_inAuto)
      {
        return 0.0;
      }
      //Cuanto tiempo pas desde el ltimo clculo.
      unsigned long now = millis();
      double timeChange = (double)(now - _lastTime);
      if (timeChange < 0.0) timeChange = 0;

      //Calculamos todas las variables de error.
      double error = _Setpoint - _Input;
      _ITerm += (_ki * error * timeChange);
      //anti-WindUp.
      if (_ITerm > _outMax) _ITerm = _outMax;
      else if (_ITerm < _outMin) _ITerm = _outMin;
      double dErr = (error - _lastErr) / timeChange;

      //Calculamos la funcin de salida del PID.
      _Output = _kp * (error + _ITerm + _kd * dErr);
      //bloque para la salida.
      /*
      if (_Output > _outMax) _Output = _outMax;
      else if (_Output < _outMin) _Output = _outMin;
      */


      if (_Output > _outMax)
      {
        double ITermAux = _Output - _outMax;
        _ITerm = _ITerm - ITermAux;
      }

      else if (_Output < _outMin)
      {
        double ITermAux = _outMin - _Output;
        _ITerm += ITermAux;
      }

      //Recalculamos la funcin de salida del PID con el nuevo _ITerm.
      _Output = _kp * error + _ITerm + _kd * dErr;


      //Guardamos el valor de algunas variables para el prximo ciclo de clculo.
      _lastErr = error;
      _lastTime = now;
      return _Output;
    }

    void SetTunings(double Kp, double Ki, double Kd) //Funcin para cambiar los parametros del PID.
    {
      _kp = Kp;
      _ki = Ki;
      _kd = Kd;
    }

    void SetOutputLimits(double Min, double Max)  //Funcin para cambiar los limites del sistema.
    {
      if (Min > Max) return;
      _outMin = Min;
      _outMax = Max;

      if (_Output > _outMax) _Output = _outMax;
      else if (_Output < _outMin) _Output = _outMin;

      if (_ITerm > _outMax) _ITerm = _outMax;
      else if (_ITerm < _outMin) _ITerm = _outMin;
    }

    void SetMode(int Mode) //Funcin para cambiar de automtico a manual.
    {
      bool newAuto = (Mode == AUTOMATIC);
      if (newAuto && !_inAuto)
      { // Para cambiar de manual a automtico, inicializamos algunos parmetros.
        Initialize();
      }
      _inAuto = newAuto;
    }

  private:
    unsigned long _lastTime;
    double _Input, _Output, _Setpoint;
    double _errSum, _lastErr;
    double _ITerm, _lastInput;
    double _kp, _ki, _kd;
    double _outMin, _outMax;
    bool _inAuto;
};
