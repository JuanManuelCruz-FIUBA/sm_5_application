/** Generated by YAKINDU Statechart Tools code generator. */

#include "Statechart.h"

/*! \file
Implementation of the state machine 'Statechart'
*/




Statechart::Statechart() :
	evButtonUnpressed_raised(false),
	evButtonPressed_raised(false),
	evButtonPressed_value(0),
	viMyCounter(0),
	viTecla(0),
	siIdelBlink_raised(false),
	timerService(sc_null),
	isExecuting(false),
	stateConfVectorPosition(0)
{
	for (sc_ushort state_vec_pos = 0; state_vec_pos < maxOrthogonalStates; ++state_vec_pos)
		stateConfVector[state_vec_pos] = Statechart_last_state;
	
	clearInEvents();
	clearInternalEvents();
}

Statechart::~Statechart()
{
}


using namespace statechart_events;

SctEvent* Statechart::getNextEvent()
{
	SctEvent* nextEvent = 0;
	
	if(!internalEventQueue.empty()) {
		nextEvent = internalEventQueue.front();
		internalEventQueue.pop_front();
	}
	else if(!inEventQueue.empty()) {
		nextEvent = inEventQueue.front();
		inEventQueue.pop_front();
	}
	
	return nextEvent;
}

void Statechart::dispatch_event(SctEvent * event)
{
	if(event == 0) {
		return;
	}
	switch(event->name)
	{
		case evButtonUnpressed:
		case evButtonPressed:
		{
			iface_dispatch_event(event);
			break;
		}
		case Internal_siIdelBlink:
		{
			internal_dispatch_event(event);
			break;
		}
		case Statechart_Button_DEBOUNCE_time_event_0:
		{
			timeEvents[0] = true;
			break;
		}
		case Statechart_IdleBlink_BLINK_Blink_Turn_OFF_time_event_0:
		{
			timeEvents[1] = true;
			break;
		}
		case Statechart_IdleBlink_BLINK_Blink_Turn_ON_time_event_0:
		{
			timeEvents[2] = true;
			break;
		}
		default:
			/* do nothing */
			break;
	}
	delete event;
}

void Statechart::iface_dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		case evButtonUnpressed:
		{
			internal_raiseEvButtonUnpressed();
			break;
		}
		case evButtonPressed:
		{
			SctEvent__evButtonPressed * e = static_cast<SctEvent__evButtonPressed*>(event);
			if(e != 0) {
				internal_raiseEvButtonPressed(e->value);
			}
			break;
		}
		default:
			/* do nothing */
			break;
	}
}
void Statechart::internal_dispatch_event(SctEvent * event)
{
	switch(event->name)
	{
		case Internal_siIdelBlink:
		{
			internal_raiseSiIdelBlink();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

StatechartEventName Statechart::getTimedEventName(sc_eventid evid)
{
	if (evid == (sc_eventid)(&timeEvents[0])) {
		return Statechart_Button_DEBOUNCE_time_event_0;
	}
	if (evid == (sc_eventid)(&timeEvents[1])) {
		return Statechart_IdleBlink_BLINK_Blink_Turn_OFF_time_event_0;
	}
	if (evid == (sc_eventid)(&timeEvents[2])) {
		return Statechart_IdleBlink_BLINK_Blink_Turn_ON_time_event_0;
	}
	return invalid_event;
}



sc_boolean Statechart::isActive() const
{
	return stateConfVector[0] != Statechart_last_state||stateConfVector[1] != Statechart_last_state;
}

/* 
 * Always returns 'false' since this state machine can never become final.
 */
sc_boolean Statechart::isFinal() const
{
   return false;}

sc_boolean Statechart::check() {
	if(timerService == sc_null) {
		return false;
	}
	return true;
}


void Statechart::setTimerService(sc::timer::TimerServiceInterface* timerService_)
{
	this->timerService = timerService_;
}

sc::timer::TimerServiceInterface* Statechart::getTimerService()
{
	return timerService;
}

sc_integer Statechart::getNumberOfParallelTimeEvents() {
	return parallelTimeEventsCount;
}

void Statechart::raiseTimeEvent(sc_eventid evid)
{
	if ((evid >= (sc_eventid)timeEvents) && (evid < (sc_eventid)(&timeEvents[timeEventsCount])))
	{
		inEventQueue.push_back(new TimedSctEvent(getTimedEventName(evid)));
		runCycle();
	}
}


sc_boolean Statechart::isStateActive(StatechartStates state) const
{
	switch (state)
	{
		case Button_DEBOUNCE :
		{
			return (sc_boolean) (stateConfVector[SCVI_BUTTON_DEBOUNCE] == Button_DEBOUNCE);
			break;
		}
		case Button_BUTTON_UNPRESSED :
		{
			return (sc_boolean) (stateConfVector[SCVI_BUTTON_BUTTON_UNPRESSED] == Button_BUTTON_UNPRESSED);
			break;
		}
		case Button_BUTTON_PRESSED :
		{
			return (sc_boolean) (stateConfVector[SCVI_BUTTON_BUTTON_PRESSED] == Button_BUTTON_PRESSED);
			break;
		}
		case Button_VALIDATE :
		{
			return (sc_boolean) (stateConfVector[SCVI_BUTTON_VALIDATE] == Button_VALIDATE);
			break;
		}
		case IdleBlink_BLINK :
		{
			return (sc_boolean) (stateConfVector[SCVI_IDLEBLINK_BLINK] >= IdleBlink_BLINK && stateConfVector[SCVI_IDLEBLINK_BLINK] <= IdleBlink_BLINK_Blink_Turn_ON);
			break;
		}
		case IdleBlink_BLINK_Blink_Turn_OFF :
		{
			return (sc_boolean) (stateConfVector[SCVI_IDLEBLINK_BLINK_BLINK_TURN_OFF] == IdleBlink_BLINK_Blink_Turn_OFF);
			break;
		}
		case IdleBlink_BLINK_Blink_Turn_ON :
		{
			return (sc_boolean) (stateConfVector[SCVI_IDLEBLINK_BLINK_BLINK_TURN_ON] == IdleBlink_BLINK_Blink_Turn_ON);
			break;
		}
		case IdleBlink_IDLE :
		{
			return (sc_boolean) (stateConfVector[SCVI_IDLEBLINK_IDLE] == IdleBlink_IDLE);
			break;
		}
		default:
		{
			/* State is not active*/
			return false;
			break;
		}
	}
}

/* Functions for event evButtonUnpressed in interface  */
void Statechart::raiseEvButtonUnpressed()
{
	inEventQueue.push_back(new SctEvent__evButtonUnpressed(evButtonUnpressed));
        runCycle();
}
void Statechart::internal_raiseEvButtonUnpressed()
{
	evButtonUnpressed_raised = true;
}
/* Functions for event evButtonPressed in interface  */
void Statechart::raiseEvButtonPressed(uint32_t evButtonPressed_)
{
	inEventQueue.push_back(new SctEvent__evButtonPressed(evButtonPressed, evButtonPressed_));
        runCycle();
}
void Statechart::internal_raiseEvButtonPressed(uint32_t evButtonPressed_)
{
	evButtonPressed_value = evButtonPressed_;
	evButtonPressed_raised = true;
}
/* Functions for event siIdelBlink in interface Internal */
void Statechart::raiseSiIdelBlink()
{
	internalEventQueue.push_back(new SctEvent_Internal_siIdelBlink(Internal_siIdelBlink));
        runCycle();
}
void Statechart::internal_raiseSiIdelBlink()
{
	siIdelBlink_raised = true;
}
sc_boolean Statechart::isRaisedSiIdelBlink() const
{
	return siIdelBlink_raised;
}

// implementations of all internal functions
/* Entry action for state 'DEBOUNCE'. */
void Statechart::enact_Button_DEBOUNCE()
{
	/* Entry action for state 'DEBOUNCE'. */
	timerService->setTimer(this, (sc_eventid)(&timeEvents[0]), 100, false);
}

/* Entry action for state 'BUTTON_PRESSED'. */
void Statechart::enact_Button_BUTTON_PRESSED()
{
	/* Entry action for state 'BUTTON_PRESSED'. */
	internalEventQueue.push_back(new SctEvent_Internal_siIdelBlink(Internal_siIdelBlink));
	viTecla = evButtonPressed_value;
	viMyCounter++;
}

/* Entry action for state 'Turn_OFF'. */
void Statechart::enact_IdleBlink_BLINK_Blink_Turn_OFF()
{
	/* Entry action for state 'Turn_OFF'. */
	timerService->setTimer(this, (sc_eventid)(&timeEvents[1]), 750, false);
	opLedUpdate();
	viMyCounter++;
}

/* Entry action for state 'Turn_ON'. */
void Statechart::enact_IdleBlink_BLINK_Blink_Turn_ON()
{
	/* Entry action for state 'Turn_ON'. */
	timerService->setTimer(this, (sc_eventid)(&timeEvents[2]), 250, false);
	opLedUpdate();
	viMyCounter++;
}

/* Exit action for state 'DEBOUNCE'. */
void Statechart::exact_Button_DEBOUNCE()
{
	/* Exit action for state 'DEBOUNCE'. */
	timerService->unsetTimer(this, (sc_eventid)(&timeEvents[0]));
}

/* Exit action for state 'Turn_OFF'. */
void Statechart::exact_IdleBlink_BLINK_Blink_Turn_OFF()
{
	/* Exit action for state 'Turn_OFF'. */
	timerService->unsetTimer(this, (sc_eventid)(&timeEvents[1]));
}

/* Exit action for state 'Turn_ON'. */
void Statechart::exact_IdleBlink_BLINK_Blink_Turn_ON()
{
	/* Exit action for state 'Turn_ON'. */
	timerService->unsetTimer(this, (sc_eventid)(&timeEvents[2]));
}

/* 'default' enter sequence for state DEBOUNCE */
void Statechart::enseq_Button_DEBOUNCE_default()
{
	/* 'default' enter sequence for state DEBOUNCE */
	enact_Button_DEBOUNCE();
	stateConfVector[0] = Button_DEBOUNCE;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state BUTTON_UNPRESSED */
void Statechart::enseq_Button_BUTTON_UNPRESSED_default()
{
	/* 'default' enter sequence for state BUTTON_UNPRESSED */
	stateConfVector[0] = Button_BUTTON_UNPRESSED;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state BUTTON_PRESSED */
void Statechart::enseq_Button_BUTTON_PRESSED_default()
{
	/* 'default' enter sequence for state BUTTON_PRESSED */
	enact_Button_BUTTON_PRESSED();
	stateConfVector[0] = Button_BUTTON_PRESSED;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state VALIDATE */
void Statechart::enseq_Button_VALIDATE_default()
{
	/* 'default' enter sequence for state VALIDATE */
	stateConfVector[0] = Button_VALIDATE;
	stateConfVectorPosition = 0;
}

/* 'default' enter sequence for state BLINK */
void Statechart::enseq_IdleBlink_BLINK_default()
{
	/* 'default' enter sequence for state BLINK */
	enseq_IdleBlink_BLINK_Blink_default();
}

/* 'default' enter sequence for state Turn_OFF */
void Statechart::enseq_IdleBlink_BLINK_Blink_Turn_OFF_default()
{
	/* 'default' enter sequence for state Turn_OFF */
	enact_IdleBlink_BLINK_Blink_Turn_OFF();
	stateConfVector[1] = IdleBlink_BLINK_Blink_Turn_OFF;
	stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state Turn_ON */
void Statechart::enseq_IdleBlink_BLINK_Blink_Turn_ON_default()
{
	/* 'default' enter sequence for state Turn_ON */
	enact_IdleBlink_BLINK_Blink_Turn_ON();
	stateConfVector[1] = IdleBlink_BLINK_Blink_Turn_ON;
	stateConfVectorPosition = 1;
}

/* 'default' enter sequence for state IDLE */
void Statechart::enseq_IdleBlink_IDLE_default()
{
	/* 'default' enter sequence for state IDLE */
	stateConfVector[1] = IdleBlink_IDLE;
	stateConfVectorPosition = 1;
}

/* 'default' enter sequence for region Button */
void Statechart::enseq_Button_default()
{
	/* 'default' enter sequence for region Button */
	react_Button__entry_Default();
}

/* 'default' enter sequence for region IdleBlink */
void Statechart::enseq_IdleBlink_default()
{
	/* 'default' enter sequence for region IdleBlink */
	react_IdleBlink__entry_Default();
}

/* 'default' enter sequence for region Blink */
void Statechart::enseq_IdleBlink_BLINK_Blink_default()
{
	/* 'default' enter sequence for region Blink */
	react_IdleBlink_BLINK_Blink__entry_Default();
}

/* Default exit sequence for state DEBOUNCE */
void Statechart::exseq_Button_DEBOUNCE()
{
	/* Default exit sequence for state DEBOUNCE */
	stateConfVector[0] = Statechart_last_state;
	stateConfVectorPosition = 0;
	exact_Button_DEBOUNCE();
}

/* Default exit sequence for state BUTTON_UNPRESSED */
void Statechart::exseq_Button_BUTTON_UNPRESSED()
{
	/* Default exit sequence for state BUTTON_UNPRESSED */
	stateConfVector[0] = Statechart_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state BUTTON_PRESSED */
void Statechart::exseq_Button_BUTTON_PRESSED()
{
	/* Default exit sequence for state BUTTON_PRESSED */
	stateConfVector[0] = Statechart_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state VALIDATE */
void Statechart::exseq_Button_VALIDATE()
{
	/* Default exit sequence for state VALIDATE */
	stateConfVector[0] = Statechart_last_state;
	stateConfVectorPosition = 0;
}

/* Default exit sequence for state BLINK */
void Statechart::exseq_IdleBlink_BLINK()
{
	/* Default exit sequence for state BLINK */
	exseq_IdleBlink_BLINK_Blink();
}

/* Default exit sequence for state Turn_OFF */
void Statechart::exseq_IdleBlink_BLINK_Blink_Turn_OFF()
{
	/* Default exit sequence for state Turn_OFF */
	stateConfVector[1] = Statechart_last_state;
	stateConfVectorPosition = 1;
	exact_IdleBlink_BLINK_Blink_Turn_OFF();
}

/* Default exit sequence for state Turn_ON */
void Statechart::exseq_IdleBlink_BLINK_Blink_Turn_ON()
{
	/* Default exit sequence for state Turn_ON */
	stateConfVector[1] = Statechart_last_state;
	stateConfVectorPosition = 1;
	exact_IdleBlink_BLINK_Blink_Turn_ON();
}

/* Default exit sequence for state IDLE */
void Statechart::exseq_IdleBlink_IDLE()
{
	/* Default exit sequence for state IDLE */
	stateConfVector[1] = Statechart_last_state;
	stateConfVectorPosition = 1;
}

/* Default exit sequence for region Button */
void Statechart::exseq_Button()
{
	/* Default exit sequence for region Button */
	/* Handle exit of all possible states (of Statechart.Button) at position 0... */
	switch(stateConfVector[ 0 ])
	{
		case Button_DEBOUNCE :
		{
			exseq_Button_DEBOUNCE();
			break;
		}
		case Button_BUTTON_UNPRESSED :
		{
			exseq_Button_BUTTON_UNPRESSED();
			break;
		}
		case Button_BUTTON_PRESSED :
		{
			exseq_Button_BUTTON_PRESSED();
			break;
		}
		case Button_VALIDATE :
		{
			exseq_Button_VALIDATE();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default exit sequence for region IdleBlink */
void Statechart::exseq_IdleBlink()
{
	/* Default exit sequence for region IdleBlink */
	/* Handle exit of all possible states (of Statechart.IdleBlink) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case IdleBlink_BLINK_Blink_Turn_OFF :
		{
			exseq_IdleBlink_BLINK_Blink_Turn_OFF();
			break;
		}
		case IdleBlink_BLINK_Blink_Turn_ON :
		{
			exseq_IdleBlink_BLINK_Blink_Turn_ON();
			break;
		}
		case IdleBlink_IDLE :
		{
			exseq_IdleBlink_IDLE();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default exit sequence for region Blink */
void Statechart::exseq_IdleBlink_BLINK_Blink()
{
	/* Default exit sequence for region Blink */
	/* Handle exit of all possible states (of Statechart.IdleBlink.BLINK.Blink) at position 1... */
	switch(stateConfVector[ 1 ])
	{
		case IdleBlink_BLINK_Blink_Turn_OFF :
		{
			exseq_IdleBlink_BLINK_Blink_Turn_OFF();
			break;
		}
		case IdleBlink_BLINK_Blink_Turn_ON :
		{
			exseq_IdleBlink_BLINK_Blink_Turn_ON();
			break;
		}
		default:
			/* do nothing */
			break;
	}
}

/* Default react sequence for initial entry  */
void Statechart::react_Button__entry_Default()
{
	/* Default react sequence for initial entry  */
	opButtonInit();
	viMyCounter = 0;
	enseq_Button_BUTTON_UNPRESSED_default();
}

/* Default react sequence for initial entry  */
void Statechart::react_IdleBlink_BLINK_Blink__entry_Default()
{
	/* Default react sequence for initial entry  */
	enseq_IdleBlink_BLINK_Blink_Turn_ON_default();
}

/* Default react sequence for initial entry  */
void Statechart::react_IdleBlink__entry_Default()
{
	/* Default react sequence for initial entry  */
	opLedInit();
	viMyCounter = 0;
	enseq_IdleBlink_IDLE_default();
}

sc_integer Statechart::react(const sc_integer transitioned_before) {
	/* State machine reactions. */
	return transitioned_before;
}

sc_integer Statechart::Button_DEBOUNCE_react(const sc_integer transitioned_before) {
	/* The reactions of state DEBOUNCE. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (timeEvents[0])
		{ 
			exseq_Button_DEBOUNCE();
			timeEvents[0] = false;
			enseq_Button_VALIDATE_default();
			transitioned_after = 0;
		} 
	} 
	return transitioned_after;
}

sc_integer Statechart::Button_BUTTON_UNPRESSED_react(const sc_integer transitioned_before) {
	/* The reactions of state BUTTON_UNPRESSED. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (evButtonPressed_raised)
		{ 
			exseq_Button_BUTTON_UNPRESSED();
			enseq_Button_DEBOUNCE_default();
			transitioned_after = 0;
		} 
	} 
	return transitioned_after;
}

sc_integer Statechart::Button_BUTTON_PRESSED_react(const sc_integer transitioned_before) {
	/* The reactions of state BUTTON_PRESSED. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (evButtonUnpressed_raised)
		{ 
			exseq_Button_BUTTON_PRESSED();
			enseq_Button_BUTTON_UNPRESSED_default();
			transitioned_after = 0;
		} 
	} 
	return transitioned_after;
}

sc_integer Statechart::Button_VALIDATE_react(const sc_integer transitioned_before) {
	/* The reactions of state VALIDATE. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (0))
	{ 
		if (evButtonPressed_raised)
		{ 
			exseq_Button_VALIDATE();
			enseq_Button_BUTTON_PRESSED_default();
			transitioned_after = 0;
		}  else
		{
			if (evButtonUnpressed_raised)
			{ 
				exseq_Button_VALIDATE();
				enseq_Button_BUTTON_UNPRESSED_default();
				transitioned_after = 0;
			} 
		}
	} 
	return transitioned_after;
}

sc_integer Statechart::IdleBlink_BLINK_react(const sc_integer transitioned_before) {
	/* The reactions of state BLINK. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
		if (siIdelBlink_raised)
		{ 
			exseq_IdleBlink_BLINK();
			enseq_IdleBlink_IDLE_default();
			react(0);
			transitioned_after = 1;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer Statechart::IdleBlink_BLINK_Blink_Turn_OFF_react(const sc_integer transitioned_before) {
	/* The reactions of state Turn_OFF. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
		if (timeEvents[1])
		{ 
			exseq_IdleBlink_BLINK_Blink_Turn_OFF();
			timeEvents[1] = false;
			enseq_IdleBlink_BLINK_Blink_Turn_ON_default();
			IdleBlink_BLINK_react(1);
			transitioned_after = 1;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = IdleBlink_BLINK_react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer Statechart::IdleBlink_BLINK_Blink_Turn_ON_react(const sc_integer transitioned_before) {
	/* The reactions of state Turn_ON. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
		if (timeEvents[2])
		{ 
			exseq_IdleBlink_BLINK_Blink_Turn_ON();
			timeEvents[2] = false;
			enseq_IdleBlink_BLINK_Blink_Turn_OFF_default();
			IdleBlink_BLINK_react(1);
			transitioned_after = 1;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = IdleBlink_BLINK_react(transitioned_before);
	} 
	return transitioned_after;
}

sc_integer Statechart::IdleBlink_IDLE_react(const sc_integer transitioned_before) {
	/* The reactions of state IDLE. */
	sc_integer transitioned_after = transitioned_before;
	if ((transitioned_after) < (1))
	{ 
		if (siIdelBlink_raised)
		{ 
			exseq_IdleBlink_IDLE();
			enseq_IdleBlink_BLINK_default();
			react(0);
			transitioned_after = 1;
		} 
	} 
	/* If no transition was taken then execute local reactions */
	if ((transitioned_after) == (transitioned_before))
	{ 
		transitioned_after = react(transitioned_before);
	} 
	return transitioned_after;
}

void Statechart::clearInEvents() {
	evButtonUnpressed_raised = false;
	evButtonPressed_raised = false;
	timeEvents[0] = false;
	timeEvents[1] = false;
	timeEvents[2] = false;
}

void Statechart::clearInternalEvents() {
	siIdelBlink_raised = false;
}

void Statechart::microStep() {
	sc_integer transitioned = -1;
	stateConfVectorPosition = 0;
	switch(stateConfVector[ 0 ])
	{
		case Button_DEBOUNCE :
		{
			transitioned = Button_DEBOUNCE_react(transitioned);
			break;
		}
		case Button_BUTTON_UNPRESSED :
		{
			transitioned = Button_BUTTON_UNPRESSED_react(transitioned);
			break;
		}
		case Button_BUTTON_PRESSED :
		{
			transitioned = Button_BUTTON_PRESSED_react(transitioned);
			break;
		}
		case Button_VALIDATE :
		{
			transitioned = Button_VALIDATE_react(transitioned);
			break;
		}
		default:
			/* do nothing */
			break;
	}
	if ((stateConfVectorPosition) < (1))
	{ 
		switch(stateConfVector[ 1 ])
		{
			case IdleBlink_BLINK_Blink_Turn_OFF :
			{
				IdleBlink_BLINK_Blink_Turn_OFF_react(transitioned);
				break;
			}
			case IdleBlink_BLINK_Blink_Turn_ON :
			{
				IdleBlink_BLINK_Blink_Turn_ON_react(transitioned);
				break;
			}
			case IdleBlink_IDLE :
			{
				IdleBlink_IDLE_react(transitioned);
				break;
			}
			default:
				/* do nothing */
				break;
		}
	} 
}

void Statechart::runCycle() {
	/* Performs a 'run to completion' step. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	dispatch_event(getNextEvent());
	do
	{ 
		microStep();
		clearInEvents();
		clearInternalEvents();
		dispatch_event(getNextEvent());
	} while ((((((evButtonUnpressed_raised) || (evButtonPressed_raised)) || (siIdelBlink_raised)) || (timeEvents[0])) || (timeEvents[1])) || (timeEvents[2]));
	isExecuting = false;
}

void Statechart::enter() {
	/* Activates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default enter sequence for statechart Statechart */
	enseq_Button_default();
	enseq_IdleBlink_default();
	isExecuting = false;
}

void Statechart::exit() {
	/* Deactivates the state machine. */
	if (isExecuting)
	{ 
		return;
	} 
	isExecuting = true;
	/* Default exit sequence for statechart Statechart */
	exseq_Button();
	exseq_IdleBlink();
	isExecuting = false;
}

/* Can be used by the client code to trigger a run to completion step without raising an event. */
void Statechart::triggerWithoutEvent() {
	runCycle();
}
