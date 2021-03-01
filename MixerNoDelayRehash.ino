//State Machine example
//LarryD
//CheckTime is a variable


//byte messageNumber;
unsigned long FlashTime;
unsigned long TaskWait;
unsigned long TaskStir;
unsigned long stirTime = 3.0E5;//should be 5 minutes
unsigned long restTime = 1.8E6;//should be 30 minutes
unsigned long currentmillis;



//define the available machine states that we can have for this sketch
//add more states as needed
enum States{//iterates through each state/case
  stateStir, stateRest, stateOrange, statePear, statePeach, stateKiwi};

//mstate = machine State
States mstate = stateStir;              //we start out in this machine state

void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(13, OUTPUT);
  FlashTime = millis();
  TaskWait = millis();                   //initialize the next wait time
  TaskStir = millis();
  mstate = stateStir;                   //we start out in this machine state

} //        >>>>>>>>>>>>>> END OF setup() <<<<<<<<<<<<<<<<<


void loop()
{
  //leave this line of code at the top
  currentmillis  = millis();
  //***************************
  //just some code to see if the sketch is blocking
  if (CheckTime(FlashTime, 500UL))
  {
    digitalWrite(13,!digitalRead(13));
  }
  //***************************

  //Put your non-blocking regular stuff here


  //****************************************************************
  //Check machine state and do things that must be done accordingly
  switch (mstate) 
  { 
  
    //***************************
  case stateStir:
    {
      //TaskWait = millis();
    
      //let us wait for 5 seconds before we print the Welcome message
      if (CheckTime(TaskWait, stirTime))//
      //if (CheckTime(TaskWait, waitTime)) //we could use a variable for the time to wait
      {     
        Serial.println(F("Turn pin 5 on for 5 seconds"));
        digitalWrite(5,HIGH);
        Serial.print("Case = stateStart");
        TaskWait = millis();
        //digitalWrite(5,LOW);
        mstate = stateRest; //advance to the next state
        
      }         
    }
    break; //end case stateStart
    

    //***************************
  case stateRest:
  if (CheckTime(TaskWait, restTime))
        {
          Serial.println   (F("Here is another message."));
          Serial.println   (F("We will now wait 5 sec and continue."));
          Serial.println();
          digitalWrite(5,LOW);
          Serial.println("Pin 5 is low");
          TaskWait = millis();
          mstate = stateStir;
        }   

        break;
    }
 }
 
//======================================================================
//                    F U N C T I O N S
//======================================================================

//***************************
//Delay time expired function
boolean CheckTime(unsigned long &lastMillis, unsigned long wait)
{
  //is the time up for this task?
  if (currentmillis - lastMillis >= wait)
  {
    lastMillis += wait;  //get ready for the next iteration

    return true;
  }

  return false;
} //END of CheckTime()

//***************************

//======================================================================
//                             END OF CODE
//======================================================================
