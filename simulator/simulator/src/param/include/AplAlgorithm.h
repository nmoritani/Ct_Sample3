
#ifndef AplAlgorithm_H
#define AplAlgorithm_H


namespace AplContainer{

// T�^�̗v�f��T������
//�����������͂��̗v�f���w��iterator��Ԃ��B
//������Ȃ��������́Alast��Ԃ��B
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

// First ���� Last �܂ł̊e�v�f�ɑ΂��� Func( *Itr ) �����s����B
template<typename ITERATOR, typename FUNC>
FUNC for_each( ITERATOR First, ITERATOR Last, FUNC Func ){
	while( First != Last ) {
		Func( *(First ++) );
	}
	return Func;
}

// Iterator �� n �i�߂�
// ��肠�����o�������X�g��p�̎����̂�
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
