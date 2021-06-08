/************************************************************************/
/* Vectorの再実装 */
/************************************************************************/
#ifndef __CtVector_H__
#define __CtVector_H__

#include "CtMemory.h"

#define	 ALLOC_FROM_MPL
#define  SPACE_CAPACITY 5
namespace CtVector
{
    template<typename Object>
    class Vector
    {
    public:
		typedef Object* iterator;
        typedef const Object* const_iterator;

        /************************************************************************/
        /* コンストラクタ */
        /************************************************************************/
        explicit Vector(int initsize = 0)                     // Vectorの初期サイズ
            :theSize(initsize)
            ,theCapacity(initsize + SPACE_CAPACITY)
        {
#ifdef ALLOC_FROM_MPL
			Objects = (Object*)CtMemory::get(sizeof(Object) * theCapacity);
#else
            Objects = new Object[theCapacity];        // 初期サイズを配布する
#endif
			memset(Objects, 0, sizeof(Object) * theCapacity);
        }

        /************************************************************************/
        /* コピーコンストラクタ */
        /************************************************************************/
        Vector(const Vector& V)
            :theSize(0)
            ,theCapacity(0)
            ,Objects(NULL)
        {
            *this = V;
        }

        /************************************************************************/
        /* デストラクタ */
        /************************************************************************/
        ~Vector()
        {
#ifdef ALLOC_FROM_MPL
			CtMemory::free(Objects);
#else
            delete[ ] Objects;
#endif
        }

        /************************************************************************/
        /* イコール演算子をオーバロードする */
        /************************************************************************/
        Vector &operator = (const Vector& ths)                // const型に定義
        {
            if (this != ths)        // 自身へのコピーを防止する
            {
#ifdef ALLOC_FROM_MPL
				CtMemory::free(Objects);
#else
                delete [] Objects;         // 元のオブジェクトを削除
#endif
                theSize = ths.theSize;
                theCapacity = ths.theCapacity;
#ifdef ALLOC_FROM_MPL
				Objects = (Object*)CtMemory::get(sizeof(Object) * theCapacity);
#else
                Objects = new Object[theCapacity];  // メモリを再配布する
#endif
                // 高いレベルのコピー
                /* Objects = ths.Objects  ポインタしかコピーしない
                ** もし元の対象が変わったら、コピーの対象も変わる */
                for (int i = 0; i < ths.theSize; ++i)
                {
                    Objects[i] = ths.Objects[i];
                }
            }
            return *this;
        }

        /************************************************************************/
        /* 関数名：resize */
        /* 機能：サイズを変わる */
        /* 説明：サイズを変わるが、theCapacityのサイズが変わらない */
        /* 時間：2017.03 */
        /************************************************************************/
        void resize(int newSize)
        {
            if (newSize <= theSize) {
				for (int i = newSize;  i < theSize; ++i) {
					Objects[i] = NULL;
				}
				theSize = newSize;
                return;
			}
            /* もしsizeはcapacityより大きい、メモリの再配布が必要、メモリはnewsizeの二倍 */
            if(newSize > theCapacity)
                reserve(2 * newSize + 1);         // +1の理由は、newsizeが0の場合、1のスペースを配布する
            theSize = newSize;
        }

        /************************************************************************/
        /* 関数名：reserve */
        /* 機能：メモリのサイズを再配布する */
        /* 説明：theCapacityのサイズを変更する、theSizeが変わらない */
        /* 時間：2017.03 */
        /************************************************************************/
        void reserve(int newCapacity)
        {
            if (newCapacity < theSize)
            {
                return;
            }
            /* 元の内容を一時変数へコピーしておく */
            Object * temp = Objects;
            /* 元の対象より、大きいスペースを配布する */
#ifdef ALLOC_FROM_MPL
			Objects = (Object*)CtMemory::get(sizeof(Object) * newCapacity);
#else
            Objects = new Object[newCapacity];
#endif
			memset(Objects, 0, sizeof(Object) * newCapacity);
            /* 元のデータを戻す、メモリのサイズが変わったが、サイズが変わらない */
            for (int i = 0;  i < theSize; ++i)
            {
                Objects[i] = temp[i];	/* parasoft-suppress BD-PB-NP */
            }
            /* 元の対象を解放する */
#ifdef ALLOC_FROM_MPL
			CtMemory::free(temp);
#else
            delete[] temp;
#endif

			theCapacity = newCapacity;
        }

        /************************************************************************/
        /* 関数名：operate[] */
        /* 機能：添字オペレータをオーバロード */
        /* 説明：変数のバージョン */
        /* 時間：2017.03 */
        /************************************************************************/
        // 添字演算子の戻り値は要素の参照、変数版と定数版を定義する
        Object& operator[] (int index)
        {
            return Objects[index];       // ポインタの添字計算
        }

        /************************************************************************/
        /* 関数名：operate[] */
        /* 機能：添字オペレータをオーバロード */
        /* 説明：定数のバージョン */
        /* 時間：2017.03 */
        /************************************************************************/
        const Object& operator[] (int index) const
        {
            return Objects[index];
        }

        /************************************************************************/
        /* 関数名：isEmpty */
        /* 機能：Vectorが空か判断する */
        /* 説明：「機能」を参照してください */
        /* 時間：2017.03 */
        /************************************************************************/
        bool isEmpty() const
        {
            return size() == 0;
        }
        bool empty() const
        {
            return size() == 0;
        }
        /************************************************************************/
        /* 関数名：size */
        /* 説明：Vectorのサイズを取得する */
        /* 説明：「機能」を参照してください */
        /* 時間：2017.03 */
        /************************************************************************/
        int size() const
        {
            return theSize;
        }

        /************************************************************************/
        /* 関数名：capacity */
        /* 機能：Vectorのcapacityのsizeを取得する */
        /* 説明：「機能」を参照してください */
        /* 時間：2017.03 */
        /************************************************************************/
        int capacity() const
        {
            return theCapacity;
        }

        /************************************************************************/
        /* 関数名：push_back */
        /* 機能：Vectorに一つの要素をPushする */
        /* 説明：「機能」を参照してください */
        /* 時間：2017.03 */
        /************************************************************************/
        void push_back(Object obj)
        {
            // Capacityのスペースがまだあるか、判断する
            if (theSize == theCapacity)
            {
                // メモリが足りなければ、現在のサイズを倍で拡大する
                reserve(2 * theCapacity + 1);
            }
            // size関数で取得できる要素数。
            Objects[theSize++] = obj;
        }

        /************************************************************************/
        /* 関数名：pop_back */
        /* 機能：Vectorの後ろから、一つの要素を削除する */
        /* 説明：「機能」を参照してください */
        /* 時間：2017.03 */
        /************************************************************************/
        void pop_back()
        {
            if(theSize != 0){
                --theSize;
            }

        }
	
		/************************************************************************/
        /* 関数名：pop_back */
        /* 機能：indexの要素を削除する */
        /* 説明：「機能」を参照してください */
        /* 時間：2017.05 */
        /************************************************************************/
		void erase(int index)
		{
			if (theSize <= index){
				return;
			}
			
			// index以降を前方コピー
			for (int i=index; i<theSize-1; i++) {
				Objects[i] = Objects[i+1];
			}
			theSize--;
		}

		/************************************************************************/
        /* 関数名：pop_back */
        /* 機能：positionの要素を削除する */
        /* 説明：「機能」を参照してください */
        /* 時間：2017.05 */
        /************************************************************************/
		void erase(const_iterator position)
		{
			erase(position, position+1);	/* pgr0541	*/
		}

		/************************************************************************/
        /* 関数名：pop_back */
        /* 機能：firstからlastの要素を削除する */
        /* 説明：「機能」を参照してください */
        /* 時間：2017.05 */
        /************************************************************************/
		void erase(const_iterator first, const_iterator last)
		{
			int first_idx=-1;
			int erase_cnt=0;

			// 削除開始位置を探す
			for (int i=0; i<theSize; i++){
				if( first == &Objects[i] ){
					first_idx=i;
					break;
				}
			}
			if (first_idx == -1) return;

			for (int i=first_idx; i<theSize; i++){
				if (erase_cnt == 0){
					// 削除終了位置の探索
					if (last == &Objects[i+1]){
						erase_cnt = i - first_idx + 1;
					}
				}
				else{
					// 削除処理
					Objects[i-erase_cnt] = Objects[i];
				}
			}

			theSize -= erase_cnt;
		}
		
		/************************************************************************/
        /* 関数名：clear */
        /* 機能：全ての要素を削除 */
        /* 説明：「機能」を参照してください */
        /* 時間：2017.05 */
        /************************************************************************/
		void clear()
		{
			theSize = 0;
		}

		/* FirstからLastまでのVal要素位置を返す */
		iterator find( iterator First, iterator Last, const Object& Val )
		{
			iterator Itr = First;
			for( ; Itr != Last ; ++ Itr ){
				if( *Itr == Val ) {
					break;
				}
			}
			return Itr;
		}

		bool find(const Object& Val) {
			for (int i = 0; i < theSize; i++) {
				if (Objects[i] == Val) {
					return true;
				}
			}
			return false;
		}

		
		/* index位置にItemを挿入する */
		void insert(int index, const Object& Item)
		{
			if (theSize <= index){
				return;
			}
			
			// index以降を前方コピー
			for (int i=index; i<theSize; i++) {
				Objects[i+1] = Objects[i];
			}
			Objects[index] = Item;
			theSize++;
		}

		/* Position位置にItemを挿入する */
		iterator insert(iterator Position, const Object& Item)
		{
			// メモリ確保でPositionが無効になる可能性があるため
			// indexへ変換
			int idx = Position - this->begin();	/* pgr0541	*/

			// メモリ確保
			resize(theSize + 1);
			
			// Positionを再取得
			Position = &Objects[idx];

			for (iterator Itr = this->end() - 1; Itr != Position; Itr -= 1) {
				*Itr = *(Itr - 1);
			}

			*Position = Item;

			return Position;
		}

		/* Position位置にItemをNum個挿入する */
		void insert(iterator Position, size_t Num, const Object& Item)
		{
			for (size_t i = 0; i < Num; i++) {
				Position = insert(Position, Item);
			}
		}

		/* 新たな要素を先頭に追加する */
		void push_front(const Object& Item)
		{
			insert(this->begin(), Item);
		}

		/* 先頭の要素を削除する */
		void pop_front()
		{
			erase(0);
		}

		/* Itemと一致する全ての要素を削除する */
		void remove(const Object& Item)
		{
			iterator Itr = begin();
			while (Itr != end())
			{
				if (*Itr == Item) {
					erase(Itr);
				}
				else {
					++Itr;
				}
			}
		}

        const Object & back() const
        {
            return Objects[size() - 1];
		}

        iterator begin()
        {
            return &Objects[0];
        }

        iterator end()
        {
            return &Objects[size()];
        }

        const_iterator cbegin() const
        {
            return &Objects[0];
        }

        const_iterator cend() const
        {
            return &Objects[size()];
        }

    private:
        int theSize;
        int theCapacity;
        Object* Objects;    // Vectorの内部で、配列のポインタを管理している。
    };
}
#endif
