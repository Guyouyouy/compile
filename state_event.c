#include <stdio.h>


//步骤 1: 定义状态和事件
typedef enum {
    STATE_INITIAL,
    STATE_RUNNING,
    STATE_PAUSED,
    STATE_STOPPED
} State;

typedef enum {
    EVENT_START,
    EVENT_PAUSE,
    EVENT_STOP,
    EVENT_RESUME
} Event;


//步骤 2: 定义状态机结构体
typedef void (*EventCallback)(void);

typedef struct {
    State currentState;
    EventCallback onStart;
    EventCallback onPause;
    EventCallback onStop;
    EventCallback onResume;
} StateMachine;



//步骤 3: 实现状态转换和事件处理逻辑
void changeState(StateMachine *machine, State newState) {
    machine->currentState = newState;
}

void handleEvent(StateMachine *machine, Event event) {
    switch (event) {
        case EVENT_START:
            if (machine->onStart != NULL) {
                machine->onStart();
                changeState(machine, STATE_RUNNING);
            }
            break;
        case EVENT_PAUSE:
            if (machine->currentState == STATE_RUNNING && machine->onPause != NULL) {
                machine->onPause();
                changeState(machine, STATE_PAUSED);
            }
            break;
        case EVENT_STOP:
            if (machine->onStop != NULL) {
                machine->onStop();
                changeState(machine, STATE_STOPPED);
            }
            break;
        case EVENT_RESUME:
            if (machine->currentState == STATE_PAUSED && machine->onResume != NULL) {
                machine->onResume();
                changeState(machine, STATE_RUNNING);
            }
            break;
    }
}

//步骤 4: 实现具体的回调函数
void onStartAction() {
    printf("System is starting...\n");
}

void onPauseAction() {
    printf("System is pausing...\n");
}

void onStopAction() {
    printf("System is stopping...\n");
}

void onResumeAction() {
    printf("System is resuming...\n");
}

//步骤 5: 注册回调函数并运行状态机
int main() {
    StateMachine machine;

    // 初始化状态机
    machine.currentState = STATE_INITIAL;
    machine.onStart = onStartAction;
    machine.onPause = onPauseAction;
    machine.onStop = onStopAction;
    machine.onResume = onResumeAction;

    // 模拟事件触发
    handleEvent(&machine, EVENT_START);
    handleEvent(&machine, EVENT_PAUSE);
    handleEvent(&machine, EVENT_RESUME);
    handleEvent(&machine, EVENT_STOP);

    return 0;
}
