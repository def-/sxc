#ifndef SINGLETON_H
#define SINGLETON_H


template <class Type>
class Singleton
{
    public:
        static Type &getInstance()
        {
            static Instance instance;
            return instance;
        }
    private:
        virtual void SingletonCannotBeInstantiated() = 0;

        class Instance : public Type
        {
            private:
                void SingletonCannotBeInstantiated() {}
        };
};


#endif // SINGLETON_H
