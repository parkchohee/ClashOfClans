#pragma once


template<typename T>
class singletonBase
{
protected:
	//ΩÃ±€≈Ê ¿ŒΩ∫≈œΩ∫ º±æ
	static T* singleton;

	singletonBase() {}
	~singletonBase() {}

public:
	static T* getSingleton();
	void releaseSingleton();
};

//ΩÃ±€≈Ê √ ±‚»≠
template <typename T>
T* singletonBase<T>::singleton = NULL;

//ΩÃ±€≈Ê ∞™ ∞°¡Æø¿±‚
template <typename T>
T* singletonBase<T>::getSingleton()
{
	if ( !singleton ) singleton = new T;
	return singleton;
}

//ΩÃ±€≈Ê ∏ﬁ∏∏Æ «ÿ¡¶
template <typename T>
void singletonBase<T>::releaseSingleton()
{
	if ( singleton )
	{
		delete singleton;
		singleton = NULL;
	}
}