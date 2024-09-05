#ifndef SINGLETON_DB
#define SINGLETON_DB

template <class T>
class Singleton
{
	private:
	static T* instance;
	
	public:
	Singleton () {instance = nullptr;}
	
	static void create_instance () {instance = new T();}
	
	static void destroy_instance ()
	{
		delete instance;
		instance = nullptr;
	}
	
	static void set_instance (T* newInstance)
	{
		if (instance != nullptr) {destroy_instance ();}
		instance = newInstance;
	}
	
	static T& get_instance () {return *instance;}
};

template <class T>
T* Singleton<T>::instance = nullptr;

#endif // SINGLETON_DB