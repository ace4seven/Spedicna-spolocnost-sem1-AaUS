#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../ds_routines.h"
#include "structures\heap_monitor.h"

namespace structures
{

	/// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
	template<typename T>
	class LinkedListItem : public DataItem<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		LinkedListItem(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti.. </param>
		LinkedListItem(const LinkedListItem<T>& other);

		/// <summary> Destruktor. </summary>
		~LinkedListItem();

		/// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
		LinkedListItem<T>* getNext();

		/// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
		/// <param name�= "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
		void setNext(LinkedListItem<T>* next);
	private:
		/// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
		LinkedListItem<T>* next_;
	};

	/// <summary> Jednostranne zretazeny zoznam. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class LinkedList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		LinkedList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
		LinkedList(const LinkedList<T>& other);

		/// <summary> Destruktor. </summary>
		~LinkedList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		LinkedList<T>& operator=(const LinkedList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	private:
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
		/// <summary> Prvy prvok zoznamu. </summary>
		LinkedListItem<T>* first_;
		/// <summary> Posledny prvok zoznamu. </summary>
		LinkedListItem<T>* last_;
	private:
		/// <summary> Vrati prvok zoznamu na danom indexe. </summary>
		/// <param name = "index"> Pozadovany index. </summary>
		/// <returns> Prvok zoznamu na danom indexe. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		LinkedListItem<T>* getItemAtIndex(int index) const;
	private:
		/// <summary> Iterator pre LinkedList. </summary>
		class LinkedListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
			LinkedListIterator(LinkedListItem<T>* position);

			/// <summary> Destruktor. </summary>
			~LinkedListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;
		private:
			/// <summary> Aktualna pozicia v zozname. </summary>
			LinkedListItem<T>* position_;
		};
	};

	template<typename T>
	inline LinkedListItem<T>::LinkedListItem(T data) :
		DataItem<T>(data),
		next_(nullptr)
	{
	}

	template<typename T>
	inline LinkedListItem<T>::LinkedListItem(const LinkedListItem<T>& other) :
		DataItem<T>(other),
		next_(other.next_)
	{
	}

	template<typename T>
	inline LinkedListItem<T>::~LinkedListItem()
	{
		next_ = nullptr;
	}

	template<typename T>
	inline LinkedListItem<T> * LinkedListItem<T>::getNext()
	{
		return next_;
	}

	template<typename T>
	inline void LinkedListItem<T>::setNext(LinkedListItem<T> * next)
	{
		next_ = next;
	}

	template<typename T>
	inline LinkedList<T>::LinkedList() :
		List(),
		size_(0),
		first_(nullptr),
		last_(nullptr)
	{
	}

	template<typename T>
	inline LinkedList<T>::LinkedList(const LinkedList<T>& other) :
		LinkedList()
	{
		*this = other; // operator priradenia mame ako kopirovaci konstruktor, netreba duplikovat
	}

	template<typename T>
	inline LinkedList<T>::~LinkedList()
	{
		//TODO 04: LinkedList
		clear();
	}

	template<typename T>
	inline Structure * LinkedList<T>::clone() const
	{
		return new LinkedList<T>(*this);
	}

	template<typename T>
	inline size_t LinkedList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& LinkedList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const LinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other)
	{
		//TODO 04: LinkedList
		if (this != &other)
		{
			clear();

			LinkedListItem<T> *otherCur = other.first_;

			while (otherCur != nullptr)
			{
				add(otherCur->accessData());
				otherCur = otherCur->getNext();
			}
		}

		return *this;
	}

	template<typename T>
	inline T & LinkedList<T>::operator[](const int index)
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T LinkedList<T>::operator[](const int index) const
	{
		return getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void LinkedList<T>::add(const T & data)
	{
		LinkedListItem<T>* newItem = new LinkedListItem<T>(data);

		if (first_ == nullptr)
		{
			first_ = newItem;
		}
		else
		{
			last_->setNext(newItem);
		}
		last_ = newItem;
		size_++;
	}

	template<typename T>
	inline void LinkedList<T>::insert(const T & data, const int index)
	{
		if (index == size_)
		{
			add(data);
		}
		else
		{
			DSRoutines::rangeCheckExcept(index, size_, "Out of index");
			LinkedListItem<T>* newItem = new LinkedListItem<T>(data);
			if (index == 0)
			{
				newItem->setNext(first_);
				first_ = newItem;
			}
			else
			{
				LinkedListItem<T>* prev = getItemAtIndex(index - 1);
				newItem->setNext(prev->getNext());
				prev->setNext(newItem);
			}
			size_++;
		}
	}

	template<typename T>
	inline bool LinkedList<T>::tryRemove(const T & data)
	{
		int index = getIndexOf(data);
		if (index == -1)
			return false;
		else
		{
			removeAt(index);
			return true;
		}
	}

	template<typename T>
	inline T LinkedList<T>::removeAt(const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid Index");

		LinkedListItem<T>* deleted;

		if (index != 0)
		{
			LinkedListItem<T>* prev = getItemAtIndex(index - 1);
			deleted = prev->getNext();
			prev->setNext(deleted->getNext());

			if (last_ == deleted)
				last_ = prev;
		}
		else
		{
			deleted = first_;
			first_ = first_->getNext();

			if (last_ == deleted)
				last_ = nullptr;
		}

		size_--;
		T data = deleted->accessData();
		delete deleted;

		return data;
	}

	template<typename T>
	inline int LinkedList<T>::getIndexOf(const T & data)
	{
		LinkedListItem<T> *cur = first_;
		int index = 0;
		bool finded = false;

		while (cur != nullptr)
		{
			if (cur->accessData() == data)
			{
				finded = true;
				break;
			}
			index++;
			cur = cur->getNext();
		}

		return finded ? index : -1;
	}

	template<typename T>
	inline void LinkedList<T>::clear()
	{
		//TODO 04: LinkedList
		LinkedListItem<T>* cur = first_;
		while (cur != nullptr)
		{
			first_ = cur->getNext();
			delete cur;
			cur = first_;
		}

		last_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* LinkedList<T>::getBeginIterator() const
	{
		return new LinkedListIterator(first_);
	}

	template<typename T>
	inline Iterator<T>* LinkedList<T>::getEndIterator() const
	{
		return new LinkedListIterator(nullptr);
	}

	template<typename T>
	inline LinkedListItem<T>* LinkedList<T>::getItemAtIndex(int index) const
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid Index");

		LinkedListItem<T> *cur = first_;
		for (int i = 0; i < index; i++)
		{
			cur = cur->getNext();
		}

		return cur;
	}

	template<typename T>
	inline LinkedList<T>::LinkedListIterator::LinkedListIterator(LinkedListItem<T> * position) :
		position_(position)
	{

	}

	template<typename T>
	inline LinkedList<T>::LinkedListIterator::~LinkedListIterator()
	{
		position_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator=(const Iterator<T>& other)
	{
		//TODO 04: LinkedList<T>::LinkedListIterator
		position_ = dynamic_cast<const LinkedListIterator&>(other).position_;
		return *this;
	}

	template<typename T>
	inline bool LinkedList<T>::LinkedListIterator::operator!=(const Iterator<T>& other)
	{
		return position_ != dynamic_cast<const LinkedListIterator&>(other).position_;
	}

	template<typename T>
	inline const T LinkedList<T>::LinkedListIterator::operator*()
	{
		return position_->accessData();
	}

	template<typename T>
	inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator++()
	{
		position_ = position_->getNext();
		return *this;
	}
}