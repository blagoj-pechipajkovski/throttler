#ifndef THROTTLER
#define THROTTLER

class Throttler {
  private:
    unsigned long _interval = 1000;
    unsigned long _last_execution = 0;
    
    void (*_fn)() = nullptr;
    
    bool _do_run = false;
    
    Throttler* _prev_instance = nullptr;
    static Throttler* _latest_instance;
  public:
    
    void fn(void (*new_fn)()) {
        _fn = new_fn;
    }
    
    void set_interval(unsigned long new_interval) {
        _interval = new_interval;
    }
    
    Throttler(unsigned long new_interval, void (*new_fn)() = nullptr) {
        if (Throttler::_latest_instance != nullptr)
            _prev_instance = Throttler::_latest_instance;
        Throttler::_latest_instance = this;
        set_interval(new_interval);
        fn(new_fn);
    }
    
    void loop() {
        if (_do_run && millis() > _last_execution + _interval) {
            if (_fn != nullptr)
                _fn();
            _last_execution = millis();
            _do_run = false;
        }
    }
    
    void execute() {
        _do_run = true;
    }
    
    static void loop_all() {
        Throttler* li = Throttler::_latest_instance;
        while (li != nullptr) {
            li->loop();
            li = li->_prev_instance;
        }
    }
};
Throttler* Throttler::_latest_instance = nullptr;
#endif