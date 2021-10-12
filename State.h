
class State
{
public:
    virtual void start() = 0;
    virtual void abort() = 0;
    virtual void pause() = 0;
    virtual void resume() = 0;
    std::string state{};
    const std::string& getCurrentState() const { return state; };

    ~State() { }

};


