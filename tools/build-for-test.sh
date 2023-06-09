set -e

TARGET="$1"
if [ -z "$TARGET" ]; then
  exit 1
fi

BUILD_CFLAGS="-std=c++20"
BUILD_LDFLAGS=""
BUILD_RUSTFLAGS=""

# TODO: add instrumented libc++ and gtest for MSan

for sanitizers in none address leak; do
  echo "Building libc with $sanitizers sanitizer"
  rm -rf a.out target

  case $sanitizers in
    none)
      SANITIZER_CFLAGS=""
      SANITIZER_RUSTFLAGS=""
      ;;
    address)
      SANITIZER_CFLAGS="-fsanitize=address"
      SANITIZER_RUSTFLAGS="-Zsanitizer=address"
      ;;
    memory)
      SANITIZER_CFLAGS="-fsanitize=memory"
      SANITIZER_RUSTFLAGS="-Zsanitizer=memory"
      ;;
    leak)
      SANITIZER_CFLAGS="-fsanitize=leak"
      SANITIZER_RUSTFLAGS="-Zsanitizer=leak"
      ;;
  esac

  RUSTFLAGS="$BUILD_RUSTFLAGS $SANITIZER_RUSTFLAGS" \
  cargo build --target $TARGET
  for test in ctype string uchar wchar wctype; do
    echo "Testing: $test"
    clang++ $BUILD_CFLAGS $SANITIZER_CFLAGS $BUILD_LDFLAGS \
      -lgtest -lgtest_main src/tests/${test}.cc \
      "$PWD/target/$TARGET/debug/libc.a"
    ./a.out
  done
done

exit 0

