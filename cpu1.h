//Oh Darling, even Rome fell thrice!

/*
CPU_1 has a dedicated self-aware scheduler to implement Protothreading of sensors and actuators
Each task knows it's own context switch time called run_start
Each task automatically switches to the next, when it's life span is at an end.
*/

#define dct 1000 //1 ms is the max time alloted to any task to run. It is the slot time
#define i_0 1000 //minimum interval

int run_count_001 = 0, run_count_002 = 0; //count keeping variable
unsigned int run_start = 0; //common run_time keeping variable
unsigned int exec_start_001 = 0, exec_start_002 = 0; //execution time tracker

int f001[] = { 0 , 0}; //Parameter vectors
int f002[] = { 0 , 0};

void F_001(int dur, int dc){ //FID 001 - Actuator 1 - On Board LED (Primary)
  /*Parameter List:-
  * Blink duration in millis
  * Blink duty cycle %
  */
  if(run_count_001 == 0){ //on first run of the task, update start time
    exec_start_001 = micros();
  }
  
  Serial << endl<<"Process F_001 running on core " << (xPortGetCoreID()) << endl ;; //core ID serial return
  unsigned int on_time = dc*dur*1000/100; //compute on_time in us
  unsigned t_period = dur * 1000; //compute total time period
  
  run_start = micros(); //start time keeping for the context
  
  unsigned int exec_time = micros() - exec_start_001; //variable added to keep type consistency, try by deletion
  int on_off = (exec_time < on_time); //variable can be avoided
  Serial << "F_001 run count = " << run_count_001 << " Execution time elapsed = " << exec_time << endl;
  
  if(on_off){
    Serial << "Light On" << endl ;;
    unsigned int run_time = micros() - run_start; //variable added to keep type consistency, try by deletion
    while(true){
      digitalWrite(LED_BUILTIN, HIGH); //Turn the LED High
      run_time = micros() - run_start; //Track how many uS elapsed
      if(run_time > dct) break; //If the process runs more than dct, pre-empt
    }
  }

  if(!on_off){
    Serial <<endl<< "Light Off" << endl ;;
    unsigned int run_time = micros() - run_start;
    while(true){
      digitalWrite(LED_BUILTIN, LOW);
      run_time = micros() - run_start;
      if(run_time > dct) break;
    }
  }
  run_count_001 = run_count_001+1; //keep track of number of counts the context has appeared

  if((exec_time) > t_period){
    run_count_001 = 0;
    Serial <<"Process F_001 exiting at time " << exec_time << " uS " << endl ;;
  }
  Serial << "Context switch F_001 at time " << micros() - run_start << " uS " << endl ;;
}

void F_002(int dur, int dc){ //FID 001 - Actuator 1 - LED Secondary
  /*Parameter List:-
  * Blink duration in millis
  * Blink duty cycle %
  */
    if(run_count_002 == 0){ //on first run of the task, update start time
    exec_start_002 = micros();
  }
  
  Serial << endl<<"Process F_002 running on core " << (xPortGetCoreID()) << endl ;;
  unsigned int on_time = dc*dur*1000/100; //compute on_time in us
  unsigned t_period = dur * 1000;
  
  run_start = micros(); //start time keeping for the context
  
  unsigned int exec_time = micros() - exec_start_002;
  int on_off = (exec_time < on_time);
  Serial << "F_002 run count = " << run_count_002 << " Execution time elapsed = " << exec_time << endl;;
  
  if(on_off){
    Serial <<"Light On" << endl ;;
    unsigned int run_time = micros() - run_start;
    while(true){
      digitalWrite(23, HIGH);
      run_time = micros() - run_start;
      if(run_time > dct) break;
    }
  }

  if(!on_off){
    Serial <<endl<< "Light Off" << endl ;;
    unsigned int run_time = micros() - run_start;
    while(true){
      digitalWrite(23, LOW);
      run_time = micros() - run_start;
      if(run_time > dct) break;
    }
  }
  run_count_002 = run_count_002+1;

  if((exec_time) > t_period){
    run_count_002 = 0;
    Serial << "Process F_002 exiting at time " << exec_time << " uS " << endl ;;
  }
  Serial << "Context switch F_002 at time " << micros() - run_start << " uS " << endl ;;
}

void SchedulerMain(void * Parameter){
  while(true){ //Works without the infinite loop too
    F_001(f001[0],f001[1]);
    F_002(f002[0],f002[1]);
  }
}
