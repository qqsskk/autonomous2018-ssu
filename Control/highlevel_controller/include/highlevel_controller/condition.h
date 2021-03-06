#pragma once
#include "HybridAutomata.h"

class Init_to_toward_goal : public TimedCondition{
public:
    Init_to_toward_goal(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Init_to_toward_goal";}
};

/* crosswalk class */
class Toward_goal_to_process_crosswalk: public TimedCondition{
public:
    Toward_goal_to_process_crosswalk(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Toward_goal_to_process_crosswalk";}
};

class Process_crosswalk_to_toward_goal: public TimedCondition{
public:
    Process_crosswalk_to_toward_goal(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "process_crosswalk_to_toward_goal";}
};

/* movingobj class */
class Toward_goal_to_process_movingobj: public TimedCondition{
public:
    Toward_goal_to_process_movingobj(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "toward_goal_to_process_movingobj";}
};

class Process_movingobj_to_toward_goal : public TimedCondition{
public:
    Process_movingobj_to_toward_goal(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Process_movingobj_to_toward_goal";}
};

/* parking class */
class Toward_goal_to_process_parking: public TimedCondition{
public:
    Toward_goal_to_process_parking(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Toward_goal_to_process_parking";}
};

class Process_parking_to_toward_goal : public TimedCondition{
public:
    Process_parking_to_toward_goal(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Process_parking_to_toward_goal";}
};

/* uturn class */
class Toward_goal_to_process_uturn: public TimedCondition{
public:
    Toward_goal_to_process_uturn(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Toward_goal_to_process_uturn";}
};

class Process_uturn_to_toward_goal : public TimedCondition{
public:
    Process_uturn_to_toward_goal(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Process_uturn_to_toward_goal";}
};

/* nload class */
class Toward_goal_to_process_nload: public TimedCondition{
public:
    Toward_goal_to_process_nload(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Toward_goal_to_process_nload";}
};

class Process_nload_to_toward_goal : public TimedCondition{
public:
    Process_nload_to_toward_goal(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Process_nload_to_toward_goal";}
};

/* sturn class */
class Toward_goal_to_process_sload: public TimedCondition{
public:
    Toward_goal_to_process_sload(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Toward_goal_to_process_sload";}
};

class Process_sload_to_toward_goal : public TimedCondition{
public:
    Process_sload_to_toward_goal(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Process_sload_to_toward_goal";}
};

/* recovery */
class Toward_goal_to_process_recovery: public TimedCondition{
public:
    Toward_goal_to_process_recovery(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Toward_goal_to_process_recovery";}
};

class Process_recovery_to_toward_goal : public TimedCondition{
public:
    Process_recovery_to_toward_goal(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Process_recovery_to_toward_goal";}
};

/* Done */
class Toward_goal_to_done : public TimedCondition{
public:
    Toward_goal_to_done(unsigned int condCount) : TimedCondition(condCount) {}
    virtual bool timedCheck(HybridAutomata *HA);
    std::string toString() const {return "Toward_goal_to_done";}
};