#include <throttler.h>

Throttler event_1(1000, []() {
    Serial.println(millis());
});

void setup() {
    Serial.begin(115200);
    
    /*
    // change function
    event_1.fn([]() {
        Serial.println("Other function");
    });
    */
    
    /*
    // change interval
    event_1.set_interval(5000);
    */
}

void loop() {
    // call from anywhere in the code
    event_1.execute();
    
    // run in loop
    Throttler::loop_all();
}