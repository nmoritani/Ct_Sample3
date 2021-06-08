/************************************************************************/
/* Vector�̍Ď��� */
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
        /* �R���X�g���N�^ */
        /************************************************************************/
        explicit Vector(int initsize = 0)                     // Vector�̏����T�C�Y
            :theSize(initsize)
            ,theCapacity(initsize + SPACE_CAPACITY)
        {
#ifdef ALLOC_FROM_MPL
			Objects = (Object*)CtMemory::get(sizeof(Object) * theCapacity);
#else
            Objects = new Object[theCapacity];        // �����T�C�Y��z�z����
#endif
			memset(Objects, 0, sizeof(Object) * theCapacity);
        }

        /************************************************************************/
        /* �R�s�[�R���X�g���N�^ */
        /************************************************************************/
        Vector(const Vector& V)
            :theSize(0)
            ,theCapacity(0)
            ,Objects(NULL)
        {
            *this = V;
        }

        /************************************************************************/
        /* �f�X�g���N�^ */
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
        /* �C�R�[�����Z�q���I�[�o���[�h���� */
        /************************************************************************/
        Vector &operator = (const Vector& ths)                // const�^�ɒ�`
        {
            if (this != ths)        // ���g�ւ̃R�s�[��h�~����
            {
#ifdef ALLOC_FROM_MPL
				CtMemory::free(Objects);
#else
                delete [] Objects;         // ���̃I�u�W�F�N�g���폜
#endif
                theSize = ths.theSize;
                theCapacity = ths.theCapacity;
#ifdef ALLOC_FROM_MPL
				Objects = (Object*)CtMemory::get(sizeof(Object) * theCapacity);
#else
                Objects = new Object[theCapacity];  // ���������Ĕz�z����
#endif
                // �������x���̃R�s�[
                /* Objects = ths.Objects  �|�C���^�����R�s�[���Ȃ�
                ** �������̑Ώۂ��ς������A�R�s�[�̑Ώۂ��ς�� */
                for (int i = 0; i < ths.theSize; ++i)
                {
                    Objects[i] = ths.Objects[i];
                }
            }
            return *this;
        }

        /************************************************************************/
        /* �֐����Fresize */
        /* �@�\�F�T�C�Y��ς�� */
        /* �����F�T�C�Y��ς�邪�AtheCapacity�̃T�C�Y���ς��Ȃ� */
        /* ���ԁF2017.03 */
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
            /* ����size��capacity���傫���A�������̍Ĕz�z���K�v�A��������newsize�̓�{ */
            if(newSize > theCapacity)
                reserve(2 * newSize + 1);         // +1�̗��R�́Anewsize��0�̏ꍇ�A1�̃X�y�[�X��z�z����
            theSize = newSize;
        }

        /************************************************************************/
        /* �֐����Freserve */
        /* �@�\�F�������̃T�C�Y���Ĕz�z���� */
        /* �����FtheCapacity�̃T�C�Y��ύX����AtheSize���ς��Ȃ� */
        /* ���ԁF2017.03 */
        /************************************************************************/
        void reserve(int newCapacity)
        {
            if (newCapacity < theSize)
            {
                return;
            }
            /* ���̓��e���ꎞ�ϐ��փR�s�[���Ă��� */
            Object * temp = Objects;
            /* ���̑Ώۂ��A�傫���X�y�[�X��z�z���� */
#ifdef ALLOC_FROM_MPL
			Objects = (Object*)CtMemory::get(sizeof(Object) * newCapacity);
#else
            Objects = new Object[newCapacity];
#endif
			memset(Objects, 0, sizeof(Object) * newCapacity);
            /* ���̃f�[�^��߂��A�������̃T�C�Y���ς�������A�T�C�Y���ς��Ȃ� */
            for (int i = 0;  i < theSize; ++i)
            {
                Objects[i] = temp[i];	/* parasoft-suppress BD-PB-NP */
            }
            /* ���̑Ώۂ�������� */
#ifdef ALLOC_FROM_MPL
			CtMemory::free(temp);
#else
            delete[] temp;
#endif

			theCapacity = newCapacity;
        }

        /************************************************************************/
        /* �֐����Foperate[] */
        /* �@�\�F�Y���I�y���[�^���I�[�o���[�h */
        /* �����F�ϐ��̃o�[�W���� */
        /* ���ԁF2017.03 */
        /************************************************************************/
        // �Y�����Z�q�̖߂�l�͗v�f�̎Q�ƁA�ϐ��łƒ萔�ł��`����
        Object& operator[] (int index)
        {
            return Objects[index];       // �|�C���^�̓Y���v�Z
        }

        /************************************************************************/
        /* �֐����Foperate[] */
        /* �@�\�F�Y���I�y���[�^���I�[�o���[�h */
        /* �����F�萔�̃o�[�W���� */
        /* ���ԁF2017.03 */
        /************************************************************************/
        const Object& operator[] (int index) const
        {
            return Objects[index];
        }

        /************************************************************************/
        /* �֐����FisEmpty */
        /* �@�\�FVector���󂩔��f���� */
        /* �����F�u�@�\�v���Q�Ƃ��Ă������� */
        /* ���ԁF2017.03 */
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
        /* �֐����Fsize */
        /* �����FVector�̃T�C�Y���擾���� */
        /* �����F�u�@�\�v���Q�Ƃ��Ă������� */
        /* ���ԁF2017.03 */
        /************************************************************************/
        int size() const
        {
            return theSize;
        }

        /************************************************************************/
        /* �֐����Fcapacity */
        /* �@�\�FVector��capacity��size���擾���� */
        /* �����F�u�@�\�v���Q�Ƃ��Ă������� */
        /* ���ԁF2017.03 */
        /************************************************************************/
        int capacity() const
        {
            return theCapacity;
        }

        /************************************************************************/
        /* �֐����Fpush_back */
        /* �@�\�FVector�Ɉ�̗v�f��Push���� */
        /* �����F�u�@�\�v���Q�Ƃ��Ă������� */
        /* ���ԁF2017.03 */
        /************************************************************************/
        void push_back(Object obj)
        {
            // Capacity�̃X�y�[�X���܂����邩�A���f����
            if (theSize == theCapacity)
            {
                // ������������Ȃ���΁A���݂̃T�C�Y��{�Ŋg�傷��
                reserve(2 * theCapacity + 1);
            }
            // size�֐��Ŏ擾�ł���v�f���B
            Objects[theSize++] = obj;
        }

        /************************************************************************/
        /* �֐����Fpop_back */
        /* �@�\�FVector�̌�납��A��̗v�f���폜���� */
        /* �����F�u�@�\�v���Q�Ƃ��Ă������� */
        /* ���ԁF2017.03 */
        /************************************************************************/
        void pop_back()
        {
            if(theSize != 0){
                --theSize;
            }

        }
	
		/************************************************************************/
        /* �֐����Fpop_back */
        /* �@�\�Findex�̗v�f���폜���� */
        /* �����F�u�@�\�v���Q�Ƃ��Ă������� */
        /* ���ԁF2017.05 */
        /************************************************************************/
		void erase(int index)
		{
			if (theSize <= index){
				return;
			}
			
			// index�ȍ~��O���R�s�[
			for (int i=index; i<theSize-1; i++) {
				Objects[i] = Objects[i+1];
			}
			theSize--;
		}

		/************************************************************************/
        /* �֐����Fpop_back */
        /* �@�\�Fposition�̗v�f���폜���� */
        /* �����F�u�@�\�v���Q�Ƃ��Ă������� */
        /* ���ԁF2017.05 */
        /************************************************************************/
		void erase(const_iterator position)
		{
			erase(position, position+1);	/* pgr0541	*/
		}

		/************************************************************************/
        /* �֐����Fpop_back */
        /* �@�\�Ffirst����last�̗v�f���폜���� */
        /* �����F�u�@�\�v���Q�Ƃ��Ă������� */
        /* ���ԁF2017.05 */
        /************************************************************************/
		void erase(const_iterator first, const_iterator last)
		{
			int first_idx=-1;
			int erase_cnt=0;

			// �폜�J�n�ʒu��T��
			for (int i=0; i<theSize; i++){
				if( first == &Objects[i] ){
					first_idx=i;
					break;
				}
			}
			if (first_idx == -1) return;

			for (int i=first_idx; i<theSize; i++){
				if (erase_cnt == 0){
					// �폜�I���ʒu�̒T��
					if (last == &Objects[i+1]){
						erase_cnt = i - first_idx + 1;
					}
				}
				else{
					// �폜����
					Objects[i-erase_cnt] = Objects[i];
				}
			}

			theSize -= erase_cnt;
		}
		
		/************************************************************************/
        /* �֐����Fclear */
        /* �@�\�F�S�Ă̗v�f���폜 */
        /* �����F�u�@�\�v���Q�Ƃ��Ă������� */
        /* ���ԁF2017.05 */
        /************************************************************************/
		void clear()
		{
			theSize = 0;
		}

		/* First����Last�܂ł�Val�v�f�ʒu��Ԃ� */
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

		
		/* index�ʒu��Item��}������ */
		void insert(int index, const Object& Item)
		{
			if (theSize <= index){
				return;
			}
			
			// index�ȍ~��O���R�s�[
			for (int i=index; i<theSize; i++) {
				Objects[i+1] = Objects[i];
			}
			Objects[index] = Item;
			theSize++;
		}

		/* Position�ʒu��Item��}������ */
		iterator insert(iterator Position, const Object& Item)
		{
			// �������m�ۂ�Position�������ɂȂ�\�������邽��
			// index�֕ϊ�
			int idx = Position - this->begin();	/* pgr0541	*/

			// �������m��
			resize(theSize + 1);
			
			// Position���Ď擾
			Position = &Objects[idx];

			for (iterator Itr = this->end() - 1; Itr != Position; Itr -= 1) {
				*Itr = *(Itr - 1);
			}

			*Position = Item;

			return Position;
		}

		/* Position�ʒu��Item��Num�}������ */
		void insert(iterator Position, size_t Num, const Object& Item)
		{
			for (size_t i = 0; i < Num; i++) {
				Position = insert(Position, Item);
			}
		}

		/* �V���ȗv�f��擪�ɒǉ����� */
		void push_front(const Object& Item)
		{
			insert(this->begin(), Item);
		}

		/* �擪�̗v�f���폜���� */
		void pop_front()
		{
			erase(0);
		}

		/* Item�ƈ�v����S�Ă̗v�f���폜���� */
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
        Object* Objects;    // Vector�̓����ŁA�z��̃|�C���^���Ǘ����Ă���B
    };
}
#endif
