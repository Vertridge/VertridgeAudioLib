#include "AudioLoader/WavLoader.h"

#include <cassert>

Loader::Wav::WavData Loader::Wav::LoadWav(const std::string &wav) {
  Loader::Wav::WavData wavData;

  int headerSize = sizeof(Loader::Wav::WavHeader);
  int fileLength = 0;

  FILE *wavFile = fopen(wav.c_str(), "r");

  std::size_t bytesRead = fread(&wavData.Header, 1, headerSize, wavFile);

  if (bytesRead > 0) {
    uint16_t bytesPerSample = wavData.Header.BitsPerSample / 8;
    uint64_t numSamples = wavData.Header.ChunkSize / bytesPerSample;

    wavData.Buffer = new uint8_t[wavData.Header.DataSize];
    static const uint16_t BUFFER_SIZE = 4096;
    uint8_t *buffer = new uint8_t[BUFFER_SIZE];
    std::size_t totalBytesRead = 0;
    while ((bytesRead = fread(buffer, sizeof buffer[0],
                              BUFFER_SIZE / (sizeof buffer[0]), wavFile)) > 0) {

      totalBytesRead += bytesRead;

      assert(totalBytesRead <= wavData.Header.DataSize &&
             "Read more bytes than the data size.");
      if (totalBytesRead > wavData.Header.DataSize) {
        std::cerr << "Read more bytes: " << totalBytesRead
                  << "than the data size: " << wavData.Header.DataSize << ".\n";
      }
    }
    delete[] buffer;
  }
  fclose(wavFile);
  return wavData;
}

void Loader::Wav::PrintWavHeader(const WavHeader &header) {
  // clang-format off
  std::cout << "RIFF: " << header.RIFF[0] << header.RIFF[1] << header.RIFF[2] << header.RIFF[3] << "\n"
            << "Chunk size: " << header.ChunkSize << "\n"
            << "WAVE: " << header.WAVE[0] << header.WAVE[1] << header.WAVE[2] << header.WAVE[3] << "\n"
            << "fmt: " << header.fmt[0] << header.fmt[1] << header.fmt[2] << header.fmt[3] << "\n"
            << "Data length: " << header.FmtSize << "\n"
            << "Format type: " << header.AudioFormat << "\n"
            << "Channels: " << header.Channels << "\n"
            << "Sample rate: " << header.SampleRate << "\n"
            << "Total size: " << header.BytesPerSec << "\n"
            << "Stereo type: " << header.BlockAlign << "\n"
            << "Bit per sample: " << header.BitsPerSample << "\n"
            << "Data header: " << header.DataMagic[0] << header.DataMagic[1] << header.DataMagic[2] << header.DataMagic[3] << "\n"
            << "Data size: " << header.DataSize << "\n";

  // clang-format on
}

void Loader::Wav::FreeWav(Loader::Wav::WavData &wav) {
  delete[] wav.Buffer;
  wav.Buffer = nullptr;
}
