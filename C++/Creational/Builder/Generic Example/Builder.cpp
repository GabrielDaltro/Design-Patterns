/*
Gabriel Daltro Duarte
Structure of Builder Design Pattern.

*/

class Object { // Object that will be build
    public:
        //Methods
    private:
        //attributes
};


class Builder { // Builder Interfaces
    public:
        virtual void BuilObjectPartOne(){/*Do nothing*/}
        virtual void BuilObjectPartTwo(){/*Do nothing*/}
        virtual void BuilObjectPartThree(){/*Do nothing*/}
        // Other Build Methods
    protected:
        Builder(){}

};


class ConcretBuilderA: public Builder
{
    public:
        // Override BuilObjectPartOne of basic class - Construct a part of objectUnderConstruction
        virtual void BuilObjectPartOne(){/*Do nothing*/}
        // Override BuilObjectPartTwo of basic class - Construct other part of objectUnderConstruction
        virtual void BuilObjectPartTwo(){/*Do nothing*/}
        //return the constructed object
        virtual Object* getResul() {return product;}

        //Other methods
    private:
        Object* product; // Object under Construction
        // Other Attributes
};

class ConcretBuilderB: public Builder
{
    public:
        // Override BuilObjectPartTwo of basic class - Construct other part of objectUnderConstruction
        virtual void BuilObjectPartTwo(){/*Do nothing*/}
        // Override BuilObjectPartThree of basic class - Construct other part of objectUnderConstruction
        virtual void BuilObjectPartThree(){/*Do nothing*/}
        //return the constructed object
        virtual Object* getResul() {return product;}

        //Other methods
    private:
        Object* product; // Object under Construction
        //Other Attributes
};


class Director
{
    public:
        void CreateObject (Builder& builder)
        {
            builder.BuilObjectPartOne();
            builder.BuilObjectPartTwo();
            builder. BuilObjectPartThree();
        }
} ;


int main() // client
{
    Object* obj; //ptr to object that will be build
    ConcretBuilderA builderA; //object Builder A
    Director director; // director object

    director.CreateObject(builderA); // build the object
    obj = builderA.getResul();


    return 0;
}














