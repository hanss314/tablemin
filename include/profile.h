#define MAX_X 15200
#define MAX_Y 9500
#define MAX_P 4095

class Profile{
    public:
    virtual void setState(const unsigned char *state){};
    virtual float getNext(){ return 0; };
    virtual ~Profile() {};
};

class BasicProfile : public Profile{
    protected:
       float i, start, end, vol, voltarget, di;
       int rate;
    public:     
    BasicProfile(int rate, float start, float end){
        this->rate = rate;
        this->start = start;
        this->end = end;

        this->i=0.0;
        this->vol=0.0;
        this->voltarget=0.0;
        this->di=0.0;
    }
    void setState(const unsigned char *state);
    float getNext();
};
