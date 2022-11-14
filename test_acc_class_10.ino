
#define pinStep 6
#define stepPolarity 7

#define SS       0.02           // step size in mm ( mm/ step)
#define acc     100         // acceleration  mm/(s*s)
#define delta_S   100         // distance to move (mm) 
int vmax    = 181 ;            // maximum desired linear velocity in mm / s

unsigned int abs_Step = round(abs(delta_S) / SS);    // number of steps we need to do (step)

float S1 =  ( vmax*vmax ) / ( 2 * acc );
float S2 =  ( delta_S - S1);

void setup() {
  // put your setup code here, to run once:
  pinMode(pinStep, OUTPUT);
  pinMode(stepPolarity, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  if ( S1 > S2 ) // if we don't  reach full speed
  {
    S1 = delta_S / 2;
    S2 = delta_S / 2;
    vmax = sqrt(delta_S * acc);
  }


  float v_current = 0;
  for ( int inc_step = 0; inc_step < abs_Step ;  inc_step++)
  {
    // calculate position of current step
    const float S = ( inc_step + 0.5) * SS;

    // calculate velocity at current step
    if (  S < S1 )
    {
      v_current = sqrt( S * 2 * acc );
    }
    else if ( S < S2 )
    {
      v_current =  vmax ;
    }
    else
    {
      v_current =  sqrt( vmax * vmax - 2 * acc * ( S - S2) );
    }

    const int t_delay = round( (SS / v_current) * 1e6 ); // in micros (s/step)

    digitalWrite(stepPolarity, HIGH);
    digitalWrite(pinStep, HIGH);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(t_delay);

  }


}
