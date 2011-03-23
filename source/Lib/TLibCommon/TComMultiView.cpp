#include "TComMultiView.h"
#include "TComSlice.h"

TComMultiView::TComMultiView( Void )
:m_iWidth(0), m_iHeight(0), m_uiMaxWidth(0), m_uiMaxHeight(0), m_uiMaxDepth(0), m_iGOPSize(0), m_uiNumViews(0), m_acListMultiView(NULL) {}

TComMultiView::~TComMultiView( Void )
{
	closeMultiView();
}

Void TComMultiView::openMultiView( UInt uiNumViews, Int iGOPSize, Int iWidth, Int iHeight, UInt uiMaxWidth, UInt uiMaxHeight, UInt uiMaxDepth )
{
	closeMultiView();
	m_iWidth          = iWidth;
	m_iHeight         = iHeight;
	m_uiMaxWidth      = uiMaxWidth;
	m_uiMaxHeight     = uiMaxHeight;
	m_uiMaxDepth      = uiMaxDepth;
	m_iGOPSize        = iGOPSize;
	m_uiNumViews      = uiNumViews;
	m_acListMultiView = new TComList<TComPic*>[m_uiNumViews];
}

Void TComMultiView::closeMultiView( Void )
{
	if ( (m_acListMultiView != NULL) && (m_uiNumViews != 0) )
	{
		for ( UInt i = 0; i < m_uiNumViews; i++ )
		{
			TComList<TComPic*>::iterator iter = m_acListMultiView[i].begin();
			while ( iter != m_acListMultiView[i].end())
			{
				if ( (*iter) != NULL )
				{
					(*iter)->destroy();
					delete (*iter);
					(*iter) = NULL;
				}
				++iter;
			}
		}

		delete [] m_acListMultiView;
		m_acListMultiView = NULL;
		m_uiNumViews = 0;
	}
}

Void TComMultiView::addMultiViewPicture( UInt uiViewIndex, TComPicYuv* pcPic, Int iPOC, Bool bEncoding )
{
	TComPic* pcPicFromList = xGetBuffer(uiViewIndex, bEncoding);
	if ( (pcPicFromList != NULL) && (pcPic != NULL) )
	{
		if ( !bEncoding )	xDeScalePic(pcPic, pcPicFromList->getPicYuvRec());
		else				pcPic->copyToPic(pcPicFromList->getPicYuvRec());

		pcPicFromList->getSlice()->setPOC(iPOC);
		pcPicFromList->setReconMark(true);
		if ( g_uiBitIncrement )
		{
			xScalePic( pcPicFromList );
		}

		pcPicFromList->getPicYuvRec()->setBorderExtension(false);
		pcPicFromList->getPicYuvRec()->extendPicBorder();

		for ( Int iAddr = 0; iAddr < pcPicFromList->getPicSym()->getNumberOfCUsInFrame(); iAddr++ )
			pcPicFromList->getCU(iAddr)->initCU(pcPicFromList, iAddr);
	}
}

TComPic* TComMultiView::getMultiViewPicture( UInt uiViewIndex, UInt uiPOC )
{
	TComPic* pcRet = NULL;
	TComList<TComPic*>::iterator iter = m_acListMultiView[uiViewIndex].begin();
	do 
	{
		if ( (*iter)->getPOC() == uiPOC )
		{
			pcRet = (*iter);
			break;
		}
	} while ( ++iter != m_acListMultiView[uiViewIndex].end() );
	
	return pcRet;
}

TComPic* TComMultiView::xGetBuffer( UInt uiViewIndex, Bool bEncoding )
{
	TComPic* pcRet = NULL;
	if ( m_acListMultiView != NULL )
	{
		TComSlice::sortPicList(m_acListMultiView[uiViewIndex]);

		UInt uiQueueSize = bEncoding ? (m_iGOPSize + 1) : 1;

		if ( m_acListMultiView[uiViewIndex].size() >= uiQueueSize )
		{
			pcRet = m_acListMultiView[uiViewIndex].popFront();
		}
		else
		{
			pcRet = new TComPic;
			pcRet->create(m_iWidth, m_iHeight, m_uiMaxWidth, m_uiMaxHeight, m_uiMaxDepth, true);
		}

		m_acListMultiView[uiViewIndex].pushBack(pcRet);
	}
	return pcRet;
}

Void TComMultiView::xScalePic( TComPic* pcPic )
{
	Int     x, y;

	//===== calculate PSNR =====
	Pel*  pRec    = pcPic->getPicYuvRec()->getLumaAddr();
	Int   iStride = pcPic->getStride();
	Int   iWidth  = pcPic->getPicYuvRec()->getWidth();
	Int   iHeight = pcPic->getPicYuvRec()->getHeight();

	for( y = 0; y < iHeight; y++ )
	{
		for( x = 0; x < iWidth; x++ )
		{
			pRec[x] <<= g_uiBitIncrement;
		}
		pRec += iStride;
	}

	iHeight >>= 1;
	iWidth  >>= 1;
	iStride >>= 1;
	pRec  = pcPic->getPicYuvRec()->getCbAddr();

	for( y = 0; y < iHeight; y++ )
	{
		for( x = 0; x < iWidth; x++ )
		{
			pRec[x] <<= g_uiBitIncrement;
		}
		pRec += iStride;
	}

	pRec  = pcPic->getPicYuvRec()->getCrAddr();

	for( y = 0; y < iHeight; y++ )
	{
		for( x = 0; x < iWidth; x++ )
		{
			pRec[x] <<= g_uiBitIncrement;
		}
		pRec += iStride;
	}
}

Void TComMultiView::xDeScalePic( TComPicYuv* pcPic, TComPicYuv* pcPicD )
{
	Int     x, y;
	Int     offset = (g_uiBitIncrement>0)?(1<<(g_uiBitIncrement-1)):0;

	//===== calculate PSNR =====
	Pel*  pRecD   = pcPicD->getLumaAddr();
	Pel*  pRec    = pcPic->getLumaAddr();
	Int   iStride = pcPic->getStride();
	Int   iWidth  = pcPic->getWidth();
	Int   iHeight = pcPic->getHeight();

	for( y = 0; y < iHeight; y++ )
	{
		for( x = 0; x < iWidth; x++ )
		{
#if IBDI_NOCLIP_RANGE
			pRecD[x] = ( pRec[x] + offset ) >> g_uiBitIncrement;
#else
			pRecD[x] = ClipMax( ( pRec[x] + offset ) >> g_uiBitIncrement );
#endif
		}
		pRecD += iStride;
		pRec += iStride;
	}

	iHeight >>= 1;
	iWidth  >>= 1;
	iStride >>= 1;
	pRecD = pcPicD->getCbAddr();
	pRec  = pcPic->getCbAddr();

	for( y = 0; y < iHeight; y++ )
	{
		for( x = 0; x < iWidth; x++ )
		{
#if IBDI_NOCLIP_RANGE
			pRecD[x] = ( pRec[x] + offset ) >> g_uiBitIncrement;
#else
			pRecD[x] = ClipMax( ( pRec[x] + offset ) >> g_uiBitIncrement );
#endif
		}
		pRecD += iStride;
		pRec += iStride;
	}

	pRecD = pcPicD->getCrAddr();
	pRec  = pcPic->getCrAddr();

	for( y = 0; y < iHeight; y++ )
	{
		for( x = 0; x < iWidth; x++ )
		{
#if IBDI_NOCLIP_RANGE
			pRecD[x] = ( pRec[x] + offset ) >> g_uiBitIncrement;
#else
			pRecD[x] = ClipMax( ( pRec[x] + offset ) >> g_uiBitIncrement );
#endif
		}
		pRecD += iStride;
		pRec += iStride;
	}
}