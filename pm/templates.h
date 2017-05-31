#include "stdafx.h"

/*
	Csak template gykorlás, nincs a programban semmi revelanciája, csak itt írtam meg, mert nem akartam új projektet nyitni neki. :)
*/

template <class ItemType>
class Fifo {
private:
	ItemType* data;
	int size;
protected:
public:
	Fifo();
	~Fifo();
	Fifo(const Fifo& fifo);
	ItemType getFifoData();
	void setFifoData(ItemType);
	void writeDataToConsole();
};

template<class ItemType>
Fifo<ItemType>::Fifo()
{
	size = 0;
}

template<class ItemType>
Fifo<ItemType>::~Fifo()
{	
	delete data;
}

template<class ItemType>
Fifo<ItemType>::Fifo(const Fifo & fifo)
{
	size = fifo->size;
	data = fifo.data;
}

template<class ItemType>
ItemType Fifo<ItemType>::getFifoData()
{
	if (this->data != nullptr)
		return data;
	return nullptr;
}

template<class ItemType>
void Fifo<ItemType>::setFifoData(ItemType value)
{
	this->data = &value;
}

template<class ItemType>
inline void Fifo<ItemType>::writeDataToConsole()
{
	std::cout << "\nFifo data: " << data << "endl";
}
