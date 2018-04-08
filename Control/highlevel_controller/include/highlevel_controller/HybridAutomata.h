/*
 * first developer : Choi Kyu-Jin, Soongsil University. Thank you for your help!
 * edited by Park TaeWook.
 *
*/
#pragma once
#include <iostream>

#define MAX_STATES 100

using namespace std;

class HybridAutomata;
class Condition
{
public:
  virtual bool check(HybridAutomata *HA) = 0;
  virtual ~Condition() {}
};
//added by TaeWook
class TimedCondition : public Condition
{
public:
  TimedCondition(unsigned int condCount) : condCount_(condCount)
  { 
    if(condCount_ == 0) condCount_ = 1;
  }
  virtual bool check(HybridAutomata *HA)
  {
    if (timedCheck(HA) == true){
      cnt++;
      cnt %= condCount_;
      if (!cnt) return true;
    }
    else
      cnt = 0;
    return false;
  }
  int getCnt() {return cnt;}
  virtual bool timedCheck(HybridAutomata *HA) = 0;
  virtual ~TimedCondition() {}
private:
  unsigned int condCount_;
  unsigned cnt;
};
//added by TawWook End
class HybridAutomata
{
private:
  class State
  {
  public:
    unsigned int stateId;
    void (*aDo)();
    State(unsigned int id, void (*ah)())
    {
      stateId = id;
      aDo = ah;
    }
  };
  unsigned int initState, exitState;
  unsigned int nStates;
  bool stateMachine[MAX_STATES][MAX_STATES];
  State *states[MAX_STATES];
  Condition *conditions[MAX_STATES][MAX_STATES];
  void initStateMachineArr();
  void initConditionsArr();
  void initStateArr();
  bool checkStateMachine(unsigned int pre, unsigned int post);
  int checkConditions();

public:
  unsigned int curState;
  void setState(unsigned int id, void (*ah)());                                     // user sets states
  void setCondition(unsigned int preState, Condition* cDo, unsigned int postState); //user sets conditions
  void operate(); // check conditions and if condition has satisfied move to another state
  HybridAutomata(const unsigned int init, const unsigned int exit);
  HybridAutomata();
  ~HybridAutomata();
  //bool checkConditions(unsigned int post);
};