set -e

cwd="$PWD"
linuxver="6.1"

if ! type -p curl &>/dev/null; then
  echo "Install curl."
  exit 1
fi
if ! type -p bsdtar &>/dev/null; then
  echo "Install libarchive."
  exit 1
fi
if ! type -p rsync &>/dev/null; then
  echo "Install rsync."
  exit 1
fi

rm -rf \
  linux-* \
  include/*-linux-ouma*/asm \
  include/asm-generic \
  include/linux \
  include/misc \
  include/mtd \
  include/rdma \
  include/scsi \
  include/sound \
  include/video \
  include/xen
curl -C - -L -O \
  https://cdn.kernel.org/pub/linux/kernel/v6.x/linux-$linuxver.tar.xz
bsdtar -xvf linux-$linuxver.tar.xz
for arch in arm64 x86_64; do
  case $arch in
    arm64)
      karch="arm64"
      target="aarch64-linux-ouma"
      ;;
    x86_64)
      karch="x86_64"
      target="x86_64-linux-ouma"
      ;;
    *)
      echo "Unsupported platform."
      exit 1
      ;;
  esac
  cd "$cwd/linux-$linuxver"
  make -j$(nproc) mrproper
  make -j$(nproc) ARCH="$karch" INSTALL_HDR_PATH="$cwd" headers_install
  cd "$cwd/include"
  install -m755 -d "$target"
  mv asm $target
  rm -rf drm
done
find "$cwd/include" -type f ! -name '*.h' -delete

cd "$cwd"
rm -rf linux-*

exit 0

