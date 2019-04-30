#include <iostream>


class ProductA {
    public:
        virtual void printDescription(void) const
        {
            std::cout << "Product Type A ";
        }
};

class ProductB
{
    public:
        virtual void printDescription (void) const
        {
            std::cout << "Product Type B ";
        }
};


class ProductA_modelX : public ProductA
{
    public:
        virtual void printDescription (void) const
        {
            ProductA::printDescription();
            std::cout << "Model X ";
        }
};

class ProductA_modelY: public ProductA
{
    public:
        virtual void printDescription (void) const
        {
            ProductA::printDescription();
            std::cout << "Model Y ";
        }
};

class ProductB_ModelX: public ProductB
{
    public:
        virtual void printDescription (void) const
        {
            ProductB::printDescription();
            std::cout << "Model X ";
        }
};

class ProductB_ModelY: public ProductB
{
    public:
        virtual void printDescription (void) const
        {
            ProductB::printDescription();
            std::cout << "Model Y ";
        }
};

class AbstractFactory
{
    public:
        virtual ProductA* creatProductA (void) const = 0;
        virtual ProductB* creatProductB (void) const = 0;

};

class ConcreteFactoryModelX: public AbstractFactory
{
    public:
        virtual ProductA* creatProductA (void) const
        {

            return ( new ProductA_modelX() );
        }
        virtual ProductB* creatProductB (void) const
        {
            return ( new ProductB_ModelX() );
        }
};

class ConcreteFactoryModelY: public AbstractFactory
{
    public:
        virtual ProductA* creatProductA (void) const
        {
            return new ProductA_modelY();
        }
        virtual ProductB* creatProductB (void) const
        {
            return new ProductB_ModelY();
        }
};


void creatProduct(AbstractFactory* const factory)
{
    factory->creatProductA()->printDescription();
    factory->creatProductB()->printDescription();

}


int main()
{

    ConcreteFactoryModelX* modelX = new ConcreteFactoryModelX();
    ConcreteFactoryModelY* modelY = new ConcreteFactoryModelY();

    creatProduct(modelX);
    std::cout << std::endl;
    creatProduct(modelY);


    return 0;
}


