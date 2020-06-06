//
//  animal.cpp
//  Homework 3
//
//  Created by Cymfenee on 5/4/20.
//  Copyright © 2020 CDP. All rights reserved.
//

class Animal
{
public:
    Animal (string name);
    virtual string name() const
    {
        return m_name;
    }
    virtual void speak() const=0;
    virtual string moveAction() const=0;
    virtual ~Animal();
    
private:
    string m_name;
    
};

Animal::Animal(string name)
: m_name(name)
{}

Animal::~Animal()
{};

class Cat : public Animal
{
public:
    Cat(string name) : Animal(name)
    {};
    
    virtual void speak() const
    {
        cout << "Meow";
    }
    
    virtual string moveAction() const
    {
        return "walk";
    }
    
    virtual ~Cat()
    {
        cout << "Destroying " << name() << " the cat." << endl;
    }
    
};

class Pig : public Animal
{
public:
    Pig(string name, int weight) : Animal(name)
    {
        p_weight=weight;
    };
    
    virtual void speak() const
    {
        if (p_weight<160)
        {
            cout << "Oink";
        }
        else
        {
            cout << "Grunt";
        }
    }
    
    
    virtual string moveAction() const
    {
        return "walk";
    }
    
    virtual ~Pig()
    {
        cout << "Destroying " << name() << " the pig." << endl;
    }
    
private:
    int p_weight;
};

class Duck : public Animal
{
public:
    Duck(string name) : Animal(name)
    {};
     
    virtual void speak() const
    {
        cout << "Quack";
    }
    
    virtual string moveAction() const
    {
        return "swim";
    }
    
    virtual ~Duck()
    {
        cout << "Destroying " << name() << " the duck." << endl;
    }
};


int main()
{
    Animal* animals[4];
    animals[0] = new Cat("Fluffy");
      // Pigs have a name and a weight in pounds.  Pigs under 160
      // pounds oink; pigs weighing at least 160 pounds grunt.
    animals[1] = new Pig("Napoleon", 190);
    animals[2] = new Pig("Wilbur", 50);
    animals[3] = new Duck("Daffy");

    cout << "Here are the animals." << endl;
    for (int k = 0; k < 4; k++)
        animate(animals[k]);

      // Clean up the animals before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete animals[k];
}

