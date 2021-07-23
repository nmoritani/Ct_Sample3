/** 同期制御クラス

 *
 * Copyright(c) 2018 Persol AVC Technology.
 * @file
 */

#if !defined(_CTSYNCHRO_H_)
#define _CTSYNCHRO_H_


#include "Ct.h"
#include "CtObject.h"

#include <CtPlatforms.h>

class CtSynchro : public CtObject
{
/*** instance member. ***/
public:
	CtSynchro();
	virtual ~CtSynchro();

	void init();
	void term();
	
	bool wait(long timeout = SYSWRAP_TIMEOUT_FOREVER);
	bool notify();

private:
	typedef struct _FlgInfo {
		syswrap_event_t	*flg;
		unsigned int	flgptn;
	} FlgInfo;
	const FlgInfo	m_FlgInfo;

	/* コピーを禁止する */
	CtSynchro( const CtSynchro& );
	CtSynchro& operator=( const CtSynchro& );

/*** static member. ***/
	static syswrap_event_t m_Event;
	static syswrap_semaphore_t m_Semaphore;
	static void		initFlgInfo( FlgInfo &info );
	static FlgInfo	allocFlgInfo();
	static bool	freeFlgInfo( const FlgInfo &info );
	static inline bool isValidFlgInfo( const FlgInfo &info ) {
		return ( ( ms_FlgPtnMap & info.flgptn ) != 0 );
	}
	static const unsigned int ms_InvalidFlgPtn;
	static const unsigned int ms_MaxBit;
	static unsigned int ms_FlgPtnMap;
};

#endif // !defined(_CTYNCHRO_H_)
