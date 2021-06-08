
#ifndef AplAlgorithm_H
#define AplAlgorithm_H


namespace AplContainer{

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


}	// namespace AplContainer

#endif
