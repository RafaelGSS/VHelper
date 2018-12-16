#ifndef GDS_TEXTSPEAKER_H_INCLUDED
#define GDS_TEXTSPEAKER_H_INCLUDED

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars


#include <sapi.h>               // SAPI
#include <sphelper.h>           // SAPI Helper

#include "ComAutoInit.h"        // COM auto initializer


namespace gds {


	//------------------------------------------------------------------------
	// Simple class to speak some text (using SAPI).
	//------------------------------------------------------------------------
	class CTextSpeaker
	{
	public:

		//--------------------------------------------------------------------
		// Initializes the text speaker.
		//--------------------------------------------------------------------
		CTextSpeaker()
		{
			//
			// Create text to speech engine
			//
			HRESULT hr = m_tts.CoCreateInstance(CLSID_SpVoice);
			if (FAILED(hr))
			{
				ATLTRACE(TEXT("Text-to-speech creation failed.\n"));
				AtlThrow(hr);
			}


			//
			// Get token corresponding to default voice 
			//
			hr = SpGetDefaultTokenFromCategoryId(SPCAT_VOICES, &m_voiceToken, FALSE);
			if (FAILED(hr))
			{
				ATLTRACE(TEXT("Can't get default voice token.\n"));
				AtlThrow(hr);
			}


			//
			// Set default voice
			//
			hr = m_tts->SetVoice(m_voiceToken);
			if (FAILED(hr))
			{
				ATLTRACE(TEXT("Can't set default voice.\n"));
				AtlThrow(hr);
			}
		}


		//--------------------------------------------------------------------
		// Speaks some text.
		// (The input text must not be empty.)
		//--------------------------------------------------------------------
		void Speak(const CString & text)
		{
			//
			// Input text must not be empty
			//
			if (text.IsEmpty())
			{
				ATLTRACE(TEXT("Empty text passed to CTextSpeaker::Speak().\n"));
				AtlThrow(E_INVALIDARG);
			}


			//
			// Speak input text
			//
			ULONG streamNumber;
			HRESULT hr = m_tts->Speak(
				text,
				SPF_IS_NOT_XML | SPF_ASYNC | SPF_PURGEBEFORESPEAK,
				&streamNumber);
			if (FAILED(hr))
			{
				ATLTRACE(TEXT("Speak failed.\n"));
				AtlThrow(hr);
			}
		}


		//--------------------------------------------------------------------
		// Cleanup
		//--------------------------------------------------------------------
		~CTextSpeaker()
		{
			// Nothing to do here.
			// Automatic cleanup thanks to C++ RAII is fine :-)
		}



		//
		// Ban copy
		//
	private:
		CTextSpeaker(const CTextSpeaker &);
		CTextSpeaker & operator=(const CTextSpeaker &);



		//
		// IMPLEMENTATION
		//
	private:

		// COM initialization and cleanup (must precede other COM related data members)
		gds::CComAutoInit m_comInit;

		// Text to speech engine
		CComPtr<ISpVoice> m_tts;

		// Default voice token
		CComPtr<ISpObjectToken> m_voiceToken;
	};


} // namespace gds


#endif // GDS_TEXTSPEAKER_H_INCLUDED
