#!/usr/bin/env bash

# Setup
BUILD_PRESET="none"
GREEN="\e[1;32m"
RED="\e[1;31m"
NC="\e[0m"
WORKDIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
cd $WORKDIR

function print_box { # Print first argument in a nice box
  message=$1
  cleaned=$(echo $message | sed 's/\(\\e\|\x1b\)\[[0-9;]*[mGKF]//g')
  len=$(echo $cleaned | wc -c)

  printf '+='
  printf '=%.0s' $(seq 1 $len)
  printf '+\n'

  echo -e "| $message |"

  printf '+='
  printf '=%.0s' $(seq 1 $len)
  printf '+\n'
}

function show_help { # Print a help dialogue
  echo "Usage: linux-build.sh [OPTIONS] build-preset"
  echo "Options:"
  echo "  -h | --help: Show this help dialogue"
  echo
  echo "build-preset:"
  echo "  Entry in the CMakePresets.json file to use for generating build files."
  echo
}

# Print hello
print_box "${GREEN}CAM${NC} Build Script"

# Read user options
while test $# -gt 0; do
  case "$1" in
    -h|--help)
      shift
      show_help
      exit 0
      ;;
    *)
      BUILD_PRESET=$1
      shift
      ;;
  esac
done

# Check build preset
if [[ $BUILD_PRESET == "none" ]]; then
  read -p "Cmake build preset (Default: linux-default):" preset_var
  BUILD_PRESET=${preset_var:-linux-default}
fi
outdir=$(echo $BUILD_PRESET | sed 's/.*-//')

# Generate build files
echo -e "[${GREEN}*${NC}] Generating build files..."
cd ..
cmake --preset="$BUILD_PRESET" -S ./

# Build
if [ $? -ne 0 ]; then
  echo -e "[${RED}X${NC}] Build failed..."
  exit 1
fi
echo -e "[${GREEN}*${NC}] Building binary..."
mkdir -p ./out/build/$BUILD_PRESET/
cmake --build ./out/build/$BUILD_PRESET/

# Move binaries
if [ $? -ne 0 ]; then
  echo -e "[${RED}X${NC}] Build failed..."
  exit 1
fi
echo -e "[${GREEN}*${NC}] Moving binary..."
mkdir -p ./out/$BUILD_PRESET
mv ./out/build/$BUILD_PRESET/cam ./out/$BUILD_PRESET