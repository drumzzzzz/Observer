#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

#define MAX_COUNT 20

// Abstract base observer method
class Observer
{
public:
    virtual void update(float a, float b, int count) = 0;
};

// Abstract observer registration and notification
class Subject
{
public:
	virtual void registerObserver(Observer* o) = 0;
    virtual void unregisterObserver(Observer* o) = 0;
    virtual void unregisterObservers() = 0;
    virtual void notifyObservers() = 0;
};

class Processor : public Subject
{
private:
	// Input values and extents 	
    float a, b, min_value, max_value;
	int count, min_count, max_count;

    vector<Observer*> observerList;

	// Observer notification: iterate instances with random values and perform any calculations
    void notifyObservers() override
    {
        cout << "Updating " << observerList.size() << " Observers [a = " << a << ", b = "
    		 << b << ", count = " << count << "]" << endl;
 	
        for (int i = 0; i < observerList.size(); i++) 
        {
            if (observerList.at(i) != nullptr) 
            {
                observerList.at(i)->update(a, b, count);
            }
        }

        cout << endl;
    }

	// Random a, b Value 
	float getRandomValue()
    {
        return  (max_value - min_value) * ((((float)rand()) / (float)RAND_MAX)) + min_value;
    }

	// Operation count
	int getRandomCount()
    {
        return rand() % (max_count - min_count) + min_count;
    }

public:
	// Constructor
    Processor(float _min_value, float _max_value, int _min_count, int _max_count)
	{
        a = b = 0;
        count = 0;
        srand(time(0));  // Initialize random number generator.
        min_value = _min_value;
        max_value = _max_value;
        min_count = (_min_count > MAX_COUNT) ? MAX_COUNT : _min_count;
        max_count = (_max_count > MAX_COUNT) ? MAX_COUNT : _max_count;
    }

	// Add observer to list
    void registerObserver(Observer* o) override
    {
        observerList.push_back(o);
    }

	// Remove a selected observer
    void unregisterObserver(Observer* o) override
    {
        for (int i = 0; i < observerList.size(); i++) 
        {
            if (observerList.at(i) == o) 
            {
                observerList.erase(observerList.begin() + i);
            }
        }
    }

	// Remove all observers
    void unregisterObservers() override
    {
        observerList.clear();
    }

    // On data change: set values and call observer update method
    void dataChanged()
	{
        a = getRandomValue();
        b = getRandomValue();
        count = getRandomCount();

        notifyObservers();
    }
};

// Addition
class CalcAdd : public Observer
{
private:
    float a = 0;
    float b = 0;
    float result = 0;
    int count = 0;

public:
    void update(float _a, float _b, int _count) override
    {
        a = _a;
        b = _b;
        count = _count;
        result = 0;
    	
        for (int i=0; i<count; i++)
        {
            result += (a + b);
        }
    	
        display();
    }

    void display()
	{
        cout << "Addition Sum(a + b) = " << result << endl;
    }
};

// Subtraction
class CalcSubtract : public Observer
{
private:
    float a = 0;
    float b = 0;
    float result = 0;
    int count = 0;

public:
    void update(float _a, float _b, int _count) override
    {
        a = _a;
        b = _b;
        count = _count;
        result = 0;

        for (int i = 0; i < count; i++)
        {
            result += (a - b);
        }

        display();
    }

    void display()
    {
        cout << "Subtract Sum(a - b) = " << result << endl;
    }
};

// Multiplication
class CalcMultiply : public Observer
{
private:
    float a = 0;
    float b = 0;
    float result = 0;
    int count = 0;

public:
    void update(float _a, float _b, int _count) override
    {
        a = _a;
        b = _b;
        count = _count;
        result = 0;

        for (int i = 0; i < count; i++)
        {
            result += (a * b);
        }

        display();
    }

    void display()
    {
        cout << "Multiply Sum(a * b) = " << result << endl;
    }
};

// Division
class CalcDivide : public Observer
{
private:
    float a = 0;
    float b = 0;
    float result = 0;
    int count = 0;

public:
    void update(float _a, float _b, int _count) override
    {
        a = _a;
        b = _b;
        count = _count;
        result = 0;

        if (b == 0)
        {
            cout << "Division by Zero Error Occurred." << endl;
        }
        else
		    {
		        for (int i = 0; i < count; i++)
		        {
		            result += (a / b);
		        }
		    }

        display();
    }

    void display()
    {
        cout << "Division Sum(a / b) = " << result << endl;
    }
};

int main()
{
	// Instaneate observer processor with value extents
    Processor p = Processor(0, 100, 2, 10);
	
    // Instaneate calculation observers 
    CalcAdd calcAdd = CalcAdd();
    CalcSubtract calcSubtract = CalcSubtract();
    CalcMultiply calcMultiply = CalcMultiply();
    CalcDivide calcDivide = CalcDivide();
	
	// Register the observers and call update
    p.registerObserver(&calcAdd);
    p.registerObserver(&calcSubtract);
    p.registerObserver(&calcMultiply);
    p.registerObserver(&calcDivide);
    p.dataChanged();

    // Test two observer removals and update
    p.unregisterObserver(&calcSubtract);
    p.unregisterObserver(&calcDivide);
    p.dataChanged();


    // Test all observer removals and update
    p.unregisterObservers();
    p.dataChanged();
}