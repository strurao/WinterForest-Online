#include "pch.h"
#include "Sound.h"
#include "SoundManager.h"

Sound::Sound()
{

}

Sound::~Sound()
{
	if (_soundBuffer)
		_soundBuffer->Release();
}

bool Sound::LoadWave(fs::path fullPath)
{
	if (fullPath.extension() != L".wav")
		return false;

	HMMIO file = ::mmioOpen((WCHAR*)fullPath.c_str(), NULL, MMIO_READ);
	if (file == 0)
	{
		::MessageBox(NULL, L"사운드 파일 없음", L"", MB_OK);
		return false;
	}

	MMCKINFO parent;
	::memset(&parent, 0, sizeof(parent));
	parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	::mmioDescend(file, &parent, NULL, MMIO_FINDRIFF);

	MMCKINFO child;
	::memset(&child, 0, sizeof(child));
	child.ckid = mmioFOURCC('f', 'm', 't', ' ');
	::mmioDescend(file, &child, &parent, MMIO_FINDCHUNK);

	WAVEFORMATEX wft;
	::memset(&wft, 0, sizeof(wft));
	::mmioRead(file, (char*)&wft, sizeof(wft));

	::mmioAscend(file, &child, 0);
	child.ckid = mmioFOURCC('d', 'a', 't', 'a');
	::mmioDescend(file, &child, &parent, MMIO_FINDCHUNK);

	::memset(&_bufferDesc, 0, sizeof(DSBUFFERDESC));
	_bufferDesc.dwBufferBytes = child.cksize;
	_bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	_bufferDesc.dwFlags = DSBCAPS_STATIC;
	_bufferDesc.lpwfxFormat = &wft;

	if (FAILED(GET_SINGLE(SoundManager)->GetSoundDevice()->CreateSoundBuffer(&_bufferDesc, &_soundBuffer, NULL)))
	{
		::MessageBox(NULL, L"사운드 버퍼 생성 실패", L"", MB_OK);
		return false;
	}

	void* write1 = NULL;
	void* write2 = NULL;
	DWORD len1;
	DWORD len2;

	_soundBuffer->Lock(0, child.cksize, &write1, &len1, &write2, &len2, 0);

	if (write1)
		::mmioRead(file, (char*)write1, len1);

	if (write2)
		::mmioRead(file, (char*)write2, len2);

	_soundBuffer->Unlock(write1, len1, write2, len2);

	::mmioClose(file, 0);
	return true;
}

void Sound::Play(bool loop)
{
	_soundBuffer->SetCurrentPosition(0);

	if (loop)
		_soundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else
		_soundBuffer->Play(0, 0, 0);
}

void Sound::Stop(bool reset)
{
	_soundBuffer->Stop();

	if (reset)
		_soundBuffer->SetCurrentPosition(0);
}