#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 定义回调函数类型
typedef void (*EventCallback)(int, int);

// 事件处理器结构体，用于存储回调函数
typedef struct {
    EventCallback onTemperatureChange;
    EventCallback onAlarmTrigger;
    int threshold; // 用户设定的温度阈值
} SensorEventHandler;

// 注册温度变化回调函数
void registerTemperatureChangeCallback(SensorEventHandler* handler, EventCallback callback) {
    if (handler != NULL) {
        handler->onTemperatureChange = callback;
    }
}

// 注册警报触发回调函数
void registerAlarmTriggerCallback(SensorEventHandler* handler, EventCallback callback) {
    if (handler != NULL) {
        handler->onAlarmTrigger = callback;
    }
}

// 设置温度阈值
void setTemperatureThreshold(SensorEventHandler* handler, int threshold) {
    if (handler != NULL) {
        handler->threshold = threshold;
    }
}

// 模拟温度变化事件
void simulateTemperatureChange(SensorEventHandler* handler, int sensorId, int temperature) {
    if (handler != NULL && handler->onTemperatureChange != NULL) {
        handler->onTemperatureChange(sensorId, temperature);
        if (temperature > handler->threshold) {
            if (handler->onAlarmTrigger != NULL) {
                handler->onAlarmTrigger(sensorId, temperature);
            }
        }
    }
}

// 温度变化回调函数
void temperatureChangedCallback(int sensorId, int temperature) {
    printf("传感器%d: 当前温度：%d°C\n", sensorId, temperature);
}

// 警报触发回调函数
void triggerAlarmCallback(int sensorId, int temperature) {
    printf("警报：传感器%d检测到温度超过阈值！当前温度：%d°C\n", sensorId, temperature);
}

// 主函数
int main() {
    const int numSensors = 3; // 假设有3个传感器
    SensorEventHandler handlers[numSensors];

    // 初始化随机数发生器
    srand(time(NULL));

    // 初始化每个传感器的事件处理器并设置阈值
    for (int i = 0; i < numSensors; i++) {
        handlers[i].onTemperatureChange = NULL;
        handlers[i].onAlarmTrigger = NULL;
        setTemperatureThreshold(&handlers[i], 30); // 设置阈值为30°C
        registerTemperatureChangeCallback(&handlers[i], temperatureChangedCallback);
        registerAlarmTriggerCallback(&handlers[i], triggerAlarmCallback);
    }

    // 模拟每个传感器的温度变化
    for (int i = 0; i < 10; i++) { // 模拟10次温度变化
        for (int j = 0; j < numSensors; j++) {
            int simulatedTemperature = rand() % 40; // 生成0到39之间的随机温度
            simulateTemperatureChange(&handlers[j], j + 1, simulatedTemperature);
        }
    }

    return 0;
}
