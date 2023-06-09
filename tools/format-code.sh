if [ -z "$1" ]; then
  exit 1
fi

find "$PWD/include" -type f -name "*.h" -exec clang-format -style=file -i {} +
cargo fmt --all

exit 0

