struct Channel
{
    const int btnPin;
    const int relayPin;
    const int ledPin;

    bool lastState;
    bool currentState;

    bool state;
};

Channel Channels[] =
{
    { 18,  8, 6, LOW, LOW, true  },
    { 17,  9, 5, LOW, LOW, true  },
    { 16, 10, 4, LOW, LOW, false },
    { 15, 11, 3, LOW, LOW, false },
    { 14, 12, 2, LOW, LOW, false }
};

void setup()
{
    for(unsigned i = 0; i < sizeof(Channels)/sizeof(Channels[0]); i++)
    {
        const Channel& ch = Channels[i];
        pinMode(ch.btnPin, INPUT_PULLUP);
        pinMode(ch.relayPin, OUTPUT);

        pinMode(ch.ledPin, OUTPUT);
        digitalWrite(ch.ledPin, ch.state);
    }
}

void loop()
{
    for(unsigned i = 0; i < sizeof(Channels)/sizeof(Channels[0]); i++)
    {
        Channel& ch = Channels[i];
        ch.currentState = digitalRead(ch.btnPin);
    }

    delay(5);

    for(unsigned i = 0; i < sizeof(Channels)/sizeof(Channels[0]); i++)
    {
        Channel& ch = Channels[i];

        const bool last = ch.lastState;
        if(last != ch.currentState)
        {
            ch.currentState = digitalRead(ch.btnPin);
        }

        bool state = ch.state;
        if(ch.currentState == LOW && ch.lastState == HIGH)
        {
            state = !state;
        }

        ch.lastState = ch.currentState;
        ch.state = state;

        // set LED state
        digitalWrite(ch.ledPin, state);

        // set Relay state
        digitalWrite(ch.relayPin, state);
    }
}

