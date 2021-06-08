/** 同期制御クラス

 *
 * Copyright(c) 2018 Persol AVC Technology.
 * @file
 */

#if !defined(_CTSYNCHRO_H_)
#define _CTSYNCHRO_H_


#include "Ct.h"
#include "CtObject.h"

class CtSynchro : public CtObject
{
/*** instance member. ***/
public:
	CtSynchro();
	virtual ~CtSynchro();

	bool wait(W tout = TMO_FEVR);
	bool notify();

private:
	typedef struct _FlgInfo {
		ID		flg;
		FLGPTN	flgptn;
	} FlgInfo;
	const FlgInfo	m_FlgInfo;

	/* コピーを禁止する */
	CtSynchro( const CtSynchro& );
	CtSynchro& operator=( const CtSynchro& );

/*** static member. ***/
	static void		initFlgInfo( FlgInfo &info );
	static FlgInfo	allocFlgInfo();
	static bool	freeFlgInfo( const FlgInfo &info );
	static inline bool isValidFlgInfo( const FlgInfo &info ) {
		return ( ( ms_FlgPtnMap & info.flgptn ) != 0 );
	}
	static const FLGPTN	ms_InvalidFlgPtn;
	static const UW		ms_MaxBit;
	static const ID		ms_Flg;
	static FLGPTN		ms_FlgPtnMap;
};

#endif // !defined(_CTYNCHRO_H_)
