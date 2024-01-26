# throttler

## Description

Throttle the rate of execution of Arduino code.

## Usage

### Instantiation

Include library.

```c++
#include <throttler.h>
```

Specify the interval and code that should be executed.  
Example 1000ms interval and code that prints milliseconds.

```c++
Throttler throttled_event(1000, []() {
    Serial.println(millis());
});
```

### Running the code

When the code needs to be executed call the ```execute()``` method.

```c++
throttled_event.execute();
```

This will either execute the code, or wait for interval to elapse and then execute it.

### Loop

Make sure to call the loop function inside loop and make sure that your loop doesn't use any blocking code like ```delay()```.

To run every instance use:

```
Throttler::loop_all();
```

To run a particular instance use:

```
throttled_event.loop();
```

## Other methods

The function and interval can be changed at any time.

To change the function use:

```c++
throttled_event.fn([]() {
    Serial.println("Other function");
});
```

To change the interval use:

```c++
throttled_event.set_interval(5000);
```
