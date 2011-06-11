#ifndef SINGLETON_H_INCLUDED
#define SINGLETON_H_INCLUDED
 
namespace al
{
template <class T>
class Singleton
{
protected:
    Singleton() { }
    virtual ~Singleton() { }
 
public:
    static T* instance()
    {
        if (m_Instance == NULL)
            m_Instance = new T;
 
        return m_Instance;
    }
 
private:
    static T* m_Instance;
};
 
template <class T>
T* Singleton<T>::m_Instance = NULL;
}
 
#endif // SINGLETON_H_INCLUDED
 
