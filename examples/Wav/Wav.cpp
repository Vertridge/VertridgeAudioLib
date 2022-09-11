#include <iostream>

#include "AudioLoader/WavLoader.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "Pass file to open.\n";
    exit(0);
  }
  std::cout << "Starting Wav Loader: " << argv[1] << "\n";
  auto wav = Loader::Wav::LoadWav(argv[1]);
  Loader::Wav::PrintWavHeader(wav.Header);
  Loader::Wav::FreeWav(wav);
}
