/*Ted McNulty
 *2/27/17
 *ENGR 2535

*Header for vectorobject
*/



#ifndef vectorobject_h
#define vectorobject_h

class Vectorobject {

public:
	
	Vectorobject(float* c);
	Vectorobject();

	~Vectorobject();

	Vectorobject average(Vectorobject v);

    float* get();
    void set(float* c);
    
    bool add(Vectorobject v);
    
    Vectorobject distribute();

    Vectorobject invert();

    Vectorobject rotate_clockwise(double angel);

    void print();

protected:
    

    float *coordinates;
    
private:
    
};

#endif