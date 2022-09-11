#include <fstream>
#include <iostream>
#include <string>

namespace Loader::Wav {

struct WavHeader {
  // RIFF Header.
  char RIFF[4];       // RIFF Magic
  uint32_t ChunkSize; // Chunk size
  char WAVE[4];       // WAVE header
  // fmt sub-chunk
  char fmt[4];          // FMT header
  uint32_t FmtSize;     // FMT size
  uint16_t AudioFormat; // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM
                        // Mu-Law, 258=IBM A-Law, 259=ADPCM
  uint16_t Channels;    // Number of channels 1=Mono 2=Sterio
  uint32_t SampleRate; // Frequency: Sample Rate - 32 bit integer. Common values
                       // are 44100 (CD), 48000 (DAT). Sample Rate = Number of
                       // Samples per second, or Hertz.
  uint32_t BytesPerSec; // (Sample Rate * BitsPerSample * Channels) / 8
  uint16_t BlockAlign;  // 2=16-bit mono, 4=16-bit stereo

  uint16_t BitsPerSample; // Number of bits per sample
  // Data sub-chunk
  char DataMagic[4]; // "data" string
  int32_t DataSize;  // Sampled data length
};

struct WavData {
  WavHeader Header;
  uint8_t *Buffer = nullptr;
};

WavData LoadWav(const std::string &wav);

void PrintWavHeader(const WavHeader &header);

void FreeWav(WavData &wav);

} // namespace Loader::Wav
