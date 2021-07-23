
#ifndef __CtList_H__
#define __CtList_H__

#include "CtAssert.h"
#include "CtObject.h"
#ifdef WIN32_GUI_SIM
#include <EXCPT.H>
#endif
namespace CtList {

// T型の要素を探索する
//見つかった時はその要素を指すiteratorを返す。
//見つからなかった時は、lastを返す。
template<typename ITERATOR, typename T>
ITERATOR find( ITERATOR First, ITERATOR Last, const T& Val ){
	ITERATOR Itr = First;
	for( ; Itr != Last ; ++ Itr ){
		if( *Itr == Val ) {
			break;
		}
	}
	return Itr;
}

// First から Last までの各要素に対して Func( *Itr ) を実行する。
template<typename ITERATOR, typename FUNC>
FUNC for_each( ITERATOR First, ITERATOR Last, FUNC Func ){
	while( First != Last ) {
		Func( *(First ++) );
	}
	return Func;
}

// Iterator を n 進める
// 取りあえず双方向リスト専用の実装のみ
template<typename ITERATOR, typename DISTANCE>
void advance( ITERATOR& Itr, DISTANCE n )
{
	if ( n > 0) {
		while ( n-- ) {
			++ Itr;
		}
	} else {
		while ( n++ ) {
			-- Itr;
		}
	}
}	

////////////////////////////////////////////////////////////////
//	class _list_node_base
//		・next, prev を保持するだけのクラス
//		・new/delete の為にCtObjectから継承する
//		・listクラス内部で使用される
class _list_node_base : public CtObject
{
public:
	_list_node_base( _list_node_base* pPrev, _list_node_base* pNext )
		: m_pPrev( pPrev ), m_pNext( pNext ) { setClassType( CtClassType_ListNodeBase ); }
	_list_node_base*		get_prev() { return m_pPrev; }
	const _list_node_base*	get_prev() const { return m_pPrev; }
	_list_node_base*		get_next() { return m_pNext; }		/* parasoft-suppress BD-PB-NOTINIT */
	const _list_node_base*	get_next() const { return m_pNext; }
#ifdef WIN32_GUI_SIM
	bool					set_prev( _list_node_base* pPrev ) {
		//TODO:メモリリーク暫定対策。メモリ破棄する際にpPrevが不正値で失敗する
		__try {
			m_pPrev = pPrev;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
		return true;
	}

	bool					set_next( _list_node_base* pNext ) {
		//TODO:メモリリーク暫定対策。メモリ破棄する際にpNextが不正値で失敗する
		__try {
			m_pNext = pNext;
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			return false;
		}
		return true;
	}
#else
	void					set_prev( _list_node_base* pPrev ) { m_pPrev = pPrev; }
	void					set_next( _list_node_base* pNext ) { m_pNext = pNext; }
#endif

private:
	_list_node_base*		m_pPrev;
	_list_node_base*		m_pNext;
};

////////////////////////////////////////////////////////////////
//	template<typename T> class _list_node
//		・listへの格納物そのものを保持するクラス
//		・listのリンク情報はスーパークラスで管理する
//		・listクラス内部で使用される
template<typename T>
class _list_node : public _list_node_base
{
public:
	_list_node( const T& Item, _list_node_base* pPrev, _list_node_base* pNext )
		: _list_node_base( pPrev, pNext ), m_Item( Item ) { setClassType( CtClassType_ListNode ); }
	T&			get_item() { return m_Item; }
	const T&	get_item() const { return m_Item; }
private:
	T			m_Item;
};

////////////////////////////////////////////////////////////////
//	template<typename T> class list の先行宣言
template<typename T> class list;

////////////////////////////////////////////////////////////////
//	template<typename T> struct non_const_traits
//		・template<typename T, typename Traits> class _iterator を
//		　non const のiteratorとして使う為のtypedef
//		・template<typename T, typename Traits> class _iterator の
//		　２つ目の総称引数にこのstructを指定する事で、non const の
//		　iteratorとして振舞うようになる
template<typename T>
struct non_const_traits {
	typedef list<T> __list;
	typedef _list_node<T> __list_node;
	typedef _list_node_base __list_node_base;
	typedef T& Ref;
	typedef T* Ptr;
};

////////////////////////////////////////////////////////////////
//	template<typename T> struct non_const_traits
//		・template<typename T, typename Traits> class _iterator を
//		　const のiteratorとして使う為のtypedef
//		・template<typename T, typename Traits> class _iterator の
//		　２つ目の総称引数にこのstructを指定する事で、const の
//		　iteratorとして振舞うようになる
template<typename T>
struct const_traits {
	typedef const list<T> __list;
	typedef const _list_node<T> __list_node;
	typedef const _list_node_base __list_node_base;
	typedef const T& Ref;
	typedef const T* Ptr;
};

////////////////////////////////////////////////////////////////
//	template<typename T, typename Traits> class _iterator
//		・listクラス内で、list<T>::iterator, list<T>::const_iterator に
//		　typedefされる
template<typename T, typename Traits>
class _iterator
{
public:
	typedef _iterator<T, non_const_traits<T> >	iterator;
	typedef _iterator<T, const_traits<T> >		const_iterator;
	typedef _iterator<T, Traits>				__self;
	typedef typename Traits::__list __list;
	typedef typename Traits::__list_node __list_node;
	typedef typename Traits::__list_node_base __list_node_base;
	typedef typename Traits::Ref Ref;
	typedef typename Traits::Ptr Ptr;
	_iterator();
	_iterator( const iterator& Itr );
	Ref operator *() const;
	__self& operator ++();
	__self operator ++( int );
	__self& operator --();
	__self operator --( int );
	bool operator ==( const __self& itr ) const;
	bool operator !=( const __self& itr ) const;

private:
//	typedef list<T> ___list;
//	friend class ___list;
//	friend class iterator;
//	friend class const_iterator;
	friend class list<T>;
	friend class _iterator<T, non_const_traits<T> >;
	friend class _iterator<T, const_traits<T> >;

	_iterator( __list& List, __list_node_base& Node );
	bool is_valid() const;
	void invalidate();
	bool is_begin() const;
	bool is_end() const;
	__list*				m_pList;
	__list_node_base*	m_pCurrent;
};

////////////////////////////////////////////////////////////////
//	template<typename _RanIt> class _reverse_iterator
//		・listクラス内で、list<T>::reverse_iterator, list<T>::const_reverse_iterator に
//		　typedefされる
template<typename _RanIt>
class _reverse_iterator
{
public:
	typedef _reverse_iterator<_RanIt>				__self;
	typedef typename _RanIt::__list __list;
	typedef typename _RanIt::__list_node __list_node;
	typedef typename _RanIt::__list_node_base __list_node_base;
	typedef typename _RanIt::Ref Ref;
	typedef typename _RanIt::Ptr Ptr;

	_reverse_iterator();
	_reverse_iterator(_RanIt itr);

	Ref operator *() const;
	__self& operator++();
	__self operator++(int);
	__self& operator--();
	__self operator--(int);
	bool operator ==(const __self& itr) const;
	bool operator !=(const __self& itr) const;

private:
	_RanIt m_Itr;
};

////////////////////////////////////////////////////////////////
//	template<typename T> class list
//		・new/delete の為にCtObjectから継承する
template<typename T>
class list : public CtObject
{
public:
	typedef _iterator<T, non_const_traits<T> >	iterator;
	typedef _iterator<T, const_traits<T> >		const_iterator;
	typedef _reverse_iterator<iterator>			reverse_iterator;
	typedef _reverse_iterator<const_iterator>	const_reverse_iterator;

	list();
	list( size_t Num, const T& Item );
	explicit list( size_t Num );
	list( const list& obj );
	~list();
	T& front();
	const T& front() const;
	T& back();
	const T& back() const;
	bool find( const T& Item );
	void push_front( const T& Item );
	void push_back( const T& Item );
	void pop_front();
	void pop_back();
	iterator erase( iterator Itr );
	iterator erase( iterator First, iterator Last );
	iterator insert( iterator Position, const T& Item );
	void insert( iterator Position, size_t Num, const T& Item );
	void remove( const T& Item );
	void clear();
	bool empty() const;
	size_t size() const;
	const_iterator begin() const;
	iterator begin();
	const_iterator end() const;
	iterator end();
	const_reverse_iterator rbegin() const;
	reverse_iterator rbegin();
	const_reverse_iterator rend() const;
	reverse_iterator rend();
	list& operator=( const list& rhs );

private:
	typedef _list_node<T>		__list_node;
	typedef _list_node_base		__list_node_base;
//	friend class iterator;
//	friend class const_iterator;
	friend class _iterator<T, non_const_traits<T> >;
	friend class _iterator<T, const_traits<T> >;

	__list_node_base	m_Anchor;	// listの先頭要素の前、かつ、終端要素の次を指すdummy node
									// list要素はリング上に管理される
	int					m_Size;		// listの実要素数

	// list内に矛盾がないかどうかの簡易確認用のメソッド
	bool invariant_condition() {
		bool	b_ok;
		if ( m_Size == 0 ) {
			b_ok = ( m_Anchor.get_next() == &m_Anchor && m_Anchor.get_prev() == &m_Anchor );
		} else if ( m_Size == 1 ) {
			b_ok = ( m_Anchor.get_next() == m_Anchor.get_prev() );
		} else {
			b_ok = ( m_Anchor.get_next() != &m_Anchor && m_Anchor.get_prev() != &m_Anchor
													&& m_Anchor.get_next() != m_Anchor.get_prev() );
		}
		return b_ok;
	}
};



////////////////////////////////////////////////////////////////
//	template<typename T> class list のメソッド定義
template<typename T>
list<T>::list()
	: m_Anchor( NULL, NULL ), m_Size( 0 )
{
	setClassType( CtClassType_List );
	m_Anchor.set_prev( &m_Anchor );
	m_Anchor.set_next( &m_Anchor );
}

template<typename T>
list<T>::list( size_t Num, const T& Item )
	: m_Anchor( NULL, NULL ), m_Size( 0 )
{
	setClassType( CtClassType_List );
	m_Anchor.set_prev( &m_Anchor );
	m_Anchor.set_next( &m_Anchor );
	this->insert( begin(), Num, Item );
}

template<typename T>
list<T>::list( size_t Num )
	: m_Anchor( NULL, NULL ), m_Size( 0 )
{
	setClassType( CtClassType_List );
	m_Anchor.set_prev( &m_Anchor );
	m_Anchor.set_next( &m_Anchor );
	this->insert( begin(), Num, T() );
}

template<typename T>
list<T>::list( const list& obj )
	: CtObject( obj ), m_Anchor( NULL, NULL ), m_Size( 0 )
{
	setClassType( CtClassType_List );
	m_Anchor.set_prev( &m_Anchor );
	m_Anchor.set_next( &m_Anchor );
	for ( const_iterator Itr = obj.begin(); Itr != obj.end(); ++ Itr ) {
		this->push_back( *Itr );
	}
}

template<typename T>
list<T>::~list()
{
	this->clear();
	CtAssert( invariant_condition() );
}

template<typename T>
T& list<T>::front()
{
	return *begin();
}

template<typename T>
const T& list<T>::front() const
{
	return *begin();
}

template<typename T>
T& list<T>::back()
{
	return *( --end() );
}

template<typename T>
const T& list<T>::back() const
{
	return *( --end() );
}

template<typename T>
void list<T>::push_front( const T& Item )
{
	this->insert( this->begin(), Item );
}

template<typename T>
void list<T>::push_back( const T& Item )
{
	this->insert( this->end(), Item );
}

template<typename T>
void list<T>::pop_front()
{
	CtAssert( !this->empty() );
	this->erase( this->begin() );
}

template<typename T>
void list<T>::pop_back()
{
	CtAssert( !this->empty() );
	iterator Itr = this->end();
	this->erase( -- Itr );
}

template<typename T>
typename list<T>::iterator list<T>::erase( typename list<T>::iterator Itr )
{
	CtAssert( Itr.is_valid() && Itr.m_pList == this && !Itr.is_end() );

	iterator RetItr( Itr );
	++ RetItr;
#ifdef WIN32_GUI_SIM
	if (!Itr.m_pCurrent->get_prev()->set_next(Itr.m_pCurrent->get_next())) {
		m_Size = 0;
		return RetItr;
	}
	if (!Itr.m_pCurrent->get_next()->set_prev(Itr.m_pCurrent->get_prev())) {
		m_Size = 0;
		return RetItr;
	}
#else
	Itr.m_pCurrent->get_prev()->set_next( Itr.m_pCurrent->get_next() );
	Itr.m_pCurrent->get_next()->set_prev( Itr.m_pCurrent->get_prev() );
#endif
	delete static_cast<__list_node*>( Itr.m_pCurrent );
	Itr.m_pCurrent = NULL;
	-- m_Size;

	return RetItr;
}

template<typename T>
typename list<T>::iterator list<T>::erase( iterator First, iterator Last )
{
	CtAssert( First.is_valid() && First.m_pList == this
				&& Last.is_valid() && Last.m_pList == this );

	iterator Itr( First );
	while ( Itr != Last ) {
		CtAssert( Itr != this->end() );
		Itr = this->erase( Itr );
#ifdef WIN32_GUI_SIM
		if (this->size() <= 0) break;
#endif
	}
	return Itr;
}

template<typename T>
typename list<T>::iterator list<T>::insert( iterator Position, const T& Item )
{
	__list_node* pNewNode = new __list_node( Item, Position.m_pCurrent->get_prev(), Position.m_pCurrent );
	Position.m_pCurrent->get_prev()->set_next( pNewNode );
	Position.m_pCurrent->set_prev( pNewNode );
	++ m_Size;
	return iterator( *this, *pNewNode );
}

template<typename T>
void list<T>::insert( iterator Position, size_t Num, const T& Item )
{
	for ( size_t i = 0; i < Num; ++ i ) {
		insert( Position, Item );
	}
}

template<typename T>
void list<T>::remove(const T& Item)
{
	iterator Itr = begin();
	while ( Itr != end() )
	{
		if ( *Itr == Item ) {
			Itr = erase( Itr );
		} else {
			++ Itr;
		}
	}
}

template<typename T>
bool list<T>::find( const T& Item ){
	
	iterator Itr = begin();
	while ( Itr != end() )
	{
		if ( *Itr == Item ) {
			return true;
		} else {
			++ Itr;
		}
	}
	return false;
}

template<typename T>
void list<T>::clear()
{
	this->erase( this->begin(), this->end() );
}

template<typename T>
bool list<T>::empty() const
{
	return ( m_Anchor.get_next() == &m_Anchor );
}

template<typename T>
size_t list<T>::size() const
{
	return m_Size;
}

template<typename T>
typename list<T>::const_iterator list<T>::begin() const
{
	list<T>* p = const_cast<list<T>*>(this);
	return iterator( *p, *(p->m_Anchor.get_next()) );
}

template<typename T>
typename list<T>::iterator list<T>::begin()
{
	return iterator( *this, *(this->m_Anchor.get_next()) );
}

template<typename T>
typename list<T>::const_iterator list<T>::end() const
{
	list<T>* p = const_cast<list<T>*>(this);
	return iterator( *p, p->m_Anchor );
}

template<typename T>
typename list<T>::iterator list<T>::end()
{
	return iterator( *this, this->m_Anchor );
}

template<typename T>
list<T>& list<T>::operator=( const list<T>& rhs )
{
	if (this != &rhs) {
		iterator Itr = begin();
		const_iterator ItrSrc = rhs.begin();
		for (
			Itr = begin(), ItrSrc = rhs.begin();
			Itr != end() && ItrSrc != rhs.end();
			++ Itr, ++ ItrSrc
		) {
			*Itr = *ItrSrc;
		}
		if ( ItrSrc == rhs.end() ) {
			erase( Itr, end() );
		} else {
			for ( ; ItrSrc != rhs.end(); ++ ItrSrc ) {
				push_back( *ItrSrc );
			}
		}
	}
	return *this;
}

template<typename T>
typename list<T>::const_reverse_iterator list<T>::rbegin() const
{
	return (const_reverse_iterator(end()));
}

template<typename T>
typename list<T>::reverse_iterator list<T>::rbegin()
{
	return (reverse_iterator(end()));
}

template<typename T>
typename list<T>::const_reverse_iterator list<T>::rend() const
{
	return (const_reverse_iterator(begin()));
}

template<typename T>
typename list<T>::reverse_iterator list<T>::rend()
{
	return (reverse_iterator(begin()));
}

////////////////////////////////////////////////////////////////
//	template<typename T, typename Traits> class _iterator のメソッド定義
template<typename T, typename Traits>
_iterator<T,Traits>::_iterator()
	: m_pList( NULL ), m_pCurrent( NULL )
{}

template<typename T, typename Traits>
_iterator<T,Traits>::_iterator( const _iterator<T,non_const_traits<T> >& Itr )
	: m_pList( Itr.m_pList ), m_pCurrent( Itr.m_pCurrent )
{}

template<typename T, typename Traits>
_iterator<T,Traits>::_iterator( __list& List, __list_node_base& Node )
	: m_pList( &List ), m_pCurrent( &Node )
{}

template<typename T, typename Traits>
typename _iterator<T,Traits>::Ref _iterator<T,Traits>::operator *() const
{
	CtAssert( this->is_valid() && !this->is_end() );
	return static_cast<__list_node*>(m_pCurrent)->get_item();	/* parasoft-suppress BD-PB-NP */
}

template<typename T, typename Traits>
_iterator<T,Traits>& _iterator<T,Traits>::operator ++() 
{
	CtAssert( this->is_valid() && !this->is_end() );
	m_pCurrent = m_pCurrent->get_next();						/* parasoft-suppress BD-PB-NP */
	return *this;
}

template<typename T, typename Traits>
_iterator<T,Traits> _iterator<T,Traits>::operator ++( int dmy ) 
{
	__self	RetItr( *this );
	CtAssert( this->is_valid() && !this->is_end() );
	m_pCurrent = m_pCurrent->get_next();						/* parasoft-suppress BD-PB-NP */
	return RetItr;
}

template<typename T, typename Traits>
_iterator<T,Traits>& _iterator<T,Traits>::operator --()
{
	CtAssert( this->is_valid() && !this->is_begin() );
	m_pCurrent = m_pCurrent->get_prev();						/* parasoft-suppress BD-PB-NP */
	return *this;
}

template<typename T, typename Traits>
_iterator<T,Traits> _iterator<T,Traits>::operator --( int dmy ) 
{
	__self	RetItr( *this );
	CtAssert( this->is_valid() && !this->is_begin() );
	m_pCurrent = m_pCurrent->get_prev();						/* parasoft-suppress BD-PB-NP */
	return RetItr;
}

template<typename T, typename Traits>
bool _iterator<T,Traits>::operator ==( const __self& itr ) const
{
	CtAssert( this->is_valid() && m_pList == itr.m_pList );
	return ( m_pCurrent == itr.m_pCurrent );
}

template<typename T, typename Traits>
bool _iterator<T,Traits>::operator !=( const __self& itr ) const
{
	return !operator ==( itr );
}

template<typename T, typename Traits>
bool _iterator<T,Traits>::is_valid() const
{
	return ( m_pList != NULL && m_pCurrent != NULL );
}

template<typename T, typename Traits>
void _iterator<T,Traits>::invalidate()
{
	m_pCurrent = NULL;
	m_pList = NULL;
}

template<typename T, typename Traits>
bool _iterator<T,Traits>::is_begin() const
{
	return ( this->is_valid() && m_pCurrent == m_pList->m_Anchor.get_next() );
}

template<typename T, typename Traits>
bool _iterator<T,Traits>::is_end() const
{
	return ( this->is_valid() && m_pCurrent == &m_pList->m_Anchor );
}

////////////////////////////////////////////////////////////////
//	template<typename T, typename Traits> class _iterator のメソッド定義
template<typename _RanIt>
_reverse_iterator<_RanIt>::_reverse_iterator()
	: m_Itr()
{}

template<typename _RanIt>
_reverse_iterator<_RanIt>::_reverse_iterator(_RanIt itr)
	: m_Itr(itr)
{}

template<typename _RanIt>
typename _reverse_iterator<_RanIt>::Ref _reverse_iterator<_RanIt>::operator *() const
{
	_RanIt _Tmp = m_Itr;
	return (*--_Tmp);
}

template<typename _RanIt>
_reverse_iterator<_RanIt>& _reverse_iterator<_RanIt>::operator++()
{
	m_Itr--;
	return *this;
}

template<typename _RanIt>
_reverse_iterator<_RanIt> _reverse_iterator<_RanIt>::operator++(int)
{
	__self	RetItr(*this);
	m_Itr--;
	return RetItr;
}

template<typename _RanIt>
_reverse_iterator<_RanIt>& _reverse_iterator<_RanIt>::operator--()
{
	m_Itr++;
	return *this;
}

template<typename _RanIt>
_reverse_iterator<_RanIt> _reverse_iterator<_RanIt>::operator--(int)
{
	__self	RetItr(*this);
	m_Itr++;
	return RetItr;
}

template<typename _RanIt>
bool _reverse_iterator<_RanIt>::operator ==(const __self& itr) const
{
	return (m_Itr == itr.m_Itr);
}

template<typename _RanIt>
bool _reverse_iterator<_RanIt>::operator !=(const __self& itr) const
{
	return !operator ==(itr);
}

}	// namespace CtList

#endif

