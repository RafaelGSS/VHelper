#ifndef GDS_TEXTSPEAKER_H_INCLUDED
#define GDS_TEXTSPEAKER_H_INCLUDED

#pragma warning(disable: 4996)

#include <sapi.h>               // SAPI
#include <sphelper.h>           // SAPI Helper

#include <src/utils/spdlog/spdlog.h>

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
			//hr = SetVoice(L"Microsoft Maria Desktop - Portuguese(Brazil)");
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
		void speak(const LPCWSTR & text)
		{
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
				spdlog::error("Speak failed.");
			}
		}

		void pause()
		{
			m_tts->Pause();
		}

		void resume()
		{
			m_tts->Resume();
		}


		//--------------------------------------------------------------------
		// Cleanup
		//--------------------------------------------------------------------
		~CTextSpeaker()
		{
			// Nothing to do here.
			// Automatic cleanup thanks to C++ RAII is fine :-)
		}

		//--------------------------------------------------------------------
		// Set Voice installed on regedit
		//--------------------------------------------------------------------
		HRESULT SetVoice(std::wstring _voiceName)
		{
			IEnumSpObjectTokens *pProfileEnum;
			SpEnumTokens(SPCAT_VOICES, NULL, NULL, &pProfileEnum);

			unsigned long voices;
			pProfileEnum->GetCount(&voices);

			for (unsigned long i = 0; i < voices; ++i) {
				CComPtr<ISpObjectToken> IT;
				pProfileEnum->Item(i, &IT);
				CSpDynamicString dstrDefaultName;
				SpGetDescription(IT, &dstrDefaultName);

				if (wcsncmp(dstrDefaultName, _voiceName.c_str(), _voiceName.size()) == 0) {
					return m_tts->SetVoice(IT);
				}
			}
			return E_INVALIDARG;
		}


		//
		// Ban copy
		//
	private:
		CTextSpeaker(const CTextSpeaker &);
		CTextSpeaker & operator=(const CTextSpeaker &);

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
